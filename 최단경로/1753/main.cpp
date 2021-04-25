#include <iostream>
#include <vector>
#include <utility>
#include <queue>

#define INF 10000000

using namespace std;

vector<pair<int,int>> adj[20001]; //���� ����Ʈ
int v,e; //����, ���� ����
int dis[20001];

int mn(int a,int b){
    if(a > b) return b;
    return a;
}

void daik(int x){
    priority_queue<pair<int,int>> q; //�Ÿ�, ����
    dis[x] = 0;
    q.push(make_pair(-dis[x],x));


    while(1){
        if(q.empty()) break;
        int r = q.top().second; //���� ����
        int l = -q.top().first; //����� ���������� �Ÿ� �ּҰ�
        q.pop();

        if(l > dis[r]) continue; //�̹� ����Ǿ��ִ°ź��� �Ÿ��� �پ��ٸ� ��Ƽ���� �ٷ� �Ѿ��

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

    //������
    cin >> x;

    //�Ÿ� ��� �������� �ʱ�ȭ
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
