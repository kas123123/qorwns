#include <iostream>

using namespace std;

int c[51][51] = {0};
int l,r,n;

void dfs(int x,int y){
    c[x][y] = 0;
    if(x > 1 && c[x-1][y] == 1){
        dfs(x-1,y);
    }
    if(x < n && c[x+1][y] == 1){
        dfs(x+1,y);
    }
    if(y > 1 && c[x][y-1] == 1){
        dfs(x,y-1);
    }
    if(y < n && c[x][y+1] == 1){
        dfs(x,y+1);
    }
}

int main()
{
    int m;
    cin >> m;
    for(int k=0; k<m; k++){
        int cnt = 0;
        cin >> l >> r >> n;
        int x,y;
        for(int i=0; i<n; i++){
            cin >> x >> y;
            c[y+1][x+1] = 1;
        }

        for(int i=1; i<=r; i++){
            for(int j=1; j<=l; j++){
                if(c[i][j] == 1){
                    dfs(i,j);
                    cnt++;
                }
            }
        }
        cout << cnt << "\n";
    }
}
