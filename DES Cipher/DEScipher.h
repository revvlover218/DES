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

public:

	DES();
	~DES();

	string getMessage();
	void setMessage(string);


};

#endif