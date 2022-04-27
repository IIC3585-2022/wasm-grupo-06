import Module from "./partitionWASM.js"

const callBtn = document.getElementById("call-btn");
const set = document.getElementById("set");

Module().then(function(mymod) {
  callBtn.onclick = () => {
    const values = set.value.split(",") 
    var final_set = values.map(function (value) {
        return parseInt(value);  
    });
    cRunner(final_set, mymod);
    }
  }
)

const cRunner = (vector, Module) => {
    Module._partition(vector);
}

