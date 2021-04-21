#include <iostream>

using namespace std;

int sudo[10][10];
int zero_i[82];
int zero_j[82];
int cnt = 1;
int fin = 0;

int check(int a,int b,int x){
    //가로
    for(int i=1; i<=9; i++){
        if(sudo[a][i] == x) return 0;
    }

    //세로
    for(int i=1; i<=9; i++){
        if(sudo[i][b] == x) return 0;
    }

    //상자 안
    if(a%3 == 0) a -= 2;
    else if(a%3 == 2) a -= 1;

    if(b%3 == 0) b -= 2;
    else if(b%3 == 2) b -= 1;

    for(int i=0; i<=2; i++){
        for(int j=0; j<=2; j++){
            if(sudo[a+i][b+j] == x) return 0;
        }
    }

    return 1;
}

void D(int x){
    if(x == cnt){
        for(int i=1; i<=9; i++){
            for(int j=1; j<=9; j++){
                cout << sudo[i][j] << " ";
            }
            cout << "\n";
        }
        fin = 1;
        return;
    }
    if(fin == 0){
        for(int i=1; i<=9; i++){
            if(check(zero_i[x],zero_j[x],i)){
                sudo[zero_i[x]][zero_j[x]] = i;
                D(x+1);
                sudo[zero_i[x]][zero_j[x]] = 0;
            }
        }
    }
}

int main()
{
    for(int i=1; i<=9; i++){
        for(int j=1; j<=9; j++){
            cin >> sudo[i][j];
            if(sudo[i][j] == 0){
                zero_i[cnt] = i;
                zero_j[cnt] = j;
                cnt++;
            }
        }
    }

    D(1);
}
