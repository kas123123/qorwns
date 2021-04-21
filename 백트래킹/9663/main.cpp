#include <iostream>

using namespace std;

int n;
int q[15][15] = {0};
int sum = 0;

void D(int x){
    if(x == n){
        for(int i=1; i<=n; i++){
            if(q[i][n] == 0) sum++;
        }
        return;
    }
    for(int i=1; i<=n; i++){
        if(q[i][x] == 0){
            for(int j=0; x+j<=n; j++){
                if(i > j && q[i-j][x+j] == 0) q[i-j][x+j] = x;
                if(i+j <= n && q[i+j][x+j] == 0) q[i+j][x+j] = x;
                if(q[i][x+j] == 0) q[i][x+j] = x;
            }
            D(x+1);
            for(int j=0; x+j<=n; j++){
                if(i > j && q[i-j][x+j] == x) q[i-j][x+j] = 0;
                if(i+j <= n && q[i+j][x+j] == x) q[i+j][x+j] = 0;
                if(q[i][x+j] == x) q[i][x+j] = 0;
            }
        }
    }
    return;
}

int main()
{
    cin >> n;
    D(1);
    cout << sum;
}
