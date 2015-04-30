int s[100];

class AB {
public:
	string createString(int N, int K) {
		// 此算法得出的答案，B是尽量往后靠的
		for(int i=0; i<=N; i++) {
			// i表示有i个"B"，j个"A"；若i * j < K，说明就算把i个"B"都放最后面也达不到K
			int j = N - i;
			if(i * j >= K) {
				// 已经确定有i个"B"，j个"A"，因此把"B"放最后的话，可以贡献j个"A"
				string res = "";
				int k = K;
				memset(s, 0, sizeof(s));
				for(int p=1; p<=i; p++) {
					s[min(j, k)]++;
					k -= min(j, k);
				}
				for(int p=1; p<=s[0]; p++)
					res += "B";
				for(int p=1; p<=j; p++) {
					res += "A";
					for(int q=1; q<=s[p]; q++)
						res += "B";
				}
				return res;
			}
		}
		return "";
	}
};