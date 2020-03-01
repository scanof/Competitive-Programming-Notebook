#include <bits/stdc++.h>

#define fi first
#define se second
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(int i=1; i<= (int)n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define ford(i,n) for(int i=(int)(n) - 1; i>= 0; --i)
#define pb push_back

using namespace std;

typedef long long ll;

int main(){
    int n;
    cin>> n;
    ll arr[n];
    ll nums[n];
    forn(i,n){
        cin>> arr[i];
        nums[i]= arr[i];
    }
    sort(arr, arr+n);
    int conteo= 0;
    vector<int> indices;
    indices.reserve(n);
    forn(i,n){
        if(arr[i]!= nums[i]){
            conteo++;
            indices.pb(i);
        }
    }
    if(conteo==2){
        cout<< "yes"<<endl<< "swap "<< indices[0]+1<< " "<< indices[1]+1<<endl;
        return 0;
    }else if(conteo==0){
        cout<<"yes"<<endl;
        return 0;
    }else{
        reverse(nums+indices[0],nums+indices[indices.size()-1]+1);
        forn(i,n){
            if(arr[i]!= nums[i]){
                cout<<"no"<<endl;
                return 0;
            }
        }
    }
    cout<< "yes"<<endl <<"reverse "<< indices[0]+1<<" "<< indices[indices.size()-1]+1<<endl;

}
