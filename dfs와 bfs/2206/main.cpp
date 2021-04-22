#include <iostream>
#include <queue>

using namespace std;

int a[1001][1001];
int check[1001][1001] = {0}; //�� �ȶհ�
int check_[1001][1001] = {0}; // �� �հ�
int n,m;
int time = 0;

int bfs(){
    queue<int> q1,q2,q;
    q1.push(1);
    q2.push(1);
    q.push(0);
    //q�� ���� ������ �μ� ���θ� �����ϴ� ť, 1�� �μ��� �ִ°���
    check[1][1] = 1;

    while(1){
        int tmp = q.size();
        if(q.size() == 0) return 0;

        for(int i=0; i<tmp; i++){
            int l = q1.front();
            int r = q2.front();
            int x = q.front();

            //�׳� ���� �ȸ����־� �ٷ� ����
            if(l > 1 && a[l-1][r] == 0){
                if(x == 0 && check[l-1][r] == 0){
                    q1.push(l-1);
                    q2.push(r);
                    q.push(x);
                    check[l-1][r] = 1;
                }
                if(x == 1 && check_[l-1][r] == 0){
                    q1.push(l-1);
                    q2.push(r);
                    q.push(x);
                    check_[l-1][r] = 1;
                }
            }
            if(l < n && a[l+1][r] == 0){
                if(x == 0 && check[l+1][r] == 0){
                    q1.push(l+1);
                    q2.push(r);
                    q.push(x);
                    check[l+1][r] = 1;
                }
                if(x == 1 && check_[l+1][r] == 0){
                    q1.push(l+1);
                    q2.push(r);
                    q.push(x);
                    check_[l+1][r] = 1;
                }
            }
            if(r > 1 && a[l][r-1] == 0){
                if(x == 0 && check[l][r-1] == 0){
                    q1.push(l);
                    q2.push(r-1);
                    q.push(x);
                    check[l][r-1] = 1;
                }
                if(x == 1 && check_[l][r-1] == 0){
                    q1.push(l);
                    q2.push(r-1);
                    q.push(x);
                    check_[l][r-1] = 1;
                }
            }
            if(r < m && a[l][r+1] == 0){
                if(x == 0 && check[l][r+1] == 0){
                    q1.push(l);
                    q2.push(r+1);
                    q.push(x);
                    check[l][r+1] = 1;
                }
                if(x == 1 && check_[l][r+1] == 0){
                    q1.push(l);
                    q2.push(r+1);
                    q.push(x);
                    check_[l][r+1] = 1;
                }
            }

            //���� ���� �������� ���� ���� �հ� ����
            if(x == 0 && l > 1 && check_[l-1][r] == 0 && a[l-1][r] == 1){
                q1.push(l-1);
                q2.push(r);
                q.push(1);
                check_[l-1][r] = 1;
            }
            if(x == 0 && l < n && check_[l+1][r] == 0 && a[l+1][r] == 1){
                q1.push(l+1);
                q2.push(r);
                q.push(1);
                check_[l+1][r] = 1;
            }
            if(x == 0 && r > 1 && check_[l][r-1] == 0 && a[l][r-1] == 1){
                q1.push(l);
                q2.push(r-1);
                q.push(1);
                check_[l][r-1] = 1;
            }
            if(x == 0 && r < m && check_[l][r+1] == 0 && a[l][r+1] == 1){
                q1.push(l);
                q2.push(r+1);
                q.push(1);
                check_[l][r+1] = 1;
            }
            q1.pop();
            q2.pop();
            q.pop();
        }
        time++;
        if(check[n][m] == 1 || check_[n][m] == 1) return 1;
    }
}

int main()
{
    string s;
    cin >> n >> m;
    for(int i=1; i<=n; i++){
        cin >> s;
        for(int j=0; j<m; j++){
            a[i][j+1] = s[j] - '0';
        }
    }
    if(n == 1 && m == 1){cout << "1"; return 0;}

    if(bfs()){
        cout << time+1;
    }
    else cout << "-1";
}
