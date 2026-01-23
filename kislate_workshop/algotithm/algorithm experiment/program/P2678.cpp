#include <bits/stdc++.h>
using namespace std;

int L, N, M;	
vector<int> D;

bool check_possible(int mid) {
	int removed = 0;
	int last = 0;
	for (int i = 1; i <= N + 1; i++) {
		if (D[i] - D[last] < mid) {
			++removed;
			if (removed > M) return false;
		} else last = i;
	}
	return true;
}

int main(void){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> L >> N >> M;
	D.resize(N + 2, 0);
	D[0] = 0, D[N + 1] = L;
	for (int i = 1; i <= N; ++i) cin >> D[i];
	int mid, l = 0, r = L;
	while(l < r){
		mid = (l + r + 1) >> 1;
		if(check_possible(mid)) l = mid;
		else r = mid - 1;
	}
	cout << r << endl;
	return 0;
}

	

