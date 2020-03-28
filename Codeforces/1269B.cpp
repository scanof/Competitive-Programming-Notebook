#include <bits/stdc++.h>

using namespace std;

int main(){
  int n, m;
  cin>> n>> m;
  vector<int> a(n), b(n);
  for(int i= 0; i<n; ++i){
    cin>> a[i];
  }
  unordered_map<int,int> mapa;
  for(int i= 0; i<n; ++i){
    cin>> b[i];
    mapa[b[i]]++;
  }
  sort(a.begin(),a.end());
  sort(b.begin(),b.end());
  int x = m+2;
  unordered_map<int,int> mapa2;
  for(int i= 0; i<n; ++i){
    int dist = (b[i]-a[0]+m)%m;
    mapa2.clear();
    for(int j= 0; j<n; ++j){
      mapa2[(a[j]+dist)%m]++;
    }
    bool works = true;
    for(pair<int,int> x: mapa){
      if(mapa2[x.first]!= x.second){
        works =false;
        break;
      }
    }
    if(works) x = min(x, dist);
  }
  cout<< x<< endl;
}
