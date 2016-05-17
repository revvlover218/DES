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
	string P;
	int count = 0;

	//Get message
	cout << "Enter message to be encrypted: " << endl;
	getline(cin, P);
	enc.setMessage(P);

	enc.prepMessage();
	cout << "Message" << endl;
	cout << enc.getMessage();

	/*//Key generation
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
	*/

	cout << endl;
	system("pause");
	return 0;
}