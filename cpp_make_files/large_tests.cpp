
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;

string dec2bin(int num, int numbits)
{
  int pow_num;
  string out_string;
  for (int i = numbits-1; i >= 0; i--)
  {
    pow_num = pow(2, i);
    if (num - pow_num >= 0)
    {
      num -= pow_num;
      out_string += "1";
    }
    else
    {
      out_string += "0";
    }  
  }    

  if (num != 0)
  {
    cout << "this shouldn't happen." << endl;
    exit(1);
  }

  return out_string;
}

int main(int argc, char *argv[])
{
  int numbits = atoi(argv[1]);
  int num1 = atoi(argv[2]);
  int num2 = atoi(argv[3]);
  string binary_string1 = dec2bin(num1, numbits);
  string binary_string2 = dec2bin(num2, numbits);

  for (int i = 0; i < numbits; i++)
  {
    stringstream sstr;
    sstr << i;
    cout << "a[" + sstr.str() + "] " + binary_string1[i] << endl;
    cout << "b[" + sstr.str() + "] " + binary_string2[i] << endl;
  } 

  return 0;
}


