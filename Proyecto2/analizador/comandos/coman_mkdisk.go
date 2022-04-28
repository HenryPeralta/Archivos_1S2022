package comandos

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"log"
	"math/rand"
	"os"
	"strconv"
	"strings"
	"time"
	"unsafe"
)

func Recorrido_mkdisk(comando string) {
	sinsalto := strings.TrimRight(comando, "\n")
	coman := strings.Split(sinsalto, " ")
	var bandera_size bool = false
	var bandera_path bool = false
	var bandera_error bool = false
	var valor_size int = 0
	var valor_fit string = "ff"
	var valor_unit string = "m"
	var valor_path string = ""
	for i := 0; i < len(coman); i++ {
		param := strings.Split(coman[i], "=")
		for j := 0; j < len(param); j++ {
			if param[j] == "-size" || param[j] == "-SIZE" {
				sv, _ := strconv.Atoi(param[j+1])
				valor_size = sv
				if valor_size <= 0 {
					bandera_error = true
					fmt.Println("Los valores de size no pueden ser menores o iguales a cero")
				} else {
					bandera_size = true
				}
			} else if param[j] == "-fit" || param[j] == "-FIT" {
				valor_fit = param[j+1]
			} else if param[j] == "-unit" || param[j] == "-UNIT" {
				valor_unit = param[j+1]
			} else if param[j] == "-path" || param[j] == "-PATH" {
				bandera_path = true
				valor_path = param[j+1]
			}
		}
	}
	if !bandera_size {
		bandera_error = true
		fmt.Println("Error: El parametro -size es obligatorio")
	}
	if !bandera_path {
		bandera_error = true
		fmt.Println("Error: El parametro -path es obligatorio")
	}
	if !bandera_error {
		ejecutarDisco(valor_size, valor_fit, valor_unit, valor_path)
	}
}

func ejecutarDisco(psize int, pfit string, punit string, ppath string) {

	comillaDer := strings.TrimRight(ppath, "\"")
	comillaIzq := strings.TrimLeft(comillaDer, "\"")
	cambio_ruta := comillaIzq

	crearDirectorio(cambio_ruta)

	file, _ := os.Create(cambio_ruta)
	defer file.Close()

	prueba := MBR{}

	var temporal int8 = 0
	s := &temporal
	var binario bytes.Buffer
	binary.Write(&binario, binary.BigEndian, s)

	if punit == "k" || punit == "K" {
		prueba.Mbr_tamano = int64(psize * 1024)

		for i := 0; i < psize*1024; i++ {
			escribirBytes(file, binario.Bytes())
		}
	} else if punit == "m" || punit == "M" {
		prueba.Mbr_tamano = int64(psize * 1024 * 1024)

		for i := 0; i < psize*1024*1024; i++ {
			escribirBytes(file, binario.Bytes())
		}
	}

	tiempo := time.Now()
	time := tiempo.String()

	for t := 0; t < 19; t++ {
		prueba.Mbr_fecha_creacion[t] = time[t]
	}

	numeroRandom := rand.Intn(100-1) + 1
	prueba.Mbr_dsk_signature = int64(numeroRandom)

	var auxfit byte = 0

	if pfit == "bf" || pfit == "BF" {
		auxfit = 'B'
	} else if pfit == "ff" || pfit == "FF" {
		auxfit = 'F'
	} else if pfit == "wf" || pfit == "WF" {
		auxfit = 'W'
	}

	prueba.Dsk_fit = auxfit

	for p := 0; p < 4; p++ {
		prueba.Mbr_partition[p].Part_status = '0'
		prueba.Mbr_partition[p].Part_type = '0'
		prueba.Mbr_partition[p].Part_fit = '0'
		prueba.Mbr_partition[p].Part_size = 0
		prueba.Mbr_partition[p].Part_start = -1
		for n := 0; n < 16; n++ {
			prueba.Mbr_partition[p].Part_name[n] = '0'
		}
	}

	//nos posicionamos al inicio del archivo usando la funcion Seek
	file.Seek(0, 0)

	//Escribimos struct de mbr
	var bufferControl bytes.Buffer
	binary.Write(&bufferControl, binary.BigEndian, &prueba)
	escribirBytes(file, bufferControl.Bytes())

	//movemos el puntero a donde ira nuestra primera estructura
	file.Seek(int64(unsafe.Sizeof(prueba)), 0)

	fmt.Println("Disco creado correctamente")
	fmt.Println("Se agrego el mbr de manera correcta")

}

func crearDirectorio(path string) {
	directorio := obtener_path(path)
	if _, err := os.Stat(directorio); os.IsNotExist(err) {
		err = os.MkdirAll(directorio, 0777)
		if err != nil {
			panic(err)
		}
	}
}

func obtener_path(path string) string {
	var aux_path int
	var aux_ruta string

	for i := len(path) - 1; i >= 0; i-- {
		aux_path++
		if string(path[i]) == "/" {
			break
		}
	}

	for i := 0; i < ((len(path)) - (aux_path - 1)); i++ {
		aux_ruta += string(path[i])
	}

	return aux_ruta
}

func escribirBytes(file *os.File, bytes []byte) {
	_, err := file.Write(bytes)

	if err != nil {
		log.Fatal(err)
	}
}
