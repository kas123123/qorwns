#include <iostream>

#define INF 1000000
using namespace std;

int a[1000000];

int mn(int a,int b){
    if(a > b) return b;
    return a;
}

int dp(int x){
    if(x == 1) return a[1] = 0;
    else if(a[x] == 0){
        int i=INF,j=INF,k=INF;
        if(x % 3 == 0){
            i = dp(x/3);
        }
        if(x % 2 == 0){
            j = dp(x/2);
        }
        k = dp(x-1);
        return a[x] = mn(mn(i,j),k) + 1;
    }
    else return a[x];
}

int main()
{
    int n;
    cin >> n;
    a[2] = 1;
    a[3] = 1;
    dp(n);
    cout << a[n] << "\n";
    while(1){
        cout << n << " ";
        if(n == 1) break;

        if(n % 3 == 0 && a[n/3] == a[n] - 1) n /=3;
        else if(n % 2 == 0 && a[n/2] == a[n] - 1) n /=2;
        else n -= 1;
    }
}
