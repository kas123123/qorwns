#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

int l[1001][1001];
stack<char> s;

int main()
{
    string s1,s2;
    cin >> s1;
    cin >> s2;

    for(int i=0; i<=s1.size(); i++){
        for(int j=0; j<=s2.size(); j++){
            if(i == 0 || j == 0) l[i][j] = 0;
            else if(s1[i-1] == s2[j-1]){
                l[i][j] = l[i-1][j-1] + 1;
            }
            else{
                l[i][j] = max(l[i-1][j],l[i][j-1]);
            }
        }
    }
    int tmp = l[s1.size()][s2.size()];
    cout << tmp << "\n";
    int w,h;
    h = s1.size();
    w = s2.size();
    while(1){
        int ed = 0;
        for(int i=h; i>=0; i--){
            for(int j=w; j>=0; j--){
                if(s1[i-1] == s2[j-1] && l[i][j] == tmp){
                    s.push(s1[i-1]);
                    tmp--;
                    h = i-1;
                    w = j-1;
                    ed = 1;
                    break;
                }
            }
            if(ed) break;
        }
        if(tmp == 0) break;
    }
    while(1){
        cout << s.top();
        s.pop();
        if(s.empty()) break;
    }
}
