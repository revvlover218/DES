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


void DES::stringtoASCII()
{

	for (int i = 0; i < message.length(); i++)
		arr[i] = (int)message[i];

	for (int i = 0; i < 8; i++)
		cout << arr[i] << "\t";
}

int DES::asciitoBIN(int n)
{

	if (n == 0)
		return n;
	else return (n % 2) + (10 * asciitoBIN(n / 2));
}
