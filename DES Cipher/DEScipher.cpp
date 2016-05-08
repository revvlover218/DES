//Name: Reshal Luchman
//Student number: 213501051
//ENEL4SE - Security and Encryption
//DES Cipher
//Filename: DEScipher.cpp

#include "DEScipher.h"
#include "iostream"
#include "string"
#include "cctype"

using namespace std;

DES::DES(){}

DES::~DES(){}

string DES::getMessage()
{
	return message;
}

void DES::setMessage(string m)
{
	message = m;
}

void DES::prepMessage()
{

	string mes = message; 
	char filler; //default filler character
	int testfillq = 0; //test if filler character exists in message, if it does 
	int testfillx = 0; //(testfill = 1) use next character (Q, X, Z)
	int testfillz = 0;

	

	if (message.length() % 2 == 1)
	{

		//Check for filler character
	    for (int i = 0; i < message.length(); i++)
		{

			if (message[i] == 'q')
				testfillq = 1;
			if (message[i] == 'x')
				testfillx = 1;
			if (message[i] == 'z')
				testfillz = 1;
		}

		if (testfillx == 0)
			filler = 'x';
		else if (testfillz == 0)
			filler = 'z';
		else if (testfillq == 0)
			filler = 'q';

				//Since encryption requires the characters of 
										//the message to be in pairs, it means that 
			mes += filler;			//the length of the string must be even. Therefore, if there is an odd number of 
									//characters in the string insert an 'X' to make the length of the string even.
		


	}

	for (int i = 0; i < mes.length(); i++)
		mes[i] = static_cast<char>(toupper(mes[i]));	//Converts each character to upper case

	message = mes;

}

////////////////////////////Key Schdeule//////////////////////////////////////
//Accesoor and Mutator
//Accessor
string keySchedule::getkeyInput()
{
	return keyinput;
}

//Mutator
void keySchedule::setkeyInput(string key)
{
	keyinput = key;
}


void keySchedule::inputKeyword(string tempkey)
{


	int binkeyArr[8][8]; //2D array to store 64 bit ascii codes

	//Remove spaces
	for (int i = 0; i < tempkey.length(); i++)
	{
		if (tempkey[i] == ' ')
			tempkey.erase(i, 1);
	}

	for (int i = 0; i < tempkey.length(); i++)
		tempkey[i] = static_cast<char>(toupper(tempkey[i]));	//Converts each character to upper case

	if (tempkey.length() < 8)	//if length of keyword is less than 8 insert filler characters.
	{

		char filler; //default filler character
		int testfillq = 0; //test if filler character exists in message, if it does (testfill = 1) use next character (Q, X, Z)
		int testfillx = 0;
		int testfillz = 0;
		int len; //subtract 8 from keyword
		string fillerarr;

		//Find appropriate filler character
		for (int i = 0; i < tempkey.length(); i++)
		{

			if (tempkey[i] == 'Q')
				testfillq = 1;
			if (tempkey[i] == 'X')
				testfillx = 1;
			if (tempkey[i] == 'Z')
				testfillz = 1;
		}

		if (testfillx == 0)
			filler = 'X';
		else if (testfillz == 0)
			filler = 'Z';
		else if (testfillq == 0)
			filler = 'Q';
		else
			filler = 'X';

		//cout << "Key length is less than 8 using filler characters as well." << endl;
		//cout << "Key length: " << tempkey.length() << endl;

		len = 8 - tempkey.length();
		for (int i = 0; i < len; i++)	//create string of filler characters to make length of 8 characters for key
			fillerarr += filler;
		tempkey.append(fillerarr);

		//	cout << "New Key length: " << tempkey.length() << endl;
		//  cout << "Final Key: " << endl;
		cout << tempkey << endl;

		stringtoASCII(tempkey);
	}

	else if (tempkey.length() > 7)	//else if it is greater than 8 trim to length of 8 characters.
	{

		//cout << "Key entered is longer than  characters taking the first 8 charcters instead. " << endl;
		//cout << "Key length: " << tempkey.length() << endl;
		cout << "Key entered: " << tempkey << endl;

		tempkey = tempkey.substr(0, 8);
		cout << "Updated key: " << tempkey << endl;

		stringtoASCII(tempkey);

	}

}

void keySchedule::stringtoASCII(string tempkey)
{

	int keyArr[8];
	//	cout << "Convert to equivalent ASCII integer: " << endl;
	for (int i = 0; i < tempkey.length(); i++)
		keyArr[i] = int(tempkey[i]);

	for (int i = 0; i < 8; i++)
		cout << keyArr[i] << " ";

}

int keySchedule::asciitoBIN(int n)
{

	if (n == 0)
		return n;
	else return (n % 2) + (10 * asciitoBIN(n / 2));
}
