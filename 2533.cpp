#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
#define MAXINT 65535
vector<int> dp[2];

struct node {
	int index = -1;
	bool adapt = false;
	vector<node*> next;
};

void connect(node &a, node &b) {
	//cout << "push : " << a.index << " " << b.index << endl;
	b.next.push_back(&a);
	a.next.push_back(&b);
}

class tree {
	private:
		vector<node> Node;
		int size;

	public:
		tree(int size) {
			for(int i = 0; i < size; i++) {
				node tmp = {i+1, false, vector<node*>{}};
				Node.push_back(tmp);
			}
		}

		node gethead() {
			return Node[0];
		}

		void connect_by_edge(int m, int n) {
			connect(Node[m], Node[n]);
		}

		int find(node pos, int prev_ind, bool state, bool prev_state) {
			int posind = pos.index;
			if(dp[state][posind] != -1) return dp[state][posind];
			cout << posind << endl;
			int sum1 = 0, sum2 = 0;

			if(state){ //선택될 경우
				if(pos.next.size() == 1) return 1; //리프 노드 

				sum1 += 1;
				for(node* &n : pos.next) { 
					if(n->index == prev_ind) continue;
					sum1 += find(*n, posind, false, true);
				}
				dp[1][posind] = sum1; return sum1;
			}

			else { //선택 안 될 경우
				if(pos.next.size() == 1) return prev_state == true? 1 : MAXINT; //리프 노드

				for(node* &n : pos.next) {
					if(n->index == prev_ind) continue;
					if(prev_state) sum2 += min(find(*n, posind, true, true), find(*n, posind, false, true));
					else sum2 += find(*n, posind, true, false);
				}


				dp[0][posind] = sum2; return sum2;	
			}
		}
};

int main() {
	int N; cin >> N;
	tree T = tree(N);

	for(int i = 0; i < N-1; i++) {
		int a,b; cin >> a >> b;
		T.connect_by_edge(a-1, b-1);
		dp[0].push_back(-1);
		dp[1].push_back(-1);
	}

	dp[0].push_back(-1);
	dp[1].push_back(-1);
	dp[0].push_back(-1);
	dp[1].push_back(-1);
	cout << min(T.find(T.gethead(), -1, false, false), T.find(T.gethead(), -1, true, false));
}