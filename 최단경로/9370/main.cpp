#include <iostream>
#include <vector>
#include <queue>
#include <utility>

#define INF 100000000

using namespace std;

vector<pair<int,int>> adj[2001];
int dis1[2001];
int dis2[2001];
int dis3[2001];

void daik(int* d, int x,int n){

    for(int i=1; i<=n; i++){
        d[i] = INF;
    }
    d[x] = 0;

    priority_queue<pair<int,int>> q;//-거리, 정점

    q.push(make_pair(0,x));

    while(1){
        if(q.empty()) return;
        int l = -q.top().first;
        int r = q.top().second;
        q.pop();

        if(l > d[r]) continue;

        for(int i=0; i<adj[r].size(); i++){
            if(d[adj[r][i].first] > d[r] + adj[r][i].second){
                d[adj[r][i].first] = d[r] + adj[r][i].second;
                q.push(make_pair(-d[adj[r][i].first],adj[r][i].first));
            }
        }
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for(int k=0; k<T; k++){
        int n,m,t; //교차로, 도로, 목적지 후보 개수
        int s,g,h; //출발지, g - h 사이를 반드시 지나야함

        cin >> n >> m >> t;
        cin >> s >> g >> h;

        int a,b,c;
        for(int i=0; i<m; i++){
            cin >> a >> b >> c;
            adj[a].push_back(make_pair(b,c));
            adj[b].push_back(make_pair(a,c));
        }

        daik(dis1,g,n);
        daik(dis2,h,n);
        daik(dis3,s,n);

        priority_queue<int> q;
        int x;
        int mid = dis1[h];
        //s -> h -> g
        if(dis1[s] > dis2[s]){
            for(int i=0; i<t; i++){
                cin >> x;
                if(dis3[x] == dis3[h] + mid + dis1[x]) q.push(-x);
            }
        }
        else{
            for(int i=0; i<t; i++){
                cin >> x;
                if(dis3[x] == dis3[g] + mid + dis2[x]) q.push(-x);
            }
        }

        while(1){
            if(q.empty()) break;
            cout << -q.top() << " ";
            q.pop();
        }
        cout << "\n";

        for(int i=1; i<=n; i++){
            adj[i].clear();
        }
    }
}
