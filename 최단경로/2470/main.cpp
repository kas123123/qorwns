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

int Abs(int a){
    if(a < 0) return -a;
    return a;
}


int main()
{
    int n;
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a[i];
    }
    Merge(0,n-1);

    if(a[n-1] < 0){
        cout << a[n-2] << " " << a[n-1];
        return 0;
    }

    if(a[0] > 0){
        cout << a[0] << " " << a[1];
        return 0;
    }

    int L = 0;
    int R = n-1;

    int sum = Abs(a[L] + a[R]);
    int l = L;
    int r = R;

    while(1){
        if(L >= R) break;

        if(Abs(a[L] + a[R]) < sum){
            sum = Abs(a[L] + a[R]);
            l = L;
            r = R;
        }

        if(a[L] + a[R] > 0) R--;
        else if(a[L] + a[R] < 0) L++;
        else{
            cout << a[L] << " " << a[R];
            return 0;
        }
    }

    cout << a[l] << " " << a[r];
}
