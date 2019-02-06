struct BIT{
	#define LOGMAX 22
	#define N 101010
	
	int bit[N];
	BIT(){};
	
	void clear(){
		memset(bit, 0, sizeof bit);
	}
	
	void update(int pos, int v){
		for(; pos<N; pos+=(pos&(-pos))) bit[pos]+=v;
	}

	int sum(int pos){
		int s=0;
		for(; pos; pos-=(pos&(-pos))) s+=bit[pos];
		return s;
	}
	
	int kth(int k){
		
		int ans=0;
		for(int j=LOGMAX; j>=0; j--){
			if(ans+(1<<j) >= N) continue;
			
			if(bit[ans+(1<<j)]<k){
				ans+=(1<<j);
				k-=bit[ans];
			}
		}
		return ans+1;
	}
	
	int query(int l, int r){
		if(l > r) return 0;
		return sum(r) - sum(l-1);
	}
};

int main(){
	BIT bit;
	bit.clear();
}
