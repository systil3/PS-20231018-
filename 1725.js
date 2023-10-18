let fs = require('fs');
const input = fs.readFileSync(__dirname + '/input.txt').toString().split(' ').map(Number)
const INT_MAX = 2147483647

class minTree {
	init(arr, idx, start, end) {
		if(start == end) {
			return this.tree[idx] = arr[start]
		} else {
			const mid = parseInt((start+end)/2)
			return this.tree[idx] = Math.min(
				init(arr, 2*idx, start, mid),
				init(arr, 2*idx+1, mid+1, end)
			) 
		}
	}

	constructor(arr, n) {
		this.tree = new Array(2**(parseInt(Math.log2)+2))
		this.n = n
		init(arr, 1, 0, n-1)
	}

	find_min(idx, i, j, l, r) {
		if(i < l || j > r) {return INT_MAX}
		if(i == j) {return this.tree[idx] * 1}
		else {
			const mid = parseInt((i+j)/2)
			return Math.min(
				find_min(2*idx, i, mid, l, r) / (mid-i+1),
				find_min(2*idx+1, mid+1, j, l, r) / (j-(mid+1)+1)
			) * (j-i+1)
		}
	}
}

const 

const segtree = new minTree(input, n)

