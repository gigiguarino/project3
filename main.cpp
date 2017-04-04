#include "circuit.h"
#include <math.h>

#include <utility>

using namespace std;

void usage(const char* exename);

void print_info(Circuit c);

int main(int argc, char **argv)
{
  // parsing inputs
  if (argc < 2)
  {
    usage(argv[0]);
  }
  
  for (int i = 1; i < argc; ++i)
  {
    if (argv[i] == string("-h") || argv[i] == string("-help"))
    {
      usage(argv[0]);
    }
    
    else if (argv[i] == string("-topoSort"))
    {
      if (i + 1 < argc)
      {
        string inFilename = string(argv[++i]);
        Circuit c(inFilename);
        topological_sort(c);
      }
      
      else
      {
        cout << "option -topoSort requires an additional argument." << endl;
        usage(argv[0]);
      }
    }
    
    else if (argv[i] == string("-simulate"))
    {
      if (i + 2 < argc)
      {
        string inFilename = string(argv[++i]);
        Circuit c(inFilename);
        string inputFile(argv[++i]);
        simulate(c, inputFile);
      }
      
      else
      {
        cout << "option -simulate requires two additional arguments." << endl;
        usage(argv[0]);
      }
    }
    
    else if (argv[i] == string("-print"))
    {
      if (i + 1 < argc)
      {
        string inFilename = string(argv[++i]);
        Circuit c(inFilename);
        print_info(c);
      }
      
      else
      {
        cout << "option -print requires one additional argument." << endl;
        usage(argv[0]);
      }
    }
    
  }
  
  return 0;
}

void usage(const char* exename)
{
  cout << "Usage: " << exename << " <options> " << endl;
  cout << "-h or -help                     prints out this help message. " << endl;
  cout << "-topoSort <inFile>              prints a topological ordering of the circuit in <inFile>. " << endl;
  cout << "-simulate <inFile> <inputs>     simulates the circuit in <inFile> with the inputs in <inputs>." << endl;
  cout << "-print <inFile>                 prints the values of this blif's circuit and nodes." << endl;
  cout << endl;
  
  exit(0);
}

void print_info(Circuit c)
{
  cout << "Printing whole circuit: " << endl;
  c.print();
  cout << endl << endl;
  
  vector<Node*> primary_inputs = c.getPIs();
  vector<Node*> primary_outputs = c.getPOs();
  
  cout << "Primary input nodes: " << endl;
  while (!primary_inputs.empty())
  {
    primary_inputs.back().print();
    primary_inputs.pop_back();
  }
  cout << endl;
  
  cout << "Primary output nodes: " << endl;
  while (!primary_outputs.empty())
  {
    primary_outputs.back().print();
    primary_outputs.pop_back();
  }
  cout << endl;
  
  return;
}





