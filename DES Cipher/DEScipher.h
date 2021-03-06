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
	vector<bitset<8>> PasciitoBin;			//Vector + bitset data type, where each element in the vector
											//holds an 8- bit binary number i.e., to store each ascii code which is
											//converted to binary.
	int PasciitoBinary_64_init[100][64];	//Store in blocks of 64- bits to 2D- array, PasciitoBinary_64_init[block][64]. 
	
	int block = 0;		//Track how many blocks are created. 1 block = 8 characters of plaintext = 8 ascii codes = 64- bits.

	int PasciitoBinary_64_final[100][64];		//After IP is applied result is stored here.
	int L0[100][32];							//Split each block into 32- bits to create the initial left half L(0)
	int R0[100][32];							//and right half R(0).

	int enc_key[16][48];						//Store 16 generated keys from keySchedule class for encryption.

	int L[17][32];								//For each round, result of Left and Right bits are stored in L and R.
	int R[17][32];

	int R_Expand[48];		//Holds the result of R after Expansion table has been applied and after R has been XORed 
							//with the key for that round.
	int R_group[8][6];		//2D array to hold the 48- bits into 8 groups of 6- bits so that the S- boxes can be applied to
							//it.
	int R_SB[32];		//Stores the 32- bit result of S-box.
	int R_Pbox[32];		//Stores result after P- box permutation.

	vector<int>tempascii;		//Stores 8- bits at a time so that it can be converted to ascii.
	vector<int> finalascii;		//Stores ascii codes converted from binary from both L and R.

public:

	DES();		//Constructor
	~DES();		//Destructor
	
	//Accessor and Mutator functions
	//Accessor

	string getMessage();
	int getEncKey(int, int);	//Takes in as parameters i and j and returns the (key) element in 2D- array.

	//Mutator
	void setMessage(string);
	void setEncKey(int, int, int);	//Takes in as parameters, positions i, j and a single bit value and stores 
									//the result in enc_Key[i][j].

	//Encryption
	void prepMessage();		//Once the meesage has been received, this method first removes any spaces in the plaintext 
							//and the converts all characters to upper case for consistency. Thereafter, a check of the 
							//length of the plaintext is done. If the length of the plaintext is equal to 8, it implies that
							//only 8 characters have been entered, hence, only one block is to be encrypted. Else if the  
							//length of the plaintext is not equal to 8 it leads to two cases. 1. The length of the text is
							//less than 8 characters or 2. the length of the text is more than 8 characters. For
							//case 1: Search for the appropriate filler character(X, Q, Z) and append an array of filler 
							//characters to the meesage to make 8 characters = 1 block. For case 2: find appropriate
							//filler character and append array of filler characters to the message such that the  
							//length % 8 = 0, since each block = 8 characters. Lastly, messagetoAscii() is
							//called to convert each character to its equivalent ASCII code.

	void messagetoAscii();		//convert each character to ascii code and store the result in the vector, ascii.
	void amestoBIN();		//Function which converts ascii numbers to binary using the bitset data type.
							//When a number is stored in a bit set data type, the bitset essentially type casts
							//the integer to an N- bit binary number (defined by user = 8). Nevertheless, this is also
							//where the initial blocks of the plaintext is created, P(0), P(1) etc. Since one block
							//is equal to 8 characters which is equal to 64- bits, take 64- bits at a time and store in
							//PasciitoBinary_64_init[number of blocks][64]. This is required so that the initial 
							//permutation, IP can be applied to each block.

	void applyIP();		//Apply Initial permutation table to each block. IP changes the positions of the bits in each block.
						//Thereafter, function splits each block into halves of 32- bits L(0) and R(0) which is required for 
						//the encryption rounds.

	void encrypt();		//For encryption, L and R store the 32- bit results to be used for the next round. A loop is run for
						//each block. The initial L(0) and R(0) of each block is copied into L and R and then the 16 
						//round encryption begins. L is taken care of since it only requires R i.e. for round n: 
						//L(n) = R(n-1).
						//Thereafter, R is taken care of. First, the expansion table is applied to R to convert the 32- bits 
						//into 48- bits. This result is stored in R_Expand[48]. Next, the required key for that round 
						//is XORed with R_Expand and the result is stored back in R_Expand. The 48- bits need to be grouped
						//so that the S- box can be applied. The 48- bits are split into 8 groups
						//each containing 6- bits and the result is stored in the 2D array, R_group[8][6].
						//Furthermore, for the 8 groups there are 8 S- boxes, so, S- box1 is applied to group 1, S- box 2 is
						//applied to group 2 and so fourth. All S- boxes have 4 rows (0 - 3) and 16 columns (0 - 15)
						//and each element is an integer, a 4- bit number in binary. To get the row number, the first and 
						//last bit in each group is converted to decimal. To get the column number, the middle 4- bits 
						//in each group is converted to decimal.. The result returned from the S- box is an integer,
						//therefore, it needs to be converted to binary so that the next table can be applied to it. 
						//The bitset data type is again used, whereby storing an integer in a bitset of N- bits
						//(defined by the user = 4) is type casted to binary. However, it must also be noted that the bits
						//are stored in the reverse order, therefore, a loop is used to traverse the bitset data from 
						//the last element and store it in the correct order in a temporary array. Now that the 4- bits 
						//are in the correct order, it is then stored in R_SB[32] and since, the result is applied 
						//to 8 groups, in total there is 32- bits. Next, the P- box is applied to the 32- bits. The
						//P- box changes the positions of the bits in R_SB and the result is stored in R_PBox[32].
						//To get R for this round, R_PBox is XORed with L. Thus, completing one round of 
						//encryption. At the end of the 16 rounds, L[16] and R[16] each contain 32- bits of the cipher text.
						//8- bits at a time is taken from L[16] and then from R[16] until all 32- bits have been taken and
						//are copied into a temporary vector, which is passed as a parameter to bintoAscii and once the 
						//integer value has been calculated, the result is stored in the vector, finalAscii. Nevertheless,
						//finalAscii, stores the ascii code for each block, in other words, finalAscii contains the 
						//ciphertext in ascii code. Getting the characters is essentially type casting each ascii integer
						//to data type: char, completing the encryption of the ciphertext.

	void bintoAscii(vector<int>);		//Takes in as a parameter a vector which contains an 8- bit binary number and 
										//converts it to its equivalent integer. This result is stored in the finalascii
										//vector.
};

