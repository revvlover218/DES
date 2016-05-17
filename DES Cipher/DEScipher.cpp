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

/////////////////////////////////Class DES///////////////////////////////////////
//Constructor
DES::DES(){}
//Destructor
DES::~DES(){}

///Accessor
string DES::getMessage()
{
	return message;
}

//Mutator
void DES::setMessage(string m)
{
	message = m;
}

void DES::prepMessage()
{

	for (int i = 0; i < message.length(); i++) //Remove spaces
	{
		if (message[i] == ' ')
			message.erase(i, 1);
	}

	for (int i = 0; i < message.length(); i++)		//Converts each character to upper case
		message[i] = static_cast<char>(toupper(message[i]));







/*	string mes = message; 
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

	message = mes;*/

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

		stringtoASCII(keyinput); //convert string to ascii integers
	}

	else if (keyinput.length() > 7)	//else if it is greater than 8 trim to length of 8 characters.
	{

		cout << "Taking the first 8 charcters. " << endl;
		//cout << "Key length: " << keyinput.length() << endl;
		cout << "Key entered: " << keyinput << endl;

		keyinput = keyinput.substr(0, 8);
		cout << "Updated key: " << keyinput << endl;

		stringtoASCII(keyinput); //convert string to ascii integers
	}
}

void keySchedule::stringtoASCII(string keyinput)
{

	cout << "\nEquivalent ASCII integer: " << endl;
	for (int i = 0; i < keyinput.length(); i++)		//Type cast string to integer
		asciiInt[i] = int(keyinput[i]);

	for (int i = 0; i < 8; i++)
		cout << asciiInt[i] << " ";
}

void keySchedule::asciitoBIN()
{

	//Store ascii numbers in binary data type which automatically converts integers to binary
	for (int i = 0; i < 8; i++)
	{
		asciitoBin[i] = asciiInt[i];
	}

	//Store binary numbers into integer array so that PC1 can be applied to it
	int k = 0;

	for (int i = 0; i < 8; i++)
	{

		for (int j = 0; j < 8; j++)
		{
			asciitoBinary_64[k] =  asciitoBin[i][j];
			k++;
		}
	}

	//Display ascii code in binary.
	cout << "Binary representation of ASCII code: " << endl;
	int i = 1;

	while (i <= 64)
	{

		cout << asciitoBinary_64[i-1];

		if (i % 8 == 0)
			cout << endl;

		i++;
	}

	system("pause");
}

void keySchedule::applyPC1()
{

	system("cls");

	//PC- 1 table
	int PC1[56] = { 57, 49, 41, 33, 25, 17, 9,
		1, 58, 50, 42, 34, 26, 18,
		10, 2, 59, 51, 43, 35, 27,
		19, 11, 3, 60, 52, 44, 36,
		63, 55, 47, 39, 31, 23, 15,
		7, 62, 54, 46, 38, 30, 22,
		14, 6, 61, 53, 45, 37, 29,
		21, 13, 5, 28, 20, 12, 4 };

	cout << "Applying PC- 1 table to 64- bits to get 56- bits." << endl;
 
	for (int i = 0; i < 56; i++)
	{
		initialKey[0][i] = asciitoBinary_64[PC1[i] - 1];	
	}

	//Display key after PC- 1
	int k = 1;
	while (k <= 56)
	{

		cout << initialKey[0][k-1];

		if (k % 7 == 0)
			cout << endl;
		k++;
	}

	system("pause");
}

void keySchedule::applyRotation()
{

	system("cls");
	
	cout << "Applying rotation (left shift) to get 16 keys for the 16 rounds." << endl;

	for (int k = 1; k <= 16; k++)			//For 16 rounds.
	{

		for (int i = 0; i < 28; i++)		//Store each half of 56- bit key in C & D each of length 28.
		{

			Cn[i] = initialKey[k - 1][i];			//Cn = Kn_0 (store first half of 56- bits).
			Dn[i] = initialKey[k - 1][i + 28];		//Dn = Kn_28 (store second half of 56- bits).
		}

		if (k == 1 || k == 2 || k == 9 || k == 16)	//Key rounds: 1, 2, 9, and 16 are rotated only once. 
		{

			CnR[0] = Cn[27];		//Left shift the lsb and wrap around the end of C to the beginning.
			DnR[0] = Dn[27];		//Left shift the lsb and wrap around the end of D to the beginning.

			for (int i = 1; i < 28; i++)		//Shift rest of binary numbers in each half i.e. in C & D.
			{

				CnR[i] = Cn[i - 1];			
				DnR[i] = Dn[i - 1];			
			}
		}

		else
		{
									//For the rest of the rounds:
			CnR[0] = Cn[26];		//Left shift twice and wrap around the end of C to the beginning.
			CnR[1] = Cn[27];			

			DnR[0] = Dn[26];		//Left shift twice and wrap around the end of D to the beginning.
			DnR[1] = Dn[27];

			for (int i = 2; i < 28; i++)	//Shift rest of binary numbers in each half i.e. in C & D.
			{

				CnR[i] = Cn[i - 2];			
				DnR[i] = Dn[i - 2];
			}
		}

		for (int i = 0; i < 28; i++)		//Store the result back in the initialKey		
		{

			initialKey[k][i] = CnR[i];
			initialKey[k][i + 28] = DnR[i];
		}
	}

	//Display all keys generated.
	for (int i = 1; i <= 16; i++)
	{

		int k = 1;
		cout << "Key Round: " << i << endl;

		while (k <= 56)
		{

			cout << initialKey[i][k - 1];

			if (k % 7 == 0)
				cout << endl;
			k++;
		}
	}

	system("pause");
}

void keySchedule::applyPC2()
{

	system("cls");
	
	cout << "Applying PC- 2 table to 56- bits to get 48- bits." << endl;

	//PC- 2 table.
	int PC2[48] = { 14, 17, 11, 24, 1, 5, 3, 28,
		15, 6, 21, 10, 23, 19, 12, 4,
		26, 8, 16, 7, 27, 20, 13, 2,
		41, 54, 31, 37, 47, 55, 30, 40,
		51, 45, 33, 48, 44, 49, 39, 56,
		34, 53, 46, 42, 50, 36, 29, 32 };

	for (int i = 0; i<16; i++)
	{
		for (int j = 0; j<48; j++)
		{
			finalKey[i][j] = initialKey[i + 1][PC2[j] - 1];
		}
	}
	
	//Display keys after PC2 has been applied
	for (int i = 0; i < 16; i++)
	{

		int k = 1;
		cout << "\nFinal Key Round: " << i + 1 << endl;

		while (k <= 48)
		{

			cout << finalKey[i][k - 1];

			if (k % 6 == 0)
				cout << "\t";
			k++;
		}
	}
}