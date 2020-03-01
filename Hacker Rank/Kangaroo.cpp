#include <bits/stdc++.h>

using namespace std;

int main()
{
    long x1, s1, x2,s2,t;
    cin>> x1 >>s1>>x2>>s2;
    if(s1==s2){
        if(x1==x2){
            cout<<"YES"<<endl;
        }else{
            cout<<"NO"<<endl;

        }
        return 0;
    }
    t= abs(x2-x1)/abs(s1-s2);
    if(t!=int(t)){
        cout<<"NO"<<endl;
        return 0;
    }
    t= int(t);
    s1 = t*s1 +x1;
    s2 = t*s2 +x2;
    if(s1==s2){
        cout<<"YES"<<endl;
    }else{
        cout<<"NO"<<endl;
    }

}
