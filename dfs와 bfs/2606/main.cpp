#include <iostream>

using namespace std;

int injub[101][101];
int check[101] = {0};
int n,m;

void dfs(int x){
    check[x] = 1;
    for(int i=1; i<=n; i++){
        if(check[i] == 0 && injub[x][i] == 1){
            dfs(i);
        }
    }
}


int main()
{
    int a,b;
    cin >> n >> m;
    for(int i=1; i<=m; i++){
        cin >> a >> b;
        injub[a][b] = 1;
        injub[b][a] = 1;
    }
    dfs(1);
    int sum = 0;
    for(int i=1; i<=n; i++){
        if(check[i] == 1) sum++;
    }
    cout << sum-1;
}
