#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#define ll long long
using namespace std;
vector<vector<int>> output;
int s, n, k;

void fractal(int r1, int c1, int r2, int c2) {
	int t = 0;
	while(t < s) {
		ll unit_size = pow(n, t); 
		for(int i = r1; i <= r2; i++) {
			for(int j = c1; j <= c2; j++) {
				if(!output[i-r1][j-c1]) continue;

				if((int)(i/unit_size)%3 == 1 && (int)(j/unit_size)%3 == 1)
					output[i-r1][j-c1] = 0;
			}
		}

		t++;
	}
}

int main() {
	int r1, r2, c1, c2; 
	cin >> s >> n >> k >> r1 >> r2 >> c1 >> c2;
	for(int i = 0; i < r2-r1+1; i++) 
		output.push_back(vector<int>(c1-c2+1, 1));

	fractal(r1, c1, r2, c2);
	for(auto &row : output) {
		for(auto &num : row) cout << num;
		cout << "\n";
	}
	
}