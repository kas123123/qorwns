#include <iostream>
#include <queue>

using namespace std;

typedef struct Tree* BTree;

struct Tree{
    BTree C[4]; //자식 주소 최대 4개 저장 (물론 2-3트리이므로 4개 저장되면 바로 나눠야한다)
    int data[3]; //key 최대 3개 저장 (역시 3개되면 나눠야함)
    int cnt; //data개수 1~3
    BTree P; //부모 주소
};

BTree MakeTree(int x){
    BTree T = new struct Tree;
    for(int i=0; i<4; i++){
        T -> C[i] = NULL;
    }
    T -> data[0] = x;
    T -> data[1] = -1;
    T -> data[2] = -1;
    T -> cnt = 1;
    T -> P = NULL;
}


BTree Split(BTree T){ //크기가 3일때 분할
    BTree Y = MakeTree(T -> data[0]);
    BTree X = MakeTree(T -> data[1]);
    BTree Z = MakeTree(T -> data[2]);
    if(T -> C[0] != NULL){
        Y -> C[0] = T -> C[0];
        Y -> C[0] -> P = Y;
    }
    if(T -> C[1] != NULL){
        Y -> C[1] = T -> C[1];
        Y -> C[1] -> P = Y;
    }
    if(T -> C[2] != NULL){
        Z -> C[0] = T -> C[2];
        Z -> C[0] -> P = Z;
    }
    if(T -> C[3] != NULL){
        Z -> C[1] = T -> C[3];
        Z -> C[1] -> P = Z;
    }
    Y -> P = X;
    Z -> P = X;
    X -> C[0] = Y;
    X -> C[1] = Z;

    if(T -> P == NULL) return X;
    else if(X -> data[0] < T -> P -> data[0]){
        T -> P -> data[2] = T -> P -> data[1];
        T -> P -> C[3] = T -> P -> C[2];
        T -> P -> data[1] = T -> P -> data[0];
        T -> P -> C[2] = T -> P -> C[1];

        T -> P -> data[0] = X -> data[0];
        T -> P -> C[0] = Y;
        T -> P -> C[1] = Z;

        Y -> P = T -> P;
        Z -> P = T -> P;

        T -> P -> cnt += 1;
    }
    else if(T -> P -> cnt == 1 || X -> data[0] < T -> P -> data[1]){
        T -> P -> data[2] = T -> P -> data[1];
        T -> P -> C[3] = T -> P -> C[2];

        T -> P -> data[1] = X -> data[0];
        T -> P -> C[1] = Y;
        T -> P -> C[2] = Z;

        Y -> P = T -> P;
        Z -> P = T -> P;

        T -> P -> cnt += 1;
    }
    else{
        T -> P -> data[2] = X -> data[0];
        T -> P -> C[2] = Y;
        T -> P -> C[3] = Z;

        Y -> P = T -> P;
        Z -> P = T -> P;

        T -> P -> cnt += 1;
    }
    return Y;
}

BTree Insert(BTree T,int x){
    if(T == NULL){
        T = MakeTree(x);
    }
    else if(x < T -> data[0]){
        if(T -> C[0] == NULL){
            T -> data[2] = T -> data[1];
            T -> data[1] = T -> data[0];
            T -> data[0] = x;
            T -> cnt += 1;
            if(T -> cnt == 3) T = Split(T);
        }
        else{
            T -> C[0] = Insert(T -> C[0],x);
            if(T -> C[0] -> cnt == 3) T -> C[0] = Split(T -> C[0]);
        }
    }
    else if(T -> cnt == 1 || x < T -> data[1]){
        if(T -> C[1] == NULL){
            T -> data[2] = T -> data[1];
            T -> data[1] = x;
            T -> cnt += 1;
            if(T -> cnt == 3) T = Split(T);
        }
        else{
            T -> C[1] = Insert(T -> C[1],x);
            if(T -> C[1] -> cnt == 3) T -> C[1] = Split(T -> C[1]);
        }
    }
    else{
        if(T -> C[2] == NULL){
            T -> data[2] = x;
            T -> cnt += 1;
            if(T -> cnt == 3) T = Split(T);
        }
        else{
            T -> C[2] = Insert(T -> C[2],x);
            if(T -> C[2] -> cnt == 3) T -> C[2] = Split(T -> C[2]);
        }
    }
    if(T -> cnt == 3) T = Split(T); //마지막에 head가 크기가 3일때
    return T;
}

