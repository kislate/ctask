// XOR_2
// 2025_2
#include <iostream>
#include <string>
#include <bitset>
#include <vector>

using namespace std;

int main(void)
{
    int n, m;
    string string_damage;
    cin >> n >> m >> string_damage;
    vector<unsigned long long> Bis_to_ll(n / 64 + 1);
    for(int i = 0; i < n; i++)
    {
        if(string_damage[i] == '1')
            Bis_to_ll[i / 64] |= 1ULL << (i % 64);
    }
    for(int i = 0; i < m; i++)
    {
        int input_c, l, r;
        cin >> input_c >> l >> r;
        if(input_c)
        {
            // 输出1的个数
            int ret = 0;
            for (size_t j = l - 1; j < r; j++)
            {
                size_t block_idx = j / 64;
                size_t bit_offset = j % 64;
                if (Bis_to_ll[block_idx] & (1ULL << bit_offset))
                    ret++;
            }
            cout << ret << endl;
        }
        else
        {
            // 反转
            size_t block_idx_l = (l - 1) / 64;
            size_t bit_offset_l = (l - 1) % 64;
            size_t block_idx_r = (r - 1) / 64;
            size_t bit_offset_r = (r - 1) % 64;
            if (block_idx_l == block_idx_r)
            {
                Bis_to_ll[block_idx_l] ^= (((1ULL << (bit_offset_r - bit_offset_l + 1)) - 1) << bit_offset_l);
            }
            else
            {
                Bis_to_ll[block_idx_l] ^= (0xFFFFFFFFFFFFFFFFULL << bit_offset_l);
                Bis_to_ll[block_idx_r] ^= ((1ULL << bit_offset_r) - 1);
                for (size_t j = block_idx_l + 1; j < block_idx_r; j++)
                {
                    Bis_to_ll[j] = ~Bis_to_ll[j];
                }
            }
        }
    
    }
    return 0;
}