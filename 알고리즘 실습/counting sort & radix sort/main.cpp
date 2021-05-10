#include <iostream>

using namespace std;

void Counting_sort(int* A,int* B,int n,int k){ //�Է¹޴� ��� ���Ұ� k���� ����
    int* C = new int[k+1];
    for(int i=0; i<=k; i++){
        C[i] = 0;
    }
    for(int i=1; i<=n; i++){
        C[A[i]]++;
    } // C[i]�� A�� ����ִ� i�� ����

    for(int i=1; i<=k; i++){
        C[i] += C[i-1];
    } // ���� C[i]�� i���� �۰ų� ���� ���� ����

    for(int i=n; i>0; i--){ //�ڿ������� �ִ� ������ Stable ���¸� �����ϱ� ���ؼ� �̴�.
        B[C[A[i]]] = A[i];
        C[A[i]]--;
    }
    delete[] C;
}



void Radix_Counting_sort(int* A,int n,int d){ //�Է¹޴� ��� ���Ұ� k���� ����
    int* B = new int[n+1];
    int* C = new int[10];

    for(int i=0; i<10; i++){
        C[i] = 0;
    }

    for(int i=1; i<=n; i++){
        C[(A[i]/d)%10]++;
    } // C[i]�� A�� ����ִ� i�� ����

    for(int i=1; i<10; i++){
        C[i] += C[i-1];
    } // ���� C[i]�� i���� �۰ų� ���� ���� ����

    for(int i=n; i>0; i--){ //�ڿ������� �ִ� ������ Stable ���¸� �����ϱ� ���ؼ� �̴�.
        B[C[(A[i]/d)%10]] = A[i];
        C[(A[i]/d)%10]--;
    }

    for(int i=1; i<=n; i++){
        A[i] = B[i];
    }

    delete[] B,C;
}

void Radix_sort(int* A,int n,int d){ //d�� �ڸ��� ����, ex) 456�̸� 3�ڸ� ������
    int cnt = 1;
    for(int i=1; i<=d; i++){
        Radix_Counting_sort(A,n,cnt);
        cnt *= 10;
    }
}


int main()
{
    int a[10000],b[10000],n;
    cin >> n;
    for(int i=1; i<=n; i++){
        cin >> a[i];
    }

    Radix_sort(a,n,3);

    for(int i=1; i<=n; i++){
        cout << a[i] << " ";
    }
}
