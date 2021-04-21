#include <iostream>
#include <queue>

using namespace std;

int a[1001][101];
int check[1001][101];
int n,m;
int cnt = 1;


void bfs(int x,int y){
    queue<int> q1,q2;
    check[x][y] = 1;
    q1.push(x);
    q2.push(y);

    while(1){
        int tmp = q1.size();
        for(int i=0; i<tmp; i++){
            int l = q1.front();
            int r = q2.front();
            if(l > 1 && a[l-1][r] == 1 && check[l-1][r] == 0){
                q1.push(l-1);
                q2.push(r);
                check[l-1][r] = 1;
            }
            if(l < n && a[l+1][r] == 1 && check[l+1][r] == 0){
                q1.push(l+1);
                q2.push(r);
                check[l+1][r] = 1;
            }
            if(r > 1 && a[l][r-1] == 1 && check[l][r-1] == 0){
                q1.push(l);
                q2.push(r-1);
                check[l][r-1] = 1;
            }
            if(r < m && a[l][r+1] == 1 && check[l][r+1] == 0){
                q1.push(l);
                q2.push(r+1);
                check[l][r+1] = 1;
            }
            q1.pop();
            q2.pop();
        }
        cnt++;
        if(check[n][m] == 1) return;
    }
}


int main()
{
    string s;
    cin >> n >> m;
    for(int i=1; i<=n; i++){
        cin >> s;
        for(int j=0; j<m; j++){
            a[i][j+1] = s[j] - '0';
        }
    }
    bfs(1,1);
    cout << cnt;
}
