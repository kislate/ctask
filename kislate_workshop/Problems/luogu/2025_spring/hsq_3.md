### 下面是第一版代码(30分):
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
unordered_map<int, int> RAM_memory;// 0 是在内存里没写过, 1 是在内存里但是写过, 10 是在缓存里但是没写过, 11 是在缓存里写过;
// 其实如果是0的话,就是直接给erase了.
class myqueues{
    vector<queue<int>> queue_id;
    vector<int> size_queue;
public:
    myqueues(int N)
    {
        queue_id.resize(N);
        size_queue.resize(N);
    }
    // 如果所放的缓存组里面已经满了,那么推出最久未使用的那个,并且获取它的id, 把他放回内存里,然后存入新的id
    void enqueue(int which_queue, int id, int n, int op_type)
    {
        if(size_queue[which_queue] == n)
        {
            int id_to_remove = queue_id[which_queue].front();
            queue_id[which_queue].pop();
            size_queue[which_queue]--;
            if(RAM_memory[id_to_remove] == 11)
            {
                RAM_memory[id_to_remove] = 1;
                cout << 1 <<" " << id_to_remove << endl;
            }
            else if(RAM_memory[id_to_remove] == 10)
            {
                RAM_memory.erase(id_to_remove);
            }
            queue_id[which_queue].push(id);
            size_queue[which_queue]++;
            if(op_type == 0 && RAM_memory.find(id) == RAM_memory.end())
            {
                RAM_memory[id] = 10;
            }
            else
            {
                RAM_memory[id] = 11;
            }
        }
        else{
            queue_id[which_queue].push(id);
            size_queue[which_queue]++;
            if(op_type == 0 && RAM_memory.find(id) == RAM_memory.end())
            {
                RAM_memory[id] = 10;
            }
            else
            {
                RAM_memory[id] = 11;
            }
        }
    }
    void moveToBack(int which_queue, int id)
    {
        queue<int> temp_queue;
        while(!queue_id[which_queue].empty())
        {
            int current_id = queue_id[which_queue].front();
            queue_id[which_queue].pop();
            if(current_id != id)
            {
                temp_queue.push(current_id);
            }
        }
        temp_queue.push(id);
        queue_id[which_queue] = temp_queue;
    }

    void dequeue(int which_queue)
    {
        queue_id[which_queue].pop();
        size_queue[which_queue]--;
    }
    int size(int id)
    {
        return size_queue[id];
    }
};


int main(void)
{
    int n, N, q;
    cin >> n >> N >> q;
    vector<vector<int>> buffer_memory(N, vector<int>(n));
    vector<queue<int>> queue_id(N);
    myqueues myqueue(N);
    for(int i = 0; i < q; i++)
    {
        int op_type, id;
        cin >> op_type >> id;
        int which_queue = id % (n * N) / n;
        if(!op_type)
        {
            if(RAM_memory.find(id) == RAM_memory.end())
            {
                myqueue.enqueue(which_queue, id, n, op_type);// 同时进行了写入操作(如果缓存里的数据进行过写的话)
                cout << 0 <<" " << id << endl; // 因为没找到,要在内存里写入,输出0, id
            }
            else{
                // 在缓存中找到,对内存没有操作,无需输出,因为输出的1,0 是对内存操作;
                myqueue.moveToBack(which_queue, id);
            }
        }
        else
        {
            if(RAM_memory.find(id) == RAM_memory.end() || RAM_memory[id] == 1)
            {
                myqueue.enqueue(which_queue, id, n, op_type);
                cout << 0 << " " << id << endl;
            }
            else{
                myqueue.moveToBack(which_queue, id);
                RAM_memory[id] == 11;
            }
        }
    }
}



#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
using namespace std;

unordered_map<int, int> RAM_memory; // 0 是在内存里没写过, 1 是在内存里但是写过, 10 是在缓存里但是没写过, 11 是在缓存里写过;

class myqueues {
    vector<list<int>> queue_id;
    vector<int> size_queue;
    unordered_map<int, list<int>::iterator> position_map;

public:
    myqueues(int N) {
        queue_id.resize(N);
        size_queue.resize(N);
    }

    void enqueue(int which_queue, int id, int n, int op_type) {
        if (size_queue[which_queue] == n) {
            int id_to_remove = queue_id[which_queue].front();
            queue_id[which_queue].pop_front();
            size_queue[which_queue]--;
            position_map.erase(id_to_remove);
            if (RAM_memory[id_to_remove] == 11) {
                RAM_memory[id_to_remove] = 1;
                cout << 1 << " " << id_to_remove << endl;
            } else if (RAM_memory[id_to_remove] == 10) {
                RAM_memory.erase(id_to_remove);
            }
        }
        queue_id[which_queue].push_back(id);
        size_queue[which_queue]++;
        position_map[id] = --queue_id[which_queue].end();
        if (op_type == 0 && RAM_memory.find(id) == RAM_memory.end()) {
            RAM_memory[id] = 10;
        } else {
            RAM_memory[id] = 11;
        }
    }

    void moveToBack(int which_queue, int id) {
        if (position_map.find(id) != position_map.end()) {
            queue_id[which_queue].erase(position_map[id]);
            queue_id[which_queue].push_back(id);
            position_map[id] = --queue_id[which_queue].end();
        }
    }

    void dequeue(int which_queue) {
        int id_to_remove = queue_id[which_queue].front();
        queue_id[which_queue].pop_front();
        size_queue[which_queue]--;
        position_map.erase(id_to_remove);
    }

    int size(int id) {
        return size_queue[id];
    }
};

int main(void)
{
    int n, N, q;
    cin >> n >> N >> q;
    vector<vector<int>> buffer_memory(N, vector<int>(n));
    myqueues myqueue(N);

    for (int i = 0; i < q; i++)
    {
        int op_type, id;
        cin >> op_type >> id;
        int which_queue = id % (n * N) / n;
        if (!op_type)
        {
            if (RAM_memory.find(id) == RAM_memory.end())
            {
                myqueue.enqueue(which_queue, id, n, op_type); // 同时进行了写入操作(如果缓存里的数据进行过写的话)
                cout << 0 << " " << id << endl; // 因为没找到,要在内存里写入,输出0, id
            }
            else
            {
                // 在缓存中找到,对内存没有操作,无需输出,因为输出的1,0 是对内存操作;
                myqueue.moveToBack(which_queue, id); // 将对应id移到队列的末尾
            }
        }
        else
        {
            if (RAM_memory.find(id) == RAM_memory.end() || RAM_memory[id] == 1)
            {
                myqueue.enqueue(which_queue, id, n, op_type);
                cout << 0 << " " << id << endl;
            }
            else
            {
                myqueue.moveToBack(which_queue, id);
                RAM_memory[id] = 11;
            }
        }
    }

    return 0;
}
```