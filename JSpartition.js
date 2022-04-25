function isSubsetExist(S, n, a, b, c, subList) {
	if (a === 0 && b === 0 && c === 0) return true;
	if (n < 0) return false;

	let A = false;
	if (a - S[n] >= 0) {
		subList[n] = 1;
		A = isSubsetExist(S, n - 1, a - S[n], b, c, subList);
	}

	let B = false;
	if (!A && b - S[n] >= 0) {
		subList[n] = 2;
		B = isSubsetExist(S, n - 1, a, b - S[n], c, subList);
	}

	let C = false;
	if (!A && !B && c - S[n] >= 0) {
		subList[n] = 3;
		C = isSubsetExist(S, n - 1, a, b, c - S[n], subList);
	}

	return A || B || C;
}

export function partition_js(S) {
	let total = S.reduce((a, b) => a + b);
	let A = Array(S.length).fill(null);

	let result =
		S.length >= 3 &&
		total % 3 === 0 &&
		isSubsetExist(S, S.length - 1, total / 3, total / 3, total / 3, A);

	if (!result) return [false, ""];

	let partArray = [[], [], []];
	for (let i = 0; i < 3; i++) {
		for (let j = 0; j < S.length; j++) {
			if (A[j] == i + 1) {
				partArray[i].push(S[j]);
			}
		}
	}

	return [true, partArray];
}
