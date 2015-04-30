
//第一种方法时间复杂度太高
class NumberGameAgain {
public:
	void solve_help(long long &ret, long long temp, long long p, map<int, bool> table_map);
	long long solve(int k, vector<long long> table);
};
//如图，一棵二叉树，每个结点都会衍生出两个节点；如果当前节点可以到达且在2-2^k-1范围内，则ret++，并进一步处理它的子节点
void NumberGameAgain::solve_help(long long &ret, long long temp, long long p, map<int, bool> table_map) {
	if(table_map.find(temp) == table_map.end()) {
		ret++;
		if(2 * temp < p)
			solve_help(ret, 2 * temp, p, table_map);
		if(2 * temp + 1 < p)
			solve_help(ret, 2 * temp + 1, p, table_map);
	}
}
long long NumberGameAgain::solve(int k, vector<long long> table) {
	long long ret = 0;
	long long p = (long long)(pow((float)2, (float)k));
	int temp = 1;
	map<int, bool> table_map;
	for(int i=0; i<table.size(); i++)
		table_map[table[i]] = true;
	solve_help(ret, temp, p, table_map);
	if(find(table.begin(), table.end(), 1) == table.end())
		ret--;
	return ret;
}


//第二种方法
typedef long long ll;
ll cal(ll x, int k) {
	//算出非法数及以它为根节点的子二叉树的节点个数
	if(x == 0) return 0;
	int c = 0;
	while(x > 0) {
		++c;
		x >>= 1;
	}
	--c;
	return (1LL << (k-c)) - 1LL;
}

class NumberGameAgain {
public:
	long long solve(int k, vector<long long> table) {
		ll ans = (1LL << k) - 2LL;
		int n = table.size();
		sort(table.begin(), table.end());
		for(int i=0; i<n ;i++) {
			//遍历table，如果某个元素可以由前面已经遍历过的元素经过2x或者2x+1得到，则跳过它；如果没有的话则需要将以其为根的子二叉树的个数减去
			bool ok = true;
			ll x = table[i];
			while(x > 0 && ok) {
				for(int j=0; j<i; j++) {
					if(table[j] == x) {
						ok = false;
						break;
					}
				}
				x >>= 1;
			}
			if(ok)
				ans -= cal(table[i], k);
		}
		return ans;
	}
};