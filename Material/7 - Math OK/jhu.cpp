#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int last[maxn];
void sieve(){
	for(ll i=2;i<maxn;i++){
		if(last[i])
			continue;
		last[i] = i;
		for(ll j=i*i;j<maxn;j+=i)
			last[j] = i;
	}
}

vector<int> fatoracao(int n){
	vector<int> ans;
	while(n != 1){
		ans.push_back(last[n]);
		n /= last[n];
	}
	return ans;
}

bool isPrime(ll n){
    for(int i=2;i<=sqrt(n);i++)
        if(n % i == 0)
            return false;
    return true;
}

int totientSieve(int n){
	double ans = n;
	int lastp = n+1;
	while(n != 1){
		if(lastp != last[n])
			ans *= 1 - (1.0 / last[n]);
		lastp = last[n];
		n /= last[n];
	}
	return int(ans);
}

ll totient(ll n){
	double ans = n;
	for(int i=2;i<=sqrt(n);i++){
		if(n % i)
			continue;
		if(isPrime(i))
			ans *= 1 - (1.0 / i);
		if(n/i != i && isPrime(n/i))
			ans *= 1 - (1.0 / (n/i));
	}
	if(isPrime(n))
		ans *= 1 - (1.0 / n);
	return ans;
}

ll mdc, x, y; // ax + by = mdc(a, b);
void extendEuclid(ll a, ll b){
    if(b == 0){
        mdc = a;
        x = 1;
        y = 0;
    }
    else{
        extendEuclid(b, a%b);
        ll aux = x;
        x = y;
        y = aux - (a/b)*y;
    }
}

// inverso modular fatorial
// se MAXN <= 10e7
void pre(){
  fat[0] = fat[1] = den[0] = den[1] = deni[0] = deni[1] = 1;
  for(int i=2;i<1005;i++){
    fat[i] = (fat[i-1] * i) % mod;
    
    // opcao 1:
    deni[i] = ((mod - mod/i) * deni[mod%i]) % mod;
    den[i] = deni[i] * den[i-1] % mod;

    // opcao 2:
    den[i] = modPow(fat[i], mod-2, mod);
  }
}

ll modEuclid(ll n, ll mod){
    extendEuclid(n, mod);
    x = ((x % m) + m) % m;
    return x;
}

ll modPow(ll n, ll k, ll mod){
    if(!k) 
        return 1LL;
    ll aux = modPow(n, k/2, mod);
    aux = (aux * aux) % mod;
    return k % 2 ? (aux * n) % mod : aux;
}

// inverso modular:
ll inverso(ll n, ll mod){
	// se mod eh primo:
	inv[0] = inv[1] = 1;
	for(int i=2;i<n;i++){
		inv[i] = modPow(n, mod-2, mod);			 	 // opcao 1
		inv[i] = ((mod - mod/i) * inv[mod%i]) % mod; // opcao 2, se N < 1e7
	}

	// se mod eh composto ou muito grande
	inv[n] = modPow(n, totient(mod)-1, mod); // opcao 3
	inv[n] = modEuclid(n, mod);		 		 // opcao 4
}
