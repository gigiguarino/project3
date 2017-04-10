
#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;

// returns a binary string that corresponds to the following num
string dec2bin(int num, int numbits)
{
  string return_string = "";
  int pow2num = 0;
  
  for (int i = 0; i < numbits; i++)
  {
    return_string += " ";
  }
  
  for (int i = numbits - 1; i >= 0; i--)
  {
    pow2num = pow(2, i);
    
    if (num - pow2num >= 0)
    {
      num -= pow2num;
      return_string[i] = '1';
    }
    
    else
    {
      return_string[i] = '0';
    }
  }
  
  return return_string;
}

int main(int argc, char *argv[])
{
  // input file form:
  // name value
  // i[0] 0
  // i[1] 0
  
  // command line inputs:
  // numbits input1 input2
  
  assert(argc == 4);
  
  int numbits = atoi(argv[1]);
  int num1 = atoi(argv[2]);
  int num2 = atoi(argv[3]);
  
  string input1 = dec2bin(num1, numbits);
  string input2 = dec2bin(num2, numbits);
  
  for (int i = 0; i < numbits; i++)
  {
    stringstream sstr;
    sstr << i;
    
    cout << "a[" << sstr.str() << "] ";
    cout << input1[i] << endl;
    cout << "b[" << sstr.str() << "] ";
    cout << input2[i] << endl;
  }
  
  return 0;
}
