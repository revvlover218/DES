//Name: Reshal Luchman
//Student number: 213501051
//ENEL4SE - Security and Encryption
//DES Cipher
//Filename: Main.cpp

#include "iostream"
#include "string"
#include "DEScipher.h"

using namespace std;

int main()
{

	DES enc;
	string mes;
	int n;

	/*cout << "Security and Encryption - Data Encryption Standard (DES): " << endl;

	cout << "Enter message to  be encrypted: " << endl;
	cin >> mes;

	enc.setMessage(mes);
	enc.prepMessage();

	cout << "\n\n" << enc.getMessage() << endl;
	
	enc.stringtoASCII();
	*/

	cin >> n;

	cout << "\n\n" << enc.asciitoBIN(n) << endl;

	system("pause");

	return 0;
}