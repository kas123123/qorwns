#include <iostream>
#include <queue>

using namespace std;

int a[100001] = {0};
int n,k;
int time = 0;

void bfs(int x){
    queue<int> q;
    a[x] = 1;
    q.push(x);

    while(1){
        int tmp = q.size();
        for(int i=0; i<tmp; i++){
            int l = q.front();
            if(l < 100000 && a[l+1] == 0){
                q.push(l+1);
                a[l+1] = 1;
            }
            if(l > 0 && a[l-1] == 0){
                q.push(l-1);
                a[l-1] = 1;
            }
            if(l <= 50000 && a[2*l] == 0){
                q.push(2*l);
                a[2*l] = 1;
            }
            q.pop();
        }
        time++;
        if(a[k] == 1) break;
    }
}



int main()
{
    cin >> n >> k;
    if(n == k){
        cout << "0";
        return 0;
    }
    bfs(n);
    cout << time;
}
