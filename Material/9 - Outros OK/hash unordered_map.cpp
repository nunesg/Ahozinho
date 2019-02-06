#include <bits/stdc++.h>
#include <unordered_map>
#define maxn 30
#define mp make_pair
#define pb push_back
using namespace std;

int n, A[maxn], B[maxn], C[maxn], mid;

struct Hash{
    size_t operator()(const pair<int,int>&x)const{
        return ((long long)x.first)^(((long long)x.second)<<32);
    }
};

unordered_map< pair<int,int>, int, Hash> m, k;

void solve(int id, int a, int b, int c, int mask){
    if(id == mid){
        pair<int,int> p = mp(a-b,b-c);
        if( !(m.count(p)) || m[p] < a) 
            m[p] = a, k[p] = mask;
        return;
    }
    
    solve(id+1, a + A[id], b + B[id], c, 3*mask);
    solve(id+1, a + A[id], b, c + C[id], 3*mask + 1);
    solve(id+1, a, b + B[id], c + C[id], 3*mask + 2);
}

int ans = INT_MIN, mask1, mask2;

vector<int> vet;

void find(int id, int a, int b, int c, int mask){
    if(id == n+1){
        pair<int,int> p = mp(b-a,c-b);
        if( m.count(p) && m[p] + a > ans) 
            ans = m[p] + a, mask1 = k[p], mask2 = mask;
        return;
    }
    
    find(id+1, a + A[id], b + B[id], c, 3*mask);
    find(id+1, a + A[id], b, c + C[id], 3*mask + 1);
    find(id+1, a, b + B[id], c + C[id], 3*mask + 2);
}

void output(int x){
    if(x == 0) cout << "LM\n";
    if(x == 1) cout << "LW\n";
    if(x == 2) cout << "MW\n";
}

int main(){
    cin >> n;
    for(int i = 1; i <= n; i++) 
        cin >> A[i] >> B[i] >> C[i];
    
    mid = n / 2 + 1;
    
    solve(0,0,0,0,0);
    find(mid,0,0,0,0);
    
    if(ans == INT_MIN){
        cout << "Impossible";
        return 0;
    }
    
    for(int i = 0; i < mid; i++) 
        vet.pb(mask1 % 3), mask1 /= 3;
    
    for(int i = vet.size()-2; i >= 0; i--) 
        output(vet[i]);
    
    vet.clear();
    
    for(int i = mid; i <= n; i++) 
        vet.pb(mask2 % 3), mask2 /= 3;
    
    for(int i = vet.size()-1; i >= 0; i--) 
        output(vet[i]);
}