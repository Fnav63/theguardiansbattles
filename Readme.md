//// Funciones ////

crearNodo: Se crea el nodo para el arbol binario, un código estándar de creación de nodo.

insertarNodo: Se inserta un nodo en el árbol binario. Esta funcion se llama desde leerGuardianes y su código es uno común y corriente donde el nivel de poder del guardian se toma como referencia para el orden de los nodos.

GrafoLista: Esta es la clase para poder crear el grafo usando una lista de adyacencia.

leerCiudades: Se lee el archivo en busca de los nombres de las ciudades, donde se guardan en un vector de string para su uso más adelante sin que se repitan los nombres.

leerConexiones: Esta función permite leer las conexiones entre ciudades leídas desde el archivo cities.conf, aquí se van agregando las aristas en el grafo, representando correctamente las relaciones entre ciudades.

leerGuardianes: Esta función permite leer los guardianes desde el archivo, con la correcta validación de los niveles de poder y las ciudades.

insertarMaestrosEnArbol: Esta función permiteinsertar a los guardianes en el arbol de jerarquía. Mediante el uso de queue, se pueden ir agregando a los guardianes dependiendo también de su nombre y quién es su maestro.

buscar: Con esta función se puede buscar a un guardián dentro del arbol de jerarquía usando su nombre y una cola para encontrarlo.

resultadoPelea: Se genera un numero aleatorio del 1 al 6, representando un dado, si se obtiene 5 o 6 el guardian ganará. En esta función se utilizó la función rand para la generación del numero random y srand para la seed.

eliminarNodo: Esta función permite eliminar a un nodo del arbol binario, buscando con un el nivel de poder y el nombre del guardian. Se usa luego de cada pelea para poder luego actualizar el arbol de ranking.

encontrarNodoMinimo: Esta función forma parte de eliminarNodo, permite buscar al nodo más pequeño dentro del arbol binario, es decir, el nodo que se encuentra más a la izquierda.

mostrarArbol: Imprime a los guardianes dentro del arbol binario, aquí se indica si el personaje es un guardian o candidato a guardián.

mostrarArbolsologuardianesJugables: Funcion que imprime solo a los personaje que esten por debajo de 90 de nivel de poder, es decir, los personajes que el usuario puede elegir.

mostrarCandidatos: Funcion para imprimir solo a los candidatos a guardian o a los que ya son guardianes.

mostrarGuardianesdelaCiudad: Funcion para mostrar a los guardianes que se encuentran en una ciudad en específico utilizando recursividad.

mostrarGuardianesdelaCiudadPelea: Funcion para mostrar y comprobar si hay personajes que el usuario puede retar a una pelea en una ciudad. Se utilizó una cola para su funcionamiento.

