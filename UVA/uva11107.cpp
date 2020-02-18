#include <bits/stdc++.h>

#define fi first
#define se second
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(int i=1; i<= (int)n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define ford(i,n) for(int i=(int)(n) - 1; i>= 0; --i)
#define fored(i,l,r) for(int i=(int)r; i>= (int)l; --i)
#define pb push_back
#define el '\n'
#define d(x) cout<< #x<< " " << x<<el

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<char,int> pci;
typedef tuple<int, int, int> tiii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;

string t;
int n; // the length of input string
vector<int> RA, tempRA; // rank array and temporary rank array (value determining the sorting order)
vector<int> SA, tempSA; // suffix array and temporary suffix array (actual sorted order)
vector<int> cnt; // for counting sort
vector<int> LCP, PLCP; // longest common prefix

// counting sort on offset k, O(N)
void countingSort(int k) {
    int i, sum, maxi = max(300, n); // up to 255 ASCII chars or length of n (max rank)
    cnt.assign(maxi,0); // frequency table assignment
    // step 1: counting
    for(i = 0; i < n; i++) // count the frequency of each rank
        cnt[i + k < n ? RA[i + k] : 0]++;
    // step 2: summing
    for (i = sum = 0; i < maxi; i++) {
        int tmp = cnt[i];
        cnt[i] = sum;
        sum += tmp;
    }
    // step 3: placement
    for (i = 0; i < n; i++)
        if(SA[i]+k < n)// offset is within bound (not empty)
            tempSA[cnt[RA[SA[i]+k]]++] = SA[i];
        else // out of bound (empty character), have highest precedence lexicographically
            tempSA[cnt[0]++] = SA[i];
    // update the suffix array
    for (i = 0; i < n; i++)
        SA[i] = tempSA[i];
}
// O(NlogN)
void constructSA() {
    int i, k, r;
    RA.assign(n,0), tempRA.assign(n,0);
    SA.assign(n,0), tempSA.assign(n,0);
    for (i = 0; i < n; i++) RA[i] = t[i]; // initial rankings (ASCII value)
    for (i = 0; i < n; i++) SA[i] = i; // initial SA: {0, 1, 2, ..., n-1}

    for (k = 1; k < n; k <<= 1) { // repeat sorting process logN times by power of 2
        // sort based on pair(0,k) to get suffix array (sorted ordering)
        countingSort(k);
        countingSort(0);
        tempRA[SA[0]] = r = 0; // re-ranking; start from rank r = 0, used for subsequent count sort
        for (i = 1; i < n; i++){ // compare adjacent suffixes
            // pair rank (value) are the same as previous
            if(RA[SA[i]] == RA[SA[i-1]] &&
               RA[SA[i]+k] == RA[SA[i-1]+k]
               )
                tempRA[SA[i]] = r; // same rank
            else
                tempRA[SA[i]] = ++r; // next rank
        }
        // update the rank array
        for (i = 0; i < n; i++)
            RA[i] = tempRA[i];
        if (RA[SA[n-1]] == n-1) break; // nice optimization trick
    }
}

// based on Permuted Longest-Common-Prefix (PLCP) theorem
// O(N) as there are at most N increment&decrement
void computeLCP() {
    int i, L;
    LCP.assign(n,0); PLCP.assign(n,0);
    vector<int> phi(n,-1);
    for(i=1;i<n;i++)
        phi[SA[i]] = SA[i-1];
    // L is current character we are looking at
    for(i=L=0;i<n;i++) {
        if(phi[i] == -1) { // special case
            PLCP[i] = 0;
            continue;
        }
        // compare with previous suffix in SA to check if prefix matches
        // can only increase N times at most, since string is n length
        while(i+L < n && phi[i] + L < n &&
              t[i+L] == t[phi[i] + L] &&
              t[i+L] != '$') // additional requirement for > 1 string
            L++;
        PLCP[i] = L;
        if(L) L--; // decrease 1 as we go to next suffix
    }
    // LCP is for suffix array ordering, PLCP is for original array ordering
    for(i =0;i<n;i++)
        LCP[i] = PLCP[SA[i]];  // put the permuted LCP to the correct position
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int q; bool detect= false;
    while(cin>> q){
        if(q==0) return 0;
        if(detect) cout<<el;
        detect= true;
        t = "";
        string s;
        vector<int> owner;
        forn(i,q){
            cin >> s;
            t += s;
            t += "$";
            while(owner.size() < t.length())
                owner.push_back(i);
        }
        n = t.length();
        constructSA();
        computeLCP();

        // loop through suffix array
        // generalize LCS using sliding window
        // where a window contain t/2 different owner
        int maxLCP = 0;
        int uniqueOwner = 0;
        vector<int> LCSidx;
        vector<int> ownerCounter(q);
        int low=0,high=0;
        while(high<n){
            if(uniqueOwner<=q/2){
                int ownidx = owner[SA[high]];
                if(ownerCounter[ownidx]++==0){
                    uniqueOwner++;
                }
                high++;
            }else{
                int pos = low+1, mi = INT_MAX;
                for(int i = low+1; i<high; i++){
                    if(LCP[i]<mi){
                        mi = LCP[i];
                        pos= i;
                    }
                }
                if(LCP[pos]> maxLCP){
                    maxLCP = LCP[pos];
                    LCSidx.clear();
                }
                if(LCP[pos]== maxLCP) LCSidx.pb(pos);
                int ownidx = owner[SA[low]];
                if(--ownerCounter[ownidx]==0){
                    uniqueOwner--;
                }
                low++;
            }
        }
        if(maxLCP==0){
            cout<< "?\n";
        }else{
            set<string> conj;
            for(int pos : LCSidx){
                conj.insert(t.substr(SA[pos],maxLCP));
            }
            for(string x : conj){
                cout<< x<<el;
            }
        }
    }
}
