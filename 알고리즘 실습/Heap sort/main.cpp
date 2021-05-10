#include <iostream>

//Max heap 기준

using namespace std;

int heap[10000];
int heap_size;

//Max_heapify는 i번째 원소가 힙특성을 만족하는지 검사하고 아니면 계속 내려보냄으로서 검사하는 함수이다.
void Max_heapify(int* A,int i){
    int mx;
    if(2*i <= heap_size && A[2*i] > A[i]){
        mx = 2*i;
    }
    else mx = i;

    if(2*i < heap_size && A[2*i+1] > A[mx]){
        mx = 2*i+1;
    }

    if(i != mx){
        int tmp = A[i];
        A[i] = A[mx];
        A[mx] = tmp;
        Max_heapify(A,mx);
    }
}

void Build_Max_heap(int* A,int n){
    heap_size = n;
    for(int i=n/2; i>0; i--){   //leaf 노드들은 모두 힘의 특성을 만족하므로 리프가 아닌 노드들의 힙특성을 고쳐줘야한다.
        Max_heapify(A,i);
    }
}

void Heap_sort(int* A,int n){
    Build_Max_heap(A,n);
    for(int i = n; i > 1; i--){
        int tmp = A[1]; //A[1]은 항상 힙안에서 최대값이므로 계속 뽑아주고 맨뒤에 저장한다.
        A[1] = A[heap_size];
        A[heap_size] = tmp;
        heap_size--;
        Max_heapify(A,1);
    }
}

int main()
{
    int n,a[10000];
    cin >> n;
    for(int i=1; i<=n; i++){
        cin >> a[i];
    }

    Heap_sort(a,n);

    for(int i=1; i<=n; i++){
        cout << a[i] << " ";
    }
}
