
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <deque>
using namespace std;


void print_binary(deque<int> binary)
{
  for (int i = 0; i < int(binary.size()); i++)
  {
    cout << binary[i];
  }
  cout << endl;
  
  return;
}

int bin2dec_unsigned(deque<int> binary, int numbits)
{
  int num = 0;
  int return_num = 0;
  
  for (int i = 0; i < numbits; i++)
  {
    num = pow(2,i);
    
    if (binary[i] == 1)
    {
      return_num += num;
    }
  }
  
  return return_num;
}

int bin2dec_signed(deque<int> binary, int numbits)
{
  int sign = binary.back();
  deque<int> new_binary;
  
  
  for (int i = 0; i < numbits; i++)
  {
    new_binary.push_back(0);
  }
  
  if (sign == 1)
  {
    for (int i = 0; i < numbits - 1; i++)
    {
      if (binary[i] == 1)
      {
        new_binary[i] = 0;
      }
      
      else if (binary[i] == 0)
      {
        new_binary[i] = 1;
      }
    }

    return (bin2dec_unsigned(new_binary, numbits) + 1)*(-1);
  }
  
  else
  {
    return bin2dec_unsigned(binary, numbits);
  }
}




int main(int argc, char *argv[])
{
  // inputs will be two files
  // one of them will be the input which we will need to calculate the correct output
  // the other will be the output we got from running the program
  // we will output "FAILED" if this ever fails
  // we will output nothing if it passes
  // will check in shell script if anything was output
  
  assert (argc == 5);
  string type = argv[1];
  int numbits = atoi(argv[2]);
  string file1 = argv[3];
  string file2 = argv[4];
  
  ifstream infile1(file1);
  ifstream infile2(file2);
  
  string trash;
  int bit = 0;
  deque<int> binary1, binary2, binary3;
  
  
  
  for (int i = 0; i < numbits; i++)
  {
    binary1.push_back(0);
    binary2.push_back(0);
    if (type == "-add" || type == "-sub")
    {
      binary3.push_back(0);
    }
  }
  
  if (type == "-mult")
  {
    for (int i = 0; i < numbits*2; i++)
    {
      binary3.push_back(0);
    }
  }
  
  // for the first input file (the inputs)
  // we can go every other line to create the values we are adding together
  for (int i = 0; i < numbits; i++)
  {
    getline(infile1, trash);
    bit = trash[5] - '0';
    binary1[i] = bit;
    getline(infile1, trash);
    bit = trash[5] - '0';
    binary2[i] = bit;
  }
  
  int num1;
  int num2;
  int output1 = 0;
  
  if (type == "-add")
  {
    num1 = bin2dec_unsigned(binary1, numbits);
    num2 = bin2dec_unsigned(binary2, numbits);
    
    getline(infile1, trash);
    bit = trash[4] - '0';
    
    if (bit == 1)
    {
      // cin = 1
      output1 = num1 + num2 + 1;
    }
    
    else
    {
      // cin = 0
      output1 = num1 + num2;
    }
  }
  
  else if (type == "-sub")
  {
    num1 = bin2dec_signed(binary1, numbits);
    num2 = bin2dec_signed(binary2, numbits);
    output1 = num1 - num2;
    
    if (output1 < pow(2, numbits - 1)*(-1))
    {
      output1 += pow(2, numbits);
    }
    
    if (output1 > pow(2, numbits - 1) - 1)
    {
      output1 -= pow(2, numbits);
    }
  }
  
  else if (type == "-mult")
  {
    num1 = bin2dec_unsigned(binary1, numbits);
    num2 = bin2dec_unsigned(binary2, numbits);
    output1 = num1 * num2;
  }
  
  else
  {
    cerr << "unrecognizable command." << endl;
  }
  
  getline(infile2, trash);
  getline(infile2, trash);
  getline(infile2, trash);
  
  int current_index = 0;
  string in_string;
  bool c = false;
  
  if (type == "-add")
  {
    infile2 >> trash >> trash >> in_string;
    
    if (in_string[0] == '0')
    {
      c = false;
    }
    
    else if (in_string[0] == '1')
    {
      c = true;
    }
  }
  
  while (infile2 >> in_string)
  {
    if (in_string[0] == '0')
    {
      binary3[current_index] = 0;
      current_index += 1;
    }
    
    else if (in_string[0] == '1')
    {
      binary3[current_index] = 1;
      current_index += 1;
    }
  }

  
  int output2 = 0;
  int c_num = pow(2, numbits);
  
  if (type == "-add")
  {
    if (c)
    {
      output2 = bin2dec_unsigned(binary3, numbits) + c_num;
    }
    
    else
    {
      output2 = bin2dec_unsigned(binary3, numbits);
    }
  }
  
  else if (type == "-sub")
  {
    output2 = bin2dec_signed(binary3, numbits);
  }
  
  else if (type == "-mult")
  {
    output2 = bin2dec_unsigned(binary3, numbits*2);
  }
  
  //cout << output1 << endl;
  //cout << output2 << endl;
  
  if (output1 != output2)
  {
    cout << "FAILED" << endl;
  }
  
  return 0;
}
