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
//All elements of A and B will be between 1 and 1,000,000,000, inclusive
//如何判断哪个是最短距离，如果是遍历m，那复杂度高
//下面这种解法把遍历m的时候仅遍历了素数，且素数范围限制在10005之内
//问题
//1） 为什么只遍历素数；若取m为合数，得到的距离只会增加
//2） 为什么m的范围可以限制在10000之内；取最大的数的平方根，取更大的数距离只会增加

int N = 10005;

class TwoNumberGroupsEasy {
public:
	int solve(vector <int> A, vector <int> numA, vector <int> B, vector <int> numB) {
		vi p;
		vi c(N, 1);
		f(i, 2, N) {
			if(c[i]) {
				p.push_back(i);
				for(int j=i*2; j<N; j+=i) {
					c[j] = 0;
				}
			}
		}
		mii M;
		int N = p.size();
		int N1 = A.size();
		int N2 = B.size();
		int ret = INF;
		int a_max = A[0];
		int b_max = B[0];
		f(i, 1, A.size()) {
			if(A[i] > a_max)
				a_max = A[i];
		}
		f(i, 1, B.size()) {
			if(B[i] > b_max)
				b_max = B[i];
		}
		f(i, 0, N) {
			M.clear();
			f(j, 0, N1)
				M[A[j] % p[i]] += numA[j];
			f(j, 0, N2)
				M[B[j] % p[i]] -= numB[j];

			int d = 0;
			mii::iterator it;
			for(it = M.begin(); it!= M.end(); it++)
				d += abs(it->second);
			ret = min(ret, d);
			if(ret == 0)
				//如果距离已经达到最小了，即为0
				break;
			if(p[i] > a_max && p[i] > b_max)
				//如果素数p[i]已经超过A/B中的最大值，则终止遍历p
				break;
		}
		return ret;
	}
};

int main() {
	int a[4] = {1, 2, 3, 4};
	int a1[4] = {1, 1, 1, 2};
	int b[4] = {5, 6, 7, 8};
	int b1[4] = {2, 1, 1, 1};

	vi A(a, a+4);
	vi numA(a1, a1+4);
	vi B(b, b+4);
	vi numB(b1, b1+4);
	TwoNumberGroupsEasy tnge;
	cout << tnge.solve(A, numA, B, numB);

	system("pause");
	return 0;
}