
#include <string>
#include <deque>
#include <vector>
#include <iostream>

#include "circuit.h"
#include "node.h"
#include "truthTable.h"

using namespace std;

void print_sorted(deque<string> inputs);

void topological_sort(Circuit c);
