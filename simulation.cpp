
#include "simulation.h"


deque<input> get_inputs(string input_filename)
{
  string in_name;
  string in_val;
  
  input current_input;
  deque<input> inputs;
  
  while (cin >> in_name >> in_val)
  {
    current_input.name = in_name;
    
    if (in_val == "0")
    {
      current_input.value = 0;
    }
    
    else
    {
      current_input.value = 1;
    }
    
    inputs.push_back(current_input);
  }
  
  return inputs;
}

void print_outputs(deque<output> outputs)
{
  cout << "*** Outputs:" << endl;
  
  while (!outputs.empty())
  {
    cout << outputs.front().name << " = ";
    cout << outputs.front().value << ", ";
    outputs.pop_front();
  }
  
  cout << endl;
  
  return;
}

void simulate(Circuit c, string input_filename)
{
  deque<input> inputs = get_inputs(input_filename);
  deque<output> outputs;
  
  
}
