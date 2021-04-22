#include <iostream>
#include <queue>

using namespace std;

int a[101][101][101];
int m,n,h;
int cnt = 0;
int day = 0;

void bfs(){
    queue<int> q,q1,q2;
    for(int k=1; k<=h; k++){
        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                if(a[k][i][j] == 1){
                    q.push(k);
                    q1.push(i);
                    q2.push(j);
                }
            }
        }
    }

    while(1){
        if(q1.size() == 0) break;
        int tmp = q1.size();
        for(int i=0; i<tmp; i++){
            int t = q.front();
            int l = q1.front();
            int r = q2.front();
            if(l > 1 && a[t][l-1][r] == 0){
                q.push(t);
                q1.push(l-1);
                q2.push(r);
                a[t][l-1][r] = 1;
                cnt--;
            }
            if(l < n && a[t][l+1][r] == 0){
                q.push(t);
                q1.push(l+1);
                q2.push(r);
                a[t][l+1][r] = 1;
                cnt--;
            }
            if(r > 1 && a[t][l][r-1] == 0){
                q.push(t);
                q1.push(l);
                q2.push(r-1);
                a[t][l][r-1] = 1;
                cnt--;
            }
            if(r < m && a[t][l][r+1] == 0){
                q.push(t);
                q1.push(l);
                q2.push(r+1);
                a[t][l][r+1] = 1;
                cnt--;
            }
            if(t > 1 && a[t-1][l][r] == 0){
                q.push(t-1);
                q1.push(l);
                q2.push(r);
                a[t-1][l][r] = 1;
                cnt--;
            }
            if(t < h && a[t+1][l][r] == 0){
                q.push(t+1);
                q1.push(l);
                q2.push(r);
                a[t+1][l][r] = 1;
                cnt--;
            }
            q.pop();
            q1.pop();
            q2.pop();
        }
        day++;
    }
}


int main()
{
    cin >> m >> n >> h;
    for(int k=1; k<=h; k++){
        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                cin >> a[k][i][j];
                if(a[k][i][j] == 0) cnt++;
            }
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
