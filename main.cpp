#include "circuit.h"
#include "topological.h"
#include "simulation.h"
#include <math.h>

#include <utility>

using namespace std;

void usage(const char* exename);

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
        vector<Node*> all_nodes = c.getAllNodes();
        topological_sort(all_nodes);
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
        vector<Node*> all_nodes = c.getSpecificNodes();
        vector<Node*> POs = c.getPOs();
        simulate(all_nodes, inputFile, POs);
      }
      
      else
      {
        cout << "option -simulate requires two additional arguments." << endl;
        usage(argv[0]);
      }
    }
    
    else
    {
      cout << "unrecognized command." << endl;
      usage(argv[0]);
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
  cout << endl;
  
  exit(0);
}





