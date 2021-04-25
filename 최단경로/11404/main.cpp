#include <iostream>

#define INF 210000000
using namespace std;

int adj[101][101];

//�÷��̵� ���� �˰���

void W(int v){
    for(int k=1; k<=v; k++){
        for(int i=1; i<=v; i++){
            for(int j=1; j<=v; j++){
                if(adj[i][j] > adj[i][k] + adj[k][j]) adj[i][j] = adj[i][k] + adj[k][j];
            }
        }
    }
}

/*
���� ��� adj[i][j](k)�� �տ��� �ٲ���ٰ� ����. �׷� �ڿ��� ���ظ� ���°� ũ��

adj[i][x](j) = min(adj[i][x](j-1), adj[i][j](j-1) + adj[j][x](j-1))
adj[x][j](i) = min(adj[x][j](i-1), adj[x][i](i-1) + adj[i][j](i-1))

ù��°�� ��� adj[i][j](j-1)�� ���� adj[i][j](j)�� �Ǿ� �����µ� �� ���� i -> j -> j�� ����̰�
�̴� adj[i][j](j-1)�� ���� ���� ����� ������ ��ġ�� �ʴ´�. �ι�°�� ��쵵 �������� �̴�.

��������� ���� �����ؼ� �ٽ� ������ �����ʰ� �ٷ� �ٷ� ���� �ٲ㵵 ����� ������ ��ġ�� �ʴ´�.
*/

int main()
{
    int v,e;
    cin >> v >> e;

    int a,b,c;
    for(int i=1; i<=v; i++){
        for(int j=1; j<=v; j++){
            if(i == j) adj[i][j] = 0;
            else adj[i][j] = INF;
        }
    }
    for(int i=0; i<e; i++){
        cin >> a >> b >> c;
        if(adj[a][b] > c) adj[a][b] = c;
    }
    W(v);
    for(int i=1; i<=v; i++){
        for(int j=1; j<=v; j++){
            if(adj[i][j] == INF) cout << "0 ";
            else cout << adj[i][j] << " ";
        }
        cout << "\n";
    }
}