BTree Delete(BTree T,int x){
    if(T == NULL)   cout << "삭제할거 없음\n";
    else if(T -> data[0] == x || T -> data[1] == x){
        if(T -> C[0] == NULL && T -> C[1] == NULL && T -> C[2] == NULL){ //리프일때 삭제 시작
            if(T -> cnt == 2){ //리프에서 삭제할값이 2개면 그냥 삭제하면됨
                if(T -> data[0] == x){
                    T -> data[0] = T -> data[1];
                }
                T -> data[1] = -1;
                T -> cnt -= 1;
            }
            else if(T -> P == NULL){
                cout << "하나 남았는데 왜 삭제하는거야!!!\n";
            }
            else if(T -> P -> cnt == 2){ //부모의 원소가 2개일때
                if(T -> P -> C[0] -> cnt + T -> P -> C[1] -> cnt + T -> P -> C[2] -> cnt == 3){ //2,1,1,1 인 경우
                    if(T -> P -> C[0] == T){
                        T -> P -> C[0] -> data[0] = T -> P -> data[0];
                        T -> P -> data[0] = T -> P -> C[1] -> data[0];
                        T -> P -> C[1] -> data[0] = T -> P -> data[1];
                        T -> P -> C[1] -> data[1] = T -> P -> C[2] -> data[0];
                    }
                    else if(T -> P -> C[1] == T){
                        T -> P -> C[1] -> data[0] = T -> P -> data[1];
                        T -> P -> C[1] -> data[1] = T -> P -> C[2] -> data[0];
                    }
                    else{
                        T -> P -> C[1] -> data[1] = T -> P -> data[1];
                    }
                    T -> P -> C[1] -> cnt += 1;
                    T -> P -> data[1] = -1;
                    T -> P -> cnt -= 1;
                    T -> P -> C[2] = NULL;
                }
                else if(T -> P -> C[0] == T){
                    T -> data[0] = T -> P -> data[0];
                    T -> P -> data[0] = T -> P -> C[1] -> data[0];
                    T -> P -> C[1] -> data[0] = T -> P -> C[1] -> data[1];
                    T -> P -> C[1] -> data[1] = -1;
                    T -> P -> C[1] -> cnt -= 1;
                    if(T -> P -> C[1] -> cnt == 0){
                        T -> P -> C[1] -> data[0] = T -> P -> data[1];
                        T -> P -> data[1] = T -> P -> C[2] -> data[0];
                        T -> P -> C[2] -> data[0] = T -> P -> C[2] -> data[1];
                        T -> P -> C[2] -> data[1] = -1;
                        T -> P -> C[2] -> cnt -= 1;
                    }
                }
                else if(T -> P -> C[1] == T){
                    if(T -> P -> C[0] -> cnt == 2){
                        T -> data[0] = T -> P -> data[0];
                        T -> P -> data[0] = T -> P -> C[0] -> data[1];
                        T -> P -> C[0] -> data[1] = -1;
                        T -> P -> C[0] -> cnt -= 1;
                    }
                    else{
                        T -> data[0] = T -> P -> data[1];
                        T -> P -> data[1] = T -> P -> C[2] -> data[0];
                        T -> P -> C[2] -> data[0] = T -> P -> C[2] -> data[1];
                        T -> P -> C[2] -> data[1] = -1;
                        T -> P -> C[2] -> cnt -= 1;
                    }
                }
                else{
                    if(T -> P -> C[1] -> cnt == 2){
                        T -> data[0] = T -> P -> data[1];
                        T -> P -> data[1] = T -> P -> C[1] -> data[1];
                        T -> P -> C[1] -> data[1] = -1;
                        T -> P -> C[1] -> cnt -= 1;
                    }
                    else{
                        T -> data[0] = T -> P -> data[1];
                        T -> P -> data[1] = T -> P -> C[1] -> data[0];
                        T -> P -> C[1] -> data[0] = T -> P -> data[0];
                        T -> P -> data[0] = T -> P -> C[0] -> data[1];
                        T -> P -> C[0] -> data[1] = -1;
                        T -> P -> C[0] -> cnt -= 1;
                    }
                }
            }
            else{ //부모의 원소가 1개 일때
                if(T -> P -> C[0] -> cnt + T -> P -> C[1] -> cnt == 2){ // 1,1,1 인 경우 -> ******* 제일 중요한 경우임 *******
                    if(T -> P -> P == NULL){
                        T -> P -> data[2] = T -> P -> C[1] -> data[0];
                        T -> P -> data[1] = T -> P -> data[0];
                        T -> P -> data[0] = T -> P -> C[0] -> data[0];
                        if(T -> P -> data[0] == x){
                            T -> P -> data[0] = T -> P -> data[1];
                            T -> P -> data[1] = T -> P -> data[2];
                        }
                        T -> P -> data[2] = -1;
                        T -> P -> cnt = 2;
                        T = T -> P;
                        T -> C[0] = NULL;
                        T -> C[1] = NULL;
                        T -> C[2] = NULL;
                    }
                    else if(T -> P -> P -> cnt == 2){ //부모의 부모에서 무난히 가져올수 있는 경우 (노드가 2개라 가져와도 크게 문제없음)
                        if(T -> P -> P -> C[0] == T -> P){
                            T -> P -> C[0] -> data[1] = T -> P -> data[0];
                            T -> P -> C[0] -> data[2] = T -> P -> C[1] -> data[0];
                            T -> P -> data[0] = T -> P -> P -> data[0];
                            if(T -> P -> P -> C[1] -> cnt == 2){
                                T -> P -> P -> data[0] = T -> P -> P -> C[1] -> data[0];
                                T -> P -> C[1] = T -> P -> P -> C[1] -> C[0];
                                T -> P -> P -> C[1] -> C[0] -> P = T -> P;
                                T -> P -> P -> C[1] -> data[0] = T -> P -> P -> C[1] -> data[1];
                                T -> P -> P -> C[1] -> data[1] = -1;
                                T -> P -> P -> C[1] -> cnt -= 1;
                                T -> P -> P -> C[1] -> C[0] = T -> P -> P -> C[1] -> C[1];
                                T -> P -> P -> C[1] -> C[1] = T -> P -> P -> C[1] -> C[2];
                                T -> P -> P -> C[1] -> C[2] = NULL;
                            }
                            else{
                                T -> P -> P -> data[0] = T -> P -> P -> data[1];
                                T -> P -> P -> data[1] = -1;
                                T -> P -> P -> cnt -= 1;
                                T -> P -> data[1] = T -> P -> P -> C[1] -> data[0];
                                T -> P -> cnt += 1;
                                T -> P -> C[1] = T -> P -> P -> C[1] -> C[0];
                                T -> P -> P -> C[1] -> C[0] -> P = T -> P;
                                T -> P -> C[2] = T -> P -> P -> C[1] -> C[1];
                                T -> P -> P -> C[1] -> C[1] -> P = T -> P;
                                T -> P -> P -> C[1] = T -> P -> P -> C[2];
                                T -> P -> P -> C[2] = NULL;
                            }

                            if(T -> P -> C[0] -> data[0] == x){
                                T -> P -> C[0] -> data[0] = T -> P -> C[0] -> data[1];
                                T -> P -> C[0] -> data[1] = T -> P -> C[0] -> data[2];
                            }
                            T -> P -> C[0] -> data[2] = -1;
                            T -> P -> C[0] -> cnt = 2;
                        }
                        else if(T -> P -> P -> C[1] == T -> P){
                            T -> P -> C[0] -> data[1] = T -> P -> data[0];
                            T -> P -> C[0] -> data[2] = T -> P -> C[1] -> data[0];
                            T -> P -> data[0] = T -> P -> P -> data[1];
                            if(T -> P -> P -> C[2] -> cnt == 2){
                                T -> P -> P -> data[1] = T -> P -> P -> C[2] -> data[0];
                                T -> P -> C[1] = T -> P -> P -> C[2] -> C[0];
                                T -> P -> P -> C[2] -> C[0] -> P = T -> P;
                                T -> P -> P -> C[2] -> data[0] = T -> P -> P -> C[2] -> data[1];
                                T -> P -> P -> C[2] -> cnt -= 1;
                                T -> P -> P -> C[2] -> C[0] = T -> P -> P -> C[2] -> C[1];
                                T -> P -> P -> C[2] -> C[1] = T -> P -> P -> C[2] -> C[2];
                                T -> P -> P -> C[2] -> C[2] = NULL;
                            }
                            else{
                                T -> P -> data[1] = T -> P -> P -> C[2] -> data[0];
                                T -> P -> cnt += 1;
                                T -> P -> C[1] = T -> P -> P -> C[2] -> C[0];
                                T -> P -> C[2] = T -> P -> P -> C[2] -> C[1];
                                T -> P -> P -> C[2] -> C[0] -> P = T -> P;
                                T -> P -> P -> C[2] -> C[1] -> P = T -> P;
                                T -> P -> P -> cnt -= 1;
                                T -> P -> P -> C[2] = NULL;
                            }

                            if(T -> P -> C[0] -> data[0] == x){
                                T -> P -> C[0] -> data[0] = T -> P -> C[0] -> data[1];
                                T -> P -> C[0] -> data[1] = T -> P -> C[0] -> data[2];
                            }
                            T -> P -> C[0] -> data[2] = -1;
                            T -> P -> C[0] -> cnt = 2;

                        }
                        else{
                            T -> P -> C[1] -> data[2] = T -> P -> C[1] -> data[0];
                            T -> P -> C[1] -> data[1] = T -> P -> data[0];
                            T -> P -> C[1] -> data[0] = T -> P -> C[0] -> data[0];
                            T -> P -> data[0] = T -> P -> P -> data[1];
                            if(T -> P -> P -> C[1] -> cnt == 2){
                                T -> P -> P -> data[1] = T -> P -> P -> C[1] -> data[1];
                                T -> P -> P -> C[1] -> data[1] = -1;
                                T -> P -> C[0] = T -> P -> P -> C[1] -> C[2];
                                T -> P -> P -> C[1] -> C[2] -> P = T -> P;
                                T -> P -> P -> C[1] -> cnt -=  1;
                                T -> P -> P -> C[1] -> C[2] = NULL;
                                if(T -> P -> C[1] -> data[0] == x){
                                    T -> P -> C[1] -> data[0] = T -> P -> C[1] -> data[1];
                                    T -> P -> C[1] -> data[1] = T -> P -> C[1] -> data[2];
                                }
                                T -> P -> C[1] -> data[2] = -1;
                                T -> P -> C[1] -> cnt = 2;
                            }
                            else{
                                T -> P -> P -> data[1] = -1;
                                T -> P -> P -> cnt -= 1;
                                T -> P -> P -> C[1] -> data[1] = T -> P -> P -> C[2] -> data[0];
                                T -> P -> P -> C[1] -> cnt += 1;
                                T -> P -> P -> C[1] -> C[2] = T -> P -> C[1];
                                T -> P -> C[1] -> P = T -> P -> P -> C[1];
                                T -> P -> P -> C[2] = NULL;
                                T = T -> P -> P -> C[1] -> C[2]; //***유일하게 이 경우에만 T의 값을 바꿔야함***
                                if(T -> data[0] == x){
                                    T -> data[0] = T -> data[1];
                                    T -> data[1] = T -> data[2];
                                }
                                T -> data[2] = -1;
                                T -> cnt = 2;
                            }
                        }
                    }
                    else{ //부모의 부모 노드 1개 일때
                        if(T -> P -> P -> C[0] -> cnt == 2){
                            T -> P -> C[1] -> data[2] = T -> P -> C[1] -> data[0];
                            T -> P -> C[1] -> data[1] = T -> P -> data[0];
                            T -> P -> C[1] -> data[0] = T -> P -> C[0] -> data[0];
                            T -> P -> data[0] = T -> P -> P -> data[0];
                            T -> P -> P -> data[0] = T -> P -> P -> C[0] -> data[1];
                            T -> P -> P -> C[0] -> data[1] = -1;
                            T -> P -> P -> C[0] -> cnt -= 1;
                            T -> P -> C[0] = T -> P -> P -> C[0] -> C[2];
                            T -> P -> P -> C[0] -> C[2] -> P = T -> P;

                            if(T -> P -> C[1] -> data[0] == x){
                                T -> P -> C[1] -> data[0] = T -> P -> C[1] -> data[1];
                                T -> P -> C[1] -> data[1] = T -> P -> C[1] -> data[2];
                            }
                            T -> P -> C[1] -> data[2] = -1;
                            T -> P -> C[1] -> cnt = 2;
                        }
                        else if(T -> P -> P -> C[1] -> cnt == 2){
                            T -> P -> C[0] -> data[1] = T -> P -> data[0];
                            T -> P -> C[0] -> data[2] = T -> P -> C[1] -> data[0];
                            T -> P -> data[0] = T -> P -> P -> data[0];
                            T -> P -> P -> data[0] = T -> P -> P -> C[1] -> data[0];
                            T -> P -> P -> C[1] -> data[0] = T -> P -> P -> C[1] -> data[1];
                            T -> P -> P -> C[1] -> data[1] = -1;
                            T -> P -> P -> C[1] -> cnt -= 1;
                            T -> P -> C[1] = T -> P -> P -> C[1] -> C[0];
                            T -> P -> C[1] -> P = T -> P;
                            T -> P -> P -> C[1] -> C[0] = T -> P -> P -> C[1] -> C[1];
                            T -> P -> P -> C[1] -> C[1] = T -> P -> P -> C[1] -> C[2];
                            T -> P -> P -> C[1] -> C[2] = NULL;
                            if(T -> P -> C[0] -> data[0] == x){
                                T -> P -> C[0] -> data[0] = T -> P -> C[0] -> data[1];
                                T -> P -> C[0] -> data[1] = T -> P -> C[0] -> data[2];
                            }
                            T -> P -> C[0] -> data[2] = -1;
                            T -> P -> C[0] -> cnt = 2;
                        }
                        else{ //트리의 높이가 낮아지는 경우이다
                            if(T -> P -> P -> C[0] != T -> P){ // 이거 왜 T -> P -> P -> C[1] = T -> P -> P -> C[0] 이 되는거지?
                                T -> P -> P -> data[1] = T -> P -> P -> data[0];
                                T -> P -> data[2] = T -> P -> C[1] -> data[0];
                                T -> P -> data[1] = T -> P -> data[0];
                                T -> P -> data[0] = T -> P -> C[0] -> data[0];
                                T -> P -> P -> C[2] = T -> P;
                                T -> P -> P -> data[0] = T -> P -> P -> C[0] -> data[0];
                                T -> P -> P -> cnt = 2;
                                T -> P -> P -> C[1] = T -> P -> P -> C[0] -> C[1];
                                T -> P -> P -> C[1] -> P = T -> P -> P;
                                T -> P -> P -> C[0] = T -> P -> P -> C[0] -> C[0];
                                T -> P -> P -> C[0] -> P = T -> P -> P;
                            }
                            else{
                                T -> P -> data[2] = T -> P -> C[1] -> data[0];
                                T -> P -> data[1] = T -> P -> data[0];
                                T -> P -> data[0] = T -> P -> C[0] -> data[0];
                                T -> P -> P -> data[1] = T -> P -> P -> C[1] -> data[0];
                                T -> P -> P -> cnt += 1;
                                T -> P -> P -> C[2] = T -> P -> P -> C[1] -> C[1];
                                T -> P -> P -> C[2] -> P = T -> P -> P;
                                T -> P -> P -> C[1] = T -> P -> P -> C[1] -> C[0];
                                T -> P -> P -> C[1] -> P = T -> P -> P;
                            }
                            T = T -> P;
                            if(T -> data[0] == x){
                                T -> data[0] = T -> data[1];
                                T -> data[1] = T -> data[2];
                            }
                            T -> data[2] = -1;
                            T -> cnt = 2;
                            T -> C[0] = NULL;
                            T -> C[1] = NULL;
                            T -> C[2] = NULL;
                        }
                    }
                }
                else if(T -> P -> C[0] == T){
                    T -> data[0] = T -> P -> data[0];
                    T -> P -> data[0] = T -> P -> C[1] -> data[0];
                    T -> P -> C[1] -> data[0] = T -> P -> C[1] -> data[1];
                    T -> P -> C[1] -> data[1] = -1;
                    T -> P -> C[1] -> cnt -= 1;
                }
                else{
                    T -> data[0] = T -> P -> data[0];
                    T -> P -> data[0] = T -> P -> C[0] -> data[1];
                    T -> P -> C[0] -> data[1] = -1;
                    T -> P -> C[0] -> cnt -= 1;
                }
            }
        }
        else{ //리프가 아니면 값을 리프에 있게 바꾸고 다시 삭제
            if(T -> data[0] == x){
                int tmp = T -> C[1] -> data[0];
                T -> C[1] -> data[0] = T -> data[0];
                T -> data[0] = tmp;
                Delete(T -> C[1],x);
            }
            else{
                int tmp = T -> C[2] -> data[0];
                T -> C[2] -> data[0] = T -> data[1];
                T -> data[1] = tmp;
                Delete(T -> C[2],x);
            }
        }
    }
    else if(x < T -> data[0]) Delete(T -> C[0],x);
    else if(T -> cnt == 1 || x < T -> data[1]) Delete(T -> C[1],x);
    else Delete(T -> C[2],x);
    return T;
}

void Print(BTree T){
    queue<BTree> q;
    q.push(T);
    while(!q.empty()){
        int tmp = q.size();
        for(int i=0; i<tmp; i++){
            cout << "data is : ";
            for(int j=0; j<q.front() -> cnt; j++){
                cout << q.front() -> data[j] << " ";

                if(q.front() -> C[j] != NULL){
                    q.push(q.front() -> C[j]);
                    cout << j << "번째 자식 " << q.front() -> C[j] -> data[0] << " ";
                }
            }
            if(q.front() -> C[q.front() -> cnt] != NULL){
                q.push(q.front() -> C[q.front() -> cnt]);
                cout << q.front() -> cnt << "번째 자식 " << q.front() -> C[q.front() -> cnt] -> data[0] << " ";
            }
            if(q.front() -> P != NULL) cout << "부모는 " << q.front() -> P -> data[0] << "    ";
            q.pop();
        }
        cout << "\n";
    }
}


int main()
{
    int n;
    BTree head = NULL;
    int x;
    while(1){
        cin >> x;
        if(x == 0){
            int n;
            cin >> n;
            head = Delete(head,n);
        }
        else{
            head = Insert(head,x);
        }
        Print(head);
    }
}
