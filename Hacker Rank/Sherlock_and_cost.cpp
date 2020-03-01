#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, t;
    cin>> t;
    for (int i = 0; i < t; ++i)
    {
        cin>>n;
        int b[n];
        long long opcion1[n-1];
        long long opcion2[n-1];
        for (int j = 0; j < n; ++j)
        {
            cin>>b[j];
        }
        opcion1[0]=b[0]-1;
        opcion2[0]=b[1]-1;
        for (int j = 1; j < n-1; ++j)
        {
            
            opcion1[j] = max(opcion2[j-1]+b[j]-1, opcion1[j-1]);
            opcion2[j] = max(opcion1[j-1]+ b[j+1]-1, opcion2[j-1]+ abs(b[j+1]- b[j]));
        }
        
        cout<< max(opcion1[n-2], opcion2[n-2])<<endl;
        
    }

}
