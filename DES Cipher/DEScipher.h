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
	int keyround = 16;
	int arr[8];
	int asciitobin[8*8];

public:

	DES();
	~DES();

	string getMessage();
	void setMessage(string);

	//Encryption
	void prepMessage();
	void stringtoASCII();
	int asciitoBIN(int);

	//Decryption

};
#endif