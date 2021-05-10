#include <iostream>

using namespace std;

void Counting_sort(int* A,int* B,int n,int k){ //입력받는 모든 원소가 k보다 작음
    int* C = new int[k+1];
    for(int i=0; i<=k; i++){
        C[i] = 0;
    }
    for(int i=1; i<=n; i++){
        C[A[i]]++;
    } // C[i]는 A에 들어있는 i의 개수

    for(int i=1; i<=k; i++){
        C[i] += C[i-1];
    } // 이제 C[i]는 i보다 작거나 같은 수의 개수

    for(int i=n; i>0; i--){ //뒤에서부터 넣는 이유는 Stable 상태를 유지하기 위해서 이다.
        B[C[A[i]]] = A[i];
        C[A[i]]--;
    }
    delete[] C;
}



void Radix_Counting_sort(int* A,int n,int d){ //입력받는 모든 원소가 k보다 작음
    int* B = new int[n+1];
    int* C = new int[10];

    for(int i=0; i<10; i++){
        C[i] = 0;
    }

    for(int i=1; i<=n; i++){
        C[(A[i]/d)%10]++;
    } // C[i]는 A에 들어있는 i의 개수

    for(int i=1; i<10; i++){
        C[i] += C[i-1];
    } // 이제 C[i]는 i보다 작거나 같은 수의 개수

    for(int i=n; i>0; i--){ //뒤에서부터 넣는 이유는 Stable 상태를 유지하기 위해서 이다.
        B[C[(A[i]/d)%10]] = A[i];
        C[(A[i]/d)%10]--;
    }

    for(int i=1; i<=n; i++){
        A[i] = B[i];
    }

    delete[] B,C;
}

void Radix_sort(int* A,int n,int d){ //d는 자리의 숫자, ex) 456이면 3자리 숫자임
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
