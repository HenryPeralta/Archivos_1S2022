package main

import (
	"Proyecto2/analizador"
	"bufio"
	"fmt"
	"os"
)

func main() {
	var salir bool = false
	var entrada string
	fmt.Println(" -------------------------------")
	fmt.Println("|          Proyecto 2           |")
	fmt.Println(" -------------------------------")
	fmt.Println("|Henry Gabriel Peralta Martinez |")
	fmt.Println("|          2017122789           |")
	fmt.Println(" -------------------------------")

	for {
		if !salir {
			fmt.Println(" -------------------------------")
			fmt.Println("|      Ingrese un Comando       |")
			fmt.Println(" -------------------------------")
			reader := bufio.NewReader(os.Stdin)
			text, _ := reader.ReadString('\n')
			entrada = text
			if entrada == "salir\n" {
				fmt.Println("Se Finalizo el programa")
				salir = true
				break
			} else {
				analizador.AnalizadorTexto(entrada)
			}
		}
	}
}
