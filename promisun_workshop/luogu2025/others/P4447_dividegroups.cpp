#include <bits/stdc++.h>
using namespace std;
int main(void)
{
    string nihao = "nihao";
    int num;
    vector<int> a(10, 0);
    for(int i = 0; i < 10; i++)
    {
        cin >> a[i];
    }
    for(int i = 0; i < 10; i++)
    {
        cout << a[i] << " ";
    }
    cin >> num >> nihao;
    cout << "HELLO WORLD " << nihao << " " <<  num << endl;
}
