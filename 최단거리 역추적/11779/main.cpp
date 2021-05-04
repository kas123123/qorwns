#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <stack>

#define INF 1000000000

using namespace std;

vector<pair<int,int>> adj[1001];
int d[1001][2];

void go(int x,int y){
    for(int i=1; i<=1000; i++){
        d[i][0] = INF;
    }
    d[x][0] = 0;
    priority_queue<pair<int,int>> q;
    q.push(make_pair(0,x));

    while(1){
        int D = -q.top().first;
        int N = q.top().second;
        q.pop();
        if(N == y) break;
        if(D > d[N][0]) continue;

        for(int i=0; i<adj[N].size(); i++){
            if(d[adj[N][i].first][0] > d[N][0] + adj[N][i].second){
                d[adj[N][i].first][0] = d[N][0] + adj[N][i].second;
                d[adj[N][i].first][1] = N;
                q.push(make_pair(-d[adj[N][i].first][0],adj[N][i].first));
            }
        }
    }

    cout << d[y][0] << "\n";

    stack<int> s;
    int tmp=y;
    while(1){
        s.push(tmp);
        if(tmp == x) break;
        tmp = d[tmp][1];
    }

    cout << s.size() << "\n";

    while(!s.empty()){
        cout << s.top() << " ";
        s.pop();
    }
}

int main()
{
    int n,m;
    cin >> n >> m;
    int a,b,c;
    for(int i=0; i<m; i++){
        cin >> a >> b >> c;
        adj[a].push_back(make_pair(b,c));
    }
    cin >> a >> b;
    go(a,b);
}
