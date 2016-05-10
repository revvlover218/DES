//Name: Reshal Luchman
//Student number: 213501051
//ENEL4SE - Security and Encryption
//DES Cipher
//Filename: DEScipher.h

#ifndef DESCIPHER_H
#define DESCIPHER_H
#include "string"
#include "bitset"

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
 int asciiInt[8];
 bitset<8> asciitoBin[8];
 bitset<7> removePar[8];


public:
	//Accessor and Mutator functions
	//Accessor

	string getkeyInput();
	int getasciiInt(int);
	bitset<8> getasccitoBin(int);
	bitset<7> getremovePar(int);
	//Mutator
	void setkeyInput(string);
	void setasciiInt(int, int);
	void setasciitoBin(int, int);
	void setremovePar(int, int);

	void inputKeyword();
	void stringtoASCII(string);
	void asciitoBIN();
	void removeParity();		//Remove parity bits after ascii code has been cinverted to binary

};




#endif