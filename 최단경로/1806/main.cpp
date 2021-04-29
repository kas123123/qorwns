#include <iostream>

using namespace std;

int a[100001];

int main()
{
    int n,s;
    int sum = 0;
    cin >> n >> s;
    for(int i=0; i<n; i++){
        cin >> a[i];
        sum += a[i];
    }
    if(sum < s){
        cout << "0";
        return 0;
    }
    int L = 0;
    int R = 0;
    sum = a[0];
    int cnt = n;
    while(1){
        if(sum >= s){
            if(R-L+1 < cnt){
                cnt = R - L + 1;
            }
            sum -= a[L];
            L++;
        }
        else if(sum < s){
            R++;
            if(R >= n) break;
            sum += a[R];
        }
        if(L > R) R = L;
    }
    cout << cnt;
}
