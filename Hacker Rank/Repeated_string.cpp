#include <bits/stdc++.h>
using namespace std;

int main(){

    string str,text="";
    cin>> str;
    long long n;
    cin>> n;
    long long ans = 0;
    long long k;

    for(int i= 0; i< str.length(); ++i){
        if(str[i]=='a') ans++;
    }
    ans = (n/str.length())*ans;
    if(n%str.length()==0){
    }else{
        for(int i= 0; i< n%str.length() ; ++i){
            if(str[i]=='a') ans++;
        }
    }
    cout<< ans<<endl;
}
