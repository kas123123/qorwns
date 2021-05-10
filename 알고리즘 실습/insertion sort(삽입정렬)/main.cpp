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
        //a[j] <= key이면 종료하기 때문에 같은 숫자를 비교할때 먼저온 친구가 결과에도 먼저나온다 -> stable
        a[j+1] = key;
    }

    for(int i=1; i<=n; i++){
        cout << a[i] << " ";
    }

}

// O(n^2)
