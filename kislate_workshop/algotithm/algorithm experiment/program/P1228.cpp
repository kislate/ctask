#include <bits/stdc++.h>
#include <iostream>
using namespace std;
/*
1, 2
3, 4
*/
// check which quadrant the (x, y) is in
int check(int size, int start_x, int start_y, int x, int y){
	int half_x = start_x + size / 2;
	int half_y = start_y + size / 2;
	if (x < half_x && y < half_y){
		return 1;
	}
	else if (x < half_x && y >= half_y){
		return 2;
	}
	else if (x >= half_x && y < half_y){
		return 3;
	}
	else{
		return 4;
	}
}

void fill(int size, int start_x, int start_y, int x, int y){
	int quad = check(size, start_x, start_y, x, y);
	switch(quad){
		case 1:
			// fill 2, 3, 4
			cout << start_x + size / 2 << " " << start_y + size / 2 << " " << 1 << endl;
			if (size == 2){
				return;
			}
			fill(size / 2, start_x, start_y, x, y);
			fill(size / 2, start_x, start_y + size / 2, start_x + size / 2 - 1, start_y + size / 2);
			fill(size / 2, start_x + size / 2, start_y, start_x + size / 2, start_y + size / 2 - 1);
			fill(size / 2, start_x + size / 2, start_y + size / 2, start_x + size / 2, start_y + size / 2);
			break;

		case 2:
			// fill 1, 3, 4
			cout << start_x + size / 2 << " " << start_y + size / 2 - 1 << " " << 2 << endl;
			if (size == 2){
				return;
			}
			fill(size / 2, start_x, start_y + size / 2, x, y);
			fill(size / 2, start_x, start_y, start_x + size / 2 - 1, start_y + size / 2 - 1);
			fill(size / 2, start_x + size / 2, start_y, start_x + size / 2, start_y + size / 2 - 1);
			fill(size / 2, start_x + size / 2, start_y + size / 2, start_x + size / 2, start_y + size / 2);
			break;

		case 3:
			// fill 1, 2, 4
			cout << start_x + size / 2 - 1 << " " << start_y + size / 2 << " " << 3 << endl;
			if (size == 2){
				return;
			}
			fill(size / 2, start_x + size / 2, start_y, x, y);
			fill(size / 2, start_x, start_y, start_x + size / 2 - 1, start_y + size / 2 - 1);
			fill(size / 2, start_x, start_y + size / 2, start_x + size / 2 - 1, start_y + size / 2);
			fill(size / 2, start_x + size / 2, start_y + size / 2, start_x + size / 2, start_y + size / 2);
			break;

		case 4:
			// fill 1, 2, 3
			cout << start_x + size / 2 - 1 << " " << start_y + size / 2 - 1 << " " << 4 << endl;
			if (size == 2){
				return;
			}
			fill(size / 2, start_x + size / 2, start_y + size / 2, x, y);
			fill(size / 2, start_x, start_y, start_x + size / 2 - 1, start_y + size / 2 - 1);
			fill(size / 2, start_x, start_y + size / 2, start_x + size / 2 - 1, start_y + size / 2);
			fill(size / 2, start_x + size / 2, start_y, start_x + size / 2, start_y + size / 2 - 1);
			break;
	}
}

int main(void){
	int n, x_tmp, y_tmp;
	cin >> n >> x_tmp >> y_tmp;
	// print
	fill(1 << n, 1, 1, x_tmp, y_tmp);
	return 0;
}	
