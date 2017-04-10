

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
  
  for (int i = numbits - 1; i >= 0; i--)
  {
    pow2num = pow(2, i);
    
    if (num - pow2num >= 0)
    {
      num -= pow2num;
      return_string += "1";
    }
    
    else
    {
      return_string += "0";
    }
  }
  
  return return_string;
}

int main(int argc, char *argv[])
{
  assert(argc == 4);
  
  int numbits = atoi(argv[1]);
  int num1 = atoi(argv[2]);
  int num2 = atoi(argv[3]);

  string input1 = dec2bin(num1, numbits);
  string input2 = dec2bin(num2, numbits);
  
  cout << input1 << endl;
  cout << input2 << endl;
  
  return 0;
}
