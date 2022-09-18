#include "bigint.h"
#include <iostream>
#include <string>
#include <climits>
#include <cmath>
using namespace std;


/*
// Create a default BigInt with base 10.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(){
  base = 10;
  isPositive = true;
}

/*
// Create a BigInt with a specified base.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    base = setbase;
    isPositive = true;
}

/*
// Destructure. You do not have to add anything.
// This function is complete
*/
BigInt::~BigInt(){}



BigInt::BigInt(const string &s, int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }

    int is_pos = 0;
    base = setbase;
    if (s[0] == '-')
    {
      isPositive = false;
      is_pos++;
    }

    if (base <= 10)
    {
      for (int i = 0; i < (signed)s.length() - is_pos; i++)
      {
        vec.push_back((int)(s[s.length() - 1 - i]) - 48);
      }
    }

    else if (base > 10)
    {
      for (int i = 0; i < (signed)s.length() - is_pos; i++)
      {
        if (s[s.length() - 1 - i] >= 48 && s[s.length() - 1 - i] <= 57) vec.push_back((int)(s[s.length() - 1 - i]) - 48);

        else if (s[s.length() - 1 - i] >= 65 && s[s.length() - 1 - i] <= 90)
        {
          vec.push_back((int)(s[s.length() - 1 - i]) - 55);
        }
      }
    } 
}



BigInt::BigInt(int input,int setbase){
  if(setbase < 2 || setbase > 36){
    throw InvalidBaseException();
  }

  base = setbase;

  if (input < 0)
  {
    isPositive = false;
    input *= -1;
  }

  if (input == 0)
  {
    vec.push_back(0);
  }

  else
  {
    while (input > 0)
    {
      int digit = input % base;
      vec.push_back(digit);
      input /= base;
    }
  }

}


BigInt::BigInt(const BigInt &b){

  *this = b;
 
}


BigInt & BigInt::operator = (const BigInt &b){


    base = b.base;
    isPositive = b.isPositive;
    while (!vec.empty())
    {
      vec.pop_back();
    }
    for (int i = 0; i < (signed)b.vec.size(); i++)
    {
      vec.push_back(b.vec[i]);  
    }

    return *this; 
}


//******************************************************************
//END OF THE CONSTRUCTORS SECTION
//******************************************************************

//******************************************************************
//START OF THE DISPLAYS SECTION
//******************************************************************


string BigInt::to_string(){

    
  string s = "";
  if (!isPositive) s += '-';
  for (int i = 0; i < (signed)vec.size(); i++)
  {
    if (vec[vec.size() - 1 - i] < 10)
    {
      s += (char)(vec[vec.size() - 1 - i] + 48);
    }

    else 
    {
      s += (char)(vec[vec.size() - 1 - i] + 'A' - 10);
    }
  }

  if (s == "") s = '0';

  return s;
}


int BigInt::to_int() const{


    long long x = 0;

    if (isPositive)
    {
      
      for (unsigned int i = 0; i < vec.size(); i++)
      {
        x += (pow(base, i)) * vec[i];
        if (x > INT_MAX) return INT_MAX;
      }
    }
    else if (!isPositive)
    {
  
      for (unsigned int i = 0; i < vec.size(); i++)
      {
        x -= (pow(base, i)) * vec[i];
        
      }
    }

    if (x > INT_MAX) return INT_MAX;
    else if (x < INT_MIN) return INT_MIN;
    return x;
}

//******************************************************************
//END OF THE DISPLAYS SECTION
//******************************************************************

//******************************************************************
//START OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

/*
//  Compare a and b.
//     If a = b, return 0.
//     If a < b, return -1.
//     If a > b, return 1.
*/
int BigInt::compare(const BigInt &b) const{
    if(base != b.base){
        throw DiffBaseException();
    }
    

    if (b.isPositive && !isPositive) return -1;
    else if (isPositive && !b.isPositive) return 1;

    
    
    if ((b.isPositive && isPositive) || (!b.isPositive && !isPositive))
    {
      if (vec.size() != b.vec.size())
      {
        if (vec.size() > b.vec.size() && isPositive) return 1;
        else if (vec.size() < b.vec.size() && isPositive) return -1;
        else if (vec.size() > b.vec.size() && !isPositive) return -1;
        else if (vec.size() < b.vec.size() && !isPositive) return 1;


      }

      else
      {
        for (int i = vec.size() - 1; i >= 0; i--)
        {
          if (vec[i] != b.vec[i])
          {
            if (vec[i] > b.vec[i] && isPositive) return 1;
            else if (vec[i] < b.vec[i] && isPositive) return -1;
            else if (vec[i] > b.vec[i] && !isPositive) return -1;
            else if (vec[i] < b.vec[i] && !isPositive) return 1;
          }
        }
      }
    }
    
    
    return 0;
}



