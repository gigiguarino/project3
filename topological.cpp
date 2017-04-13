

#include "topological.h"


// prints the sorted nodes
void print_sorted(deque<string> nodes)
{
  cout << "*** Topological order:" << endl;
  while (!nodes.empty())
  {
    cout << nodes.front() << " ";
    nodes.pop_front();
  }
  
  cout << endl;
  return;
}

// returns true if nodes contains the node with the following name
bool contains_node(deque<string> nodes, string name)
{
  for (int i = 0; i < int(nodes.size()); i++)
  {
    if (nodes[i] == name)
    {
      // contains it
      return true;
    }
  }
  
  // doesn't contain it
  return false;
}

// returns index of node with the following name
int get_index(deque<string> nodes, string name)
{
  for (int i = 0; i < int(nodes.size()); i++)
  {
    if (nodes[i] == name)
    {
      return i;
    }
  }
  
  cerr << "this node should be contained in the deque." << endl;
  return 0;
}

// returns true if the fanin string comes before the node string
// in the deque
bool comes_before(string fanin, string node, deque<string> nodes)
{
  int fanin_index = 0;
  int node_index = 0;
  
  if (!contains_node(nodes, fanin) || !contains_node(nodes, node))
  {
    return false;
  }
  
  for (int i = 0; i < int(nodes.size()); i++)
  {
    if (nodes[i] == fanin)
    {
      fanin_index = i;
    }
    
    if (nodes[i] == node)
    {
      node_index = i;
    }
  }
  
  return fanin_index < node_index;
}

// creates a deque of node names from the vector of nodes
deque<string> create_name_deque(vector<Node*> nodes)
{
  deque<string> return_deque;
  for (int i = 0; i < int(nodes.size()); i++)
  {
    return_deque.push_back(nodes[i]->getName());
  }
  
  return return_deque;
}

// returns true if all fanin nodes come before their nodes
// false otherwise
bool check_sort(vector<Node*> all_nodes, deque<string> sorted_nodes)
{
  vector<Node*> current_fanin;
  string current_node_name;
  string current_fanin_name;
  
  for (int i = 0; i < int(all_nodes.size()); i++)
  {
    current_fanin = all_nodes[i]->getFanin();
    current_node_name = all_nodes[i]->getName();
    for (int j = 0; j < int(current_fanin.size()); j++)
    {
      current_fanin_name = current_fanin[j]->getName();
      if (!comes_before(current_fanin_name, current_node_name, sorted_nodes))
      {
        return false;
      }
    }
  }
  
  return true;
}

// prints the names of the nodes in the deque
// used for debugging purposes
void print_nodes(deque<string> nodes)
{
  for (int i = 0; i < int(nodes.size()); i++)
  {
    cout << nodes[i] << endl;
  }
  
  return;
}

void move_to_index(deque<string> &sorted_nodes, int move_to_index, int current_index, string to_add)
{
  // remove thing at current_index and all of its fan in nodes
  // this index is greater than the move_to_index
  // now insert this thing at the move_to_index - 1
  sorted_nodes.erase(sorted_nodes.begin() + current_index);
  sorted_nodes.insert(sorted_nodes.begin() + move_to_index, to_add);
  return;
}


void topological_sort(vector<Node*> all_nodes)
{
  // a topological sort will contain all nodes in the circuit
  // all fan in nodes of a node will need to come before the actual node
  deque<string> sorted_nodes;
  
  vector<Node*> current_fanin;
  int current_index = 0;
  int other_index = 0;
  
  // for each intermediate node, adds it fanin before the actual node
  // check if they are already in the deque beforehand
  while (!check_sort(all_nodes, sorted_nodes))
  {
    for (int i = 0; i < int(all_nodes.size()); i++)
    {
      current_fanin = all_nodes[i]->getFanin();
      
      // need to check if a fan in node is already in the list
      // move it before the output that it is a fan in for
      
      if (!contains_node(sorted_nodes, all_nodes[i]->getName()))
      {
        // sorted nodes doesn't contain this output node
        current_index = int(sorted_nodes.size()) - 1;
        sorted_nodes.push_back(all_nodes[i]->getName());
      }
      
      else
      {
        current_index = get_index(sorted_nodes, all_nodes[i]->getName());
      }
      
      for (int j = 0; j < int(current_fanin.size()); j++)
      {
        if (!contains_node(sorted_nodes, current_fanin[j]->getName()))
        {
          // sorted nodes doesn't contain this fan in node
          // insert it before the current_index
          sorted_nodes.insert(sorted_nodes.begin()+current_index, current_fanin[j]->getName());
        }
        
        else
        {
          other_index = get_index(sorted_nodes, current_fanin[j]->getName());
          if (other_index >= current_index)
          {
            // make sure that this currentfan and all of its fanins are moved
            // before this current_index
            move_to_index(sorted_nodes, current_index, other_index, current_fanin[j]->getName());
          }
        }
      }
    }
  }

  
  if (check_sort(all_nodes, sorted_nodes))
  {
    print_sorted(sorted_nodes);
    return;
  }
  
  else
  {
    //print_sorted(sorted_nodes);
    cerr << "failed. :/" << endl;
    return;
  }
}
