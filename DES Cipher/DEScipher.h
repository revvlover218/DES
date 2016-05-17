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
	vector<int> ascii;	//vector to hold each chracters converted to ascii.
	vector<bitset<8>> PasciitoBin; //Plaintext in binary, each element in the vector is 8 bits long.
	int PasciitoBinary_64_init[100][64]; 
	int block = 0;
	int PasciitoBinary_64_final[100][64];
	int L0[100][32];
	int R0[100][32];

public:

	DES();
	~DES();

	string getMessage();
	void setMessage(string);

	//Encryption
	void prepMessage();
	void messagetoAscii();
	void amestoBIN();		//Ascii converted plaintext to binary
	void applyIP();


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

	//Key Schedule methods
	void inputKeyword();	//The following method provides a keyword verification. Once a key has been entered by the user,
							//the purpose of this function is to set the keyword to a length 8 characters, so that
							//a 64- bit binary key can be generated. Any spaces entered in the keyword is first removed.
							//Thereafter, check the length of the keyword. If the length of the keyword is less than 8 chars
							//use filler characters to make the keyword of length 8, else if the keyword is more than 8
							//characters long, take the first 8 characters only. To keep consistency all characters
							//are converted to upper case. Once the key has been set to the DES standard, the stringtoASCII
							//and asciitoBIN functions are called to do the relevant conversions.

	void stringtoASCII(string);	//Takes in as input the keyword after verification and converts each character to its 
								//equivalent ascii integer code (type casting).
	void asciitoBIN();			//Once all characters have been converted to ascii, this function converts each integer
								//to binary. The result is stored in a bitset data type. This function essentially type casts
								//an integer to an N- bit binary number (defined by user = 8). After conversion, all 
								//binary numbers are copied to the asciitoBin_64 array, which is required so that the PC- 1
								//table can be applied.
	void applyPC1();		//Integers in PC1 indicate the position of the element in the asciitoBin_64 array to be 
							//taken and stored in initialKey[0][]. Since PC1 is only 56 elements, it also reveals how the 
							//64- bit binary number is reduced to the 56- bit binary number.

	void applyRotation(); //This method takes the 56 bit- key and splits it into halves each of length 28, 
						  //K[56] = C[28]*D[28].
						  //A rotation is essentially left shifting a binary number while wrapping around the end of the 
						  //binary number to the beginning.
						  //When applying rotations, key rounds: 1, 2, 9, and 16 are rotated only once, while the other 
						  //rounds are rotated twice.
						  //Therefor, each half (C and D) is rotated and the result is the key for
						  //for that round. Once a rotation for that round is complete it is combined and stored back in
						  //initial key so that the PC- 2 table can be applied.
	void applyPC2();		//Integers in PC2 indicate the position of the element in the initialKey[][] array to be 
							//taken and stored in finalKey[][48]. Since PC2 is only 48 elements, it also reveals how the 
							//56- bit binary number is reduced to the 48- bit binary number.
};
#endif