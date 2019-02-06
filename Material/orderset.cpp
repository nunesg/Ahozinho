#include <bits/stdc++.h>

#define debug(x) cout << #x << " = " << x << endl
#define fori(i, ini, lim) for(int i= int(ini); i<int(lim); ++i)
#define ford(i, ini, lim) for(int i= int(ini); i>=int(lim); --i)
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

typedef tree<ii, null_type, less<ii>, rb_tree_tag, tree_order_statistics_node_update> oset;

const int MAX = 2e5 + 5;
oset bit[MAX];

void update(int x, int y, int val) {
    int _x = x;
    while(x < MAX) {
        if(val == 1) {
            bit[x].insert(ii(y, _x));
        }
        else {
            bit[x].erase(ii(y, _x));
        }
        x += x & -x;
    }
}

int query(int x, int y) {
    int sum = 0;
    while(x) {
        sum += bit[x].order_of_key(ii(y + 1, 0));   
        x -= x & -x;
    }
    return sum;
}

int arr[3][MAX];
int pos[3][MAX];

int main(){
    int n;
    scanf("%d", &n);
    fori(i, 0, 3) {
        fori(j, 1, n + 1) {
            scanf("%d", &arr[i][j]);
            pos[i][arr[i][j]] = j;
        }
    }

    fori(i, 1, 3) {
        fori(j, 1, n + 1) {
            arr[i][j] = pos[0][arr[i][j]];
            pos[i][arr[i][j]] = j;
        }
    }

    vector<ii> v;
    fori(i, 1, n + 1) {
        v.emplace_back(pos[1][i], pos[2][i]);
    }

    ll ans = 0;
    for(auto &each : v) {
        ans += query(each.first, each.second);
        update(each.first, each.second, 1);
    }
    printf("%lld\n", ans);

	return 0;
}
