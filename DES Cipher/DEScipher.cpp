//Name: Reshal Luchman
//Student number: 213501051
//ENEL4SE - Security and Encryption
//DES Cipher
//Filename: DEScipher.cpp

#include "DEScipher.h"
#include "iostream"
#include "string"
#include "cctype"
#include "bitset"

using namespace std;

/////////////////////////////////Class DES///////////////////////////////////////
//Constructor
DES::DES(){}
//Destructor
DES::~DES(){}

///Accessor
string DES::getMessage()
{
	return message;
}

int DES::getEncKey(int i, int j)
{
	return enc_key[i][j];
}

//Mutator
void DES::setMessage(string m)
{
	message = m;
}

void DES::setEncKey(int i, int j, int bin)
{
	enc_key[i][j] = bin;
}

//Methods
void DES::prepMessage()
{

	for (int i = 0; i < message.length(); i++) //Remove spaces
	{
		if (message[i] == ' ')
			message.erase(i, 1);
	}

	for (int i = 0; i < message.length(); i++)		//Converts each character to upper case
		message[i] = static_cast<char>(toupper(message[i]));

	if (message.length() % 8 != 0)	//if length of plaintext is not 8 insert filler characters.
	{

		string fillerarr;		//default filler character
		int testfillq = 0; //test if filler character exists in message, if it does (testfill = 1) use next character
		int testfillx = 0;
		int testfillz = 0;

		int len = message.length();
		int filllength = 8 - (len % 8);
		
		//Find appropriate filler character
		for (int i = 0; i < len; i++)
		{

			if (message[i] == 'Q')
				testfillq = 1;
			if (message[i] == 'X')
				testfillx = 1;
			if (message[i] == 'Z')
				testfillz = 1;
		}

		if (testfillx == 0)
			fillerarr = 'X';
		else if (testfillz == 0)
			fillerarr = 'Z';
		else if (testfillq == 0)
			fillerarr = 'Q';
		else
			fillerarr = 'X';

		cout << "\nPlaintext length is not a block of 8 characters. Using filler characters as well." << endl;
		cout << "Current Plaintext length: " << len << endl;

		for (int i = len; i < len + filllength; i++)
		{
			message.append(fillerarr);
		}

		len = message.length();

		cout << "Blocks to be encrypted: " << endl;
		for (int i = 0; i < len; i++)
		{

			if (i % 8 == 0)
				cout << endl;
			cout << message[i];
		}
		
		cout << "\n\nNew length of plaintext: " << len << endl;
	}

	else if (message.length() == 8)
	{
	
		cout << "\nMessage to be encrypted: " << endl;
		for (int i = 0; i < message.size(); i++)
		{

			if (i % 8 == 0)
			cout << endl;
			cout << message[i];
		}
	
		cout << endl;

	}

	messagetoAscii();
}

void DES::messagetoAscii()
{

	for (int i = 0; i < message.length(); i++)		//Type cast string to integer
		ascii.push_back((int)message[i]);

	cout << "\nEquivalent ASCII integers: " << endl;
	for (int i = 0; i < ascii.size(); i++)
	{

		if (i % 8 == 0)
			cout << endl;
		cout << ascii[i] << " ";
	}
		
	amestoBIN(); //ascii message to binary
}

void DES::amestoBIN()
{

	int temp[64];

	//Store ascii numbers in binary data type which automatically converts integers to binary
	for (int i = 0; i < ascii.size(); i++)
		PasciitoBin.push_back(ascii[i]);

	//cout << "\n\nEquivalent Binary values: " << endl;
	
	/*for (int i = 0; i < PasciitoBin.size(); i++)
	{

		for (int j = 7; j > -1; j--)
			cout << PasciitoBin[i][j];

		cout << endl;

		if (i > 0)
		{

			if (i % 8 == 0)
				cout << endl;
		}
	}*/

	int k = 0;
	//int b = 0;

		for (int i = 0; i < PasciitoBin.size(); i++)
		{

			for (int j = 7; j > -1; j--)
			{		
				temp[k] = PasciitoBin[i][j]; //Store first set of 64- bits into temporary array
				k++;
				
				if (k == 64)
				{
					
					for (int l = 0; l < 64; l++)
					{
						PasciitoBinary_64_init[block][l] = temp[l];
					}
					
					block++;
					k = 0;
				}
			}
		}
	
	cout << "\n\nEquivalent 64- bit Binary values for each block: " << endl;

	for (int i = 0; i < block; i++)
	{

		cout << "Block: " << i + 1 << endl;

		for (int j = 0; j < 64; j++)
		{
			cout << PasciitoBinary_64_init[i][j];
		}

		cout << endl << endl;
	}

	system("pause");
}

