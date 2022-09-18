#include <string>
#include <vector>
#include <iostream>
#include <exception>
using namespace std;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//IMPORTANT: This file is complete. 
//			-	Do NOT add/remove anything in this file.
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


//===================================
//BigInt class definition
//===================================
class BigInt {

	public:
		//-----------------------------------
		//Constructor/Destructor
		//-----------------------------------
		BigInt();					          //create BigInt with base 10
		BigInt(int setbase);		    //create BigInt with a certain base
		BigInt(int input,int base);	//create BigInt from int (base 10) to a certain base
		BigInt(const string &s,int base);	//create BigInt from string
		BigInt(const BigInt &b);	  //create BigInt from another BigInt (copy constructor)
		~BigInt();					        //destructor
    BigInt & operator = (const BigInt &b);	//assignment or copy
  
		//-----------------------------------
		//Comparison
		//-----------------------------------
		int compare(const BigInt &b) const;

		//-----------------------------------
		//Display
		//-----------------------------------
		string to_string();
		int to_int() const;
  
    //-----------------------------------
		//Arithmetic operations
		//	Operator overloading -> member functions
		//-----------------------------------
		const BigInt & operator += (const BigInt &b);	//addition assignment
		const BigInt & operator -= (const BigInt &b);	//subtraction assignment
		const BigInt & operator *= (const BigInt &b);	//multiplication assignment
		const BigInt & operator /= (const BigInt &b);	//division assignment
		const BigInt & operator %= (const BigInt &b);	//modulus assignment
    //-----------------------------------
		const BigInt & exponentiation(const BigInt &b);	//exponentiation assignment
		const BigInt & modulusExp(const BigInt &b, const BigInt &mod);//mod exponentiation assignment

		//sanity check -- no need to do anything with these
		void printVecItems();
		bool getSign();
		int getBase();

	private:
		vector<int> vec;		//vector to hold digits
		int base = 10;				    //any base between 2 and 36 (default = 10)
		bool isPositive = true;	  //true if positive, false if negative. (default = positive)
		//main function for division and modulus (private)
		void divisionMain(const BigInt &b, BigInt &quotient, BigInt &remainder);
};

//===================================
//===================================
//Operator overloading -> non-member functions (binary)
//===================================
BigInt operator + (const BigInt &a, const BigInt &b);
BigInt operator - (const BigInt &a, const BigInt &b);
BigInt operator * (const BigInt &a, const BigInt &b);
BigInt operator / (const BigInt &a, const BigInt &b);
BigInt operator % (const BigInt &a, const BigInt &b);
BigInt pow(const BigInt &a, const BigInt &b);
BigInt modPow(const BigInt &a, const BigInt &b, const BigInt &m);
//---- Equality Check ---- 
bool operator == (const BigInt &a, const BigInt &b);
bool operator != (const BigInt &a, const BigInt &b);
bool operator <= (const BigInt &a, const BigInt &b);
bool operator >= (const BigInt &a, const BigInt &b);
bool operator < (const BigInt &a, const BigInt &b);
bool operator > (const BigInt &a, const BigInt &b);


//===================================
//Custom Exceptions
//	to handle math function errors
//===================================
struct DivByZeroException : exception{
	const char * what () const throw (){
    	return "Error: Divide by zero";
    }
};

struct ExpByNegativeException : exception{
	const char * what () const throw (){
    	return "Error: Exponentiate by negative";
    }
};

struct DiffBaseException : exception{
	const char * what () const throw (){
    	return "Error: Bases are not equal";
    }
};

struct InvalidBaseException : exception{
	const char * what () const throw (){
    	return "Error: Base should be between 2 and 36";
    }
};