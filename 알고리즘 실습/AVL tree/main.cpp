#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

typedef struct Tree* AVL;

struct Tree{
    int data;
    AVL L;
    AVL R;
    int H; //���� (�ؿ� ������ �󸶳� �ް��ֳ�)
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
        if(height(T -> L) - height(T -> R) == 2){ //���ʿ� ���ԵǴ� ��� �̹Ƿ� ������ �����ٸ� ������ �����ʺ��� 2�� ū���̴�.
            if(T -> L -> data  > x) T = Single_R(T);
            else T = Double_LR(T);
        }
    }
    else{
        T -> R = Insert(T -> R,x);
        if(height(T -> R) - height(T -> L) == 2){
            if(T -> R -> data  <= x) T = Single_L(T); //���� ���� ���� ���������� ������� �߱� ������ ��ȣ�ٿ���� Rotation ����
            else T = Double_RL(T);
        }
    }

    T -> H = max(height(T -> L),height(T -> R)) + 1;

    return T;
}

AVL Max(AVL T){ //T�� ������ Ʈ������ ���� ū ģ���� �����͸� ����
    if(T -> R == NULL) return T;
    else return Max(T -> R);
}


AVL Delete(AVL T,int x){
    if(T == NULL){
        cout << "�����Ұ� ����\n";
    }
    else if(T -> data == x){
        if(T -> L == NULL && T -> R == NULL){
            delete T;
            T = NULL;
        } //�ڽ��� ���� ��� �׳� ����

        else if(T -> L == NULL){
            AVL tmp = T;
            T = T -> R;
            delete tmp;
        } //���� �ڽ��� ���°��
        else{
            AVL tmp = Max(T -> L); //���� �ڽĵ��߿��� ���� ū��
            int tmp1 = tmp -> data;
            tmp -> data = T -> data;
            T -> data = tmp1; //�� ���� ��� �ٲٴ� ���� ���� ������ �Ǵ°��� �����̴ϱ� ���ϰ� ����� ���� ���߱� �ϸ�ȴ�.

            T -> L = Delete(T -> L,x);
            if(height(T -> R) - height(T -> L) == 2){ //������ �����ϴ� ����̹Ƿ� ������ �����ٸ� �������� ū���̴�.
                if(height(T -> R -> R) >= height(T -> R -> L)) T = Single_L(T);
                else T = Double_RL(T);
            }
        } //�ڽ��� �Ѵ� �ִ� ���(���� �ڽ��� �ִ� ���) ���� subtree���� ����ū�ų� ������ subtree���� ���� ���� ģ���� �θ� ��ü�Ҽ��ִ�. ���⼭�� ���� �ڽ��� ����
    }
    else if(T -> data > x){
        T -> L = Delete(T -> L,x);
        if(height(T -> R) - height(T -> L) == 2){ //������ �����ϴ� ����̹Ƿ� ������ �����ٸ� �������� ū���̴�.

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