class keySchedule
{

private:
 
 string keyinput;
 int asciiInt[8];		//Array to hold converted ascii integers.
 bitset<8> asciitoBin[8];		//Stores binary version of ascii code where one element in the array contains 8- bits.
 int asciitoBinary_64[64];	//Stores all 8 characters = 8 ascii codes = 64- bits.

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
								//equivalent ascii integer code (type casting). By default when characters are type casted
								//to an integer it is stored as the ASCII equivalent number.
	
	void asciitoBIN();			//Once all characters have been converted to ascii, this function converts each integer
								//to binary. The result is stored in a bitset data type. This function essentially type casts
								//an integer to an N- bit binary number (defined by user = 8). It must also be noted that 
								//the bits are stored in the reverse order, therefore, a loop is used to traverse
								//the bitset data from the last element and store it in the correct order in 
								//asciitoBinary_64. All binary numbers are copied to the asciitoBin_64 array, which is 
								//required so that the PC- 1 table can be applied.

	void applyPC1();		//Integers in PC1 indicate the position of the element in the asciitoBin_64 array to be 
							//taken and stored in initialKey[0][]. Since PC1 is only 56 elements, it also reveals how the 
							//64- bit binary number is reduced to the 56- bit binary number.

	void applyRotation(); //This method takes the 56 bit- key and splits it into halves each of length 28, 
						  //K[56] = C[28]*D[28].
						  //A rotation is essentially left shifting a binary number while wrapping around the end of the 
						  //binary number to the beginning.
						  //When applying rotations, key rounds: 1, 2, 9, and 16 are rotated only once, while any other 
						  //round is rotated twice.
						  //Therefore, each half (C and D) is rotated and the result is the key for
						  //for that round. Once a rotation for that round is complete it is combined and stored back in
						  //initial key so that the PC- 2 table can be applied.
	void applyPC2();		//Integers in PC2 indicate the position of the bits to be taken in the initialKey[][] 
							//and stored in finalKey[][48]. Since PC2 is only 48 elements, it also reveals how the 
							//56- bit binary number is reduced to the 48- bit binary number.
};
#endif