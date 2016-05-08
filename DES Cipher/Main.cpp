//Name: Reshal Luchman
//Student number: 213501051
//ENEL4SE - Security and Encryption
//DES Cipher
//Filename: Main.cpp

#include "iostream"
#include "string"
#include "DEScipher.h"

using namespace std;

int main()
{

	DES enc;
	keySchedule ks;

	string keyinput;
	cout << "Enter 8 - character keyword to be used: " << endl;
	getline(cin, keyinput);

	ks.setkeyInput(keyinput);
	ks.inputKeyword();




	cout << endl;
	system("pause");
	return 0;
}