#include <iostream>

using namespace std;

int Partition(int* A,int L,int R){ //A[R]을 기준으로 잡아서 이 값보다 작은건 왼쪽 큰건 오른쪽으로 보내고 그 위치를 리턴하는 함수
    int pivot = A[R];
    int i = L-1; //i 왼쪽은 pivot 보다 작은거, i 오른쪽은 pivot 보다 큰거

    for(int j = L; j < R; j++){
        if(A[j] <= pivot){
            i++;
            int tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
        }
    }
    int tmp = A[i+1]; //A[i]까지 pivot보다 작거나 같고 A[i+1]부터 pivot 보다 크므로 A[i+1], A[R]을 교환해주면 (i+1)을 기준으로 잘 나뉜다.
    A[i+1] = A[R];
    A[R] = tmp;

    return i+1;
}

void Quick_sort(int* A,int L,int R){
    if(L < R){
        int p = Partition(A,L,R);
        Quick_sort(A,L,p-1);
        Quick_sort(A,p+1,R);
    }
}

int main()
{
    int n,a[10000];
    cin >> n;
    for(int i=1; i<=n; i++){
        cin >> a[i];
    }

    Quick_sort(a,1,n);

    for(int i=1; i<=n; i++){
        cout << a[i] << " ";
    }
}
