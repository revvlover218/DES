//Name: Reshal Luchman
//Student number: 213501051
//ENEL4SE - Security and Encryption
//DES Cipher
//Filename: DEScipher.h

#ifndef DESCIPHER_H
#define DESCIPHER_H
#include "string"
#include "bitset"
#include "vector"
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
 bitset<8> asciitoBin[8]; //store binary version of ascii code
 int asciitoBinary_64[64]; 

 //PC-1 table
 //int PC1[56] = { 57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4 };

 int initialKey[16][56]; //Stores the result of PC1 and after bits have been shifted.



public:
	//Accessor and Mutator functions
	//Accessor

	string getkeyInput();
	int getasciiInt(int);
	bitset<8> getasccitoBin(int);
	
	//Mutator
	void setkeyInput(string);
	void setasciiInt(int, int);
	void setasciitoBin(int, int);


	void inputKeyword();
	void stringtoASCII(string);
	void asciitoBIN();
	void applyPC1();

};




#endif