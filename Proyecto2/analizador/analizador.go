package analizador

import (
	"Proyecto2/analizador/comandos"
	"fmt"
	"strings"
)

func AnalizadorTexto(texto string) {
	//fmt.Println(texto)
	//textoM := strings.ToUpper(texto)
	//fmt.Println(textoM)
	//fmt.Println(strings.Split(textoM, " "))
	//sas := "1234,\"Calle Jaime III, 34\", 67,3,U"
	//sas := "juan perez \"Calle Jaime III, 34\" 67 3 Union"
	//sas := "mkdisk -size=300 -unit=k ,-fit=ff -path=\"/home/henry/disco,1.dk\""
	//prueba := strings.Split(sas, "")
	//fmt.Println(len(prueba))
	//fmt.Println(prueba)
	palabras := strings.Split(texto, " ")
	//fmt.Println(len(palabras))
	//fmt.Println(palabras[0] + " Esta es la primera palabra")
	//fmt.Println(len(palabras))
	if palabras[0] == "MKDISK" || palabras[0] == "mkdisk" {
		//fmt.Println("Estoy en MKDISK")
		comandos.Recorrido_mkdisk(texto)
	} else {
		fmt.Println("Comando no reconocido")
	}
	/*for index, palabra := range palabras {
		fmt.Printf("Porción %d es: %s\n", index, palabra)
	}*/
}
