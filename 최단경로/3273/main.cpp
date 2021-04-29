#include <iostream>

using namespace std;

int a[100001];
int b[100001];

void hap(int L,int M,int R){
    int l = L;
    int r = M+1;
    int cnt = 0;
    while(1){
        if(l > M || r > R) break;

        if(a[l] > a[r]){
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
    else if(r > R){
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
    if(L != R){
        int M = (L+R)/2;
        Merge(L,M);
        Merge(M+1,R);
        hap(L,M,R);
    }
}



int main()
{
    int n,s,cnt = 0;
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a[i];
    }
    Merge(0,n-1);
    cin >> s;
    int L,R;
    L = 0;
    R = n-1;

    while(1){
        if(L >= R) break;

        if(a[L] + a[R] < s) L++;
        else if(a[L] + a[R] > s) R--;
        else{
            cnt++;
            L++;
        }
    }
    cout << cnt;
}
