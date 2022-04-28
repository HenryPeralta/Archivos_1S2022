package comandos

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func Recorrido_rmdisk(comando string) {
	sinsalto := strings.TrimRight(comando, "\n")
	coman := strings.Split(sinsalto, " ")
	var bandera_path bool = false
	var bandera_error bool = false
	var valor_path string = ""
	for i := 0; i < len(coman); i++ {
		param := strings.Split(coman[i], "=")
		for j := 0; j < len(param); j++ {
			if param[j] == "-path" || param[j] == "-PATH" {
				bandera_path = true
				valor_path = param[j+1]
			}
		}
	}
	if !bandera_path {
		bandera_error = true
		fmt.Println("Error: El parametro -path es obligatorio")
	}
	if !bandera_error {
		ejecutarRmdisk(valor_path)
	}
}

func ejecutarRmdisk(ppath string) {

	comillaDer := strings.TrimRight(ppath, "\"")
	comillaIzq := strings.TrimLeft(comillaDer, "\"")
	cambio_ruta := comillaIzq

	var opcion string
	fmt.Println("¿Esta seguro que desea eliminar el disco? S/N : ")
	reader := bufio.NewReader(os.Stdin)
	text, _ := reader.ReadString('\n')
	opcion = text

	if opcion == "S\n" || opcion == "s\n" {
		err := os.Remove(cambio_ruta)
		if err != nil {
			fmt.Println("Error: No se encontro el Disco")
		} else {
			fmt.Println("Disco eliminado exitosamente!")
		}
	} else if opcion == "N\n" || opcion == "n\n" {
		fmt.Println("Opcion Cancelada")
	} else {
		fmt.Println("Solo se permite la opcion s o n")
	}
}
