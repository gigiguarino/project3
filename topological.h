
#include <string>
#include <deque>
#include <vector>
#include <iostream>

#include "circuit.h"
#include "node.h"
#include "truthTable.h"

using namespace std;

// prints the topologically sorted nodes
void print_sorted(deque<string> nodes);

// returns true if the deque of nodes contains that string
bool contains_node(deque<string> nodes, string name);

// returns true if the fanin string comes before the node string
// in the deque of nodes
bool comes_before(string fanin, string node, deque<string> nodes);

// creates a string deque from the deque of Nodes
deque<string> create_name_deque(vector<Node*> nodes);

// checks the topological sort to make sure all fanin nodes
// come before the node they fan in to
bool check_sort(vector<Node*> all_nodes, deque<string> sorted_nodes);

// prints the names of the nodes in the deque
void print_nodes(deque<string> nodes);

// moves the thing at current_index
// to the move_to_index
void move_to_index(deque<string> &sorted_nodes, int move_to_index, int current_index, string to_add);

// topologically sorts all the nodes in the circuit
void topological_sort(vector<Node*> all_nodes);
