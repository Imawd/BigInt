#include "bigint.h"
#include <iostream>
#include <fstream>
using namespace std;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//IMPORTANT: This file is complete. 
//			-	Do NOT add/remove anything in this file.
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int main(int argc, char* argv[]) {
	if (argc < 3) {
		cout<<"\033[1;41m----Missing arguments----\033[0m"<<endl;
	    cout << "Usage: ./test <base> <mode>"<<endl;
	    cout<<"<base>\t2, 10, or 16"<<endl;
	    cout<<"<mode>\t0: compare, 1: convertToInt, 2: Int10ToOtherBase 3: add,"<<endl;
	    cout<<"\t4: subtract, 5: multiply, 6: divide, 7: mod,"<<endl;
	    cout<<"\t8: exponential, 9: modexp"<<endl;
	    cout << "Examples:" << endl;
	    cout << "\t./test 10 2  \033[1;90m//base 10, run add\033[0m" << endl;
	    cout << "\t./test 16 1 \033[1;90m//base 16, run convertToInt\033[0m"<<endl;
	    cout << "\t./test 2 4 \033[1;90m//base 2, run multiply\033[0m" << endl;
		return 1;
	}
	const char *check  = "\u2713";
	const char *cross  = "\u2717";
	string test_base = argv[1];
	int mode = atoi(argv[2]);
	string file;
	switch(mode){
		case 0:
			file = "testcases/compare_"+test_base+".txt";
			break;
		case 1:
			file = "testcases/convertoint_"+test_base+".txt";
			break;
		case 2:
			file = "testcases/int10_to_base_"+test_base+".txt";
			break;
		case 3:
			file = "testcases/add_"+test_base+".txt";
			break;
		case 4:
			file = "testcases/subtract_"+test_base+".txt";
			break;
		case 5:
			file = "testcases/multiply_"+test_base+".txt";
			break;
		case 6:
			file = "testcases/divide_"+test_base+".txt";
			break;
		case 7:
			file = "testcases/mod_"+test_base+".txt";
			break;
		case 8:
			file = "testcases/exponential_"+test_base+".txt";
			break;
		case 9:
			file = "testcases/modexp_"+test_base+".txt";
			break;
		default:
            if (argc < 4){
                cerr<<"\033[1;31mError:\033[0m Incorrect mode input"<<endl;
                return 1;
            }else{
                //required for auto-graders to work!
                mode = atoi(argv[3]);
                file = argv[4];
            }
	}
	ifstream ifile(file);
	if(ifile.fail()){
		cout << "\033[1;31mError:\033[0m Incorrect base input (" << test_base <<")"<< endl;
        return -1;
	}
	int base;
	string a,b,expected_result,type,symbol;
	ifile >> base;
	int failed = 0;
	int passed = 0;
	int testnum = 0;
	cout<<"======================================="<<endl;
	while (ifile >> a >> b >> expected_result){
    	try{
			BigInt first(a, base);
			BigInt second(b, base);
			BigInt actual_result;
			int compareResult = 0;
			int intresult = 0;
			string m;
			if (mode == 0){
				compareResult = first.compare(second);
				type = "comparison";
			}
			else if (mode == 1){
				intresult = first.to_int();
				type = "convert to int";
			}
			else if (mode == 2){
				int base10 = stoi(a);
				BigInt tmp(base10,base);
				actual_result = tmp;
				type = "int 10 to base "+to_string(base);
			}
			else if (mode == 3){
				actual_result = first + second;
				type = "addition";
				symbol ="+";
			}else if(mode == 4){
				actual_result = first - second;
				type = "subtraction";
				symbol ="-";
			}else if(mode == 5){
				actual_result = first * second;
				type = "multiplication";
				symbol ="*";
			}else if(mode == 6){
				actual_result = first / second;
				type = "division";
				symbol ="/";
			}else if(mode == 7){
				actual_result = first % second;
				type = "modulus";
				symbol ="%";
			}else if(mode == 8){
				actual_result = pow(first,second);
				type = "exponentiation";
				symbol ="^";
			}else if (mode == 9){
				//mod expo is using another variable (m)
				ifile >> m;
				BigInt mod(m, base);
				actual_result = modPow(first,second,mod);
				type = "modular exponentiation";
			}else{
				return -1;
			}
			//Processing Results
			if(mode > 2){
				if(mode == 9){
					//mod expo using additional variable
					if(actual_result.to_string() != expected_result){
						cout<<"\033[1;31m"<<cross<<" Failed: \033[0m("<<a<<" ^ "<<b<<") % "<<m<<" | "<<"Expected: "<<expected_result<<", Actual: "<<actual_result.to_string()<<endl;
						failed+=1;
					}else{
						cout<<"\033[1;32m"<<check<<" Passed: \033[0m("<<a<<" ^ "<<b<<") % "<<m<<endl;
						passed+=1;						
					}
				}else{
					if(actual_result.to_string() != expected_result){
						cout<<"\033[1;31m"<<cross<<" Failed: \033[0m"<<a<<" "<<symbol<<" "<<b<<" | "<<"Expected: "<<expected_result<<", Actual: "<<actual_result.to_string()<<endl;
						failed+=1;
					}else{
						cout<<"\033[1;32m"<<check<<" Passed: \033[0m"<<a<<" "<<symbol<<" "<<b<<endl;
						passed+=1;
					}
				}
			}else{
				//0 1 2 are special modes, they aren't using the second value
				if(mode == 0){
					//compare
					if(to_string(compareResult) != expected_result){
						cout<<"\033[1;31m"<<cross<<" Failed: \033[0m"<<a<<" and "<<b<<" | "<<"Expected: "<<expected_result<<", Actual: "<<compareResult<<endl;
						failed+=1;
					}else{
						cout<<"\033[1;32m"<<check<<" Passed: \033[0m"<<a<<" and "<<b<<endl;
						passed+=1;	
					}
				}else if(mode == 1){
					//to int base 10
					if(to_string(intresult) != expected_result){
						cout<<"\033[1;31m"<<cross<<" Failed: \033[0m"<<a<<" | "<<"Expected: "<<expected_result<<", Actual: "<<intresult<<endl;
						failed+=1;
					}else{
						cout<<"\033[1;32m"<<check<<" Passed: \033[0m"<<a<<endl;
						passed+=1;
					}		
				}else{
					//int base 10 to other base
					if(actual_result.to_string() != expected_result){
						cout<<"\033[1;31m"<<cross<<" Failed: \033[0m"<<a<<" | "<<"Expected: "<<expected_result<<", Actual: "<<actual_result.to_string()<<endl;
						failed+=1;
					}else{
						cout<<"\033[1;32m"<<check<<" Passed: \033[0m"<<a<<endl;
						passed+=1;		
					}			
				}
			}
			testnum+=1;
		}
		//Catch exceptions, print its message and exit program.
		catch(const exception& e){
			cout<<e.what()<<endl;
			return -1;
		}
	}
	//=======================================
	//Print Summary
	cout<<"======================================="<<endl;
	cout<<testnum<<" \033[1;36m"<<type<<"\033[0m tests for base \033[1;36m"<<base<<"\033[0m (";
	if(failed != 0){
		cout<<"\033[1;31m"<<failed<<" failed\033[0m, "<<passed<<" passed)"<<endl;
	}else{
		cout<<failed<<" failed, \033[1;32m"<<passed<<" passed\033[0m)"<<endl;
	}
	return 0;
}
