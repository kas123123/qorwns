#include <iostream>
#include <queue>

using namespace std;

int injub[1001][1001] = {0};
int check[1001] = {0};
int check_[1001] = {0};
int n;


void dfs(int x){
    cout << x << " ";
    check[x] = 1;
    for(int i=1; i<=n; i++){
        if(injub[x][i] == 1 && check[i] == 0){
            dfs(i);
        }
    }
}

void bfs(int x){
    queue<int> q;
    q.push(x);
    while(1){
        check_[q.front()] = 1;
        for(int i=1; i<=n; i++){
            if(injub[q.front()][i] == 1 && check_[i] == 0){
                q.push(i);
                check_[i] = 1;
            }
        }
        cout << q.front() << " ";
        q.pop();
        if(q.empty()) return;
    }
}

int main()
{
    int m,x;
    int a,b;
    cin >> n >> m >> x;
    for(int i=1; i<=m; i++){
        cin >> a >> b;
        injub[a][b] = 1;
        injub[b][a] = 1;
    }
    dfs(x);
    cout << "\n";
    bfs(x);
}
