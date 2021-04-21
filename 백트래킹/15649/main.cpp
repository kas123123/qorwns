#include <iostream>

using namespace std;

int n,m;
int a[9];
int check[9]={0};

void D(int x){
    if(x == m){
        for(int i=1; i<=m; i++){
            cout << a[i] << " ";
        }
        cout << "\n";
        return;
    }

    for(int i=1; i<=n; i++){
        if(check[i] == 0){
            check[i] = 1;
            a[x+1] = i;
            D(x+1);
            check[i] = 0;
        }
    }

}

int main()
{
    cin >> n >> m;
    D(0);
}
