#include <bits/stdc++.h>
using namespace std;

int main(){
    int s, t, a, b, m, n;
    cin >> s>> t>>a >>b>>m >>n;
    int num, result, result1;
    result=0;
    for (int i = 0; i < m; i++)
    {
        cin>> num;
        if(a+num>= s && a+num<=t){
            result+=1;
        }
    }
    
    result1=0;
    for (int i = 0; i < n; i++)
    {
        cin>> num;
        if(b+num>= s && b+num<=t){
            result1+=1;
        }
    }
    cout<< result<< endl;
    cout<< result1<< endl;
    return 0;
}