bool operator == (const BigInt &a, const BigInt &b){
  

  bool solution = false;
  if (a.compare(b) == 0) solution = true;
  return solution;
}

bool operator != (const BigInt &a, const BigInt &b){
  
  bool solution = true;
  if (a.compare(b) == 0) solution = false;
  return solution;
}

bool operator <= (const BigInt &a, const BigInt &b){
  
  bool solution;

  if (a.compare(b) == -1 || a.compare(b) == 0)
  {
    solution = true;
  }
  else
  {
    solution = false;
  }

  return solution;

}

bool operator >= (const BigInt &a, const BigInt &b){
  

  bool solution;
  if (a.compare(b) == 1 || a.compare(b) == 0)
  {
    solution = true;
  }
  else
  {
    solution = false;
  }

  return solution;
}

bool operator > (const BigInt &a, const BigInt &b){
  
  bool solution;
  if (a.compare(b) == 1)
  {
    solution = true;
  }
  else
  {
    solution = false;
  }


  return solution;
}


bool operator < (const BigInt &a, const BigInt &b){
  
  bool solution;
  if (a.compare(b) == -1)
  {
    solution = true;
  }
  else
  {
    solution = false;
  }

  return solution;
  
}

//******************************************************************
//END OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************


BigInt operator + (const  BigInt &a, const BigInt & b){


  BigInt c(a);
  c += b;
  return c;  
}

/*
//==================
// MEMBER function
//==================
//  Addition assignment operator.
//    i.e., a += b
*/
const BigInt & BigInt::operator += (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }

  int carry = 0;
  bool Positive = isPositive;

  if ((vec[vec.size() - 1] == 0 && !b.isPositive) || (b.vec[b.vec.size() - 1] == 0 && !isPositive)) Positive = false;


  for (int i = 0; i < (signed)max(vec.size(),b.vec.size()); i++)
  {
    
    if (i >= (signed)vec.size()) vec.push_back(0);
    else if (i >= (signed)b.vec.size()) 
    {
      while (i <= (signed)vec.size() - 1)
      {
        vec[i] += carry;
        if(vec[i] >= base)
        { 
          vec[i] -= base;
          carry = 1;
        }
        else carry = 0;
        i++;
      }
      break;
    }

    if (isPositive == b.isPositive)
    {
      if ((!isPositive && !b.isPositive)) Positive = false;
      else Positive = true;
      vec[i] += b.vec[i] + carry;
      if(vec[i] >= base)
      { 
        vec[i] -= base;
        carry = 1;
      }
      else carry = 0;
    }

    else
    {
      if (isPositive && !b.isPositive)
      {
        BigInt d(*this);
        BigInt c(b);
        c.isPositive = true;
        *this -= c;
        if (d.compare(c) >= 0) isPositive = true;
        else isPositive = false;
        return *this;
      }

      else if (!isPositive && b.isPositive)
      {
        isPositive = true;
        BigInt d(*this);
        *this -= b;
        if (d.compare(b) == 1) isPositive = false;
        else if (d.compare(b) <= 0) isPositive = true;
        return *this;
      }
    }



  }

  if (carry == 1) 
  {
    vec.push_back(1);  
  }


  while (vec[vec.size() - 1] == 0 && vec.size() > 1) vec.pop_back();
    
  isPositive = Positive;
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call -= operator on the copy and b
// 3. Return the copy
*/
BigInt operator - (const  BigInt &a, const BigInt & b){

  BigInt c(a);
  c -= b;
  return c;
}


