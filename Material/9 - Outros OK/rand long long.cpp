#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
#define MAXN 100100

llu seed = 0;
llu my_rand() {
    seed ^= llu(102938711);
    seed *= llu(109293);
    seed ^= seed >> 13;
    seed += llu(1357900102873);
    return seed;
}

int main () {
	//rand c++
	srand(time(NULL));
	cout << rand() << endl;

	//rand Endagorion / FMota
	cout << my_rand() << endl;
	
	
	return 0;
}

