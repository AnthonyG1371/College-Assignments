#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

template <typename T>
ostream &operator <<(ostream &os, vector<T> &v) {
	os << "[";
	for (int i = 0; i < v.size(); i++)
		os << v[i] << (i < v.size()-1 ? ", " : "");
	os << "]";
	return os;
}

template <typename T>
bool contains(const vector<T> &v, T val) {
	for (int i = 0; i < v.size(); i++)
		if (v[i] == val) return true;
	return false;
}
	
int main() {
	cout << boolalpha;

	vector<int> vi;

	for (int i = 0; i < 20; i++)
		vi.push_back(i);

	cout << vi << endl;

	cout << "vi contains 15: " << contains(vi, 15) << endl;
	cout << "vi contains 23: " << contains(vi, 23) << endl;

	const int ARR_SIZE = 4;
	string arr[ARR_SIZE] = {"cat", "dog", "cow", "elephant"};

	cout << endl;

	vector<string> vs;

	for (int i = 0; i < ARR_SIZE; i++)
		vs.push_back(arr[i]);

	cout << vs << endl;

	cout << "vs contains \"dog\": " << contains(vs, string("dog")) << endl;
	cout << "vs contains \"muskrat\": " << contains(vs, string("muskrat")) << endl;

	cout << endl;

	vector<string> vs2;

	for (int i = 0; i < 10; i++) {
		ostringstream oss;
		oss << "String-" << i;
		vs2.push_back(oss.str());
	}

	cout << vs2 << endl;

	cout << "vs2 contains \"String-1\": " << contains(vs2, string("String-1")) << endl;
	cout << "vs2 contains \"String-15\": " << contains(vs2, string("String-15")) << endl;

    system("pause");
	return 0;
}

	
