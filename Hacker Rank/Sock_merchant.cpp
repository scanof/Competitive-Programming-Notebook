#include <bits/stdc++.h>
using namespace std;

// Check Examples


//Compiler version g++ 6.3.0

int main()
{
	int n;
	cin>> n;
	map<int,int> arr;
	int num;
	for(int i=0; i<n;++i){
		cin>> num;
		arr[num]++;
	}
	int suma=0;
	for(pair<int,int> a: arr){
		suma+= a.second/2;
	}
	cout<<suma<<endl;
}

