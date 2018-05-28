// File: prg3_5.cpp
// the program evaluates Fibonacci number 43 using
// an iterative and a recursive algorithm. the iterative
// algorithm executes in a fraction of a second. the program
// uses a timer object to output the computation time
// of the very inefficient recursive algorithm (exponential
// running time)

#include <iostream>

#include "d_timer.h"

using namespace std;

// prototypes for the recursive and iterative versions
int fib(int n);
int fibiter(int n);

int main()
{
	timer t;			// time recursive version
	int fib_43;
	
	// evaluate fib() using iteration and recursion
	cout << "Value of fib(43) by iteration is ";
	cout << fibiter(43) << endl;

	cout << "Value of fib(43) by recursion is ";
	// start/stop timer object for recursive process
	t.start();
	fib_43 = fib(43);
	t.stop();

	cout << fib_43 << endl;
	cout << "   Time required by recursive version is " << t.time() 
  << " sec" <<endl;

#include <pause.h>

	return 0;
}

int fib(int n)
{
	if (n <= 1)								// stopping conditions
		return n;
	else
		return fib(n-1) + fib(n-2);	// recursive step
}

int fibiter(int n)
{
	// integers to store previous two Fibonacci value 
	int oneback = 1, twoback = 0, current;
	int i;

	// return is immediate for first two numbers
	if (n <= 1)
		return n;
	else
		// compute successive terms beginning at 3
		for (i = 2; i <= n; i++)
		{
			current = oneback + twoback;
			twoback = oneback;	// update for next calculation
			oneback = current;
		}

	return current;			
}

/*
Run:

Value of fib(43) by iteration is 433494437
Value of fib(43) by recursion is 433494437
   Time required by recursive version is 90.953 sec
*/
