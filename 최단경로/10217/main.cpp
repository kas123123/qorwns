#include <iostream>
#include <vector>
#include <utility>

#define INF 200000000
using namespace std;

vector<pair<int,int>> W[101]; //���
vector<pair<int,int>> T[101]; //�ð�
int d[101][10001]; //d[x][y] x���� ���� y�� ����� ���� �̶��� �ּ� �ð�

void B(int v,int w){
    for(int i=1; i<=v; i++){
        for(int j=0; j<=w; j++){
            d[i][j] = INF;
        }
    }

    for(int i=1; i<v; i++){
        for(int j=1; j<=v; j++){
            for(int k=0; k<W[j].size(); k++){
                for(int l=0; l<=w; l++){

                }
            }
        }
    }
}

int main()
{
    int v,w,e;
    cin >> v >> w >> e;
    int a1,a2,a3,a4;
    for(int i=0; i<e; i++){
        cin >> a1 >> a2 >> a3 >> a4;
        W[a1].push_back(make_pair(a2,a3));
        T[a1].push_back(make_pair(a2,a4));
    }
    B(v,w);
}
