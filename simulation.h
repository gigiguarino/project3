
#include <string>
#include <deque>
#include <vector>
#include <iostream>

#include "circuit.h"
#include "node.h"
#include "truthTable.h"

using namespace std;

struct reg {
  deque<string> inputs;
  string name; // name of input
  int value; // 1 or 0
};

deque<reg> get_inputs(string input_filename);

void print_outputs(deque<reg> outputs);

bool has_node(deque<reg> nodes, string name);

int get_value(deque<reg> nodes, string name);

reg get_reg(deque<reg> nodes, string name);

int find_tt_entry(string entry, TruthTable tt);

int get_value(deque<string> inputs, TruthTable tt, deque<reg> nodes);

deque<string> create_string_deque(vector<Node*> fanin, deque<reg> nodes);

deque<reg> find_nodes(Circuit c, deque<reg> nodes);

deque<reg> add_new_nodes(deque<reg> old_nodes, deque<reg> new_nodes);

bool has_all_output_nodes(deque<reg> nodes, deque<string> output_names);

deque<reg> create_output_nodes(deque<reg> nodes, deque<string> output_names);

void simulate(Circuit c, string input_filename);
