#ifndef NODE_UTILS_H
#define NODE_UTILS_H

#include <iostream>

#include "node.h"

int length(const Node *head);
void insert(Node *nodeP, const EType &val);
void removeAfter(Node *nodeP);
void removeFront(Node *&head);
bool newremove(Node *&head, const EType &data);
void clear(Node *&head);
Node *find(Node *head, const EType &val);
bool contains(Node *head, const EType &val);
Node *copy(const Node *head);
void print(std::ostream &os, const Node *head);

#endif

