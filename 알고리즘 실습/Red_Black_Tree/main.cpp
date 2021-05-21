#include <iostream>
#include <queue>

using namespace std;

typedef struct Tree* RBT;

struct Tree{
    RBT P; //�θ� �ּ�
    RBT L;
    RBT R;
    int data;
    int color; // black = 1, red = 2;
    RBT nil;
    RBT root;
};

RBT make_head(){
    RBT T = new struct Tree;
    T -> nil = new struct Tree;
    T -> nil -> color = 1;
    T -> root = T -> nil;
    return T;
}

RBT make_Tree(int x){
    RBT T = new struct Tree;
    T -> data = x;
    return T;
}

void LR(RBT T,RBT x){
    RBT y = x -> R;
    x -> R = y -> L;
    if(y -> L != T -> nil) y -> L -> P = x;

    y -> P = x -> P;
    if(x -> P == T -> nil) T -> root = y;
    else if(x == x -> P -> L) x -> P -> L = y;
    else x -> P -> R = y;

    y -> L = x;
    x -> P = y;
}

void RR(RBT T,RBT y){
    RBT x = y -> L;
    y -> L = x -> R;
    if(x -> R != T -> nil) x -> R -> P = y;

    x -> P = y -> P;
    if(y -> P == T -> nil) T -> root = x;
    else if(y == y -> P -> L) y -> P -> L = x;
    else y -> P -> R = x;

    x -> R = y;
    y -> P = x;
}

void RB_Fix(RBT T,RBT z){
    while(z -> P -> color == 2){
        if(z -> P == z -> P -> P -> L){
            RBT y = z -> P -> P -> R;
            if(y -> color == 2){
                z -> P -> color = 1;
                y -> color = 1;
                z -> P -> P -> color = 2;
                z = z -> P -> P;
            }
            else{
                if(z == z -> P -> R){
                    z = z -> P;
                    LR(T,z);
                }
                z -> P -> color = 1;
                z -> P -> P -> color = 2;
                RR(T,z -> P -> P);
            }
        }
        else{
            RBT y = z -> P -> P -> L;
            if(y -> color == 2){
                z -> P -> color = 1;
                y -> color = 1;
                z -> P -> P -> color = 2;
                z = z -> P -> P;
            }
            else{
                if(z == z -> P -> L){
                    z = z -> P;
                    RR(T,z);
                }
                z -> P -> color = 1;
                z -> P -> P -> color = 2;
                LR(T,z -> P -> P);
            }
        }
    }
    T -> root -> color = 1;
}

void RB_Insert(RBT T,int Z){
    RBT z = make_Tree(Z);
    RBT y = T -> nil;
    RBT x = T -> root;

    while(x != T -> nil){
        y = x;
        if(z -> data < x -> data) x = x -> L;
        else x = x -> R;
    }
    z -> P = y;

    if(y == T -> nil) T -> root = z; //Ʈ���� �ƹ��͵� ������ ����
    else if(z -> data < y -> data) y -> L = z;
    else y -> R = z;

    z -> L = T -> nil;
    z -> R = T -> nil;
    z -> color = 2;
    RB_Fix(T,z);
}

void RB_Trans(RBT T,RBT u,RBT v){ //u�� v�� ��ü
    if(u -> P == T -> nil) T -> root = v;
    else if(u == u -> P -> L) u -> P -> L = v;
    else u -> P -> R = v;
    v -> P = u -> P;
}

RBT MIN(RBT T,RBT x){
    while(x -> L != T -> nil){
        x = x -> L;
    }
    return x;
}

RBT Find(RBT T,int x){
    RBT tmp = T -> root;
    while(tmp != T -> nil){
        if(tmp -> data == x) return tmp;
        else if(tmp -> data < x){
            tmp = tmp -> R;
        }
        else tmp = tmp -> L;
    }
    return tmp;
}

void RB_Delete_Fix(RBT T,RBT x){
    while(x != T -> root && x -> color == 1){
        if(x == x -> P -> L){
            RBT w = x -> P -> R;
            if(w -> color == 2){
                w -> color = 1;
                x -> P -> color = 2;
                LR(T,x -> P);
                w = x -> P -> R;
            }
            if(w -> L -> color == 1 && w -> R -> color == 1){
                w -> color = 2;
                x = x -> P;
            }
            else{
                if(w -> R -> color == 1){
                    w -> L -> color = 1;
                    w -> color = 2;
                    RR(T,w);
                    w = x -> P -> R;
                }
                w -> color = x -> P -> color;
                x -> P -> color = 1;
                w -> R -> color = 1;
                LR(T,x -> P);
                x = T -> root;
            }
        }
        else{
            RBT w = x -> P -> L;
            if(w -> color == 2){
                w -> color = 1;
                x -> P -> color = 2;
                RR(T,x -> P);
                w = x -> P -> L;
            }
            if(w -> L -> color == 1 && w -> R -> color == 1){
                w -> color = 2;
                x = x -> P;
            }
            else{
                if(w -> L -> color == 1){
                    w -> R -> color = 1;
                    w -> color = 2;
                    LR(T,w);
                    w = x -> P -> L;
                }
                w -> color = x -> P -> color;
                x -> P -> color = 1;
                w -> L -> color = 1;
                RR(T,x -> P);
                x = T -> root;
            }
        }
    }
    x -> color = 1;
}

void RB_Delete(RBT T,int Z){
    RBT z = Find(T,Z);
    if(z == T -> nil){
        cout << "�����Ұ� ����\n";
        return;
    }

    RBT y = z;
    RBT x;
    int y_ori_color = y -> color;
    if(z -> L == T -> nil){
        x = z -> R;
        RB_Trans(T,z,z -> R);
    }
    else if(z -> R == T -> nil){
        x = z -> L;
        RB_Trans(T,z,z -> L);
    }
    else{
        y = MIN(T,z -> R);
        y_ori_color = y -> color;
        x = y -> R;
        if(y -> P == z) x -> P = y;
        else{
            RB_Trans(T,y,y -> R);
            y -> R = z -> R;
            y -> R -> P = y;
        }
        RB_Trans(T,z,y); //�ּҸ� �����ϴ°Ŷ� �ڽ� �����ϰ� �ϴ� �۾����� ���Ŀ� ����ߵ�
        y -> L = z -> L;
        y -> L -> P = y;
        y -> color = z -> color;
    }

    if(y_ori_color == 1) RB_Delete_Fix(T,x); //�����̸� ������� ����, �������� ����x, ��Ʈ�ϼ� �����Ƿ� ��� �����ϴ� ��쿡�� ������ �����.
}

void Print(RBT T){
    queue<RBT> q;
    q.push(T -> root);
    while(!q.empty()){
        int cnt = q.size();
        for(int i=0; i<cnt; i++){
            cout << "d:" << q.front() -> data << " c:" << q.front() -> color;
            if(q.front() -> P != T -> nil){
                cout << " p:" << q.front() -> P -> data;
                if(q.front() -> P -> L == q.front()) cout << "L";
                else cout << "R";
            }
            cout << "  ";
            if(q.front() -> L != T -> nil) q.push(q.front() -> L);
            if(q.front() -> R != T -> nil) q.push(q.front() -> R);
            q.pop();
        }
        cout << "\n";
    }
}

int main()
{
    RBT head;
    head = make_head();
    int x,n;
    while(1){
        cin >> x;
        if(x == 0){
            cin >> n;
            RB_Delete(head,n);
        }
        else RB_Insert(head,x);
        Print(head);
    }
}
