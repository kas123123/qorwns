#include <iostream>

using namespace std;

int Partition(int* A,int L,int R){ //A[R]�� �������� ��Ƽ� �� ������ ������ ���� ū�� ���������� ������ �� ��ġ�� �����ϴ� �Լ�
    int pivot = A[R];
    int i = L-1; //i ������ pivot ���� ������, i �������� pivot ���� ū��

    for(int j = L; j < R; j++){
        if(A[j] <= pivot){
            i++;
            int tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
        }
    }
    int tmp = A[i+1]; //A[i]���� pivot���� �۰ų� ���� A[i+1]���� pivot ���� ũ�Ƿ� A[i+1], A[R]�� ��ȯ���ָ� (i+1)�� �������� �� ������.
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