void DES::applyIP()
{

	system("cls");

	//Initial Permutation (IP) table Permutes bits in each block of the message
	int IP[64] = { 58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17, 9, 1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7 };

	for (int b = 0; b < block; b++)
	{

		for (int j = 0; j < 64; j++)
			PasciitoBinary_64_final[b][j] = PasciitoBinary_64_init[b][IP[j] - 1];
		
	}

	cout << "Applying Initial Permutation table to each block:" << endl;
	for (int i = 0; i < block; i++)
	{

		cout << "Block: " << i + 1 << endl;

		for (int j = 0; j < 64; j++)
		{
			cout << PasciitoBinary_64_final[i][j];
		}

		cout << endl << endl;
	}

	//Split the 64 bits of each block into halves- 32-bit each, left and right
	for (int b = 0; b < block; b++)
	{
		for (int k = 0; k < 32; k++)
		{
			L0[b][k] = PasciitoBinary_64_final[b][k];
			R0[b][k] = PasciitoBinary_64_final[b][k + 32];
		}
	}

/*	cout << "Left: " << endl;
	for (int b = 0; b < block; b++)
	{
		for (int k = 0; k < 32; k++)
		{
			cout << L0[b][k];
		}
		cout << endl;
	}

	cout << "Right " << endl;
	for (int b = 0; b < block; b++)
	{
		for (int k = 0; k < 32; k++)
		{
			cout << R0[b][k];
		}
		cout << endl;
	}*/

	system("pause");
}

void DES::encrypt()
{

	//Expansion table
	int Extable[48] = { 32, 1, 2, 3, 4, 5,
		4, 5, 6, 7, 8, 9,
		8, 9, 10, 11, 12, 13,
		12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21,
		20, 21, 22, 23, 24, 25,
		24, 25, 26, 27, 28, 29,
		28, 29, 30, 31, 32, 1 };

	system("cls");

	//Run a loop for each block
	for (int b = 0; b < block; b++)
	{

		cout << "Block number: " << b << endl;

		//copy each block into L and R
		for (int i = 0; i < 32; i++)
		{
			L[0][i] = L0[b][i];
			R[0][i] = R0[b][i];
		}
		
		cout << "Left initial block: " << endl;
		for (int i = 0; i < 32; i++)
		{
			cout << L[0][i];
		}

		cout << endl;

		cout << "\nRight initial block: " << endl;
		for (int i = 0; i < 32; i++)
		{
			cout << R[0][i];
		}

		//start 16 round key encryption
		for (int round = 0; round < 16; round++)
		{


			//L(n) = R(n-1)
			for (int i = 0; i < 64; i++)
			{
				L[round + 1][i] = R[round][i];
			}

			cout << "\nApplying Expansion table to 32- bits to get 48- bits." << endl;

			for (int i = 0; i < 48; i++)
			{
				R_Expand[i] = R[round][Extable[i]-1];
			}



		}




	}


}


////////////////////////////Key Schdeule//////////////////////////////////////
//Accesoor and Mutator
//Accessor
string keySchedule::getkeyInput()
{
	return keyinput;
}

int keySchedule::getasciiInt(int i)
{
	return asciiInt[i];
}

bitset<8> keySchedule::getasccitoBin(int i)
{
	return asciitoBin[i];
}

int keySchedule::getFinalKey(int i, int j)
{
	return finalKey[i][j];
}

