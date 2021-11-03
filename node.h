#pragma once
#include <iostream>
#include "error_code.h"
using namespace std;
typedef double Node_entry;

struct Node {
//  data members
   Node_entry entry;
   Node *next;
//  constructors
   Node();
   Node(Node_entry item, Node *add_on = NULL);
};