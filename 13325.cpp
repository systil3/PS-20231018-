#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;
#define ll long long int

struct node {
	int index;
	int l_edge = 0;
	int r_edge = 0;
	int dist = 0;
};

vector<node> tree;

int find(int pos, int n) {
	if(pos > n) return 0;

	int lw = tree[pos].l_edge, rw = tree[pos].r_edge;
	int lc = find(2*pos,n), rc = find(2*pos+1,n);
	int ld = 0, rd = 0; //양쪽 자식 노드에서 찾아낸 거리(find로)
	if(2*pos < n) 
        {ld = tree[2*pos].dist; rd = tree[2*pos+1].dist;}

	tree[pos].dist = max(lw+ld, rw+rd);
	tree[pos].l_edge = tree[pos].dist - ld;
	tree[pos].r_edge = tree[pos].dist - rd;
	return max(lw+ld, rw+rd) - min(lw+ld, rw+rd) + lc + rc;
}

int print_sum(int n) {
	int sum = 0;
	for(int i = 1; i <= n; i++) 
		sum += (tree[i].l_edge + tree[i].r_edge);

	cout << sum;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int h; cin >> h;
	int n = pow(2, h+1)-1; //전체 노드의 개수
	tree.push_back(node{-1});

	for(int i = 1; i <= n; i++) 
		tree.push_back(node{i}); 

	int s = 1, t = 2;
	for(int i = 0; i < n-1; i++) {
		int tmp; cin >> tmp;

		if(t == 2*s) {
			tree[s].l_edge = tmp;
			t++; }

		else if(t == 2*s+1) {
			tree[s].r_edge = tmp;
			s++; t = 2*s; }
	}

	find(1, n); print_sum(n);
}