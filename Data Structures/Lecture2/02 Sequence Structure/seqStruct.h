#ifndef SEQSTRUCT_H
#define SEQSTRUCT_H

const int CAPACITY = 5;

struct Sequence 
{
	int size;
	int arr[CAPACITY];
};

void initialize(Sequence &);
int get(Sequence &, int);
void set(Sequence &, int, int);
void add_back(Sequence &, int);
void remove_back(Sequence &);
void add_front(Sequence &, int);
void remove_front(Sequence &);
int front(const Sequence &);
int back(const Sequence &);
int find(Sequence &, int);
bool search(Sequence &, int);
void sort(Sequence &);

#endif
