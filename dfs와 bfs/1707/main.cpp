#include <iostream>
#include <vector>

using namespace std;

vector<int> adj[20001];
int check[20001] = {0};

void dfs(int x){
    for(int i=0; i<adj[x].size(); i++){
        if(check[adj[x][i]] == 0){
            check[adj[x][i]] = (-1) * check[x];
            dfs(adj[x][i]);
        }
    }
}

int dlqns(int n){
    for(int i=1; i<=n; i++){
        for(int j=0; j<adj[i].size(); j++){
            if(check[i] == check[adj[i][j]]) return 0;
        }
    }
    return 1;
}

void chrlghk(int n){
    for(int i=1; i<=n; i++){
        adj[i].clear();
        check[i] = 0;
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int m;
    cin >> m;
    for(int j=0; j<m; j++){
        int cnt = 0;
        int x,y;
        int v,e;
        cin >> v >> e;

        for(int i=0; i<e; i++){
            cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }

        for(int i=1; i<=v; i++){
            if(check[i] == 0){
                check[i] = 1;
                dfs(i);
            }
        }

        if(dlqns(v)){
            cout << "YES\n";
        }
        else cout << "NO\n";

        chrlghk(v);
    }
}
