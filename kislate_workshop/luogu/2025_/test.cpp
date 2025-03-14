//XOR
//2025
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void stringChange(string& string_damage, int l, int r)
{
    int length = r-l+1;
    string temp = string_damage.substr(l,length);
    for(char& c : temp)
    {
        if(c == '0')
            c = '1';
        else
            c = '0';
    }
    string_damage.replace(l,length,temp);
}

int stringCount(const string& string_damage, int l, int r)
{
    int ret = 0;
    int length = r-l+1;
    string temp = string_damage.substr(l,length);
    for(char&c : temp)
    {
        if(c == '1')
            ret++;
    }
    return ret;
}

int main(void)
{
    int n, m;
    string string_damage;
    cin >> n >> m >> string_damage;
    for(int i = 0; i < m;i++)
    {
        int input_c, l, r;
        cin >> input_c >> l >> r;
        if(input_c)
            cout << stringCount(string_damage,l-1,r-1) << endl;
        else
            stringChange(string_damage,l-1,r-1);
    }
    return 0;
}