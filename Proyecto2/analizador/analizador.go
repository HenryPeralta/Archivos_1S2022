package analizador

import (
	"Proyecto2/analizador/comandos"
	"bufio"
	"fmt"
	"log"
	"os"
	"strings"
)

var lista *comandos.Lista = comandos.New_Lista()

func AnalizadorTexto(texto string) {
	palabras := strings.Split(texto, " ")
	if palabras[0] == "MKDISK" || palabras[0] == "mkdisk" {
		comandos.Recorrido_mkdisk(texto)
	} else if palabras[0] == "RMDISK" || palabras[0] == "rmdisk" {
		comandos.Recorrido_rmdisk(texto)
	} else if palabras[0] == "FDISK" || palabras[0] == "fdisk" {
		comandos.Recorrido_fdisk(texto)
	} else if palabras[0] == "EXEC" || palabras[0] == "exec" {
		Coman_exec(texto)
	} else if palabras[0] == "MOUNT" || palabras[0] == "mount" {
		comandos.Recorrido_mount(texto, lista)
	} else {
		fmt.Println("Comando no reconocido")
	}
}

func Coman_exec(texto string) {
	var valor_path string
	sinsalto := strings.TrimRight(texto, "\n")
	coman := strings.Split(sinsalto, " ")
	for i := 0; i < len(coman); i++ {
		param := strings.Split(coman[i], "=")
		for j := 0; j < len(param); j++ {
			if param[j] == "-path" || param[j] == "-PATH" {
				valor_path = param[j+1]
			}
		}
	}
	comillaDer := strings.TrimRight(valor_path, "\"")
	comillaIzq := strings.TrimLeft(comillaDer, "\"")
	ruta := comillaIzq
	Archivo, err := os.Open(ruta)
	if err != nil {
		log.Fatal(err)
	}
	fileScanner := bufio.NewScanner(Archivo)
	fileScanner.Split(bufio.ScanLines)
	var lineas []string
	for fileScanner.Scan() {
		if fileScanner.Text() != "" {
			lineas = append(lineas, fileScanner.Text())
		}
	}
	Archivo.Close()
	for _, line := range lineas {
		palabras := strings.Split(line, " ")
		pInicio := palabras[0]
		for i := 0; i < len(pInicio); i++ {
			if pInicio[0] != 35 {
				AnalizadorTexto(line)
				break
			}
		}
	}
}
