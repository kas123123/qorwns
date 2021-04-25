#include <iostream>
#include <vector>
#include <queue>
#include <utility>

#define INF 2100000000


using namespace std;

vector<pair<int,int>> adj[801];
int v,e;
int dis[801];

void daik(int x){
    dis[x] = 0;
    priority_queue<pair<int,int>> q; //거리, 정점
    q.push(make_pair(0,x));

    while(1){
        if(q.empty()) return;
        int l = -q.top().first;
        int r = q.top().second;
        q.pop();

        if(l > dis[r]) continue;

        for(int i=0; i<adj[r].size(); i++){
            if(dis[adj[r][i].first] > dis[r] + adj[r][i].second){
                dis[adj[r][i].first] = dis[r] + adj[r][i].second;
                q.push(make_pair(-dis[adj[r][i].first],adj[r][i].first));
            }
        }
    }
}

int main()
{
    int v1,v2;
    int a,b,c;
    cin >> v >> e;
    for(int i=0; i<e; i++){
        cin >> a >> b >> c;
        adj[a].push_back(make_pair(b,c));
        adj[b].push_back(make_pair(a,c));
    }
    cin >> v1 >> v2;
    for(int i=1; i<=v; i++){
        dis[i] = INF;
    }
    daik(v1);
    int v1to1 = dis[1];
    int v1tov = dis[v];

    for(int i=1; i<=v; i++){
        dis[i] = INF;
    }
    daik(v2);

    if(dis[v1] == INF) cout << "-1";
    else if(v1to1 == INF || dis[1] == INF) cout << "-1";
    else if(v1tov == INF || dis[v] == INF) cout << "-1";
    else{
        if(v1to1 + dis[v1] + dis[v] > v1tov + dis[v1] + dis[1]){
            cout << v1tov + dis[v1] + dis[1];
        }
        else cout << v1to1 + dis[v1] + dis[v];
    }
}
