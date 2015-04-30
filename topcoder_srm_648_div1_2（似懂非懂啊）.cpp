// K种苹果，第i种苹果的原始价格为i，如果购买者购买多个同种水果，则购买的第j个同种水果的价格为2^(j-1)*i
// 现购买N个苹果，目标为总价格最低
// 给定N和K，返回N个苹果中价格模1000000007后最高的值

ll BigMod(ll base, ll pwr, ll mod) {
	ll ret = 1;
	while(pwr>0) {
		if(pwr & 1ll) {
			ret = (ret * base) % mod;
		}
		pwr >>= 1ll;
		base = (base * base) % mod;
	}
	return ret;
}

ll calc(ll K) {
	// 这样算求得的结果是
	// 对于1<= i <= K，满足i * 2 ^ (ai-1) <= K
	// 所有ai加起来的和
	// 比如K=5，则a1=3, a2=2, a3=1, a4=1, a5=1
	ll ret = 0;
	while(K) {
		ret += K;
		K >>= 1ll;
	}
	return ret;
}

const ll MOD = 1000000007ll;

class KitayutaMart {
public:
	int lastPrice(int N, int K) {
		ll lo = 1;
		ll hi = K;
		ll mid, base, total = calc(K), left;
		// base表示价格最大的苹果所在位，1<= base <= K
		// pwr表示购买同一种水果的个数-1，最后计算的时候是2的指数
		ll pwr = 0;
		if(N > total) {
			left = N - total;
			pwr = (left / K) + (left % K != 0);
			N -= pwr * K;
		}
		base = -1;
		while(lo <= hi) {
			mid = (lo + hi) >> 1ll;
			if(calc(mid) >= N) {
				hi = mid - 1;
				base = mid;
			}
			else
				lo = mid + 1;
		}
		return (BigMod(2, pwr, MOD) * base) % MOD;
	}
};