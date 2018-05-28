#include <iostream>
#include <queue>

using namespace std;

int main() {
	int n;
	cin >> n;

	int *a = new int[n];

	for (int i = 0; i < n; i++)
		cin >> a[i];

	priority_queue<int> pq;
	
	for (int i = 0; i < n; i++)
	{
		pq.push(a[i]);
    }
	
	for (int i = n-1; i >= 0; i--) {
		a[i] = pq.top();
		pq.pop();
	}

	for (int i = 0; i < n; i++) 
		cout << a[i] << " ";
	
	system("pause");
	return 0;
}
