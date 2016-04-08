//Name: Reshal Luchman
//Student number: 213501051
//ENEL4SE - Security and Encryption
//DES Cipher
//Filename: DEScipher.cpp

#include "DEScipher.h"
#include "iostream"
#include "string"

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

