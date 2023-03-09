#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <stdexcept>

using namespace std;

class Time {
private:
	unsigned day;
	unsigned month;
	unsigned year;

	time_t now = time(0);
	tm* ltm = localtime(&now);

	unsigned yearNow = 1900 + ltm->tm_year;
	unsigned monthNow = 1 + ltm->tm_mon;
	unsigned dayNow = ltm->tm_mday;

public:
	Time(){
		day = dayNow;
		month = monthNow;
		year = yearNow;
	}

	Time(unsigned _day, unsigned _month, unsigned _year) {
		day = _day;
		month = _month;
		year = _year;
	}

	unsigned getDay() { return this->day; }
	unsigned getMonth() { return this->month; }
	unsigned getYear() { return this->year; }

	string getFullTime() {
		string _day = to_string(day);
		if (_day.length() < 2) _day = "0" + _day;

		string _month = to_string(month);
		if (_month.length() < 2) _month = "0" + _month;

		string _year = to_string(year);

		return _day + "." + _month + "." + _year;
	}
};

class CNP {
private:
	string cnpNr;

public:
	CNP() {
		cnpNr = "";
	}

	CNP(string _cnpNr) {
		cnpNr = _cnpNr;
		
		// Exceptions:
		
		// if CNP length is not 13 
		if (cnpNr.length() != 13) 
			throw length_error("Length of CNP should be only 13 characters. Your length is: " + to_string(cnpNr.length()));

		// exception for first number from CNP
		if (stoi(cnpNr.substr(0, 1)) < 1 || stoi(cnpNr.substr(0, 1)) > 6)
			throw invalid_argument("First number of CNP should be form 1 to 6. Your number is: " + cnpNr.substr(0,1));

		// if CNP do not consist from only number
		if (to_string(stoll(cnpNr)).length() != 13)
			throw invalid_argument("CNP should consists only from numbers.");

		// if is born in future
		if (CNP::getAge() < 0)
			throw invalid_argument("Birth time should be older than current time. Your birth time is: " + CNP::getBirthDay());
	}

	string getCnp() { return this->cnpNr; }
	
	char getSex() {
		// takes first character of CNP
		int firstNum = stoi(cnpNr.substr(0,1));

		if (firstNum % 2 == 0) return 'F';
		else return 'M';
	}

	unsigned getDay() {	return stoi(this->cnpNr.substr(5, 2)); }

	unsigned getMonth() { return stoi(this->cnpNr.substr(3, 2)); }

	unsigned getYear() {
		string _year;

		switch (cnpNr[0]) {
		case'1':
		case'2':
			_year = "19";
			break;
		case'3':
		case'4':
			_year = "18";
			break;
		case'5':
		case'6':
			_year = "20";
			break;
		}

		_year += cnpNr.substr(1, 2);

		return stoi(_year);
	}

	string getBirthDay() {
		Time birth(CNP::getDay(), CNP::getMonth(), CNP::getYear());

		return birth.getFullTime();
	}

	int getAge() {
		Time timeNow;
		Time timeBirth(CNP::getDay(), CNP::getMonth(), CNP::getYear());

		int age = timeNow.getYear() - timeBirth.getYear();

		if (timeNow.getMonth() < timeBirth.getMonth()) {
			return --age;
		}

		if (timeNow.getMonth() == timeBirth.getMonth() && timeNow.getDay() < timeBirth.getDay()) {
			return --age;
		}
			
		
		return age;
	}
};


int main()
{
	try {
		CNP myCnp("5030430495863");

		cout << "My sex: " << myCnp.getSex() << endl;

		cout << "My birth day time is: " << myCnp.getBirthDay() << endl;

		cout << "My birth month is: " << myCnp.getMonth() << endl;

		cout << "My birth year is: " << myCnp.getYear() << endl;

		cout << "My age is: " << myCnp.getAge() << endl;
	}
	catch (invalid_argument& error) {
		cerr << "Error: " << error.what() << endl;

		return 0;
	}
	catch (length_error& error) {
		cerr << "Error: " << error.what() << endl;

		return 0;
	}

	



	


}

//strlen() -> calculeaza lungimea sirului de caractere
//strcpy() -> copiaza un sir de caractere in altul
//strcat() -> concateneaza doua siruri de caractere
//strcmp() -> compara doua siruri de caractere si returneaza o valoare negativa, zero sau pozitiva, in functie de ordinea lor lexicografica
//strchr() -> cauta prima aparitie a unui caracter intr-un sir de caractere
//strstr() -> cauta prima aparitie a unui sir de caractere in altul
//isalpha() -> verigica daca un caracter este o litera
//isdigid() -> verifica daca un caracter este o cifra
//toupper() -> converteste un caracter in majuscula
//tolower() -> converteste un caracter in minuscula