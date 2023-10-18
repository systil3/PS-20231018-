var fs = require('fs');
const input = fs.readFileSync(__dirname + '/input.txt')
	.toString().split("\n"); 

//이진법 자릿수(몇 번째인지)들을 리턴
function binary(n) {
	if(n === 0) return [];
	if(n === 1) return [0];
	let c = parseInt(Math.log2(n))
	let l = Math.pow(2, parseInt(Math.log2(n)))
	return binary(n-l).concat([c]); 
}

const m = parseInt(input[0])

//1 < n < 500000, log_2(500000) = 18.93
var dp = new Array(20); dp[0] = input[1].split(" ").map(Number).map(x => {return x-1;});
for (var i = 1; i < 20; i++) {
  dp[i] = new Array(m+1);
  for (var j = 0; j < m; j++) {
  	dp[i][j] = dp[i-1][dp[i-1][j]]
  } 
}

const q = parseInt(input[2])
for (var i = 0; i < q; i++) {
	var [n, x] = input[3+i].split(" ").map(Number);
	let digits = binary(n), res = x-1;
	
	for (digit of digits) {
		res = dp[digit][res]
	} console.log(res+1);
}