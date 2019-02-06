//esse codigo so funciona pra numeros positivos na base 10

#include <bits/stdc++.h>

using namespace std;

#define N 10101000

int n, vet[N], cnt[10], tmp[N];

void counting_sort(int k){
	memset(cnt, 0, sizeof cnt);
	
	for(int i=0; i<n; i++){
		cnt[ (vet[i]/k)%10 ]++;
	}
	for(int i=1; i<10; i++){
		cnt[i]+=cnt[i-1];
	}
	
	for(int i=n-1; i>=0; i--){
		tmp[ --cnt[ (vet[i]/k)%10 ] ] = vet[i];
	}
	for(int i=0; i<n; i++) vet[i] = tmp[i];
}

void radix(){
	int b = 0;
	for(int i=0; i<n; i++) b = max(b, (int)floor(log10(vet[i])));
	
	for(int i=0, exp=1; i<=b; i++, exp*=10){
		counting_sort(exp);
	}
	
}

int main(){
	while(scanf("%d", &n), n){
		
		for(int i=0; i<n; i++) scanf("%d", &vet[i]);
		
		radix();
		
		printf("VETOR:");
		for(int i=0; i<n; i++) printf(" %d", vet[i]);
		printf("\n");
	}
	
}
