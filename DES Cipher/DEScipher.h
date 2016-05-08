//Name: Reshal Luchman
//Student number: 213501051
//ENEL4SE - Security and Encryption
//DES Cipher
//Filename: DEScipher.h

#ifndef DESCIPHER_H
#define DESCIPHER_H
#include "string"

using namespace std;

class DES
{

private:
	string message;	//message to be encrypted

	int arr[8];
	int asciitobin[8*8];

public:

	DES();
	~DES();

	string getMessage();
	void setMessage(string);

	//Encryption
	void prepMessage();
	

	//Decryption

};

class keySchedule
{

private:
 const int keyround = 16;
 string keyinput;
 int keyArr[8];


public:
	//Accessor and Mutator functions
	//Accessor

	string getkeyInput();
	int getkeyArr(int);
	//Mutator
	void setkeyInput(string);
	void setkeyArr(int, int);



	void inputKeyword();
	void stringtoASCIItoBin(string);
	int asciitoBIN(int);

};




#endif