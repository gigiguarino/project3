
#include "simulation.h"


// gets the inputs from the input file
// create a deque with their values and names
deque<reg> get_inputs(string input_filename)
{
  string in_name;
  string in_val;
  
  reg current_input;
  deque<reg> inputs;
  
  ifstream infile(input_filename);
  
  while (infile >> in_name >> in_val)
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

// prints the final output deque and their values
void print_outputs(deque<reg> outputs)
{
  cout << "*** Outputs:" << endl;
  
  for (int i = 0; i < int(outputs.size()); i++)
  {
    cout << outputs[i].name << " = ";
    cout << outputs[i].value;
    if (i != int(outputs.size()) - 1)
    {
       cout << ", ";
    }
  }
  
  cout << endl;
  
  return;
}

// returns true if the deque contains the node
// with the same name
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

// returns the value of the node in the deque
// with the same name
int get_value(deque<reg> nodes, string name)
{
  for (int i = 0; i < int(nodes.size()); i++)
  {
    if (nodes[i].name == name)
    {
      return nodes[i].value;
    }
  }
  
  cerr << "error(1): the node should be in the deque." << endl;
  return 0;
}

// returns the whole reg with the same name
// in the node deque
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
  cerr << "error(2): the node should be in the deque." << endl;
  return empty;
}

// finds the value of the entry in the truth table
// that corresponds to the binary string given
int find_tt_entry(string entry, TruthTable tt)
{
  vector<string> logic = tt.getLogicString();
  bool found = true;
  
  // make sure that the amount of inputs matches
  // the truth table entries
  assert(entry.size() == logic[0].size());
  
  
  
  for (int i = 0; i < int(logic.size()); i++)
  {
    found = true;
    
    for (int j = 0; j < int(entry.size()); j++)
    {
      // if the truth table has a zero whereas we have a one
      // or if the truth table has a one whereas we have a zero
      if ((logic[i][j] == '0' && entry[j] == '1') ||
          (logic[i][j] == '1' && entry[j] == '0'))
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

// makes a binary string of the inputs and their values
// finds it in the truth table and gets the value
int get_value(deque<string> inputs, TruthTable tt, deque<reg> nodes)
{
  // since i add the fanin inputs from the Node* vector into the
  // nodes deque in the correct order i should be able to just make a
  // string of the input's values and find it in the truth table
  
  string entry = "";
  
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

// creates a deque of strings for all of the nodes
deque<string> create_string_deque(vector<Node*> fanin)
{
  deque<string> return_deque;
  
  for (int i = 0; i < int(fanin.size()); i++)
  {
    return_deque.push_back(fanin[i]->getName());
  }
  
  return return_deque;
}

// finds new nodes in the circuit that we are able to get the value of
deque<reg> find_nodes(vector<Node*> &all_nodes, deque<reg> nodes)
{
  // based on the values we have in our node deque
  // create a new deque of nodes we can now find the value of

  deque<reg> new_nodes;
  reg current_node;
  bool add = false;
  
  deque<int> index_to_remove;
  
  // if all of an internal node's fanin nodes are covered by our nodes deque
  // then we can get its value and add it to our internal deque
  
  for (int i = 0; i < int(all_nodes.size()); i++)
  {
    vector<Node*> current_inputs = all_nodes[i]->getFanin();
    add = true;
    cout << all_nodes[i]->getName() << endl;
    
    if (all_nodes[i]->getType() != ONE_NODE &&
        all_nodes[i]->getType() != ZERO_NODE)
    {
      for (int j = 0; j < int(current_inputs.size()); j++)
      {
        if (!has_node(nodes, current_inputs[j]->getName()))
        {
          add = false;
        }
      }
      
      if (add)
      {
        const TruthTable &theTT = all_nodes[i]->getTT();
        current_node.inputs = create_string_deque(current_inputs);
        current_node.name = all_nodes[i]->getName();
        current_node.value = get_value(current_node.inputs, theTT, nodes);
        new_nodes.push_back(current_node);
        index_to_remove.push_back(i);
        //cout << all_nodes[i]->getName() << endl;
      }
    }
  }
  cout << endl;
  print_nodes(nodes);
  cout << endl;
  
  int current_index = 0;
  while (!index_to_remove.empty())
  {
    current_index = index_to_remove.front();
    index_to_remove.pop_front();
    all_nodes.erase(all_nodes.begin() + current_index);
    for (int i = 0; i < int(index_to_remove.size()); i++)
    {
      index_to_remove[i] -= 1;
    }
  }
  
  
  return new_nodes;
}

// adds the new nodes to the old nodes
deque<reg> add_new_nodes(deque<reg> old_nodes, deque<reg> new_nodes)
{
  for (int i = 0; i < int(new_nodes.size()); i++)
  {
    // only adds the node if it isn't already in the deque
    if (!has_node(old_nodes, new_nodes[i].name))
    {
      old_nodes.push_back(new_nodes[i]);
    }
  }
  
  return old_nodes;
}

// returns true if we have all of the output nodes in our nodes deque
// indicating we can finish
bool has_all_output_nodes(deque<reg> nodes, deque<string> output_names)
{
  for (int i = 0; i < int(output_names.size()); i++)
  {
    if (!has_node(nodes, output_names[i]))
    {
      return false;
    }
  }
  
  return true;
}

// creates the output nodes from the nodes in the deque
deque<reg> create_output_nodes(deque<reg> nodes, deque<string> output_names)
{
  deque<reg> return_deque;
  for (int i = 0; i < (output_names.size()); i++)
  {
    return_deque.push_back(get_reg(nodes, output_names[i]));
  }
  
  return return_deque;
}

// prints the nodes in the deque
// used for debugging
void print_nodes(deque<reg> nodes)
{
  for (int i = 0; i < int(nodes.size()); i++)
  {
    cout << nodes[i].name <<  " " << nodes[i].value << endl;
  }
  
  return;
}

deque<reg> add_ones_zeros(vector<Node*> all_nodes)
{
  deque<reg> return_deque;
  reg current;
  
  for (int i = 0; i < int(all_nodes.size()); i++)
  {
    if (all_nodes[i]->getType() == ONE_NODE)
    {
      current.name = all_nodes[i]->getName();
      current.value = 1;
      return_deque.push_back(current);
    }
    
    else if (all_nodes[i]->getType() == ZERO_NODE)
    {
      current.name = all_nodes[i]->getName();
      current.value = 0;
      return_deque.push_back(current);
    }
  }
  return return_deque;
}

// simulates the circuit with the inputs given in the input file
void simulate(vector<Node*> all_nodes, string input_filename, vector<Node*> POs)
{
  deque<reg> nodes = get_inputs(input_filename);
  deque<reg> new_nodes;
  deque<reg> outputs;
  
  // create a deque of the output node's names
  deque<string> output_names = create_string_deque(POs);
  
  // add all one nodes and zero nodes into the nodes deque
  // because we already know their values
  new_nodes = add_ones_zeros(all_nodes);
  nodes = add_new_nodes(nodes, new_nodes);
  
  bool done = false;
  
  while (!done)
  {
    new_nodes = find_nodes(all_nodes, nodes);
    nodes = add_new_nodes(nodes, new_nodes);
    if (has_all_output_nodes(nodes, output_names))
    {
      done = true;
    }
  }
  
  outputs = create_output_nodes(nodes, output_names);
  print_outputs(outputs);
  
  return;
}


