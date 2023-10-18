#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
vector<int> dp;

struct node {
	int index = -1;
	int people = -1;
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

		void set_population(int index, int n) {
			Node[index].people = n;
		}

		node gethead() {
			return Node[0];
		}

		void connect_by_edge(int m, int n) {
			connect(Node[m], Node[n]);
		}

		int find(node pos, int prev_ind) {
			int posind = pos.index;
			if(dp[posind] != -1) return dp[posind];
			cout << posind << endl;
			int sum1 = 0, sum2 = 0;

			sum1 += 1;
			for(node* &n : pos.next) { //선택될 경우
				if(n->index == prev_ind) continue;

				for(node* &m : n->next) { //다음 것들은 선택하지 않음
					if(m->index == pos.index) continue;
					sum1 += find(*m, n->index);
				}
			}

			if(pos.next.size()-1 == 0) sum2 = 65535;
			else {
				for(node* &n : pos.next) {//선택 안 될 경우
					if(n->index == prev_ind) continue;
					sum2 += 1;
					for(node* &m : n->next) { //다음 것들을 선택함
						if(m->index == pos.index) continue;
						sum2 += find(*m, n->index);
					}
				}				
			}
			
			dp[pos.index] = min(sum1, sum2);
			return dp[pos.index];
		}
};

int main() {
	int N; cin >> N;
	tree T = tree(N);

	for(int i = 0; i < N; i++) {
		int n; cin >> n;
		T.set_population(i, n);
	}

	for(int i = 0; i < N-1; i++) {
		int a,b; cin >> a >> b;
		T.connect_by_edge(a-1, b-1);
	}

	dp.push_back(-1);
	dp.push_back(-1);
	cout << T.find(T.gethead(), -1);
}