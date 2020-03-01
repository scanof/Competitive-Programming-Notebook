#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int n;
    cin >> n;
    int num[n];
    for( int i =0; i<n;i++){
        cin >> num[i];
    }
    for(int i = 0; i<n ; i++){
        cout<< num[n-i-1] <<  " ";
    }
    return 0;
}