//Mutator
void keySchedule::setkeyInput(string key)
{
	keyinput = key;
}

void keySchedule::setasciiInt(int pos, int val)
{
	asciiInt[pos] = val;
}

void keySchedule::setasciitoBin(int pos, int val)
{
	asciiInt[pos] = val;
}

void keySchedule::inputKeyword()
{

	int binasciiInt[8][8]; //2D array to store 64 bit ascii codes

	for (int i = 0; i < keyinput.length(); i++) //Remove spaces
	{
		if (keyinput[i] == ' ')
			keyinput.erase(i, 1);
	}

	for (int i = 0; i < keyinput.length(); i++)		//Converts each character to upper case
		keyinput[i] = static_cast<char>(toupper(keyinput[i]));	

	if (keyinput.length() < 8)	//if length of keyword is less than 8 insert filler characters.
	{

		char filler; //default filler character
		int testfillq = 0; //test if filler character exists in message, if it does (testfill = 1) use next character
		int testfillx = 0;
		int testfillz = 0;

		int len; //subtract 8 from keyword
		string fillerarr;

		//Find appropriate filler character
		for (int i = 0; i < keyinput.length(); i++)
		{

			if (keyinput[i] == 'Q')
				testfillq = 1;
			if (keyinput[i] == 'X')
				testfillx = 1;
			if (keyinput[i] == 'Z')
				testfillz = 1;
		}

		if (testfillx == 0)
			filler = 'X';
		else if (testfillz == 0)
			filler = 'Z';
		else if (testfillq == 0)
			filler = 'Q';
		else
			filler = 'X';

		cout << "Key length is less than 8 using filler characters as well." << endl;
		//cout << "Key length: " << keyinput.length() << endl;

		len = 8 - keyinput.length();
		
		for (int i = 0; i < len; i++)	//create string of filler characters to append to keyinput
			fillerarr += filler;		//to make length of 8 characters.
		keyinput.append(fillerarr);

		//	cout << "New Key length: " << keyinput.length() << endl;
		//  cout << "Final Key: " << endl;
		cout << keyinput << endl;

		stringtoASCII(keyinput); //convert string to ascii integers
	}

	else if (keyinput.length() > 7)	//else if it is greater than 8 trim to length of 8 characters.
	{

		cout << "Taking the first 8 charcters. " << endl;
		//cout << "Key length: " << keyinput.length() << endl;
		cout << "Key entered: " << keyinput << endl;

		keyinput = keyinput.substr(0, 8);
		cout << "Updated key: " << keyinput << endl;

		stringtoASCII(keyinput); //convert string to ascii integers
	}
}

void keySchedule::stringtoASCII(string keyinput)
{

	cout << "\nEquivalent ASCII integers: " << endl;
	for (int i = 0; i < keyinput.length(); i++)		//Type cast string to integer
		asciiInt[i] = int(keyinput[i]);

	for (int i = 0; i < 8; i++)
		cout << asciiInt[i] << " ";
}

void keySchedule::asciitoBIN()
{

	//Store ascii numbers in binary data type which automatically converts integers to binary
	for (int i = 0; i < 8; i++)
	{
		asciitoBin[i] = asciiInt[i];
	}

	//Store binary numbers into integer array so that PC1 can be applied to it
	int k = 0;

	for (int i = 0; i < 8; i++)
	{

		for (int j = 7; j > -1; j--)
		{
			asciitoBinary_64[k] =  asciitoBin[i][j];
			k++;
		}
	}

	//Display ascii code in binary.
	cout << "Binary representation of ASCII code: " << endl;
	int i = 1;

	while (i <= 64)
	{

		cout << asciitoBinary_64[i-1];

		if (i % 8 == 0)
			cout << endl;

		i++;
	}

	system("pause");
}

