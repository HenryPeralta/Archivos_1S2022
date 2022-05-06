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
var listaLogin *comandos.ListaL = comandos.New_ListaL()
var listaFiles *comandos.ListaF = comandos.New_ListaF()

var bandera_login bool = false

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
	} else if palabras[0] == "REP" || palabras[0] == "rep" {
		comandos.Recorrido_rep(texto, lista, listaFiles)
	} else if palabras[0] == "MKFS" || palabras[0] == "mkfs" {
		comandos.Recorrido_mkfs(texto, lista)
	} else if palabras[0] == "LOGIN" || palabras[0] == "login" {
		if !bandera_login {
			comandos.Recorrido_login(texto, lista, listaLogin)
			bandera_login = true
		} else {
			fmt.Println("Error: ya hay un usuario logeado")
		}
	} else if palabras[0] == "LOGOUT" || palabras[0] == "logout" {
		if !bandera_login {
			fmt.Println("No hay ninguna sesion iniciada")
		} else {
			fmt.Println("Se ha terminado la sesion correctamente")
			bandera_login = false
		}
	} else if palabras[0] == "MKGRP" || palabras[0] == "mkgrp" {
		if !bandera_login {
			fmt.Println("Error: No se ha iniciado sesión")
		} else {
			comandos.Recorrido_mkgrp(texto)
		}
	} else if palabras[0] == "RMGRP" || palabras[0] == "rmgrp" {
		if !bandera_login {
			fmt.Println("Error: No se ha iniciado sesión")
		} else {
			comandos.Recorrido_rmgrp(texto)
		}
	} else if palabras[0] == "MKUSR" || palabras[0] == "mkusr" {
		if !bandera_login {
			fmt.Println("Error: No se ha iniciado sesión")
		} else {
			comandos.Recorrido_mkusr(texto)
		}
	} else if palabras[0] == "RMUSR" || palabras[0] == "rmusr" {
		if !bandera_login {
			fmt.Println("Error: No se ha iniciado sesión")
		} else {
			comandos.Recorrido_rmusr(texto)
		}
	} else if palabras[0] == "MKFILE" || palabras[0] == "mkfile" {
		if !bandera_login {
			fmt.Println("Error: No se ha iniciado sesión")
		} else {
			comandos.Recorrido_mkfile(texto, listaFiles)
		}
	} else if palabras[0] == "MKDIR" || palabras[0] == "mkdir" {
		if !bandera_login {
			fmt.Println("Error: No se ha iniciado sesión")
		} else {
			comandos.Recorrido_mkdir(texto, lista)
		}
	} else if palabras[0] == "PAUSE" || palabras[0] == "pause" {
		Coman_pause()
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

func Coman_pause() {
	fmt.Println("Presione enter para poder continuar")
	reader := bufio.NewReader(os.Stdin)
	text, _ := reader.ReadString('\n')
	entrada := text
	for {
		if entrada == "\n" {
			break
		}
	}
}
