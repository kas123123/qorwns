#include <iostream>

#define INF 200000000
using namespace std;

int v,e;
int d[401][401];

int mn(int a,int b){
    if(a > b) return b;
    return a;
}

void W(){
    for(int x=1; x<=v; x++){
        for(int i=1; i<=v; i++){
            for(int j=1; j<=v; j++){
                d[i][j] = mn(d[i][j],d[i][x]+d[x][j]);
            }
        }
    }
}



int main()
{
    cin >> v >> e;
    int a,b,c;

    for(int i=1; i<=v; i++){
        for(int j=1; j<=v; j++){
            if(i == j) d[i][j] = 0;
            else d[i][j] = INF;
        }
    }

    for(int i=0; i<e; i++){
        cin >> a >> b >> c;
        d[a][b] = c;
    }

    W();

    int Min = INF;

    for(int i=1; i<=v; i++){
        for(int j=1; j<=v; j++){
            if(i != j && Min > d[i][j] + d[j][i]) Min = d[i][j] + d[j][i];
        }
    }

    if(Min == INF) cout << "-1";
    else cout << Min;
}
