#include <iostream>

using namespace std;

int a[1000001];
int b[1000001];

void hap(int L,int M,int R){
    int l = L;
    int r = M+1;
    int cnt = 0;
    while(1){
        if(l > M || r > R) break;

        if(a[l] >= a[r]){
            b[cnt] = a[r];
            cnt++;
            r++;
        }
        else{
            b[cnt] = a[l];
            cnt++;
            l++;
        }
    }
    if(l > M){
        for(int i=r; i<=R; i++){
            b[cnt] = a[i];
            cnt++;
        }
    }
    else{
        for(int i=l; i<=M; i++){
            b[cnt] = a[i];
            cnt++;
        }
    }
    for(int i=L; i<=R; i++){
        a[i] = b[i-L];
    }
}

void Merge(int L,int R){
    if(L == R) return;
    int M = (L+R)/2;
    Merge(L,M);
    Merge(M+1,R);
    hap(L,M,R);
}

int main()
{
    int n;
    cin >> n;
    for(int i=1; i<=n; i++){
        cin >> a[i];
    }

    Merge(1,n);

    for(int i=1; i<=n; i++){
        cout << a[i] << "\n";
    }
}
