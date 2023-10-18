#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <string>
using namespace std;
#define ll long long int
#define IMPOS "100000000000"
vector<string> dp_min{IMPOS, IMPOS, "1", "7", "4", "2", "6", "8", "10"};
vector<string> dp_max{IMPOS, IMPOS, "1", "7"};

string smin(string a, string b, int n, int m) {
	if(n != m) return n > m ? b : a;

	for(int i = 0; i < n; i++) {
		if((int)a[i] < (int)b[i]) return a;
		else if ((int)a[i] > (int)b[i]) return b;
	}

	return a;
}

string replace_all(string s, string x, string y, bool first = true) {
	size_t pos = s.find(x);

    while (pos != std::string::npos) {
        s.replace(pos, 1, y);
        pos = s.find(x);
    }

    if(first) {
	    pos = s.find(y);
	    if(pos == 0) s.replace(pos, 1, x);    	
    }

    return s;
}

string find_min(int a) {
	if(dp_min[a] != "-1") return dp_min[a];
	string s1 = replace_all(find_min(a-7),"6", "0");
	string s2 = replace_all(find_min(a-5),"6", "0", false);
	string s3 = replace_all(find_min(a-6),"6", "0");
	int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();

	dp_min[a] = smin(smin(s1+"8", "2"+s2, n1+1, n2+1)
	, s3+"0", min(n1+1,n2+1), n3+1);

	return dp_min[a];
}

void set_dp_max(int a) {
	if(a+2 > 100) return;
	dp_max[a+2] = dp_max[a] + "1";
	set_dp_max(a+2);
}

int main() {
	for(int i = 0; i < 100; i++) {
		dp_min.push_back("-1"); dp_max.push_back("-1");
	}

	for(int i = 9; i <= 100; i++) find_min(i);
	for(int i = 2; i <= 3; i++) set_dp_max(i);

	for(int i = 2; i <= 100; i++) {
		cout << i << ": " << dp_min[i] << " " << dp_max[i] << "\n";
	}

	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		cout << dp_min[n] << " " << dp_max[n] << "\n";
	}
}