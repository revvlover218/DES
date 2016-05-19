//Name: Reshal Luchman
//Student number: 213501051
//ENEL4SE - Security and Encryption
//DES Cipher
//Filename: Main.cpp

#include "iostream"
#include "string"
#include "DEScipher.h"
#include "bitset"

using namespace std;

int main()
{

	DES enc;
	keySchedule ks;

	string keyinput;
	string P;
	int count = 0;

	cout << "ENEL4SE - Security and Encryption." << endl;
	cout << "DES Cipher" << endl;
	cout << "Reshal Luchman" << endl;
	cout << "213501051" << endl;

	system("pause");
	system("cls");
	
	//Key generation
	cout << "Enter 8 - character keyword to be used: " << endl;
	getline(cin, keyinput);

	ks.setkeyInput(keyinput); 
	ks.inputKeyword();		//Verify keyword entered and convert to ascii code.

	cout << endl;	
	ks.asciitoBIN(); //convert ascii code to binary code which is stored in an intial key
	cout << endl;
	ks.applyPC1(); //Apply PC1 table to that initial key
	cout << endl;
	ks.applyRotation();
	cout << endl;
	ks.applyPC2();

	//Create a copy of the final key from the keySchedule class to be used in encryption in the DES clas
	for (int i = 0; i < 16; i++)
	{

		for (int j = 0; j < 48; j++)
			enc.setEncKey(i, j, ks.getFinalKey(i, j));
	}

	system("pause");
	system("cls");
	
	//Get message
	cout << "Enter message to be encrypted: " << endl;
	getline(cin, P);

	enc.setMessage(P);
	enc.prepMessage();
	enc.applyIP();
		
	enc.encrypt();

	cout << endl;
	system("pause");
	return 0;
}