void keySchedule::applyPC1()
{

	system("cls");

	//PC- 1 table
	int PC1[56] = { 57, 49, 41, 33, 25, 17, 9,
		1, 58, 50, 42, 34, 26, 18,
		10, 2, 59, 51, 43, 35, 27,
		19, 11, 3, 60, 52, 44, 36,
		63, 55, 47, 39, 31, 23, 15,
		7, 62, 54, 46, 38, 30, 22,
		14, 6, 61, 53, 45, 37, 29,
		21, 13, 5, 28, 20, 12, 4 };

	cout << "Applying PC- 1 table to 64- bits to get 56- bits." << endl;
 
	for (int i = 0; i < 56; i++)
	{
		initialKey[0][i] = asciitoBinary_64[PC1[i] - 1];	
	}

	//Display key after PC- 1
	int k = 1;
	while (k <= 56)
	{

		cout << initialKey[0][k-1];

		if (k % 7 == 0)
			cout << endl;
		k++;
	}

	system("pause");
}

void keySchedule::applyRotation()
{

	system("cls");
	
	cout << "Applying rotation (left shift) to get 16 keys for the 16 rounds." << endl;

	for (int k = 1; k <= 16; k++)			//For 16 rounds.
	{

		for (int i = 0; i < 28; i++)		//Store each half of 56- bit key in C & D each of length 28.
		{

			Cn[i] = initialKey[k - 1][i];			//Cn = Kn_0 (store first half of 56- bits).
			Dn[i] = initialKey[k - 1][i + 28];		//Dn = Kn_28 (store second half of 56- bits).
		}

		if (k == 1 || k == 2 || k == 9 || k == 16)	//Key rounds: 1, 2, 9, and 16 are rotated only once. 
		{

			CnR[0] = Cn[27];		//Left shift the lsb and wrap around the end of C to the beginning.
			DnR[0] = Dn[27];		//Left shift the lsb and wrap around the end of D to the beginning.

			for (int i = 1; i < 28; i++)		//Shift rest of binary numbers in each half i.e. in C & D.
			{

				CnR[i] = Cn[i - 1];			
				DnR[i] = Dn[i - 1];			
			}
		}

		else
		{
									//For the rest of the rounds:
			CnR[0] = Cn[26];		//Left shift twice and wrap around the end of C to the beginning.
			CnR[1] = Cn[27];			

			DnR[0] = Dn[26];		//Left shift twice and wrap around the end of D to the beginning.
			DnR[1] = Dn[27];

			for (int i = 2; i < 28; i++)	//Shift rest of binary numbers in each half i.e. in C & D.
			{

				CnR[i] = Cn[i - 2];			
				DnR[i] = Dn[i - 2];
			}
		}

		for (int i = 0; i < 28; i++)		//Store the result back in the initialKey		
		{

			initialKey[k][i] = CnR[i];
			initialKey[k][i + 28] = DnR[i];
		}
	}

	//Display all keys generated.
	for (int i = 1; i <= 16; i++)
	{

		int k = 1;
		cout << "Key Round: " << i << endl;

		while (k <= 56)
		{

			cout << initialKey[i][k - 1];

			if (k % 7 == 0)
				cout << endl;
			k++;
		}
	}

	system("pause");
}

void keySchedule::applyPC2()
{

	system("cls");
	
	cout << "Applying PC- 2 table to 56- bits to get 48- bits." << endl;

	//PC- 2 table.
	int PC2[48] = { 14, 17, 11, 24, 1, 5, 3, 28,
		15, 6, 21, 10, 23, 19, 12, 4,
		26, 8, 16, 7, 27, 20, 13, 2,
		41, 54, 31, 37, 47, 55, 30, 40,
		51, 45, 33, 48, 44, 49, 39, 56,
		34, 53, 46, 42, 50, 36, 29, 32 };

	for (int i = 0; i<16; i++)
	{
		for (int j = 0; j<48; j++)
		{
			finalKey[i][j] = initialKey[i + 1][PC2[j] - 1];
		}
	}
	
	//Display keys after PC2 has been applied
	for (int i = 0; i < 16; i++)
	{

		int k = 1;
		cout << "\nFinal Key Round: " << i + 1 << endl;

		while (k <= 48)
		{

			cout << finalKey[i][k - 1];

			if (k % 6 == 0)
				cout << "\t";
			k++;
		}
	}

	cout << endl;
}