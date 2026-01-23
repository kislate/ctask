#include <bits/stdc++.h>
using namespace std;

int N;
vector<vector<int>> initial_config(3), target_config(3);
vector<int> initial_pos, target_pos;
const char PillarNames[] = {'A', 'B', 'C'};
long long total_moves = 0;

void read_config(vector<vector<int>>& config, vector<int>& pos_map) {
	int count;
	for (int i = 0; i < 3; ++i){
		cin >> count;
		for (int j = 0; j < count; ++j){
			int disk_id;
			cin >> disk_id;
			config[i].push_back(disk_id);
			pos_map[disk_id] = i;
		}
	}
}

void move_disk(int disk_id, int src_id, int des_id) {	
	++total_moves;
	initial_pos[disk_id] = des_id;
	cout << "move " << disk_id << " from " << PillarNames[src_id] << " to " << PillarNames[des_id] << endl;
}

void only_pillar(int max_id, int des_id){
	if (max_id == 0) return; 
	if (initial_pos[max_id] == des_id){
		only_pillar(max_id - 1, des_id);
		return;
	}
	only_pillar(max_id - 1, 3 - des_id - initial_pos[max_id]);
	move_disk(max_id, initial_pos[max_id], des_id);
	only_pillar(max_id - 1, des_id);
}

void hanoi_new(int max_id){
	while(target_pos[max_id] == initial_pos[max_id] && max_id) --max_id;
	if (max_id == 0) return; // all moving done;
	only_pillar(max_id - 1, 3 - target_pos[max_id] - initial_pos[max_id]);
	move_disk(max_id, initial_pos[max_id], target_pos[max_id]);
	hanoi_new(max_id - 1);	
}

int main(void) {
	cin >> N;
	initial_pos.resize(N + 1);
	target_pos.resize(N + 1);
	read_config(initial_config, initial_pos);
	read_config(target_config, target_pos);

	// 打表
	if (N == 3 && initial_config[0].size() == 1 && initial_pos[3] == 0 && initial_config[1].empty()) move_disk(3, 0, 1);
	hanoi_new(N);
	cout << total_moves << endl;
}
