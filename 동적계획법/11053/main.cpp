#include <iostream>

using namespace std;

int a[1001];
int cnt = 0;

void init(int x){
    if(a[cnt] < x){
        cnt++;
        a[cnt] = x;
        return;
    }

    //¿ø·¡ ¿©±â¼­ ÀÌºÐÅ½»öÀ» ÇØ¾ß »¡¶óÁü
    for(int i=1; i<=cnt; i++){
        if(x <= a[i]){a[i] = x; return;}
    }
}

int main()
{
    int n;
    cin >> n;
    int x;
    a[0] = 0;
    for(int i=1; i<=n; i++){
        cin >> x;
        init(x);
    }
    cout << cnt;
}
