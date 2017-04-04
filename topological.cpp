

#include "topological.h"


void print_sorted(deque<string> inputs)
{
  cout << "*** Topological order:" << endl;
  while (!inputs.empty())
  {
    cout << inputs.front() << " ";
    inputs.pop_front();
  }
  
  cout << endl;
  return;
}

void topological_sort(Circuit c)
{
  deque<string> sorted_inputs;
  
}
