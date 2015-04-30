#include<vector>
#include<algorithm>
#include<math.h>
using namespace std;
class BridgeCrossing {
public:
	int minTime(vector <int> times);
};
//n人过桥问题
//1） 每次重复的过程就是最快的和次快的先过，然后最快的送手电筒回来，然后最慢的和次慢的再一起过河（这样能够让本来都要耗费很长时间的两个人一次性过河，从而节省时间）
//	  然后再让次快的回来送手电筒，这样其实就将问题规模从1~n=>1~n-2，而问题状态不变
//	  所耗费的时间为time[n] + 2*time[2] + time[1]
//2） 每次都让最快的运送，这样时间就是time[n] + time[n - 1] + 2*time[1]
//可以重复上述过程直到只剩下3个人或者2个人
int BridgeCrossing::minTime(vector <int> times) {
	sort(times.begin(), times.end());
	if(times.size() == 0)
		return 0;
	if(times.size() == 1)
		return times[0];
	if(times.size() == 2)
		return times[1];
	int n = times.size();
	int ret = 0;
	while(n > 3) {
		ret += min(times[n-1] + 2 * times[1] + times[0], times[n-1] + times[n-2] + 2 * times[0]);
		n -= 2;
	}
	if(n == 3)
		ret += times[2] + times[1] + times[0];
	if(n == 2)
		ret += times[1];
	return ret;
}