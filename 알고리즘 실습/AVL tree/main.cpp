#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

typedef struct Tree* AVL;

struct Tree{
    int data;
    AVL L;
    AVL R;
    int H; //높이 (밑에 데이터 얼마나 달고있나)
};

int height(AVL T){
    if(T == NULL) return -1;
    else return T -> H;
}

AVL Single_L(AVL K2){
    AVL K1 = K2 -> R;

    K2 -> R = K1 -> L;
    K1 -> L = K2;

    K2 -> H = max(height(K2 -> L),height(K2 -> R)) + 1;
    K1 -> H = max(height(K1 -> R), K2 -> H) + 1;

    return K1;
}

AVL Single_R(AVL K2){
    AVL K1 = K2 -> L;

    K2 -> L = K1 -> R;
    K1 -> R = K2;

    K2 -> H = max(height(K2 -> L),height(K2 -> R)) + 1;
    K1 -> H = max(height(K1 -> L), K2 -> H) + 1;

    return K1;
}

AVL Double_RL(AVL K3){
    K3 -> R = Single_R(K3 -> R);
    return Single_L(K3);
}

AVL Double_LR(AVL K3){
    K3 -> L = Single_L(K3 -> L);
    return Single_R(K3);
}

AVL Insert(AVL T,int x){
    if(T == NULL){
        T = new struct Tree;
        T -> L = NULL;
        T -> R = NULL;
        T -> H = 0;
        T -> data = x;
    }
    else if(T -> data > x){
        T -> L = Insert(T -> L,x);
        if(height(T -> L) - height(T -> R) == 2){ //왼쪽에 삽입되는 경우 이므로 균형이 깨진다면 왼쪽이 오른쪽보다 2가 큰것이다.
            if(T -> L -> data  > x) T = Single_R(T);
            else T = Double_LR(T);
        }
    }
    else{
        T -> R = Insert(T -> R,x);
        if(height(T -> R) - height(T -> L) == 2){
            if(T -> R -> data  <= x) T = Single_L(T); //같은 값이 들어가면 오른쪽으로 넣으라고 했기 떄문에 등호붙여줘야 Rotation 잘함
            else T = Double_RL(T);
        }
    }

    T -> H = max(height(T -> L),height(T -> R)) + 1;

    return T;
}

AVL Max(AVL T){ //T가 조상인 트리에서 제일 큰 친구의 포인터를 리턴
    if(T -> R == NULL) return T;
    else return Max(T -> R);
}


AVL Delete(AVL T,int x){
    if(T == NULL){
        cout << "삭제할거 없음\n";
    }
    else if(T -> data == x){
        if(T -> L == NULL && T -> R == NULL){
            delete T;
            T = NULL;
        } //자식이 없는 경우 그냥 삭제

        else if(T -> L == NULL){
            AVL tmp = T;
            T = T -> R;
            delete tmp;
        } //왼쪽 자식이 없는경우
        else{
            AVL tmp = Max(T -> L); //왼쪽 자식들중에서 제일 큰놈
            int tmp1 = tmp -> data;
            tmp -> data = T -> data;
            T -> data = tmp1; //두 값을 계속 바꾸다 보면 이제 지워야 되는값은 리프이니까 편하게 지우고 높이 맞추기 하면된다.

            T -> L = Delete(T -> L,x);
            if(height(T -> R) - height(T -> L) == 2){ //왼쪽을 삭제하는 경우이므로 균형이 깨진다면 오른쪽이 큰것이다.
                if(height(T -> R -> R) >= height(T -> R -> L)) T = Single_L(T);
                else T = Double_RL(T);
            }
        } //자식이 둘다 있는 경우(왼쪽 자식이 있는 경우) 왼쪽 subtree에서 제일큰거나 오른쪽 subtree에서 제일 작은 친구가 부모를 대체할수있다. 여기서는 왼쪽 자식을 선택
    }
    else if(T -> data > x){
        T -> L = Delete(T -> L,x);
        if(height(T -> R) - height(T -> L) == 2){ //왼쪽을 삭제하는 경우이므로 균형이 깨진다면 오른쪽이 큰것이다.

            if(height(T -> R -> R) >= height(T -> R -> L)) T = Single_L(T);
            else T = Double_RL(T);
        }
    }
    else{
        T -> R = Delete(T -> R,x);
        if(height(T -> L) - height(T -> R) == 2){
            if(height(T -> L -> L) >= height(T -> L -> R)) T = Single_R(T);
            else T = Double_LR(T);
        }
    }
    if(T != NULL) T -> H = max(height(T -> L),height(T -> R)) + 1;
    return T;
}

void Print(AVL head){
    queue<AVL> q;
    q.push(head);

    while(!q.empty()){
        int tmp = q.size();
        for(int i=0; i<tmp; i++){
            cout << "data = " << q.front() -> data << ", height = " << q.front() -> H << "     ";
            if(q.front() -> L != NULL) q.push(q.front() -> L);
            if(q.front() -> R != NULL) q.push(q.front() -> R);
            q.pop();
        }
        cout << "\n";
    }
}



int main()
{
    int n;
    cin >> n;
    AVL head = NULL;
    int x;
    for(int i=0; i<n; i++){
        cin >> x;
        head = Insert(head,x);
    }

    while(head != NULL){
        Print(head);
        cin >> x;
        head = Delete(head,x);
    }
}
