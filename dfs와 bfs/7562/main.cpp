#include <iostream>
#include <queue>

using namespace std;

int bfs(int l,int r,int X,int Y,int n){
    int check[301][301] = {0};
    int cnt = 0;
    queue<int> q1,q2;
    q1.push(l);
    q2.push(r);
    check[l][r] = 1;
    while(1){
        int tmp = q1.size();
        for(int i=0; i<tmp; i++){
            int x = q1.front();
            int y = q2.front();

            if(x > 2 && y > 1 && check[x-2][y-1] == 0){
                q1.push(x-2);
                q2.push(y-1);
                check[x-2][y-1] = 1;
            }
            if(x > 2 && y < n && check[x-2][y+1] == 0){
                q1.push(x-2);
                q2.push(y+1);
                check[x-2][y+1] = 1;
            }
            if(x < n-1 && y > 1 && check[x+2][y-1] == 0){
                q1.push(x+2);
                q2.push(y-1);
                check[x+2][y-1] = 1;
            }
            if(x < n-1 && y < n && check[x+2][y+1] == 0){
                q1.push(x+2);
                q2.push(y+1);
                check[x+2][y+1] = 1;
            }
            if(x > 1 && y > 2 && check[x-1][y-2] == 0){
                q1.push(x-1);
                q2.push(y-2);
                check[x-1][y-2] = 1;
            }
            if(x < n && y > 2 && check[x+1][y-2] == 0){
                q1.push(x+1);
                q2.push(y-2);
                check[x+1][y-2] = 1;
            }
            if(x > 1 && y < n-1 && check[x-1][y+2] == 0){
                q1.push(x-1);
                q2.push(y+2);
                check[x-1][y+2] = 1;
            }
            if(x < n && y < n-1 && check[x+1][y+2] == 0){
                q1.push(x+1);
                q2.push(y+2);
                check[x+1][y+2] = 1;
            }
            q1.pop();
            q2.pop();
        }
        cnt++;
        if(check[X][Y] == 1) return cnt;
    }

}

int main()
{
    int m;
    int n;
    int a,b,c,d;

    cin >> m;

    for(int i=0; i<m; i++){
        cin >> n;
        cin >> a >> b >> c >> d;
        if(a == c && b == d) cout << "0\n";
        else cout << bfs(a+1,b+1,c+1,d+1,n) << "\n";
    }
}
