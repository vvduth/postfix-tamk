#include "node.h"
#include "error_code.h"
#include "Utility.h"

Node::Node()
{
   next = NULL;
}


Node::Node(Node_entry item, Node *add_on)
{
   entry = item;
   next = add_on;
}