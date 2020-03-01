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

void mover(int pos, int arr[], int deseado, int posi[]){
    int x1,x2,x3;
    if(pos-1==deseado){
        x1= arr[pos-2];
        x2= arr[pos-1];
        x3= arr[pos];
        arr[pos-2]= x2;
        arr[pos-1]= x3;
        arr[pos]=x1;
        posi[x1]= pos+1;
        posi[x3]= pos;
        posi[x2]= pos-1;

    }else{
        x1= arr[pos-1];
        x2= arr[pos-2];
        x3= arr[pos-3];
        arr[pos-3]= x1;
        arr[pos-2]= x3;
        arr[pos-1]= x2;
        posi[x1]= pos-2;
        posi[x3]= pos-1;
        posi[x2]= pos;
        if(pos-2!=deseado){
            mover(pos-2, arr, deseado,posi);
        }
    }

}


int main(){
    int t,n;
    cin>> t;
    while(t){
        t--;
        cin>> n;
        int arr[n], pos[n+1];
        forn(i,n){
            cin>> arr[i];
            pos[arr[i]]=i+1;
        }

        for1(i,n-3){
            if(pos[i]==i){

            }else{
                mover(pos[i], arr, i, pos);
            }
        }
        int m1 = arr[n-3], m2= arr[n-2], m3=arr[n-1];
        if(m1<=m2 && m2<=m3){
            cout<< "YES"<<endl;
        }else if(m1<=m2 && m3<=m1){
            cout<< "YES"<<endl;
        }else if(m2<= m3 && m3<=m1){
            cout<< "YES"<<endl;
        }else{
            cout<<"NO"<<endl;
        }
    }
}
