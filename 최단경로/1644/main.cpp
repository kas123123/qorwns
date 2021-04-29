#include <iostream>

using namespace std;

int p[4000000] = {0};
int a[4000000];

int main()
{
    int n;
    cin >> n;
    for(int i=2; i<2000;i++){
        if(p[i] == 0){
            for(int j=i*i ; j < 4000000; j += i){
                p[j] = 1;
            }
        }
    }
    int x = 1;
    for(int i=2; i<4000000; i++){
        if(p[i] == 0){
            a[x] = i;
            x++;
        }
    }
    int sum = a[1];
    int L = 1;
    int R = 1;
    int cnt = 0;
    while(1){
        if(R >= x) break;

        if(sum == n){
            cnt++;
            R++;
            sum += a[R];
        }
        else if(sum < n){
            R++;
            sum += a[R];
        }
        else{
            sum -= a[L];
            L++;
        }
    }
    cout << cnt;
}
