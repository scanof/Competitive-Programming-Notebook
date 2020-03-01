#include <bits/stdc++.h>
using namespace std;

// Check Examples


//Compiler version g++ 6.3.0

int main()
{
	int n;
	cin>> n;
	string steps;
	cin>> steps;
	int num=n+1;
	map<int,int> arr;
	if(steps[0]=='D'){
		arr[num-1]++;
		num--;
	}else{
		arr[num]++;
	}
	
	for(int i=1; i<n;++i){
		if(steps[i]=='D'){
			if(steps[i-1]=='D'){
				num--;
				arr[num]++;
			}else{
				arr[num]++;
			}
		}else{
			if(steps[i-1]=='D'){
				arr[num]++;
			}else{
				num++;
				arr[num]++;
			}
		}
	}
	cout<< arr[n]/2<<endl;
}

