#include <bits/stdc++.h>
using namespace std;

long long move_count = 0;
void hanoi_solve(int n, char source, char auxiliary, char destination){
	if (n == 1){
		++move_count;
		cout << move_count << ": Move disk " << n << " from " << source << " to " << destination << endl;
		return;
	}
	hanoi_solve(n - 1, source, destination, auxiliary);
	++move_count;
	cout << move_count << ": Move disk " << n << " from " << source << " to " << destination << endl;
	hanoi_solve(n - 1, auxiliary, source, destination);
}

int main(void){
	int n;
	cout << "Please input the nums of disks: ";
	cin >> n;
	long long total_moves = (1LL << n) - 1;
	hanoi_solve(n, 'A', 'B', 'C');
	cout << "move_count " << move_count << endl;
	return 0;
}
		 
			
			 
