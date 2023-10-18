#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <sstream>
#include <map>
#include <set>
using namespace std;
#define point pair<int, int> 
#define ll long long

int n;  //정보의 개수
int f; //벌금
int day_sum[14] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

ll to_min(vector<ll> p) {
	return ((p)[0]*1440 + (p)[1]*60 + (p)[2]);
}

struct datetime {
	ll year, month, day, hour, min;

	vector<ll> operator-(const datetime d) {
		ll year_sub = year - d.year;
		ll day_sub = day_sum[month] + day + (year%4 == 0)
		 	- (day_sum[d.month] + d.day);

		day_sub += 365*year_sub + (ll)(year/4) - (ll)(d.year/4);

		ll hour_sub = hour - d.hour;
		ll min_sub = min - d.min;
		if(min_sub < 0) {hour_sub--; min_sub += 60;}

		return vector<ll>{day_sub, hour_sub, min_sub};
	};
};

map<string, map<string, datetime>> borrow; //유저 이름 입력 -> 물품 이름 입력하면 대여 시간 파악 가능
map<string, ll> fines;

vector<int> parsetoInt(string input, char delim) {
	vector<int> answer;
	stringstream ss(input);
    string temp;
 
    while (getline(ss, temp, delim)) {
        answer.push_back(stoi(temp));
    }

    return answer;
}

int main() {

	ios::sync_with_stdio(0); cin.tie(0);
	string input; 
    cin >> n >> input >> f;

    char cinput[100]; strcpy(cinput, input.c_str());

    ll d = stoi(strtok(cinput, ":/"));
    ll h = stoi(strtok(NULL, ":/"));
    ll m = stoi(strtok(NULL, ":/"));
    vector<ll> limit{d,h,m}; //대여기간

    while(n--) {

    	string ymd, hm, article, user;
    	cin >> ymd >> hm >> article >> user;

    	datetime b_time{
    		parsetoInt(ymd, '-')[0],
    		parsetoInt(ymd, '-')[1],
    		parsetoInt(ymd, '-')[2],
    		parsetoInt(hm, ':')[0],
    		parsetoInt(hm, ':')[1]
    	};
    	
    	//대여 정보가 있음
    	if(borrow[user].find(article) != borrow[user].end()) {

    		vector<ll> period = b_time-borrow[user][article];
    		
    		borrow[user].erase(article);
			//cout << user << article << " " << to_min(period) << " " << to_min(limit) << endl;

    		//대여기간 초과 시 벌금
    		if(to_min(period) > to_min(limit)) {
    			if(!fines[user]) fines[user] = (to_min(period) - to_min(limit)) * f;
    			else fines[user] += (to_min(period) - to_min(limit)) * f;
    		}
    	} 

    	//정보가 없음
    	else {
	    	borrow[user][article] = b_time;
    	}
    }

    if(fines.empty()) cout << -1;
    else {
	    for(map<string,ll>::iterator it = fines.begin(); it != fines.end(); ++it) {
		  cout << it->first << " " << it->second << "\n";
		}
	}
}