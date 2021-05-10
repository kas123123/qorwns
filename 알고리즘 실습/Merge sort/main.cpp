#include <iostream>

#define INF 100000000

using namespace std;

void Merge(int* A, int L, int M,int R){

    int l = M - L + 1;
    int r = R - M;

    int* a = new int[l+1]; //왼쪽 부분 저장
    int* b = new int[r+1]; //오른쪽 부분 저장

    for(int i=0; i<l; i++){
        a[i] = A[L+i];
    }
    for(int i=0; i<r; i++){
        b[i] = A[M+1+i];
    }
    a[l] = INF;
    b[r] = INF;

    int cnt1 = 0;
    int cnt2 = 0;

    for(int i=L; i<=R; i++){
        if(a[cnt1] > b[cnt2]){
            A[i] = b[cnt2];
            cnt2++;
        }
        else{
            A[i] = a[cnt1];
            cnt1++;
        }
    }
    delete[] a,b;
}

void Merge_sort(int* A,int L,int R){
    if(L < R){
        int M = (L+R)/2;
        Merge_sort(A,L,M);
        Merge_sort(A,M+1,R);
        Merge(A,L,M,R);
    }
}

int main()
{
    int n,a[10000];
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a[i];
    }

    Merge_sort(a,0,n-1);

    for(int i=0; i<n; i++){
        cout << a[i] << " ";
    }
}
