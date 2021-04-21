#include <iostream>

using namespace std;

int c[26][26];
int a[1000];
int b[1000];
int n;
int sum = 0;

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

void dfs(int x,int y){
    sum++;
    c[x][y] = 0;
    if(x > 1 && c[x-1][y] == 1){
        dfs(x-1,y);
    }
    if(x < n && c[x+1][y] == 1){
        dfs(x+1,y);
    }
    if(y > 1 && c[x][y-1] == 1){
        dfs(x,y-1);
    }
    if(y < n && c[x][y+1] == 1){
        dfs(x,y+1);
    }
}

int main()
{
    int cnt = 1;
    string s;
    cin >> n;
    for(int i=1; i<=n; i++){
        cin >> s;
        for(int j=0; j<n; j++){
            c[i][j+1] = s[j] - '0';
        }
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(c[i][j] == 1){
                sum = 0;
                dfs(i,j);
                a[cnt] = sum;
                cnt++;
            }
        }
    }
    cout << cnt-1 << "\n";
    Merge(1,cnt-1);
    for(int i=1; i<cnt; i++){
        cout << a[i] << "\n";
    }
}
