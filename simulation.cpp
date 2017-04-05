
#include "simulation.h"

// TO DO:
// make some sort of structure that can hold every node and its value
// this way i can just look up nodes and get their values easily


deque<reg> get_inputs(string input_filename)
{
  string in_name;
  string in_val;
  
  reg current_input;
  deque<reg> inputs;
  
  while (cin >> in_name >> in_val)
  {
    current_input.name = in_name;
    current_input.inputs.push_back("");
    
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

void print_outputs(deque<reg> outputs)
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

bool has_node(deque<reg> nodes, string name)
{
  for (int i = 0; i < int(nodes.size()); i++)
  {
    if (nodes[i].name == name)
    {
      return true;
    }
  }
  
  return false;
}

int get_value(deque<reg> nodes, string name)
{
  for (int i = 0; i < int(nodes.size()); i++)
  {
    if (nodes[i].name == name)
    {
      return nodes[i].value;
    }
  }
  
  cerr << "error: the node should be in the deque." << endl;
  return 0;
}

reg get_reg(deque<reg> nodes, string name)
{
  for (int i = 0; i < int(nodes.size()); i++)
  {
    if (nodes[i].name == name)
    {
      return nodes[i];
    }
  }
  
  reg empty;
  // this should be an error
  cerr << "error: the node should be in the deque." << endl;
  return empty;
}

int find_tt_entry(string entry, TruthTable tt)
{
  vector<vector<truthType> > logic = tt.getLogic();
  truthType current_type = ZERO;
  bool found = true;
  
  // make sure that the amount of inputs matches
  // the truth table entries
  assert(entry.size() == logic[0].size());
  
  for (int i = 0; i < int(logic.size()); i++)
  {
    found = true;
    
    for (int j = 0; j < int(logic[i].size()); j++)
    {
      if (entry[j] == '0')
      {
        current_type = ZERO;
      }
      
      else if (entry[j] == '1')
      {
        current_type = ONE;
      }
      
      else
      {
        cerr << "error: invalid binary string character." << endl;
        return 0;
      }
      
      // if the truth table has a zero whereas we have a one
      // or if the truth table has a one whereas we have a zero
      if ((logic[i][j] == ZERO && current_type == ONE) ||
          (logic[i][j] == ONE && current_type == ZERO))
      {
        found = false;
      }
    }
    
    // a matching truth table entry was found
    if (found)
    {
      return 1;
    }
  }
  
  // no matching truth table entries were found
  return 0;
}

int get_value(deque<string> inputs, TruthTable tt, deque<reg> nodes)
{
  // since i add the fanin inputs from the Node* vector into the
  // nodes deque in the correct order i should be able to just make a
  // string of the input's values and find it in the truth table
  
  string entry = "";
  string tt_out;
  
  // make truth table entry
  for (int i = 0; i < int(inputs.size()); i++)
  {
    if (get_value(nodes, inputs[i]) == 0)
    {
      entry += "0";
    }
    
    else
    {
      entry += "1";
    }
  }
  
  return find_tt_entry(entry, tt);
}

deque<string> create_string_deque(vector<Node*> fanin, deque<reg> nodes)
{
  deque<string> return_deque;
  
  for (int i = 0; i < int(fanin.size()); i++)
  {
    return_deque.push_back(fanin[i]->getName());
  }
  
  return return_deque;
}

deque<reg> find_nodes(Circuit c, deque<reg> nodes)
{
  // based on the values we have in our node deque
  // create a new deque of nodes we can now find the value of
  
  vector<Node*> internal_nodes = c.getInternalNodes();
  vector<Node*> current_inputs;
  deque<reg> new_nodes;
  reg current_node;
  
  bool add = false;
  
  // if all of an internal node's fanin nodes are covered by our nodes deque
  // then we can get its value and add it to our internal deque
  
  for (int i = 0; i < int(internal_nodes.size()); i++)
  {
    current_inputs = internal_nodes[i]->getFanin();
    add = true;
    
    for (int j = 0; j < int(current_inputs.size()); j++)
    {
      if (!has_node(nodes, current_inputs[i]->getName()))
      {
        add = false;
      }
    }
    
    if (add)
    {
      current_node.inputs = create_string_deque(current_inputs, nodes);
      current_node.name = internal_nodes[i]->getName();
      current_node.value = get_value(current_node.inputs, internal_nodes[i]->getTT(), nodes);
      new_nodes.push_back(current_node);
    }
  }
  
  return new_nodes;
}

void simulate(Circuit c, string input_filename)
{
  deque<reg> inputs = get_inputs(input_filename);
  deque<reg> intermediate;
  deque<reg> outputs;
  
  bool done = false;
  
  while (!done)
  {
    
  }
  
  
  return;
}


