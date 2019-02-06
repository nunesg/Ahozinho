#include <bits/stdc++.h>

using namespace std;

struct BIT2D{
    #define MAXN 1010
	
    int bit[MAXN][MAXN];
    BIT2D(){}
     
    void reset(){
        memset(bit, 0, sizeof bit);
    }
     
    void update(int a, int b, int val){
        for(int x = a;  x < MAXN;  x+= (x & -x) ){
		
            for(int y = b;  y < MAXN;  y+= (y & -y) ){
                bit[x][y] += val;
            }
        
        }
    }
     
    int sum(int a, int b){
        int ans = 0;
        for(int x=a;  x;  x-= (x & -x)){
        
            for(int y=b;  y;  y-= (y & -y) ){
                ans += bit[x][y];
            }
            
        }
        return ans;
    }
     
    int query(int i1, int j1, int i2, int j2){
        return sum(i2, j2) + sum(i1-1, j1-1) - sum(i1-1,j2) - sum(i2,j1-1);
    }
};
 
int main(){
    BIT2D tr;
    tr.reset();
}
