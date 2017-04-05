

#include "topological.h"


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

// returns true if the fanin string comes before the node string
// in the deque
bool comes_before(string fanin, string node, deque<string> nodes)
{
  int fanin_index = 0;
  int node_index = 0;
  
  assert(contains_node(nodes, fanin));
  assert(contains_node(nodes, node));
  
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
      current_fanin_name = current_fanin[i]->getName();
      if (!comes_before(current_fanin_name, current_node_name, sorted_nodes))
      {
        return false;
      }
    }
  }
  
  return true;
}

void topological_sort(Circuit c)
{
  // a topological sort will contain all nodes in the circuit
  // all fan in nodes of a node will need to come before the actual node
  vector<Node*> all_nodes = c.getAllNodes();
  deque<string> nodes = create_name_deque(all_nodes);
  
  
  
}
