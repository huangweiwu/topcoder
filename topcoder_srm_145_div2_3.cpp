#include<string>
#include<sstream>
#include<vector>
#include<math.h>
#include<stdio.h>
using namespace std;

//根据上一次的状态以及本次购买的时间所经过的时间来累加时间
class VendingMachine {
public:
	int motorUse(vector <string> prices, vector <string> purchases);
};
int VendingMachine::motorUse(vector <string> prices, vector <string> purchases) {
	int whole_column = 0;				//表示一共有多少列
	for(int i=0; i<prices[0].length(); i++) {
		if(prices[0][i] == ' ')
			whole_column++;
	}
	whole_column++;
	int *column_total_price = new int[whole_column];
	int **price = new int*[prices.size()];		//商品的价格
	bool **flag = new bool*[prices.size()];		//商品是否已经被买了
	for(int i=0; i<prices.size(); i++) {
		price[i] = new int[whole_column];
		flag[i] = new bool[whole_column];
	}
	for(int i=0; i<whole_column; i++)
		column_total_price[i] = 0;
	stringstream ss;
	for(int i=0; i<prices.size(); i++) {
	//算出每一列的总价格
		ss.clear();
		ss << prices[i];
		for(int j=0; j<whole_column; j++) {
			ss >> price[i][j];
			column_total_price[j] += price[i][j];
			flag[i][j] = false;
		}
	}
	int most_expense_column = 0;		//表示当前最贵的那一列
	int most_expense = column_total_price[0];
	for(int i=1; i<whole_column; i++) {
		if(column_total_price[i] > most_expense) {
			most_expense = column_total_price[i];
			most_expense_column = i;
		}
	}
	int ret = 0;
	int start = 0;
	int dis = abs(start - most_expense_column);
	if(whole_column - dis < dis)
		dis = whole_column - dis;
	ret += dis;			//在转到购买的列之前，先转到最贵的那一列
	int row, col, time;
	char ch;
	ss.clear();
	ss << purchases[0];
	ss >> row >> ch >> col >> ch >> time;
	flag[row][col] = true;
	dis = abs(most_expense_column - col);
	if(whole_column - dis < dis)
		dis = whole_column - dis;
	ret += dis;
	start = col;			//start转到当前列
	column_total_price[col] -= price[row][col];
	most_expense_column = 0;
	most_expense = column_total_price[0];
	for(int i=0; i<whole_column; i++) {
	//更新最贵列
		if(column_total_price[i] > most_expense) {
			most_expense = column_total_price[i];
			most_expense_column = i;
		}
	}	

	for(int i=1; i<purchases.size(); i++) {
		int pre_time = time;
		ss.clear();
		ss << purchases[i];
		ss >> row >> ch >> col >> ch >> time;
		if(flag[row][col])
			return -1;
		if(time - pre_time >= 5) {
		//如果超过了五秒，则转到最贵的那一列
			dis = abs(start - most_expense_column);
			if(whole_column - dis < dis)
				dis = whole_column - dis;
			ret += dis;
			start = most_expense_column;
		}
		dis = abs(start - col);
		if(whole_column - dis < dis)
			dis = whole_column - dis;
		ret += dis;			//在转到购买之前
		column_total_price[col] -= price[row][col];
		most_expense_column = 0;
		most_expense = column_total_price[0];
		for(int i=0; i<whole_column; i++) {
		//更新最贵列
			if(column_total_price[i] > most_expense) {
				most_expense = column_total_price[i];
				most_expense_column = i;
			}
		}
		start = col;
	}
	dis = abs(start - most_expense_column);
	if(whole_column - dis < dis)
		dis = whole_column - dis;
	ret += dis;
	return ret;
}