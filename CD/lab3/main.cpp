#include <vector>
#include <string>
#include <iostream>
using namespace std;

void partPalin(string s, int n, int ind, vector<string>& ds, vector<vector<string>>& ans) {
	if(ind == n) return;

	string str = "";
	str += s[ind];

	// take
	ds.push_back(str);
	if(!ds.empty() && equal(ds.begin(), ds.begin() + ds.size()/2, ds.rbegin())) {
		ans.push_back(ds);
	}
	partPalin(s, n, ind + 1, ds, ans);

	// not take
	ds.pop_back();
	if(!ds.empty() && equal(ds.begin(), ds.begin() + ds.size()/2, ds.rbegin())) {
		ans.push_back(ds);
	}
	ds.clear();
	partPalin(s, n, ind + 1, ds, ans);

}


int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);

	freopen("output.txt", "w", stdout);
#endif

	int n;
	cin >> n;
	string str;
	cin >> str;

	vector<string> ds;
	vector<vector<string>> ans;


	partPalin(str, n, 0, ds, ans);

	for(auto &it: ans) {
		for(auto &it1: it) {
			for(auto &it2: it1) {
				cout << it2;
			}
		}
		cout << endl;
	}


	return 0;
}