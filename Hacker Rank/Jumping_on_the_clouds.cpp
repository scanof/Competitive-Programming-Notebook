#include <bits/stdc++.h>
using namespace std;


int backtrack(int *arr, int i, int op, int n ){
    if(i==n){
        return n;
    }
    if(i==n-1){
        return op;
    }
    if(arr[i]==1){
        return n;
    }
    return min(backtrack(arr,i+1, op+1, n), backtrack(arr,i+2,op+1, n));
}
int main(){
    int n;
    cin>> n;
    int arr[n];
    for (int i = 0; i < n; ++i)
    {
        cin>>arr[i];
    }
    cout<< backtrack(arr, 0, 0, n)<<endl;
}