/*
//==================
// MEMBER function
//==================
//  Subtraction assignment operator.
//    i.e., a -= b
*/
const BigInt & BigInt::operator -= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
 
  if (compare(b) == 0)
  {
    while (!vec.empty())
    {
      vec.pop_back();
    }
    vec.push_back(0);
    isPositive = true;
    return *this;
  }

  BigInt c(*this);

  int borrow = 0;
  bool Positive = true;

  if (compare(b) == 1 || compare(b) == 0) Positive = true;
  else if (compare(b) == -1) Positive = false;

  for (int i = 0; i < (signed)max(vec.size(), b.vec.size()); i++)
  {
    if (i >= (signed)vec.size()) vec.push_back(0);
    else if (i >= (signed)b.vec.size())
    {
      while (i <= (signed)vec.size() - 1)
      {
        vec[i] -= borrow;
        if (vec[i] < 0)
        {
          vec[i] = base + vec[i];
          borrow = 1;
        }
        else break;
        i++;
      }
      break;
    }

    if (isPositive && b.isPositive)
    {
      if (c.compare(b) == -1)
      {
        vec[i] = b.vec[i] - vec[i] - borrow;
        borrow = 0;
        if (vec[i] < 0)
        {
          vec[i] += base;
          borrow = 1;
        }
        else borrow = 0;
      }

      else if (c.compare(b) == 1)
      {
        vec[i] = vec[i] - b.vec[i] - borrow;
        borrow = 0;
        if (vec[i] < 0)
        {
          vec[i] += base;
          borrow = 1;
        }
        else borrow = 0;
      }
    }
    else 
    {
      if (!isPositive && !b.isPositive)
      {
        if (c.compare(b) == -1)
        {
          Positive = false;
          vec[i] = vec[i] - b.vec[i] - borrow;
          borrow = 0;
          if (vec[i] < 0)
          {
            vec[i] += base;
            borrow = 1;
          }
          else borrow = 0;
        }
        if (c.compare(b) == 1)
        {
          Positive = true;
          vec[i] = b.vec[i] - vec[i] - borrow;
          borrow = 0;
          if (vec[i] < 0)
          {
            vec[i] += base;
            borrow = 1;
          }
          else borrow = 0;
        }
      }
      if (isPositive && !b.isPositive)
      {
        isPositive = true;
        BigInt c(b);
        c.isPositive = true;
        *this += c;
        return *this;
      }
      if (!isPositive && b.isPositive)
      {
        isPositive = true;
        *this += b;
        isPositive = false;
        return *this;
      }
    }
  }

  
  while (vec[vec.size() - 1] == 0 && vec.size() > 1) vec.pop_back();
  isPositive = Positive;

  


  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call *= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator * (const  BigInt &a, const BigInt & b){


  BigInt c(a);
  c *= b;
  return c;

}



/*
//==================
// MEMBER function
//==================
//  Multiplication assignment operator.
//    i.e., a *= b
//  Implement Long Multiplication
//  Note: What are the base cases?? (e.g., multiply by 0)
*/
const BigInt & BigInt::operator *= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }

    int carry = 0;
    int product = 0;

    BigInt total(0, base);
    BigInt copy(*this);
    BigInt zero(0, base);
    BigInt one(1, base);

    if (*this == zero) return *this;
    else if (b == zero)
    {
      *this = b;
      return *this;
    }

    else if (b == one)
    {
      if ((copy.isPositive && !b.isPositive) || (!copy.isPositive && b.isPositive)) isPositive = false;
      else if ((copy.isPositive && b.isPositive) || (!copy.isPositive && !b.isPositive)) isPositive = true;
      return *this;
    }

    else if (*this == one)
    {
      *this = b;

      if ((copy.isPositive && !b.isPositive) || (!copy.isPositive && b.isPositive)) isPositive = false;
      else if ((copy.isPositive && b.isPositive) || (!copy.isPositive && !b.isPositive)) isPositive = true;
      return *this;
    }

    for (int i = 0; i < (signed)b.vec.size(); i++)
    {
      BigInt temp(base);

      for (int k = 0; k < i; k++) temp.vec.push_back(0);
      
      for (int j = 0; j < (signed)vec.size(); j++)
      {
        product = (vec[j] * b.vec[i]) + carry;
        carry = 0;
        while (product >= base)
        {
          product -= base;
          carry++;
        }

        temp.vec.push_back(product);
      }
      if (carry != 0) temp.vec.push_back(carry);
      carry = 0;

      if (total == zero) total = temp;
      else total += temp;
    }

    *this = total;

    if ((copy.isPositive && !b.isPositive) || (!copy.isPositive && b.isPositive)) isPositive = false;
    else if ((copy.isPositive && b.isPositive) || (!copy.isPositive && !b.isPositive)) isPositive = true;

    return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call /= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator / (const  BigInt &a, const BigInt & b){


    
  BigInt copy(a);
  copy /= b;
  return copy;

}


/*
//==================
// MEMBER function
//==================
//  Division assignment operator.
//    - Call 'divisionMain' to get the quotient;
*/
const BigInt & BigInt::operator /= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();
    }

  BigInt quotient(base);
  BigInt remainder(base);

  divisionMain(b, quotient, remainder);

  *this = quotient;

  return *this;

}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call %= operator on the copy and b
// 3. Return the copy
*/
BigInt operator % (const  BigInt &a, const BigInt & b){


    
  BigInt copy(a);
  copy %= b;
  return copy;

    
    
    return a;//for now
}


