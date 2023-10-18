let fs = require('fs');
const input = fs.readFileSync(__dirname + '/input.txt').toString().split(' ').map(Number)

const [x, y, d, t] = input
const l = Math.sqrt(x**2 + y**2)

if(d/t < 1) {
	console.log(l)}
else {
	//원점 도달 직전까지 뛴 후 걷기
	const t1 = parseInt(l/d) * t + (l%d)

	//원점을 넘어서 도달하기까지 뛴 후 역방향으로 걷기
	const t2 = (parseInt(l/d)+1) * t + (d-(l%d))

	let t3;
	//대각선으로 뛰기 -> 직선으로 n번 뛰기 -> 다시 대각선으로 뛰어서 도착
	if(l < d) {
		// l < d이면 그냥 대각선으로 두 번 뛰어서 가기
		t3 = 2*t
	} else {
		const n = parseInt((l-d) / d)
		t3 = (n+2) * t
	}

	console.log(Math.min(t1, t2, t3))
}

