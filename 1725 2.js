const INT_MAX = 2147483647

var fs = require('fs');
const input = fs.readFileSync(__dirname + '/input.txt')
	.toString().split("\n").map(Number); 


const n = input[0]
let arr = input.slice(1, n+1)
console.log(arr)

function find_max(l, r, arr) {
	
	if(l === r) {
		return arr[l]
	} else {
		
		const mid = parseInt((l+r)/2)
		const s1 = find_max(l, mid, arr)
		const s2 = find_max(mid+1, r, arr)

		var r_pos = mid; var l_pos = mid;
		var curr_h = arr[mid], max_s = arr[mid];
		var s3 = -1;

		while(l_pos > l || r_pos < r) {
			//console.log(l, mid, r)
			//console.log(l_pos, r_pos)
			while(r_pos+1 <= r && arr[r_pos+1] >= curr_h) {
				max_s += curr_h; r_pos++; 
			}

			while(l_pos-1 >= l && arr[l_pos-1] >= curr_h) {
				max_s += curr_h; l_pos--; 
			}

			//높이가 낮은 기둥에 부딫혀 더 못갈때 두 경계중 더 큰 높이를 중심으로 확장
			s3 = Math.max(max_s, s3)
			console.log(curr_h, l_pos, r_pos, max_s)

			if(l_pos != l && r_pos === r) curr_h = arr[l_pos-1];
			if(l_pos === l && r_pos != r) curr_h = arr[r_pos+1];
			if(l_pos != l && r_pos != r) curr_h = Math.max(arr[l_pos-1], arr[r_pos+1])
			
			max_s = (r_pos - l_pos + 1) * curr_h
			
		}

		return Math.max(s1, s2, s3)
	}
}

console.log(find_max(0, n-1, arr))
