#include <iostream>

#define INF 210000000
using namespace std;

int adj[101][101];

//플루이드 워샬 알고리즘

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
예를 들어 adj[i][j](k)가 앞에서 바뀌었다고 하자. 그럼 뒤에서 피해를 보는건 크게

adj[i][x](j) = min(adj[i][x](j-1), adj[i][j](j-1) + adj[j][x](j-1))
adj[x][j](i) = min(adj[x][j](i-1), adj[x][i](i-1) + adj[i][j](i-1))

첫번째의 경우 adj[i][j](j-1)의 값이 adj[i][j](j)가 되어 버리는데 이 뜻은 i -> j -> j인 경우이고
이는 adj[i][j](j-1)의 값과 같아 결과에 영향을 미치지 않는다. 두번째의 경우도 마찬가지 이다.

결론적으로 따로 대입해서 다시 대입을 하지않고 바로 바로 값을 바꿔도 결과에 영향을 미치지 않는다.
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
