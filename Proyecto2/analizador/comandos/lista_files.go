package comandos

type NodoF struct {
	siguiente *NodoF
	n_files   *NFiles
}

type ListaF struct {
	primero  *NodoF
	ultimo   *NodoF
	contador int
}

func New_NodoF(n_files *NFiles) *NodoF {
	return &NodoF{nil, n_files}
}

func New_ListaF() *ListaF {
	return &ListaF{nil, nil, 0}
}

func InsertarF(n_files *NFiles, lista *ListaF) {
	var nuevo *NodoF = New_NodoF(n_files)

	if lista.primero == nil {
		lista.primero = nuevo
		lista.ultimo = nuevo
		lista.contador += 1
	} else {
		lista.ultimo.siguiente = nuevo
		lista.ultimo = lista.ultimo.siguiente
		lista.contador += 1
	}
}

/*func mostrarListaFiles(lista *ListaF) {
	fmt.Println("---------------------------")
	fmt.Println("|   Lista de Files        |")
	fmt.Println("---------------------------")
	fmt.Println("|   FILES                 |")
	fmt.Println("---------------------------")
	aux := lista.primero
	for aux != nil {
		fmt.Println("   ", aux.n_files.Path)
		fmt.Println("---------------------------")
		aux = aux.siguiente
	}
}*/
