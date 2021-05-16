#include <iostream>
#include <queue>

using namespace std;

typedef struct Tree* BTree;

struct Tree{
    BTree C[4]; //�ڽ� �ּ� �ִ� 4�� ���� (���� 2-3Ʈ���̹Ƿ� 4�� ����Ǹ� �ٷ� �������Ѵ�)
    int data[3]; //key �ִ� 3�� ���� (���� 3���Ǹ� ��������)
    int cnt; //data���� 1~3
    BTree P; //�θ� �ּ�
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


BTree Split(BTree T){ //ũ�Ⱑ 3�϶� ����
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
    if(T -> cnt == 3) T = Split(T); //�������� head�� ũ�Ⱑ 3�϶�
    return T;
}

BTree Delete(BTree T,int x){
    if(T == NULL)   cout << "�����Ұ� ����\n";
    else if(T -> data[0] == x || T -> data[1] == x){
        if(T -> C[0] == NULL && T -> C[1] == NULL && T -> C[2] == NULL){ //�����϶� ���� ����
            if(T -> cnt == 2){ //�������� �����Ұ��� 2���� �׳� �����ϸ��
                if(T -> data[0] == x){
                    T -> data[0] = T -> data[1];
                }
                T -> data[1] = -1;
                T -> cnt -= 1;
            }
            else if(T -> P == NULL){
                cout << "�ϳ� ���Ҵµ� �� �����ϴ°ž�!!!\n";
            }
            else if(T -> P -> cnt == 2){ //�θ��� ���Ұ� 2���϶�
                if(T -> P -> C[0] -> cnt + T -> P -> C[1] -> cnt + T -> P -> C[2] -> cnt == 3){ //2,1,1,1 �� ���
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
            else{ //�θ��� ���Ұ� 1�� �϶�
                if(T -> P -> C[0] -> cnt + T -> P -> C[1] -> cnt == 2){ // 1,1,1 �� ��� -> ******* ���� �߿��� ����� *******
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
                    else if(T -> P -> P -> cnt == 2){ //�θ��� �θ𿡼� ������ �����ü� �ִ� ��� (��尡 2���� �����͵� ũ�� ��������)
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
                                T = T -> P -> P -> C[1] -> C[2]; //***�����ϰ� �� ��쿡�� T�� ���� �ٲ����***
                                if(T -> data[0] == x){
                                    T -> data[0] = T -> data[1];
                                    T -> data[1] = T -> data[2];
                                }
                                T -> data[2] = -1;
                                T -> cnt = 2;
                            }
                        }
                    }
                    else{ //�θ��� �θ� ��� 1�� �϶�
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
                        else{ //Ʈ���� ���̰� �������� ����̴�
                            if(T -> P -> P -> C[0] != T -> P){ // �̰� �� T -> P -> P -> C[1] = T -> P -> P -> C[0] �� �Ǵ°���?
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
        else{ //������ �ƴϸ� ���� ������ �ְ� �ٲٰ� �ٽ� ����
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
                    cout << j << "��° �ڽ� " << q.front() -> C[j] -> data[0] << " ";
                }
            }
            if(q.front() -> C[q.front() -> cnt] != NULL){
                q.push(q.front() -> C[q.front() -> cnt]);
                cout << q.front() -> cnt << "��° �ڽ� " << q.front() -> C[q.front() -> cnt] -> data[0] << " ";
            }
            if(q.front() -> P != NULL) cout << "�θ�� " << q.front() -> P -> data[0] << "    ";
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
