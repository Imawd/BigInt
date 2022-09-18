#include "bigint.h"
#include <iostream>
#include <fstream>
using namespace std;


int main() {
    //Add your own code
    //You may comment out the example code snippets below
  
    //First example
    BigInt a("1001111110010101000010001011110101010100111101010000011000000111011011101010101001111100100101101000000110110001", 2);
    BigInt b("10101101001001011111101001111001011010110101100111001100000011011011100011011001101111011111011110111110100001", 2);

    BigInt c = a - b;

    cout << c.to_string() << endl;
    
    
	return 0;
}
