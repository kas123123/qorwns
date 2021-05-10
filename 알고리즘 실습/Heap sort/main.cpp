#include <iostream>

//Max heap ����

using namespace std;

int heap[10000];
int heap_size;

//Max_heapify�� i��° ���Ұ� ��Ư���� �����ϴ��� �˻��ϰ� �ƴϸ� ��� �����������μ� �˻��ϴ� �Լ��̴�.
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
    for(int i=n/2; i>0; i--){   //leaf ������ ��� ���� Ư���� �����ϹǷ� ������ �ƴ� ������ ��Ư���� ��������Ѵ�.
        Max_heapify(A,i);
    }
}

void Heap_sort(int* A,int n){
    Build_Max_heap(A,n);
    for(int i = n; i > 1; i--){
        int tmp = A[1]; //A[1]�� �׻� ���ȿ��� �ִ밪�̹Ƿ� ��� �̾��ְ� �ǵڿ� �����Ѵ�.
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
