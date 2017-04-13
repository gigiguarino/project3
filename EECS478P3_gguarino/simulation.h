
#include <string>
#include <deque>
#include <vector>
#include <iostream>
#include <fstream>

#include "circuit.h"
#include "node.h"
#include "truthTable.h"

using namespace std;

struct reg {
  deque<string> inputs;
  string name; // name of input
  int value; // 1 or 0
};

// reads the inputs and their values from the input file
deque<reg> get_inputs(string input_filename);

// prints the outputs
void print_outputs(deque<reg> outputs);

// returns true if that deque contains the node with that name
bool has_node(deque<reg> nodes, string name);

// gets the value of the node with the following name
// only enters this function if we know for sure the deque contains that node
int get_value(deque<reg> nodes, string name);

// gets the reg/node that is has the following name
// only enters this function if we know for sure the deque contains that node
reg get_reg(deque<reg> nodes, string name);

// returns the truth table entry that looks like the following string
// returns a 1 if found, a zero otherwise
int find_tt_entry(string entry, TruthTable tt);

// returns the value in the truth table that corresponds to the inputs
// and their values, returns either a 1 or a 0
int get_value(deque<string> inputs, TruthTable tt, deque<reg> nodes);

// creates a deque of strings from the deque of nodes
// a deque of all the node names
deque<string> create_string_deque(vector<Node*> fanin);

// loops through the circuit and finds as many node values as possible
// until we have all the output node's values
deque<reg> find_nodes(vector<Node*> &all_nodes, deque<reg> nodes);

// checks if string is the name of an output node
bool is_output(string name, deque<string> output_names);

// sorts outputs to print in numerical order
deque<reg> sort_outputs(deque<reg> in_deque, deque<string> output_names);

// add the new nodes we have found into the larger node deque
deque<reg> add_new_nodes(deque<reg> old_nodes, deque<reg> new_nodes, 
    int &num_output_nodes, deque<string> output_names);

// returns true if we have all output nodes in the deque
bool has_all_output_nodes(deque<reg> nodes, deque<string> output_names);

// creates a deque of output nodes from their names in the output names string
deque<reg> create_output_nodes(deque<reg> nodes, deque<string> output_names);

// prints the names and values of the nodes
void print_nodes(deque<reg> nodes);

// prints the names of the output nodes
void print_output_names(deque<string> output_names);

// simulates circuit c with the inputs declared in the input file
void simulate(vector<Node*> all_nodes, string input_filename, vector<Node*> POs);
