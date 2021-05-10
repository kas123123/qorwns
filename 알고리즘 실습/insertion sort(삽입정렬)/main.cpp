#include <iostream>

using namespace std;

int a[500];

int main()
{
    int n;
    cin >> n;
    for(int i=1; i<=n; i++){
        cin >> a[i];
    }

    for(int i=2; i<=n; i++){
        int key = a[i];
        int j = i-1;
        while(j > 0 && a[j] > key){
            a[j+1] = a[j];
            j--;
        }
        //a[j] <= key�̸� �����ϱ� ������ ���� ���ڸ� ���Ҷ� ������ ģ���� ������� �������´� -> stable
        a[j+1] = key;
    }

    for(int i=1; i<=n; i++){
        cout << a[i] << " ";
    }

}

// O(n^2)
