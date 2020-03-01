#include <iostream>
#include <cstdio>
using namespace std;

/*
Add `int max_of_four(int a, int b, int c, int d)` here.
*/
int max_of_four(int a, int b, int c, int d){
    /*int max=a;
    if(max<b){
        max=b;
    }
    if(max<c){
        max=c;
    }
    if (max < d) {
      max = d;
    }*/
    int maximum= max(max(a,b),max(c,d));
    return maximum;
}


int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    int ans = max_of_four(a, b, c, d);
    printf("%d", ans);
    
    return 0;
}
