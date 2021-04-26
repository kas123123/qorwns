#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <utility>

#define INF 200000000

using namespace std;

vector<vector<int>> adj[101];
int t[101][10001];
int v,w,e;

void go(){

    for(int i=1; i<=v; i++){
        for(int j=0; j<=w; j++){
            t[i][j] = INF;
        }
    }
    t[1][0] = 0;
    priority_queue<vector<int>> q;
    q.push(vector<int>{0,1,0}); //시간 정점 비용

    while(1){
        if(q.empty()) break;

        int T = -q.top()[0];
        int X = q.top()[1];
        int W = q.top()[2];

        q.pop();

        if(t[X][W] < T) continue;
        if(X == v) return;

        //모든 X -> 정점에 대해
        for(int i=0; i<adj[X].size(); i++){
            if(W+adj[X][i][1] <= w && t[adj[X][i][0]][W+adj[X][i][1]] > t[X][W] + adj[X][i][2]){

                for(int j=W+adj[X][i][1]; j<=w; j++){
                    if(t[adj[X][i][0]][j] > t[X][W] + adj[X][i][2]) t[adj[X][i][0]][j] = t[X][W] + adj[X][i][2];
                } //필요없는 경우 탐색 안하기
                q.push(vector<int>{-t[adj[X][i][0]][W+adj[X][i][1]],adj[X][i][0],W+adj[X][i][1]});

            }
        }
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int cnt;
    cin >> cnt;
    for(int i=0; i<cnt; i++){
        cin >> v >> w >> e;
        int a,b,c,d;
        for(int i=0; i<e; i++){
            cin >> a >> b >> c >> d;
            adj[a].push_back(vector<int>{b,c,d});
        }

        go();

        int mn = INF;
        for(int i=0; i<=w; i++){
            if(mn > t[v][i]) mn = t[v][i];
        }
        if(mn == INF) cout << "Poor KCM\n";
        else cout << mn << "\n";

        for(int i=1; i<=v; i++){
            adj[i].clear();
        }
    }
}
