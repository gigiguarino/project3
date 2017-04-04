
#include <string>
#include <deque>
#include <iostream>

using namespace std;

struct input {
  string name; // name of input
  int value; // 1 or 0
};

struct output {
  string name; // name of output
  int value; // 1 or 0
}

deque<input> get_inputs(string input_filename);

void print_outputs(deque<output> outputs);

void simulate(Circuit c, string input_filename);
