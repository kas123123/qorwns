#include <iostream>
#include <vector>
#include <utility>
#include <queue>

#define INF 10000000

using namespace std;

vector<pair<int,int>> adj[20001]; //인접 리스트
int v,e; //정점, 간선 개수
int dis[20001];

int mn(int a,int b){
    if(a > b) return b;
    return a;
}

void daik(int x){
    priority_queue<pair<int,int>> q; //거리, 정점
    dis[x] = 0;
    q.push(make_pair(-dis[x],x));


    while(1){
        if(q.empty()) break;
        int r = q.top().second; //현재 정점
        int l = -q.top().first; //저장된 정점까지의 거리 최소값
        q.pop();

        if(l > dis[r]) continue; //이미 저장되어있는거보다 거리가 줄었다면 콘티뉴로 바로 넘어가기

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
    int a,b,c,x;
    cin >> v >> e;

    //시작점
    cin >> x;

    //거리 모두 무한으로 초기화
    for(int i=1; i<=v; i++){
        dis[i] = INF;
    }

    for(int i=0; i<e; i++){
        cin >> a >> b >> c;
        adj[a].push_back(make_pair(b,c));
    }

    daik(int x);

    for(int i=1; i<=v; i++){
        cout << dis[i] << "\n";
    }
}
