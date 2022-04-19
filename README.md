# Tarea 3 - Grupo 06
Todo esto lo hice en wsl para hacerlo en windows o mac revisen los link que deje abajo. 
## Instalación de Emscripten
Esto lo hice yo y solo tienen que hacerlo si cambian el codigo de ```partition.cc```, y pasar después al [siguiente paso](#compilacion-archivo-wasm). Si no quieren cambiar el arhivo y solo quieren probar como funciona salten [aca] de una. (#visualización-archivo-html)
```bash
# Clonar el repo de emsdk
git clone https://github.com/emscripten-core/emsdk.git

# Entrar a la carpeta
cd emsdk

# Descargaer e instalar las últimas herramientas de SDK.
./emsdk install latest

# Activar las últimas herramientas de SDK (escribe el arcihvo .emscripten)
./emsdk activate latest

# Activar el path y otras variables de entorno
source ./emsdk_env.sh
```

## Compilacion archivo wasm
En el terminal deben correr lo siguiente
```bash
emcc -s EXIT_RUNTIME=1 WASM/partition.cc -o WASM/partition.html
```
Esto va a crear o sobreescribir los archivos ```partition.html```, ```partition.js```, ```partition.wasm```. Hay que correr esto cada vez que se realice algun cambio en el archivo ```partition.cc```. 

## Visualización archivo html
Abrir directamente el archivo ```partition.html``` no les va a funcionar, ya que tiene que estar corriendo todo en un server. Para crear un server use python, entonces tienen que correr lo siguiente en el terminal:
```bash 
python3 -m http.server
```
Esto les va a crear un server en el puerto ```8000```, entonces van a http://localhost:8000 y ahi navegan hasta la carpeta ```WASM``` y abren el archivo ```partition.html```. Ahí deberían ver como el código les va a correr y les va a mostrar el output. 

## Cosas listas y por hacer
- [x] Instalación emscripten
- [x] Algoritmo particiones en c/c++
- [x] Compliación archivo WASM
- [ ] Algoritmo que reciba inputs
- [ ] HTML creado por nosotros (no sé si hay que hacer esto para el js y para el wasm o solo para el js)
- [ ] Algoritmo en js (https://www.techiedelight.com/3-partition-problem-extended-print-all-partitions/) esta la base acá. 
- [ ] Comparación de tiempos.

## Links
- Para el algoritmo de particiones: https://www.techiedelight.com/3-partition-problem-extended-print-all-partitions/ 
- Para la compilación del archivo wasm: https://developer.mozilla.org/en-US/docs/WebAssembly/C_to_wasm#creating_html_and_javascript
- Para entender Web Assembly: https://hackernoon.com/webassembly-the-journey-a069d6ea18a