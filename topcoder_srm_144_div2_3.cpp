//有一组边，fromJunction是起点，toJunction是终点，ductLength是长度，求出将所有的边遍历一遍所需的最短时间
//找到其中的最长路径，该路径应该走一遍，而其他路径需要走两遍
//不能有回路，否则递归查找最长路径无法终止

class PowerOutage {
public:
	int estimateTimeOut(vector <int> fromJunction, vector <int> toJunction, vector <int> ductLength);
	int longestduration(int start, vector <int> fromJunction, vector <int> toJunction, vector <int> ductLength);
};
int PowerOutage::estimateTimeOut(vector <int> fromJunction, vector <int> toJunction, vector <int> ductLength) {
	int result = 0;
	for(int i=0; i<ductLength.size(); i++)
		result += ductLength[i];

	int max = longestduration(0, fromJunction, toJunction, ductLength);
	result -= max;
	return result;
}
int PowerOutage::longestduration(int start, vector <int> fromJunction, vector <int> toJunction, vector <int> ductLength) {
	int ret = 0;
	for(int i=0; i<fromJunction.size(); i++) {
		if(fromJunction[i] == start) {
			ret = max(ret, ductLength[i] + longestduration(toJunction[i], fromJunction, toJunction, ductLength));
		}
	}
	return ret;
}

int main() {
	vector<int> fromJunction;
	fromJunction.push_back(0);
	fromJunction.push_back(1);
	fromJunction.push_back(2);
	vector<int> toJunction;
	toJunction.push_back(1);
	toJunction.push_back(2);
	toJunction.push_back(0);
	vector<int> ductLength;
	ductLength.push_back(1);
	ductLength.push_back(1);
	ductLength.push_back(1);
	PowerOutage po;
	po.estimateTimeOut(fromJunction, toJunction, ductLength);

	return 0;
}