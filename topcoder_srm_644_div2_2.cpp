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

//给定一组字符串数组，字符串中仅有小写字母，可能包含'?'，表示不确定字符
//要求返回一个数组，表明每个字符串经过排序后在字符串数组的最小可能位置
//思路：
//在求某一个字符串的可能的最小位置时，将其与其他字符串进行比较，注意'?'的情况

class LostCharacter {
public:
	vector <int> getmins(vector <string> str) {
		vector<int> ret;
		for(int i=0; i<str.size(); i++) {
			int pos = 0;
			for(int j=0; j<str.size(); j++) {
				if(j != i) {
					int k;
					int len = min(str[i].length(), str[j].length());
					for(k=0; k<len; k++) {
						if((str[i][k] == '?' && str[j][k] == 'a') || (str[i][k] == 'z' && str[j][k] =='?'))
							continue;
						if(str[i][k] < str[j][k] || (str[i][k] == '?' && str[j][k] != 'a') || (str[i][k] != 'z' && str[j][k] =='?')) {
							break;
						}
						if(str[i][k] > str[j][k]) {
							pos++;
							break;
						}
					}
					if(k == len) {
						if(str[i].length() > str[j].length())
							pos++;
					}
				}
			}
			ret.push_back(pos);
		}
		return ret;
	}
};

int main() {
	vector<string> str;
	str.push_back("a?");
	str.push_back("a");
	str.push_back("a");
	str.push_back("ab");
	str.push_back("aa");
	LostCharacter lc;
	lc.getmins(str);

	return 0;
}