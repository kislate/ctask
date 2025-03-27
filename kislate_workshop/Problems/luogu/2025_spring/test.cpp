#include <iostream>
#include <vector>
using namespace std;

typedef struct{
    int x, y;
    int width, height;
}carpet;

int main(void)
{
    int n;
    cin >> n;
    vector<carpet>carpets(n);
    for(int i = 0; i < n; i++)
    {
        cin >> carpets[i].x >> carpets[i].y >> carpets[i].width >> carpets[i].height; 
    }
    int nx, ny;
    cin >> nx >> ny;
    int ans = -1;
    for(int i = 0; i < n; i++)
    {
        if(nx >= carpets[i].x && nx <=carpets[i].x + carpets[i].width && ny >=carpets[i].y && ny<=carpets[i].height+carpets[i].y)
            ans = i + 1;
    }
    cout << ans << endl;
    return 0;
}