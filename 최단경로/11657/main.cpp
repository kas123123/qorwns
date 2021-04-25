#include <iostream>
#include <vector>
#include <utility>
#include <queue>

#define INF 100000000

using namespace std;

vector<pair<int,int>> adj[501];
long long d[501];
int check[501];

int bell(int x,int v){
    for(int i=1; i<=v; i++){
        d[i] = INF;
        check[i] = 0;
    }
    d[x] = 0;

    //�� �� ������ �Ÿ���  ���� ����
    for(int i=1; i<v; i++){
        //V-1 ��ŭ �ݺ�

        for(int j=1; j<=v; j++){
            if(d[j] != INF) check[j] = 1;
        }

        for(int j=1; j<=v; j++){
            if(check[j] == 1){
                for(int k=0; k<adj[j].size(); k++){
                    if(d[adj[j][k].first] > d[j] + adj[j][k].second){
                        d[adj[j][k].first] = d[j] + adj[j][k].second;
                    }
                }
            }
        }
        //E�� ��� �˻�
    }

    //�� ������ �ٽ� �˻��� ���� ��ȯ�� �ִ��� Ȯ��
    for(int j=1; j<=v; j++){
        for(int k=0; k<adj[j].size(); k++){
            if(d[adj[j][k].first] != INF && d[adj[j][k].first] > d[j] + adj[j][k].second) return 0;
        }
    }
    return 1;
}

int main()
{
    int v,e;
    cin >> v >> e;

    int a,b,c;
    for(int i=0; i<e; i++){
        cin >> a >> b >> c;
        adj[a].push_back(make_pair(b,c));
    }
    if(bell(1,v)){
        for(int i=2; i<=v; i++){
            if(d[i] == INF) cout << "-1\n";
            else cout << d[i] << "\n";
        }
    }
    else{
        cout << "-1";
    }
}
