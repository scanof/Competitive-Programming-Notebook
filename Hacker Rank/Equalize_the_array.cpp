#include <bits/stdc++.h>
using namespace std;

int main(){

    int n;
    cin>> n;
    map<int, int> nums;
    int maximo=0;
    int temp,who=0;
    for(int i= 0; i<n ; ++i){
        cin>> temp;
        nums[temp]++;
        if( nums[temp]> maximo){
            maximo= nums[temp];
            who = temp;
        }
    }
    long long ans=0;
    for(pair<int,int> a: nums){
        if(a.first!= who) ans+= a.second;
    }
    cout<< ans<<endl;

}
