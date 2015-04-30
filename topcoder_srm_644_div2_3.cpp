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

//有一棵树，给定两个数组par[]和num[]
//par[i]表示par[i]与第i+1个节点之间有一条边
//num[i]表示第i个节点上的数字，为正数或者-1
//想对树进行裁剪，使得剪完后每个部分满足下面的条件
//1） 只有一个节点上为正数
//2） 该部分的节点数刚好为那个唯一拥有正数的节点上的正数
//如果可能，则输出"possible"，不可能则输出"impossible

//节点值有k个为正数，表明需要cut k次
//所有正数之和必须等于节点个数，才有可能
//拥有正数的节点不能处于同一部分中

//思路：
//深度优先查询子树
//时间复杂度为O(N)，N为节点个数，太赞了

class TreeCutting {
public:
	struct info {
		int good;
		int size;			//part的节点个数
		int integer;		//正数之和

		info() {
			good = 1;
			size = 0;
			integer = 0;
		}
	};

	vector<int> num;
	vector<int> tree[50];				//存储和节点i有邻边的节点

	info dfs(int node) {
		info in;
		int cntIntegers = 0;			//拥有正数的节点个数
		for(int c=0; c<tree[node].size(); c++) {
			info cin = dfs(tree[node][c]);
			if(cin.good == 0) {
				in.good = 0;
				return in;
			}
			cntIntegers += (cin.integer > 0);
			/*if(cntIntegers > 1) {
				//当某条路径上（part）存在两个以上的节点包含正数，不可能达到目标
				//这里应该可以去掉，因为如果出现上面这种情况，在上一次递归的时候已经返回in.good=0了
				in.good = 0;
				return in;
			}*/
			in.size += cin.size;
			in.integer += cin.integer;
		}

		in.size++;
		cntIntegers += (num[node] >= 1);
		if(cntIntegers > 1) {
			//当某条路径上（part）存在两个以上的节点包含正数，不可能达到目标
			in.good = 0;
			return in;
		}
		in.integer += max(0, num[node]);
		if(in.integer > 0) {
			if(in.integer < in.size) {
				//当某条路径上（part）存在的唯一正数节点的正数小于该路径（part）的节点数，不可能达到目标
				in.good = 0;
				return in;
			}
			else if(in.integer == in.size) {
				//子树能够满足条件，将其cut掉
				in.size = 0;
				in.integer = 0;
			}
		}
		return in;
	}

	string can(vector <int> par, vector <int> num) {
		this->num = num;
		for(int i=0; i<par.size(); i++) {
			tree[par[i]].push_back(i+1);
		}
		info in = dfs(0);

		if(in.good == 1 && in.integer == in.size)
			//回溯到最后包含根（节点0）的路径（part），有两种情况
			//1） integer == size，"POSSBLE"
			//2） integer != size，"IMPOSSIBLE"
			return "POSSIBLE";
		else
			return "IMPOSSIBLE";
	}
};

int main() {
	//int a[21] = {0,0,0,0,1,1,2,3,3,3,4,4,4,5,9,9,14,14,14,16,20};
	//int b[22] = {-1,3,-1,-1,-1,-1,-1,1,1,-1,-1,-1,3,1,-1,1,8,-1,-1,4,-1,-1};
	int a[5] = {0, 1, 2, 0, 3};
	int b[6] = {-1, 5, -1, -1, 1, -1};

	vector<int> par(a, a+5);
	vector<int> num(b, b+6);

	TreeCutting tc;
	cout << tc.can(par, num) << endl;
	system("pause");

	return 0;
}