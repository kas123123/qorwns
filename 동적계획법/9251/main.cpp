#include <iostream>
#include <string>

using namespace std;

int a[1001][1001]={0};
int mx(int a,int b){
    if(a>b) return a;
    return b;
}

int main()
{
    string n,m;
    cin >> n >> m;

    for(int i=1; i<=n.size(); i++){
        for(int j=1; j<=m.size(); j++){
            if(n[i-1] == m[j-1]) a[i][j] = a[i-1][j-1] + 1;
            else a[i][j] = mx(a[i-1][j],a[i][j-1]);
        }
    }
    cout << a[n.size()][m.size()];
}
/*
    A C A Y K P
  0 0 0 0 0 0 0
C 0 0 1 0 0 0 0
A 0 1 1 2 2 2 2
P 0 1 1 2 2 2 3
C 0 1 2 2 2 2 3
A 0 1 2 3 3 3 3
K 0 1 2 3 3 4 4

*/
