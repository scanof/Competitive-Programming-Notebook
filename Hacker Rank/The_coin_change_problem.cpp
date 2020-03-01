#include <bits/stdc++.h>
using namespace std; 

int main(){

    int devuelta, n;
    cin>> devuelta>> n;
    int monedas[n+1];
    for (int i = 1; i <= n; ++i)
    {
        cin>> monedas[i];
    }
    long long matriz[n+1][devuelta+1];
    memset(matriz,0,sizeof matriz);
    for (int i = 0; i < n+1; ++i)
    {
        matriz[i][0] = 1;
    }

    int coin= 0;
    for (int i = 1; i <=n; i++)
    {
        coin= monedas[i];
        for (int j = 1; j <= devuelta; j++)
        {
            if(j-coin>=0){
                matriz[i][j]= matriz[i][j-coin] ;
            }
            matriz[i][j]+= matriz[i-1][j];
        }
    }
    cout<< matriz[n][devuelta]<<endl;
}
