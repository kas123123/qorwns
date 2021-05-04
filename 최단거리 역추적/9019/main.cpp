#include <iostream>
#include <queue>
#include <stack>

using namespace std;

void go(int a,int b){
    int d[10000] = {0};
    d[a] = 1;
    queue<int> q;
    q.push(a);
    int D,S,L,R;

    while(1){
        int tmp = q.front();
        q.pop();
        D = (tmp * 2) % 10000;
        if(d[D] == 0){
            d[D] = d[tmp] + 1;
            if(D == b) break;
            q.push(D);
        }

        S = (tmp + 9999) % 10000;
        if(d[S] == 0){
            d[S] = d[tmp] + 1;
            if(S == b) break;
            q.push(S);
        }

        L = tmp/1000 + (tmp%1000)*10;
        if(d[L] == 0){
            d[L] = d[tmp] + 1;
            if(L == b) break;
            q.push(L);
        }

        R = tmp/10 + (tmp%10)*1000;
        if(d[R] == 0){
            d[R] = d[tmp] + 1;
            if(R == b) break;
            q.push(R);
        }
    }

    stack<char> s;

    int cnt = b;
    while(cnt != a){
        if(cnt%2 == 0 && d[cnt] == d[cnt/2] + 1){
            s.push('D');
            cnt /= 2;
        }
        else if(cnt%2 == 0 && d[cnt] == d[(cnt+10000)/2] + 1){
            s.push('D');
            cnt = (cnt+10000)/2;
        }
        else if(d[cnt] == d[(cnt+1)%10000] + 1){
            s.push('S');
            cnt = (cnt+1)%10000;
        }
        else if(d[cnt] == d[cnt/1000 + (cnt%1000)*10] + 1){
            s.push('R');
            cnt = cnt/1000 + (cnt%1000)*10;
        }
        else{
            s.push('L');
            cnt = cnt/10 + (cnt%10)*1000;
        }
    }

    while(!s.empty()){
        cout << s.top();
        s.pop();
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;
    int n,k;
    for(int i=0; i<t; i++){
        cin >> n >> k;
        if(n == k) continue;
        go(n,k);
        if(i < t-1) cout << "\n";
    }
}
