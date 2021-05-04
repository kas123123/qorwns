#include <iostream>
#include <vector>
#include <utility>
#include <stack>

using namespace std;

int a[1000001]; //입력
int b[1000001]; //가장긴 부분수열
pair<int,int> c[1000001]; //a[i]의 pos를 저장하는 배열
stack<int> s;

int go(int L,int R,int x){
    int M;
    while(1){
        M = (L+R)/2;
        if(b[M] < x){
            L = M+1;
        }
        else{
            R = M;
        }
        if(L >= R) break;
    }
    return L;
}

int main()
{
    int cnt = 0;
    int n;
    b[0] = 0;
    cin >> n;
    for(int i=1; i<=n; i++){
        cin >> a[i];
        if(a[i] > b[cnt]){
            cnt++;
            b[cnt] = a[i];
            c[i].first = cnt;
            c[i].second = a[i];
        }
        else{
            int tmp = go(1,cnt,a[i]);
            b[tmp] = a[i];
            c[i].first = tmp;
            c[i].second = a[i];
        }
    }
    cout << cnt << "\n";
    for(int i=n; i>0; i--){
        if(c[i].first == cnt){
            s.push(c[i].second);
            cnt--;
            if(cnt == 0) break;
        }
    }
    while(1){
        cout << s.top() << " ";
        s.pop();
        if(s.empty()) break;
    }
}
