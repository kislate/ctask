/*
小 S 是历史长河。
一条历史长河是对一个文明从发展到衰亡的记录，若有好事者对这个文明感兴趣，
便可以从历史长河中一探究竟。
历史长河是一段仅包含大小写字母的字符串，记录了每一个时间点这个文明发生的
重要事件。字典序越小的字母代表的事件越重要。
现在，有两条不同的历史长河 S 和 T ，作为好事者的你正打算对比研究它们。在研
究过程中，你遇到了Q 个问题，在每个问题中，你想要比较两个文明中特定时段的事件
重要程度。
形式化的，每次给出ls, rs 和lt, rt，你需要判断S[ls, rs] 和T [lt, rt] 谁的字典序更小。
其中，S[l, r] 表示从字符串 S 的第 l 个字符到第 r 个字符连起来构成的字符串。例
如，若 S 为 kitsuki，则 s[3, 5] 为 tsu。
【输入格式】
第一行是一个字符串 S。
第二行是一个字符串 T 。
第三行是一个整数，表示询问次数 Q。
接下来 Q 行，每行四个整数 ls, rs, lt, rt，表示一次询问。
【输出格式】
对每次询问，输出一行一个字符串：
• 如果 S[ls, rs] 的字典序更小，请输出 yifusuyi。
• 如果 T [lt, rt] 的字典序更小，请输出 erfusuer。
• 如果两者的字典序一样大，请输出 ovo。
【样例 1 输入】
Yifusuyi
yifusuYi
3
1 2 7 8
1 2 1 2
7 8 7 8
ovo
yifusuyi
erfusuer
【子任务】
对 100% 的数据，1 ≤|S|, |T |, Q ≤103，1 ≤ls ≤rs ≤|S|，1 ≤lt ≤rt ≤|T |。输入
字符串仅含大小写英文字母。其中 |S|表示历史长河 S 的长度，|T |表示历史长河 T 的
长度。
*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int main()
{
    string S, T;
    cin >> S >> T;
    int Q;
    cin >>Q;
    for(int i = 0 ; i < Q ; i++)
    {
        int ls, rs, lt, rt;
        cin >>ls >>rs >>lt >>rt;
        if(S.substr(ls - 1, rs - ls + 1) <  T.substr(lt - 1, rt - lt + 1))
        {
            cout << "yifusuyi" << endl;
        }
        else if(S.substr(ls - 1, rs - ls + 1) >  T.substr(lt - 1, rt - lt + 1))
        {
            cout << "erfusuer" << endl;
        }
        else
        {
            cout << "ovo" << endl;
        }
    }
}


/*
def main():
    S = input().strip()
    T = input().strip()
    Q = int(input().strip())
    
    results = []
    for _ in range(Q):
        ls, rs, lt, rt = map(int, input().strip().split())
        subS = S[ls-1:rs]
        subT = T[lt-1:rt]
        
        if subS < subT:
            results.append("yifusuyi")
        elif subS > subT:
            results.append("erfusuer")
        else:
            results.append("ovo")
    
    # 使用 join 方法输出结果
    print("\n".join(results))

if __name__ == "__main__":
    main()
*/
