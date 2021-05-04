#include <iostream>
#include <algorithm>

using namespace std;

int n;
long long a[31];
long long a1[33000];
long long a2[33000];
int cnt1;
int cnt2;
long long sum = 0;
void go(int x){
    if(x == 0){
        a1[cnt1] = sum;
        cnt1++;
        return;
    }

    for(int i=0; i<2; i++){
        if(i == 0){
            sum += a[x];
            go(x-1);
            sum -= a[x];
        }
        else{
            go(x-1);
        }
    }
}

void go1(int x){
    if(x == n+1){
        a2[cnt2] = sum;
        cnt2++;
        return;
    }

    for(int i=0; i<2; i++){
        if(i == 0){
            sum += a[x];
            go1(x+1);
            sum -= a[x];
        }
        else{
            go1(x+1);
        }
    }
}
int main()
{
    int c;
    cin >> n >> c;
    for(int i=1; i<=n; i++){
        cin >> a[i];
    }
    cnt1 = 1;
    go((1+n)/2);
    cnt2 = 1;
    go1((1+n)/2+1);
    sort(a2,a2+cnt2);

    int cnt = 0;
    for(int i=1; i<cnt1; i++){
        for(int j=1; j<cnt2; j++){
            if(a1[i] + a2[j] > c) break;
            else cnt++;
        }
    }
    cout << cnt;
}
