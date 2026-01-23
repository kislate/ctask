#include <bits/stdc++.h>
using namespace std;

// 全局变量
int N;
// Save the sequence of disks on each tower (vector::back() is the top disk)
vector<vector<int>> initial_config(3), target_config(3); 

// Save the current tower of each disk (initial_pos) and target tower (target_pos)
vector<int> initial_pos, target_pos; 

// 柱子编号到名称的映射
const char PillarNames[] = {'A', 'B', 'C'};
// 记录总步数
long long total_moves = 0;

// --- 辅助函数：读入配置 (保持您的实现) ---
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

// --- 移动操作 ---
void move_disk(int disk_id, int source_idx, int target_idx) {
    // 移除
    initial_config[source_idx].pop_back();
    // 放置
    initial_config[target_idx].push_back(disk_id);
    
    // 更新全局位置
    initial_pos[disk_id] = target_idx;

    // 记录步数和输出
    total_moves++;
    cout << "move " << disk_id 
         << " from " << PillarNames[source_idx] 
         << " to " << PillarNames[target_idx] << endl;
}

// --- 核心递归函数：广义汉诺塔求解 ---

/**
 * @brief 将圆盘 {1..disk_id} 移动到 target_pillar 柱上。
 * 目标：将所有 {1..disk_id} 盘子堆叠到 target_pillar 柱上 (顺序是正确的)
 * @param disk_id 当前要处理的最大圆盘编号
 * @param target_pillar 圆盘 disk_id 最终要去的柱子
 * @param forbidden_pillar 禁止使用的柱子
 */
void hanoi_move_to_one(int disk_id, int target_pillar, int forbidden_pillar) {
    if (disk_id == 0) return;

    int p_current = initial_pos[disk_id];
    
    // 1. 如果 disk_id 已经在目标柱上
    if (p_current == target_pillar) {
        // 递归处理更小的盘子，将它们移动到目标柱上
        hanoi_move_to_one(disk_id - 1, target_pillar, forbidden_pillar);
        return;
    }
    
    // 2. disk_id 不在目标柱上，它必须移动
    int p_aux = 3 - target_pillar - p_current; // 辅助柱
    
    // a. 将 disk_id-1 移动到辅助柱 p_aux
    // 递归：目标是 p_aux，禁止使用 target_pillar
    hanoi_move_to_one(disk_id - 1, p_aux, target_pillar);
    
    // b. 移动 disk_id
    move_disk(disk_id, p_current, target_pillar);
    
    // c. 将 disk_id-1 移动到目标柱 target_pillar
    // 递归：目标是 target_pillar，禁止使用 p_current (旧的源柱)
    hanoi_move_to_one(disk_id - 1, target_pillar, p_current);
}

/**
 * @brief 驱动广义汉诺塔求解的主递归函数
 * @param n 当前处理的最大圆盘
 */
void solve_general(int n) {
    if (n == 0) return;

    // 1. 找到最大的错位圆盘 k
    int k = n;
    while (k >= 1 && initial_pos[k] == target_pos[k]) {
        // 必须进一步判断：k 上方的堆栈是否与目标状态一致。
        // 但为了简化和效率，我们只判断 k 盘本身的位置。
        // 如果位置一致，我们尝试在目标位置上解决 k-1 的问题。
        k--;
    }

    if (k == 0) return; // 所有盘都在目标位置，完成。

    int p_target_k = target_pos[k];
    int p_init_k = initial_pos[k];
    int p_aux_k = 3 - p_init_k - p_target_k;

    // 2. 递归地将 {1..k-1} 移动到 p_aux 柱
    // 目标：将 {1..k-1} 堆叠到 p_aux 柱上 (作为 k 移动的中转站)
    // 禁用柱子是 p_target_k
    hanoi_move_to_one(k - 1, p_aux_k, p_target_k);

    // 3. 移动 k (清空了上方盘子后，k 就可以移动了)
    move_disk(k, p_init_k, p_target_k);

    // 4. 递归地解决 {1..k-1} 的最终状态问题
    // 现在 k 在正确位置，我们只需将 {1..k-1} 移动到 target_config 中它们最终的位置。
    
    // **最巧妙的一步：** 只要 k 在正确位置，对 {1..k-1} 而言，k 所在的柱子 (p_target_k) 就可以被视为**辅助柱**。
    // 我们递归调用 solve_general(k-1)，让它将 {1..k-1} 从 p_aux_k 移动到最终的目标配置。
    // 由于是广义汉诺塔，我们不能简单地用基础汉诺塔，而是**递归调用自身**。
    
    solve_general(k - 1);
}

// --- Main Function ---
int main(void) {
    // 开启竞赛模式加速 I/O
    ios::sync_with_stdio(false);
    cin.tie(NULL);

	if (!(cin >> N)) return 0;
    
    initial_pos.resize(N + 1);
	target_pos.resize(N + 1);
    
    // 读取初始状态
	read_config(initial_config, initial_pos);
    // 读取目标状态
	read_config(target_config, target_pos);

    // 启动递归求解
    solve_general(N);

    // 输出总步数
    cout << total_moves << endl;

    return 0;
}