#include <iostream>
#include <utility>
#include <vector>
#include <stack>
#include <cstring>

using namespace std;

pair<int,int> p[1001];
int dp[1001][1001]; //dp[x][y] = 1번 경찰차가 마지막으로 해결한 사건 x, 2번 경찰차가 마지막으로 해결한 사건 y, 값은 그때의 최소 거리
int n,w;

int ab(int a){
    if(a < 0) return -a;
    return a;
}

int d(int x1,int y1,int x2,int y2){
    return ab(x1-x2) + ab(y1-y2);
}
int mx(int a,int b){
    if(a > b) return a;
    return b;
}
int mn(int a,int b){
    if(a > b) return b;
    return a;
}

int go(int x,int y){
    if(x == w || y == w) return dp[x][y] = 0;
    if(dp[x][y] != -1) return dp[x][y];

    int z = mx(x,y) + 1;

    int dis1,dis2;
    if(x == 0) dis1 = d(1,1,p[z].first,p[z].second);
    else dis1 = d(p[x].first,p[x].second,p[z].first,p[z].second);

    if(y == 0) dis2 = d(n,n,p[z].first,p[z].second);
    else dis2 = d(p[y].first,p[y].second,p[z].first,p[z].second);

    int l = dis1 + go(z,y);
    int r = dis2 + go(x,z);

    return dp[x][y] = mn(l,r);
}

void road(int x,int y){
    if(x == w || y == w) return;

    int z = mx(x,y) + 1;

    int dis1,dis2;
    if(x == 0) dis1 = d(1,1,p[z].first,p[z].second);
    else dis1 = d(p[x].first,p[x].second,p[z].first,p[z].second);

    if(y == 0) dis2 = d(n,n,p[z].first,p[z].second);
    else dis2 = d(p[y].first,p[y].second,p[z].first,p[z].second);

    if(dp[z][y] + dis1 > dp[x][z] + dis2){
        cout << "2\n";
        road(x,z);
    }
    else{
        cout << "1\n";
        road(z,y);
    }
}



int main()
{
    cin >> n >> w;
    for(int i=1; i<=w; i++){
        cin >> p[i].first >> p[i].second;
    }
    memset(dp, -1, sizeof(dp));
    cout << go(0,0) << "\n";
    road(0,0);
}
