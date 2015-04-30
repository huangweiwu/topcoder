#include<vector>
#include<algorithm>
#include<iostream>
#include<map>
#include<sstream>
#include<utility>
#include<cmath>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<long long> vl;
typedef map<int, int> mii;

#define f(i, x, y) for(int i=x; i<y; i++)
#define PI (2.0 * acos(0))
#define ERR 1e-5
#define all(a) a.begin(), a.end()
#define present(x, item) ((x).find(item) != (x).end())
#define INF 20000000

stringstream ss;

class TheKingsFactorization {
public:
	vector<long long> getVector(long long n, vector<long long> v) {
		vl ret;
		int length = v.size();
		f(i, 0, length) {
			n /= v[i];
			ret.push_back(v[i]);
		}
		for(ll i = 2; i * i <= n && ret.size() < length * 2 - 1; i += (1ll + (i & 1))) {
			while(n % i == 0) {
				n /= i;
				ret.push_back(i);
			}
		}
		if(n != 1)
			ret.push_back(n);
		sort(ret.begin(), ret.end());
		return ret;
	}
};