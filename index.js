import Module from "./Cpartition.js";
import { partition_js } from "../JSpartition.js";

const partitionInput = document.getElementById("part-input");
const JStable = document.getElementById("tabla-js");
const Ctable = document.getElementById("tabla-c");

const jsBtn = document.getElementById("calc-js");
const cBtn = document.getElementById("calc-c");
const bothBtn = document.getElementById("calc-both");

const insertToTable = (results, table_type, time) => {
	let table = "";
	if (table_type === "js") table = JStable;
	else if (table_type === "c") table = Ctable;
	let row = table.insertRow();
	let cell1 = row.insertCell(0);
	let cell2 = row.insertCell(1);
	let cell3 = row.insertCell(2);
	let cell4 = row.insertCell(3);
	cell1.innerHTML = `{${results[0]}}`;
	cell2.innerHTML = `{${results[1]}}`;
	cell3.innerHTML = `{${results[2]}}`;
	cell4.innerHTML = time + "ms";
};

const insertNotPossible = (table_type, time) => {
	let table = "";
	if (table_type === "js") table = JStable;
	else if (table_type === "c") table = Ctable;
	let row = table.insertRow();
	let cell1 = row.insertCell(0);
	row.insertCell(1);
	row.insertCell(2);
	let cell4 = row.insertCell(3);
	cell1.innerHTML = `No es posible`;
	cell4.innerHTML = time + "ms";
};

const cPartition = (mymod) => {
	let input_array = partitionInput.value.split(",").map(Number);
	let data_pointer = mymod._malloc(4 * input_array.length);
	for (let i = 0; i < input_array.length; i++) {
		mymod.setValue(data_pointer + i * 4, parseInt(input_array[i]));
	}
	let pointerArray = [
		mymod._malloc(4 * input_array.length),
		mymod._malloc(4 * input_array.length),
		mymod._malloc(4 * input_array.length),
	];
	for (let i = 0; i < input_array.length; i++) {
		mymod.setValue(pointerArray[0] + 4 * i, -1);
		mymod.setValue(pointerArray[1] + 4 * i, -1);
		mymod.setValue(pointerArray[2] + 4 * i, -1);
	}

	let partition = mymod.cwrap("partition", "number", [
		"number",
		"number",
		"number",
		"number",
		"number",
	]);

	let start = performance.now();
	partition(
		data_pointer,
		input_array.length,
		pointerArray[0],
		pointerArray[1],
		pointerArray[2]
	);
	let end = performance.now();

	let cPartArray = [[], [], []];

	for (let j = 0; j < 3; j++) {
		for (let i = 0; i < input_array.length; i++) {
			let val = mymod.getValue(pointerArray[j] + 4 * i);
			if (val != -1) cPartArray[j].push(val);
		}
	}

		if (cPartArray[0].length != 0)
		insertToTable(cPartArray, "c", (end - start).toFixed(1));
	else {
		insertNotPossible("c", (end - start).toFixed(1));
	}
};

const jsPartition = () => {
	let jarray = partitionInput.value.split(",").map(Number);
	let start = performance.now();
	let [partBool, jsPartArray] = partition_js(jarray);

	let end = performance.now();
	if (partBool) {
		insertToTable(jsPartArray, "js", (end - start).toFixed(1));
	} else {
		insertNotPossible("js", (end - start).toFixed(1));
	}
};

Module().then(function (mymod) {
	jsBtn.onclick = () => {
		jsPartition();
	};
	cBtn.onclick = () => {
		cPartition(mymod);
	};

	bothBtn.onclick = () => {
		jsPartition();
		cPartition(mymod);
	};
});
