#ifndef SEQCLASS_H
#define SEQCLASS_H

class Sequence 
{
    public:
        Sequence(int i) : size(i) 
        {
            arr[0] = 0;
            arr[1] = 4;
            arr[2] = 1;
            arr[3] = 3;
            arr[4] = 2;
        }
        int getsize();
        int get(int);
        void set(int, int);
        void add_back(int);
        void remove_back();
        void add_front(int);
        void remove_front();
        int front();
        int back();
        int find(int);
        bool search(int);
        void sort();

    private:
        static const int CAPACITY = 100;
	    int size;
	    int arr[CAPACITY];
};

#endif
