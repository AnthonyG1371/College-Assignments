#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class binary_tree 
{
public:
	class node;
	binary_tree();
	void addRoot(const string &data);
	void addLeft(node *nd, const string &data);
	void addRight(node *nd, const string &data);

	node *getRoot();
	node *getNode(node *node);

	string getData(node *node);
	bool isEmpty();

	void print(ostream &os=cout); 
	static binary_tree read(const char *filename);
	void write(const char *filename);
private:
	void print(ostream &os, node *nd, int indent);
	static node *read(ifstream &ifs);
	void write(ofstream &ofs, node *nd, int depth);
	node *root;
};

struct binary_tree::node 
{
	node(const string &data);
	string data;
	node *left, *right;
};

#endif
