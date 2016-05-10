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
	int count = 0;



	cout << "Enter 8 - character keyword to be used: " << endl;
	getline(cin, keyinput);

	ks.setkeyInput(keyinput); 
	ks.inputKeyword();

	cout << endl;
	cout << "Binary representation of ASCII code: " << endl;
	ks.asciitoBIN();
	for (int i = 0; i < 8; i++)
	{
		cout << ks.getasccitoBin(i) << endl;
		count++;
	}
		
	cout << "Total number of bits: " << ks.getasccitoBin(0).size()*count << endl;
	
	cout << "Binary codes after removing parity bits: " << endl;
	ks.removeParity();
	cout << "Total number of bits: " << ks.getremovePar(0).size()*count << endl;



	cout << endl;
	system("pause");
	return 0;
}