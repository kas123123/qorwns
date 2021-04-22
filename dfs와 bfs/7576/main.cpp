#include <iostream>
#include <queue>

using namespace std;

int a[1001][1001];
int m,n;
int cnt = 0;
int day = 0;

void bfs(){
    queue<int> q1,q2;

    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(a[i][j] == 1){
                q1.push(i);
                q2.push(j);
            }
        }
    }

    while(1){
        if(q1.size() == 0) break;
        int tmp = q1.size();
        for(int i=0; i<tmp; i++){
            int l = q1.front();
            int r = q2.front();
            if(l > 1 && a[l-1][r] == 0){
                q1.push(l-1);
                q2.push(r);
                a[l-1][r] = 1;
                cnt--;
            }
            if(l < n && a[l+1][r] == 0){
                q1.push(l+1);
                q2.push(r);
                a[l+1][r] = 1;
                cnt--;
            }
            if(r > 1 && a[l][r-1] == 0){
                q1.push(l);
                q2.push(r-1);
                a[l][r-1] = 1;
                cnt--;
            }
            if(r < m && a[l][r+1] == 0){
                q1.push(l);
                q2.push(r+1);
                a[l][r+1] = 1;
                cnt--;
            }
            q1.pop();
            q2.pop();
        }
        day++;
    }
}


int main()
{
    cin >> m >> n;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            cin >> a[i][j];
            if(a[i][j] == 0) cnt++;
        }
    }
    if(cnt == 0){
        cout << "0";
        return 0;
    }
    bfs();
    if(cnt != 0) cout << "-1";
    else cout << day-1;
}
