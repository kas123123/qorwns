#include <iostream>
#include <queue>
#include <stack>

using namespace std;

int t[100001] = {0};

int main()
{
    int n,k;
    cin >> n >> k;
    if(n == k){
        cout << "0\n" << n;
        return 0;
    }

    t[n] = 1;
    queue<int> q;
    q.push(n);
    while(1){
        int tmp = q.front();
        q.pop();
        if(tmp > 0 && t[tmp-1] == 0){
            t[tmp-1] = t[tmp] + 1;
            if(tmp - 1 == k) break;
            q.push(tmp-1);
        }
        if(tmp < 100000 && t[tmp+1] == 0){
            t[tmp+1] = t[tmp] + 1;
            if(tmp + 1 == k) break;
            q.push(tmp+1);
        }
        if(tmp <= 50000 && t[tmp*2] == 0){
            t[2*tmp] = t[tmp] + 1;
            if(tmp * 2 == k) break;
            q.push(2*tmp);
        }
    }

    cout << t[k]-1 << "\n";
    stack<int> s;

    int cnt = k;
    while(1){
        s.push(cnt);
        if(cnt == n) break;

        if(cnt > 0 && t[cnt] == t[cnt-1] + 1){
            cnt--;
        }
        else if(cnt < 100000 && t[cnt] == t[cnt+1] + 1){
            cnt++;
        }
        else{
            cnt /= 2;
        }
    }
    while(!s.empty()){
        cout << s.top() << " ";
        s.pop();
    }
}
