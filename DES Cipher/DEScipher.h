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

	string message;							//Plaintext to be encrypted.
	vector<int> ascii;						//vector to hold characters after being converted to ascii.
	vector<bitset<8>> PasciitoBin;			//Vector + bitset data type to hold each ascii code converted to binary.
	int PasciitoBinary_64_init[100][64];	//Copy all bits in blocks of 64 to 2D- array. 
	
	int block = 0;		//Track how many blocks are created. 1 block = 8 characters of plaintext = 8 ascii codes = 64- bits.

	int PasciitoBinary_64_final[100][64];		//After IP is applied result is stored here.
	int L0[100][32];							//Split each block into 32-bits to create the initial left half and right  
	int R0[100][32];							//half of each block.

	int enc_key[16][48];						//Store 16 generated keys from keySchedule class for encryption.

	int L[17][32];								//For each round, result Left and Right bits are stored in L and R.
	int R[17][32];

	int R_Expand[48];		//Holds the result of R after Expansion table has been applied and after R has been XORed 
							//with the key for that round.
	int R_group[8][6];		//2D array to hold the 48- bits into 8 groups of 6- bits so that the S- boxes can be applied to
							//it.
	int R_SB[32];		//Store the 32- bit result of S-box.
	int R_Pbox[32];		//Store result after P- box permutation.

	vector<int>tempascii;		//Stores 8- bits at a time so that it can be converted to ascii.
	vector<int> finalascii;		//Stores ascii codes converted from binary from both L and R.

public:

	DES();		//Constructor
	~DES();		//Destructor
	
	//Accessor and Mutator functions
	//Accessor

	string getMessage();
	int getEncKey(int, int);	//Takes in as parameters i and j and returns the postion of (key) element in 2D- array.

	//Mutator
	void setMessage(string);
	void setEncKey(int, int, int);	//Takes in as parameters, positions i, j and value and stores the result in enc_Key[i][j]

	//Encryption
	void prepMessage();		//Once the meesage has been received, this method first removes any spaces in the plaintext 
							//and the converts all characters to upper case for consistency. Thereafter, a check of the 
							//length of the plaintext is done. If the length of the plaintext is equal to 8, it implies that
							//only 8 characters have been entered, hence only one block is to be encrypted. Else if the  
							//length of the plaintext is not equal to 8 it leads to two cases. 1. The length of the text is
							//less than 8 characters or 2. the length of the text is more than 8 characters. For
							//case 1: Search for the appropriate filler character(X, Q, Z) and append an array of filler 
							//characters to the meesage to make 8 characters = 1 block. For case 2: find appropriate
							//filler character and append array of filler characters to the message such that the  
							//length % 8 = 0, since each block = 8 characters. Lastly, messagetoAscii() is
							//called to convert each character to its equivalent ASCII code.

	void messagetoAscii();		//convert each character to ascci and store the result in vector: ascii
	void amestoBIN();		//Ascii converted plaintext to binary
	void applyIP();
	void encrypt();
	void bintoAscii();
	void bintoAscii(vector<int>);

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

 int finalKey[16][48];		//finalKey- 2D array which holds all 16 keys generated and after PC2 is applied.

public:

	keySchedule();		//Constructor 
	~keySchedule();		//Destructor
	
	//Accessor and Mutator functions
	//Accessor

	string getkeyInput(); 
	int getasciiInt(int);
	bitset<8> getasccitoBin(int);
	int getFinalKey(int, int);
	
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