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

//一棵树，有N个节点，parent数组给出了父子节点关系，第i+1个节点的父亲节点为parent[i]
//给树的所有节点上色，有红色和绿色两种；每个节点的费用为与其颜色不同的子节点的个数（包含本身）
//求给整棵树上色的最低费用

//思路：
//递归，求以节点i为根节点，前面的选择记录为green/red的最低费用

class TheKingsTree {
private:
	vi v[52];					//保存父亲节点为i的直接子节点
	int record[52][52][52];		//记录已经求过的情况，已经求过的则直接返回，不需要重新计算，用空间换取时间
public:
	int dp(int cur, int green, int red) {
		//在cur节点前面的节点已经做好选择，统计绿色节点个数为green及红色节点个数为red
		//此时cur节点选择的着色使得费用最少
		int &ret = record[cur][green][red];
		if(ret != -1)
			return ret;
		//cur节点选择绿色
		int green_ret = green + 1;
		f(i, 0, v[cur].size())
			green_ret += dp(v[cur][i], green + 1, red);
		//cur节点选择红色
		int red_ret = red + 1;
		f(i, 0, v[cur].size())
			red_ret += dp(v[cur][i], green, red + 1);
		return ret = min(green_ret, red_ret);
	}
	int getNumber(vector<int> parent) {
		memset(record, -1, sizeof(int)*52*52*52);
		f(i, 0, parent.size())
			v[parent[i]].push_back(i + 1);
		return dp(0, 0, 0);
	}
};

int main() {
	int t = 1;
	int a[5] = {0, 1, 2, 3, 1};
	vi parent(a, a+5);
	TheKingsTree tkt;
	cout << tkt.getNumber(parent) << endl;
	system("pause");
	return 0;
}