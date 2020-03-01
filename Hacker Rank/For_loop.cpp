#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    // Complete the code.
    string num[10]={"nothing","one","two","three","four","five",
                    "six","seven","eight","nine"};

    int a;
    int b;
    cin>> a >> b ;
    for(int i=a; i<=b; i++){
        if(i<10){
            cout<< num[i] <<endl;
        }else if(i%2==0){
          cout << "even" << endl;
        }else{
          cout << "odd" << endl;
        }

    }
    return 0;
}
