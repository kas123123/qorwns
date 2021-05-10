#include <iostream>
#include <algorithm>
#include<time.h>

using namespace std;

//Select �˰���

int Rand_Partition(int* A,int L,int R){
    srand(time(NULL));
    int randNum = rand() % (R - L + 1) + L;

    int tmp1 = A[R];
    A[R] = A[randNum];
    A[randNum] = tmp1;

    int pivot = A[R];
    int i = L-1;

    for(int j = L; j < R; j++){
        if(A[j] <= pivot){
            i++;
            int tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
        }
    }
    int tmp = A[i+1];
    A[i+1] = A[R];
    A[R] = tmp;

    return i+1;
}

int Rand_select(int* A,int L,int R,int i){ // ������ �˰����� �̿��� i��° �� �����ϱ�
    if(L == R) return L;
    int x = Rand_Partition(A,L,R);
    int k = x - L + 1; //x�� ���°�� ū����? k��

    if(i == k) return x;
    else if(i < k) Rand_select(A,L,x-1,i);
    else Rand_select(A,x+1,R,i-k);
}

int middle_pos(int* A,int L,int R){ //ũ�Ⱑ �ִ� 5�� ��������
    for(int i=L+1; i<=R; i++){
        int key = A[i];
        int j = i-1;
        while(j > L-1 && A[j] > key){
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = key;
    }
    return (L+R)/2;
}

int Partition_2(int* A,int L,int R,int x){ //������ Partition, ���ϴ� ���� �������� �������ִ�.(���� 3�� �߰��ȰŴ�)
    int tmp1 = A[x];
    A[x] = A[R];
    A[R] = tmp1;

    int pivot = A[R];
    int i = L-1;

    for(int j = L; j < R; j++){
        if(A[j] <= pivot){
            i++;
            int tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
        }
    }
    int tmp = A[i+1];
    A[i+1] = A[R];
    A[R] = tmp;

    return i+1;
}


int Select_i(int* A,int L,int R,int i){

    if(L == R) return A[L];
    int cnt = L; //�� �߾Ӱ��� �Ǿտ� ���� �Ұ��̴�.
    for(int j=L; j<=R; j += 5){
        int x = middle_pos(A,j,min(j+4,R));

        int tmp = A[cnt];
        A[cnt] = A[x];
        A[x] = tmp;

        cnt++;
    }

    //A[L] ~ A[cnt-1]�� �߾Ӱ����̴�.

    int M = (cnt-1-L+1)/2;

    M = Rand_select(A,L,cnt-1,M); // M��° ū���� pos�� ���� O(N)

    int go = Partition_2(A,L,R,M); //5���� ������ �װ��� �߾Ӱ����� ��Ƴ������� �߾Ӱ��� �������� ������.

    int k = go - L + 1;

    if(k == i) return A[go];
    else if(i < k){
        Select_i(A,L,go-1,i);
    }
    else{
        Select_i(A,go+1,R,i-k);
    }
}


int main()
{
    int n,a[100000];
    for(int i=1; i<=10000; i++){
        a[i] = i;
    }
    srand(time(NULL));    // ������ ���� �߻��ϱ� ���� ����Ѵ�.

    for(int i=0; i<1000; i++) {    // �����۾��� 30�� �ݺ��ϱ� ���� for��
        int randNum1 = rand() % 10000 + 1;    //0~9������ ������ ���� �߻��Ѵ�.
        int randNum2 = rand() % 10000 + 1;
        int temp;
        temp = a[randNum1];
        a[randNum1] = a[randNum2];
        a[randNum2] = temp;
    }

    cout << Select_i(a,1,10000,5000);
}
