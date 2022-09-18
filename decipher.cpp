#include "bigint.h"
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout<<"\033[1;41m----Missing an argument----\033[0m"<<endl;
	  cout << "Usage: ./decipher <file>"<<endl;
	  cout << "Examples:" << endl;
	  cout << "\t./decipher secret/message1.txt \033[1;90m//to decipher message 1\033[0m" << endl;
	  cout << "\t./decipher secret/message2.txt \033[1;90m//to decipher message 2\033[0m"<<endl;
		return -1;
	}

	/************* You complete *************/

	try 
	{
		int base;
		string d;
		string n;
		string secretcode;
		BigInt actualcode;

		ifstream ifile(argv[1]);

		ifile >> base >> d >> n;
		BigInt D(d, base);
		BigInt N(n, base);

		while (ifile >> secretcode)
		{
			BigInt code(secretcode, base);
			actualcode = modPow(code, D, N);
			cout << (char)actualcode.to_int();
		}
		cout << endl;
	}

	catch(const exception& e)
	{
		cout << e.what() << endl;
		return -1;
	}
 
  
  
  
	return 0;
}
