import { partition } from "./partition.js";

const calcBtn = document.getElementById("calc-btn");
const partitionList = document.getElementById("part-list");
const table = document.getElementById("result-table");

calcBtn.onclick = () => {
	let jarray = partitionList.value.split(",").map(Number);

	let [partBool, partitionResult] = partition(jarray);

	if (partBool) {
		insertToTable(partitionResult);
	} else {
		insertNotPossible();
	}
};

const insertToTable = (results) => {
	let row = table.insertRow();
	let cell1 = row.insertCell(0);
	let cell2 = row.insertCell(1);
	let cell3 = row.insertCell(2);
	cell1.innerHTML = `${results[0]}`;
	cell2.innerHTML = `${results[1]}`;
	cell3.innerHTML = `${results[2]}`;
};

const insertNotPossible = () => {
	console.log(table.tbody);
	let row = table.insertRow();
	let cell1 = row.insertCell(0);
	cell1.innerHTML = `No es posible`;
};