/*
//==================
// MEMBER function
//==================
//  Modulus assignment operator.
//    - Call 'divisionMain' to get the remainder;
//    - Note: remainder takes the sign of the dividend.
*/
const BigInt & BigInt::operator %= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();//divide by zero.
    }
  

  BigInt quotient(base);
  BigInt remainder(base);

  divisionMain(b, quotient, remainder);

  *this = remainder;

  return *this;
  
}


void BigInt::divisionMain(const BigInt &b, BigInt &quotient, BigInt &remainder){


  bool isPositive_final;
  bool isPositive_start = isPositive;


  if (isPositive != b.isPositive) isPositive_final = false;
  else isPositive_final = true;

  isPositive = true;

  BigInt zero(0, base);
  BigInt one(1, base);
  BigInt minusOne(-1, base);

  BigInt b_copy(b);
  b_copy.isPositive = true;

  if (b.vec.size() == 1 && b.vec[0] == 1)
  {
    quotient = *this;
    quotient.isPositive = isPositive_final;
    remainder = zero;
    return;
  }

  if (*this == b_copy)
  {
    quotient = one;
    quotient.isPositive = isPositive_final;
    remainder = zero;
    return;
  }

  if (*this == zero)
  {
    quotient = zero;
    remainder = zero;
    remainder.isPositive = isPositive_start;
    return;
  }

  if (*this < b_copy)
  {
    quotient = zero;
    remainder = *this;
    remainder.isPositive = isPositive_start;
    return;
  }

  int pos = vec.size() - 1;
  BigInt dividend_seq(vec[pos], base);
  while (dividend_seq < b_copy)
  {
    pos--;
    dividend_seq.vec.insert(dividend_seq.vec.begin(), vec[pos]);
  }
  while (pos >= 0)
  {
    int times = 0;
    while (dividend_seq >= b_copy)
    {
      dividend_seq -= b_copy;
      times++;
    }
    quotient.vec.insert(quotient.vec.begin(), times);

    if (dividend_seq.vec.size() == 1 && dividend_seq.vec[0] == 0)
    {
      dividend_seq.vec.pop_back();
    }

    if (pos - 1 >= 0)
    {
      dividend_seq.vec.insert(dividend_seq.vec.begin(), vec[pos - 1]);
    }
    pos--;
  }

  if (dividend_seq.vec.empty())
  {
    remainder.vec.push_back(0);
    remainder.isPositive = true;
  }
  else
  {
    remainder = dividend_seq;
    remainder.isPositive = isPositive_start;
  }

  quotient.isPositive = isPositive_final;


}




BigInt pow(const  BigInt &a, const BigInt & b){

    
  
    BigInt copy(a);
    copy.exponentiation(b);
    return copy;
}


const BigInt & BigInt::exponentiation(const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
  
  BigInt exponent(b);
  BigInt result(1, base);
  BigInt one(1, base);
  BigInt two(2, base);
  BigInt zero(0, base);

  bool isPositive_final;

  if (isPositive == true) isPositive_final = true;
  else if (exponent % two == zero) isPositive_final = true;
  else isPositive_final = false;

  while (exponent > zero)
  {
    if (exponent % two == zero)
    {
      *this *= *this;
      exponent /= two;
    }

    else 
    {
      result *= *this;
      exponent -= one;
    }
  }

    *this = result;
    isPositive = isPositive_final;
    return *this;
}


BigInt modPow(const BigInt &a, const BigInt &b, const BigInt &m){

  
  BigInt copy(a);
  copy.modulusExp(b, m);
  return copy;

}



const BigInt & BigInt::modulusExp(const BigInt &b, const BigInt &m){
    if(base != b.base || base != m.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }

  BigInt result(1, base);
  BigInt one(1, base);
  BigInt two(2, base);
  BigInt zero(0, base);
  BigInt exponent(b);

  while (exponent > zero)
  {
    if (exponent % two == zero)
    {
      *this *= *this;
      *this %= m;
      exponent /= two;
    }

    else 
    {
      result *= *this;
      exponent -= one;
      result %= m;
    }
  }

    *this = result;
    return *this;

  






  
  
    return *this;
}

//sanity checks
void BigInt::printVecItems(){
  cout<<"[";
  for(size_t i = 0;i<vec.size();i++){
    cout<<vec[i];
    if(i < vec.size()-1){
      cout<<",";
    }
  }
  cout<<"]"<<endl;
}

bool BigInt::getSign(){
	return isPositive;
}

int BigInt::getBase(){
	return base;
}
