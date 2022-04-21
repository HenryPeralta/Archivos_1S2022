package analizador

import (
	"Proyecto2/analizador/comandos"
	"fmt"
	"strings"
)

func AnalizadorTexto(texto string) {
	palabras := strings.Split(texto, " ")
	if palabras[0] == "MKDISK" || palabras[0] == "mkdisk" {
		comandos.Recorrido_mkdisk(texto)
	} else if palabras[0] == "RMDISK" || palabras[0] == "rmdisk" {
		comandos.Recorrido_rmdisk(texto)
	} else {
		fmt.Println("Comando no reconocido")
	}
}
