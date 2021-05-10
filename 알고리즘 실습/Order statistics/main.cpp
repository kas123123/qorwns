#include <iostream>
#include <algorithm>
#include<time.h>

using namespace std;

//Select 알고리즘

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

int Rand_select(int* A,int L,int R,int i){ // 퀵정렬 알고리즘을 이용한 i번째 값 리턴하기
    if(L == R) return L;
    int x = Rand_Partition(A,L,R);
    int k = x - L + 1; //x가 몇번째로 큰거임? k요

    if(i == k) return x;
    else if(i < k) Rand_select(A,L,x-1,i);
    else Rand_select(A,x+1,R,i-k);
}

int middle_pos(int* A,int L,int R){ //크기가 최대 5인 삽입정렬
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

int Partition_2(int* A,int L,int R,int x){ //개선된 Partition, 원하는 원소 기준으로 나눌수있다.(위에 3줄 추가된거다)
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
    int cnt = L; //각 중앙값을 맨앞에 저장 할것이다.
    for(int j=L; j<=R; j += 5){
        int x = middle_pos(A,j,min(j+4,R));

        int tmp = A[cnt];
        A[cnt] = A[x];
        A[x] = tmp;

        cnt++;
    }

    //A[L] ~ A[cnt-1]은 중앙값들이다.

    int M = (cnt-1-L+1)/2;

    M = Rand_select(A,L,cnt-1,M); // M번째 큰수의 pos를 리턴 O(N)

    int go = Partition_2(A,L,R,M); //5개로 분할후 그것의 중앙값들을 모아놓은곳의 중앙값을 기준으로 나눴다.

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
    srand(time(NULL));    // 랜덤한 수를 발생하기 위해 사용한다.

    for(int i=0; i<1000; i++) {    // 섞는작업을 30번 반복하기 위한 for문
        int randNum1 = rand() % 10000 + 1;    //0~9까지의 랜덤한 수를 발생한다.
        int randNum2 = rand() % 10000 + 1;
        int temp;
        temp = a[randNum1];
        a[randNum1] = a[randNum2];
        a[randNum2] = temp;
    }

    cout << Select_i(a,1,10000,5000);
}
