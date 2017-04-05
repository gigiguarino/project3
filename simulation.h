
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

void simulate(Circuit c, string input_filename);
