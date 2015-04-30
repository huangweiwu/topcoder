//洗牌游戏，一副牌有2N张牌，每轮洗牌规则为
//1） 分成上下两叠，两叠牌以任意的顺序洗
//2） 再将两叠牌交叉放在一起
//一副牌的初始顺序为1, 2, 3, ..., 2N；给定一个序列，求经过两轮洗牌是否可能达到这个序列
//思路：
//假设初始牌为A1, A2, ..., AN, B1, B2, ..., BN
//则经过一轮后，若N为偶数，则前面N张牌有N/2张A和N/2张B；若N为奇数，则前面N张有N/2+1张A和N/2张B
//再经过一轮后，前面N张会分散到最终序列的奇数位
//从而判定是否有可能，只需要看奇数位的B是否达到N/2即可（N有可能为奇数）

class ShufflingCardsDiv2 {
public:
	string shuffle(vector <int> permutation) {
		int i, ct;
		vi a, b;
		for(int i=0; i<permutation.size(); i++) {
			if( i & 1)
				b.push_back(permutation[i]);
			else
				a.push_back(permutation[i]);
		}
		ct = 0;
		for(int i=0; i<a.size(); i++) {
			if(a[i] > permutation.size() / 2)
				ct++;
		}
		if(ct == a.size() / 2)
			return "Possible";
		else
			return "Impossible";
	}
};