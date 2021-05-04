#include <iostream>

#define INF 100000000

using namespace std;

int l[101][101];
int ans[101][101] = {0};

int cnt(int x,int y){
    if(ans[x][y] != 0){
        return cnt(x,ans[x][y]) + cnt(ans[x][y],y);
    }
    else return 1;
}

void print(int x,int y){
    if(ans[x][y] != 0){
        print(x,ans[x][y]);
        cout << ans[x][y] << " ";
        print(ans[x][y],y);
    }
}

int main()
{
    int n,m;
    cin >> n >> m;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(i == j) l[i][j] = 0;
            else l[i][j] = INF;
        }
    }
    int a,b,c;
    for(int i=0; i<m; i++){
        cin >> a >> b >> c;
        if(l[a][b] > c) l[a][b] = c;
    }

    for(int k=1; k<=n; k++){
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                if(l[i][j] > (l[i][k] + l[k][j])){
                    l[i][j] = (l[i][k] + l[k][j]);
                    ans[i][j] = k;
                }
            }
        }
    }

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cout << l[i][j] << " ";
        }
        cout << "\n";
    }

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(i == j || l[i][j] == INF) cout << "0\n";
            else{
                cout << cnt(i,j) + 1 << " ";
                cout << i << " ";
                print(i,j);
                cout << j << "\n";
            }
        }
    }
}
