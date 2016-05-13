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


 int initialKey[17][56];	//Stores the result of PC1 (64- bit -> 56- bit).

 int Cn[28];			//initialKey[n] = Kn = Cn*Dn where Cn is the first 28- bits (0 - 27) and Dn is the 
 int Dn[28];			//second 28- bits (28 - 55).
 int CnR[28];			//Result of Cn and Dn after rotation.
 int DnR[28]; 

 int finalKey[16][48]; 


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
	void applyRotation(); //When applying rotations key rounds: 1, 2, 9, and 16 are rotated only once, while each other 
						  //round is rotated twice. 
	void applyPC2();

};




#endif