//Name: Reshal Luchman
//Student number: 213501051
//ENEL4SE - Security and Encryption
//DES Cipher
//Filename: DEScipher.cpp

#include "DEScipher.h"
#include "iostream"
#include "string"
#include "cctype"
#include "bitset"

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

int keySchedule::getasciiInt(int i)
{
	return asciiInt[i];
}

bitset<8> keySchedule::getasccitoBin(int i)
{
	return asciitoBin[i];
}

bitset<7> keySchedule::getremovePar(int i)
{
	return removePar[i];
}

//Mutator
void keySchedule::setkeyInput(string key)
{
	keyinput = key;
}

void keySchedule::setasciiInt(int pos, int val)
{
	asciiInt[pos] = val;
}

void keySchedule::setasciitoBin(int pos, int val)
{
	asciiInt[pos] = val;
}

void keySchedule::setremovePar(int pos, int val)
{
	removePar[pos] = val;
}

void keySchedule::inputKeyword()
{

	int binasciiInt[8][8]; //2D array to store 64 bit ascii codes

	for (int i = 0; i < keyinput.length(); i++) //Remove spaces
	{
		if (keyinput[i] == ' ')
			keyinput.erase(i, 1);
	}

	for (int i = 0; i < keyinput.length(); i++)		//Converts each character to upper case
		keyinput[i] = static_cast<char>(toupper(keyinput[i]));	

	if (keyinput.length() < 8)	//if length of keyword is less than 8 insert filler characters.
	{

		char filler; //default filler character
		int testfillq = 0; //test if filler character exists in message, if it does (testfill = 1) use next character
		int testfillx = 0;
		int testfillz = 0;

		int len; //subtract 8 from keyword
		string fillerarr;

		//Find appropriate filler character
		for (int i = 0; i < keyinput.length(); i++)
		{

			if (keyinput[i] == 'Q')
				testfillq = 1;
			if (keyinput[i] == 'X')
				testfillx = 1;
			if (keyinput[i] == 'Z')
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

		cout << "Key length is less than 8 using filler characters as well." << endl;
		//cout << "Key length: " << keyinput.length() << endl;

		len = 8 - keyinput.length();
		
		for (int i = 0; i < len; i++)	//create string of filler characters to append to keyinput
			fillerarr += filler;		//to make length of 8 characters.
		keyinput.append(fillerarr);

		//	cout << "New Key length: " << keyinput.length() << endl;
		//  cout << "Final Key: " << endl;
		cout << keyinput << endl;

		stringtoASCII(keyinput);
	}

	else if (keyinput.length() > 7)	//else if it is greater than 8 trim to length of 8 characters.
	{

		cout << "Taking the first 8 charcters. " << endl;
		//cout << "Key length: " << keyinput.length() << endl;
		cout << "Key entered: " << keyinput << endl;

		keyinput = keyinput.substr(0, 8);
		cout << "Updated key: " << keyinput << endl;

		stringtoASCII(keyinput);
	}


}

void keySchedule::stringtoASCII(string keyinput)
{

	cout << "\nEquivalent ASCII integer: " << endl;
	for (int i = 0; i < keyinput.length(); i++)
		asciiInt[i] = int(keyinput[i]);

	for (int i = 0; i < 8; i++)
		cout << asciiInt[i] << " ";
}

void keySchedule::asciitoBIN()
{
	for (int i = 0; i < 8; i++)
	{
		asciitoBin[i] = asciiInt[i];
	}
}

void keySchedule::removeParity()
{
	

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			removePar[i][j] = asciitoBin[i][j];
		}
		
	}

	for (int i = 0; i < 8; i++)
	{
		cout << removePar[i] << endl;
	}

}