#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <time.h>

using namespace std;

// STRUCTS
struct Guardian 
{
    string nombre;
    int poder = 0;
    string ciudad;
    string maestro;
};
struct Ciudad
{
    string nombre;
};
struct arbolRanking 
{
    Guardian* guardian;
    arbolRanking* izq;
    arbolRanking* der;
};
struct arbolMaestro 
{
    Guardian* guardian = NULL;
    vector<arbolMaestro*> aprendices;
};

// FUNCIONES
arbolRanking* crearNodo(Guardian* n)
{
    // Se crea el nodo para el arbol binario

    arbolRanking* nuevo_nodo = new arbolRanking;

    nuevo_nodo->guardian = n;
    nuevo_nodo->der = NULL;
    nuevo_nodo->izq = NULL;

    return nuevo_nodo;
}
void insertarNodo(arbolRanking *&arbol, Guardian* guardian)
{
    // Funcion estandar para la inserción de nodos en un arbol binario usando el nivel de poder del guardian

    if (arbol == NULL)
    {
        arbolRanking* nuevo_nodo = crearNodo(guardian);
        arbol = nuevo_nodo;
    }
    else
    {
        double valorRaiz = arbol->guardian->poder;
        if (guardian->poder < valorRaiz)
        {
            insertarNodo(arbol->izq, guardian);
        }
        else
        {
            insertarNodo(arbol->der, guardian);
        }
    }
}
void mostrarArbol(arbolRanking* arbol, int contador)
{
    // Funcion para imprimir a los guardianes del arbol binario, donde se indica si el personaje es guardian o candidato a guardian

    if (arbol == NULL)
    {
        return;
    }
    else
    {
        mostrarArbol(arbol->der, contador + 1);
        if (arbol->guardian->poder > 90)
        {
            cout << "Nombre: " << arbol->guardian->nombre << "         /// Guardian/candidato a guardian ///" << endl;
            cout << "Nivel de poder: " << arbol->guardian->poder << endl << endl;
        }
        if (arbol->guardian->poder < 90)
        {
            cout << "Nombre: " << arbol->guardian->nombre << endl;
            cout << "Nivel de poder: " << arbol->guardian->poder << endl << endl;
        }
        mostrarArbol(arbol->izq, contador + 1);
    }
}
void mostrarArbolsologuardianesJugables(arbolRanking* arbol, int contador)
{
    // Funcion que imprime solo a los personaje que esten por debajo de 90 de nivel de poder, es decir, los personajes que el usuario puede elegir

    if (arbol == NULL)
    {
        return;
    }
    else
    {
        mostrarArbolsologuardianesJugables(arbol->der, contador + 1);
        if (arbol->guardian->poder < 90)
        {
            cout << "Nombre: " << arbol->guardian->nombre << endl;
            cout << "Nivel de poder: " << arbol->guardian->poder << endl;
            cout << "Ciudad: " << arbol->guardian->ciudad << endl << endl;
        }
        mostrarArbolsologuardianesJugables(arbol->izq, contador + 1);
    }
}
void mostrarCandidatos(arbolRanking* arbol, int contador)
{
    // Funcion para imprimir solo a los candidatos a guardian o a los que ya son guardianes

    if (arbol == NULL)
    {
        return;
    }
    else
    {
        mostrarCandidatos(arbol->der, contador + 1);
        if (arbol->guardian->poder > 90)
        {
            cout << "Nombre: " << arbol->guardian->nombre << endl;
            cout << "Nivel de poder: " << arbol->guardian->poder << endl << endl;
        }
        mostrarCandidatos(arbol->izq, contador + 1);
    }
}
void mostrarGuardianesdelaCiudad(arbolMaestro* arbol, string ciudad)
{
    // Funcion para mostrar a los guardianes que se encuentran en una ciudad en especifico

    if (arbol == NULL)
    {
        return;
    }
    if (arbol->guardian->ciudad == ciudad)
    {
        cout << "- " << arbol->guardian->nombre << endl;
    }
    for (size_t i = 0; i < arbol->aprendices.size(); i++)
    {
        mostrarGuardianesdelaCiudad(arbol->aprendices[i], ciudad);
    }
}
bool mostrarGuardianesdelaCiudadPelea(arbolMaestro* arbol, arbolMaestro* guardian)
{
    // Funcion para mostrar y comprobar si hay personajes que el usuario puede retar a una pelea en una ciudad

    bool hayGuardian = false;
    if (arbol == NULL)
    {
        cout << "El arbol esta vacio..." << endl;
        return hayGuardian;
    }

    queue<arbolMaestro*> cola;
    cola.push(arbol);

    while (!cola.empty()) 
    {
        arbolMaestro* nodoActual = cola.front();
        cola.pop();

        if (nodoActual->guardian->nombre != guardian->guardian->nombre)
        {
            if (nodoActual->guardian->ciudad == guardian->guardian->ciudad)
            {
                cout << "- " << nodoActual->guardian->nombre << endl;
                hayGuardian = true;
            }
        }
        for (arbolMaestro* hijo : nodoActual->aprendices) 
        {
            cola.push(hijo);
        }
    }

    cout << endl;
    return hayGuardian;
}

// GRAFO
class GrafoLista
{
    int vertices;
    vector<vector<Ciudad>> listaAdy;
    vector<Ciudad> ciudades;
public:
    GrafoLista(int n) : vertices(n)
    {
        listaAdy.resize(vertices);
    }
    void setNames(vector<string> &nombres)
    {
        // Funcion para guardar los nombres de las ciudades despues de haberlas leido desde el archivo
        for (int i = 0; i < vertices; i++)
        {
            Ciudad nuevaCiudad;
            nuevaCiudad.nombre = nombres[i];
            ciudades.push_back(nuevaCiudad);
        }
    }
    void agregarArista(string origen, string destino)
    {
        // Funcion para agregar un camino entre 2 ciudades
        Ciudad ciudadInicio, ciudadDestino;
        int inicio = 0, fin= 0;
        for (size_t i = 0; i < ciudades.size(); i++)
        {
            if (origen == ciudades[i].nombre)
            {
                ciudadInicio = ciudades[i];
                inicio = i;
            }
        }
        for (size_t i = 0; i < ciudades.size(); i++)
        {
            if (destino == ciudades[i].nombre)
            {
                ciudadDestino = ciudades[i];
                fin = i;
            }
        }
        listaAdy[fin].push_back(ciudadInicio);
        listaAdy[inicio].push_back(ciudadDestino);
    }
    void mostrarCiudad(string nombre, arbolMaestro *arbol)
    {
        // Funcion para mostrar a una ciudad en especifico y a sus guardianes
        system("cls");
        for (int i = 0; i < vertices; ++i)
        {
            if (ciudades[i].nombre == nombre)
            {
                cout << "Nombre de la ciudad: " << ciudades[i].nombre << endl;
                cout << "Guardianes:\n";
                mostrarGuardianesdelaCiudad(arbol, nombre);
                cout << "\nCiudades conectadas:\n";
                for (const Ciudad& arista : listaAdy[i])
                {
                    cout << "- " << arista.nombre << "\n";
                }
            }
        }
    }
    void mostrarCiudadesConectadas(string nombre)
    {
        // Funcion para imprimir las ciudades que se encuentran conectadas a una ciudad en especifico
        for (int i = 0; i < vertices; ++i)
        {
            if (ciudades[i].nombre == nombre)
            {
                cout << "\nCiudades conectadas a " << nombre << ": \n";
                for (const Ciudad& arista : listaAdy[i])
                {
                    cout << "- " << arista.nombre << "\n";
                }
            }
        }
    }
    void mostrarGrafo() 
    {
        // Se imprimen solo los nombres de las ciudades
        cout << "Ciudades:\n";
        for (const Ciudad& arista : ciudades)
        {
            cout << arista.nombre << "\n";
        }
    }
    void mostrarGrafoCompleto()
    {
        // Se muestran las ciudades y tambien las ciudades conectadas a ellas
        for (int i = 0; i < vertices; ++i)
        {
            for (const Ciudad& arista : listaAdy[i])
            {
                cout << ciudades[i].nombre <<" -> " << arista.nombre << "\n";
            }
            cout << endl;
        }
    }
    bool validarCiudad(string ciudad)
    {
        // Se valida si una ciudad existe
        for (const Ciudad& arista : ciudades)
        {
            if (arista.nombre == ciudad)
            {
                return true;
            }
        }
        return false;
    }
    bool encontrarCamino(string origen, string destino)
    {
        for (int i = 0; i < vertices; ++i)
        {
            if (ciudades[i].nombre == origen)
            {
                for (const Ciudad& arista : listaAdy[i])
                {
                    if (arista.nombre == destino)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

// FUNCIONES
vector<string> leerCiudades()
{
    // Se abre el archivo y luego se lee y se guardan los nombres de las
    // ciudades en un vector de string, ademas de evitar los nombres repetidos.
    vector<string> nombres;
    int repetido = 0;

    ifstream file("C:/Users/acer/Desktop/Proyecto2/Proyecto2/cities.conf");

    if (file.is_open())
    {
        string line;
        while (getline(file, line)) 
        {
            repetido = 0;
            // Crear un stringstream para facilitar la separación
            istringstream ss(line);

            string antesComa, despuesComa;

            // Leer hasta la coma
            if (getline(ss, antesComa, ','))
            {
                if (nombres.empty())
                {

                    nombres.push_back(antesComa);
                }
                else 
                {
                    for (int i = nombres.size() - 1; i >= 0; i--) 
                    {
                        if (antesComa == nombres[i])
                        {
                            repetido++;
                        }
                    }
                    if (repetido == 0)
                    {
                        nombres.push_back(antesComa);
                    }
                }
                
                // Leer después de la coma
                getline(ss, despuesComa);
                repetido = 0;
                // Procesar o mostrar la información según sea necesario
                for (int i = nombres.size() - 1; i >= 0; i--)
                {
                    if (despuesComa == nombres[i])
                    {
                        repetido++;
                    }
                }
                if (repetido == 0)
                {
                    nombres.push_back(despuesComa);
                }
            }
            else 
            {
                cerr << "Error al leer la línea: " << line << endl;
            }
        }
        file.close();
    }
    else 
    {
        cerr << "No se pudo abrir el archivo" << endl;
    }
    return nombres;
}
void leerConexiones(GrafoLista &grafo)
{
    // Se lee el archivo nuevamente, esta vez se llama a una funcion del grafo para poder
    // agregar las aristas
    ifstream archivo("C:/Users/acer/Desktop/Proyecto2/Proyecto2/cities.conf");

    if (archivo.is_open())
    {
        string linea;
        while (getline(archivo, linea))
        {
            istringstream ss(linea);

            string antesComa, despuesComa;

            if (getline(ss, antesComa, ','))
            {
                getline(ss, despuesComa);
            }
            else
            {
                cerr << "Error al leer la línea: " << linea << endl;
            }
            grafo.agregarArista(antesComa, despuesComa);
        }
        archivo.close();
    }
    else
    {
        cerr << "No se pudo abrir el archivo" << endl;
    }
}

// Funciones relacionadas con los arboles
arbolMaestro* crearNodoMaestro(Guardian* n)
{
    // Funcion que permite instanciar al nodo del arbol de jerarquia
    arbolMaestro* nuevo_nodo = new arbolMaestro;

    nuevo_nodo->guardian = n;

    return nuevo_nodo;
}
void insertarMaestrosEnArbol(arbolMaestro*& arbol, Guardian* guardian)
{
    // Esta funcion permite insertar los guardianes en el arbol de jerarquia
    // mediante el uso de una cola
    if (arbol == NULL)
    {
        arbolMaestro* nuevo_nodo = crearNodoMaestro(guardian);
        arbol = nuevo_nodo;
    }
    else
    {
        queue<arbolMaestro*> q;
        q.push(arbol);
        while (!q.empty())
        {
            arbolMaestro* actual = q.front();
            q.pop();
            if (actual->guardian->nombre == guardian->maestro) {
                arbolMaestro* nuevo_nodo = crearNodoMaestro(guardian);
                actual->aprendices.push_back(nuevo_nodo);
                break;
            }
            for (arbolMaestro* hijo : actual->aprendices)
            {
                q.push(hijo);
            }
        }
    }
}
void leerGuardianes(arbolRanking *&raiz, arbolMaestro *&raizmaestros, GrafoLista* grafo)
{
    // Se leen los guardianes desde el archivo donde inmediatamente se insertan en los arboles de jerarquia y de ranking

    ifstream archivo("C:/Users/acer/Desktop/Proyecto2/Proyecto2/guardians.conf");
    vector<Guardian*> guardianes;
    int aviso100=0, aviso390=0, i = 1;

    if (archivo.is_open())
    {
        string linea;

        while (getline(archivo, linea)) {
            istringstream ss(linea);
            string token;

            Guardian* nuevoguardian = new Guardian;

            getline(ss, nuevoguardian->nombre, ',');
            getline(ss, token, ',');
            nuevoguardian->poder = stoi(token);
            getline(ss, nuevoguardian->maestro, ',');
            getline(ss, nuevoguardian->ciudad, ',');
            if (nuevoguardian->poder == 100)
            {
                aviso100++;
            }
            if (nuevoguardian->poder >= 90)
            {
                aviso390++;
            }
            if (grafo->validarCiudad(nuevoguardian->ciudad))
            {
                insertarNodo(raiz, nuevoguardian);
                guardianes.push_back(nuevoguardian);
            }
            else
            {
                cout << "Error en la lectura de archivo, la ciudad: " << nuevoguardian->ciudad << " no existe...\n";
                delete nuevoguardian;
                system("pause");
                exit(1);
            }
        }
        archivo.close();
    }
    else
    {
        cerr << "No se pudo abrir el archivo" << endl;
        system("pause");
    }
    if (aviso100 > 1 || aviso100 < 1 || aviso390 > 4 || aviso390 < 4)
    {
        cout << "Error, los niveles de poder de los guardianes son incorrectos..." << endl;
        system("pause");
        exit(1);
    }
    for (size_t i = 0; i < guardianes.size(); i++)
    {
        insertarMaestrosEnArbol(raizmaestros, guardianes[i]);
    }
}
void mostrarArbolMaestros(arbolMaestro* arbol, int valor = 0)
{
    // Se imprime el arbol de jeraquia, mostrando el nombre del guardian y sus aprendices si es que tiene
    if (arbol == NULL) {
        return;
    }
    cout << string(valor, ' ') << arbol->guardian->nombre << endl;
    for (size_t i = 0; i < arbol->aprendices.size(); i++) 
    {
        mostrarArbolMaestros(arbol->aprendices[i], valor + 4);
    }
}
arbolMaestro* buscar(arbolMaestro* arbol, string indice) 
{
    // Se busca un guardian dentro del arbol de jerarquia usando su nombre

    if (arbol == NULL) 
    {
        return NULL;
    }

    queue<arbolMaestro*> cola;
    cola.push(arbol);

    while (!cola.empty()) 
    {
        arbolMaestro* actual = cola.front();
        cola.pop();

        if (actual->guardian->nombre == indice) 
        {
            return actual;
        }

        for (arbolMaestro* hijo : actual->aprendices) 
        {
            cola.push(hijo);
        }
    }

    return NULL;
}
bool resultadoPelea()
{
    // Se genera un numero aleatorio del 1 al 6, representando un dado, si se obtiene 5 o 6
    // el guardian ganará
    bool victoria = true;
    int num = 1 + rand() % (7 - 1);
    if (num == 5 || num == 6)
    {
        victoria = true;
    }
    else
    {
        victoria = false;
    }
    return victoria;
}
arbolRanking* encontrarNodoMinimo(arbolRanking* nodo) 
{
    // Se encuentra el nodo con el valor más pequeño posible dentro del arbol binario, es decir, el nodo que
    // se ubica lo más a la izquierda posible

    while (nodo->izq != NULL) 
    {
        nodo = nodo->izq;
    }
    return nodo;
}
arbolRanking* eliminarNodo(arbolRanking* raiz, int valor, string nombre) 
{
    // En esta funcion se encuentra al nodo que se desea eliminar dentro del arbol de ranking,
    // usando su nombre y nivel de poder para encontrarlo

    if (raiz == NULL) 
    {
        return raiz;
    }

    if (valor < raiz->guardian->poder)
    {
        raiz->izq = eliminarNodo(raiz->izq, valor, nombre);
    }
    else if (valor > raiz->guardian->poder) 
    {
        raiz->der = eliminarNodo(raiz->der, valor, nombre);
    }
    else 
    {
        if (raiz->izq == NULL && raiz->guardian->nombre == nombre)
        {
            arbolRanking* temp = raiz->der;
            delete raiz;
            return temp;
        }
        else if (raiz->der == NULL && raiz->guardian->nombre == nombre)
        {
            arbolRanking* temp = raiz->izq;
            delete raiz;
            return temp;
        }

        if (raiz->guardian->nombre == nombre)
        {
            arbolRanking* temp = encontrarNodoMinimo(raiz->der);
            raiz->guardian = temp->guardian;
            raiz->der = eliminarNodo(raiz->der, temp->guardian->poder, nombre);
        }
        
    }

    return raiz;
}

int main()
{
    srand((unsigned int)time(NULL));
    bool ciclo1 = true, ciclo2 = true, aux = false, resultado = true;
    int opcion = 0, opcion2 = 0, max = 0;
    arbolRanking* raizRank = NULL;
    arbolMaestro* raizMaestros = NULL;
    int indice = 0;
    string linea, linea2;
    arbolMaestro* jugador = NULL;
    arbolMaestro* enemigo = NULL;
    arbolMaestro* maestroJugador = NULL;
    arbolMaestro* maestroEnemigo = NULL;
    vector<string> nombres = leerCiudades();
    GrafoLista grafo(nombres.size());
    grafo.setNames(nombres);
    leerConexiones(grafo);
    leerGuardianes(raizRank, raizMaestros, &grafo);

    // MENU PRINCIPAL
    do
    {
        system("cls");
        cout << "/////         THE GUARDIANS BATTLE         /////" << endl;
        cout << "\n1. Ver lista de candidatos.\n2. Ver al guardian.\n3. Conocer el reino.\n4. Presenciar una batalla.\n5. Salir.\nEleccion: ";
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
        case 1:
            system("cls");
            mostrarCandidatos(raizRank, 0);
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            mostrarArbol(raizRank, 0);
            cout << endl << "Escriba el nombre exacto del guardian para ver sus detalles: ";
            getline(cin, linea);
            cin.ignore();
            jugador = buscar(raizMaestros, linea);
            if (jugador == NULL)
            {
                cout << "\nEl guardian ingresado no se encuentra, intentelo nuevamente...\n";
                system("pause");
            }
            else
            {
                cout << "\nNombre: " << jugador->guardian->nombre;
                cout << "\nNivel de poder: " << jugador->guardian->poder;
                cout << "\nCiudad: " << jugador->guardian->ciudad;
                cout << "\nMaestro: " << jugador->guardian->maestro;
                cout << "\nAprendices: \n";
                for (size_t i = 0; i < jugador->aprendices.size(); i++)
                {
                    cout << "- " << jugador->aprendices[i]->guardian->nombre << endl;
                }
            }
            cout << endl;
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
            grafo.mostrarGrafo();
            cout << "\nQue desea hacer?: ";
            cout << "\n1. Visitar una ciudad";
            cout << "\n2. Añadir camino";
            cout << "\n3. Ver conexiones entre ciudades\n";
            cin >> opcion2;
            cin.ignore();
            if (opcion2 == 1)
            {
                cout << "\nEscriba el nombre de la ciudad que desea visitar: ";
                getline(cin, linea);
                cin.ignore();
                grafo.mostrarCiudad(linea, raizMaestros);
                cout << endl;
                system("pause");
            }
            else if (opcion2 == 2)
            {
                cout << "\nEscriba el nombre de la ciudad de origen: ";
                getline(cin, linea);
                cin.ignore();
                cout << "\nEscriba el nombre de la ciudad de destino: ";
                getline(cin, linea2);
                cin.ignore();
                grafo.agregarArista(linea, linea2);
                cout << endl;
                system("pause");
            }
            else if (opcion2 == 3)
            {
                system("cls");
                grafo.mostrarGrafoCompleto();
                cout << endl;
                system("pause");
            }
            else
            {
                cout << "Opcion invalida...\n";
                system("pause");
            }
            system("cls");
            break;
        case 4:
            system("cls");
            mostrarArbolsologuardianesJugables(raizRank, 0);
            cout << "\nSeleccione el guardian ingresando su nombre exacto: ";
            getline(cin, linea);
            jugador = buscar(raizMaestros, linea);
            if (jugador != NULL)
            {
                do
                {
                    system("cls");
                    cout << "------- Guardian seleccionado -------\n";
                    cout << "\nNombre: " << jugador->guardian->nombre;
                    cout << "\nNivel de poder: " << jugador->guardian->poder;
                    cout << "\nCiudad actual: " << jugador->guardian->ciudad;
                    cout << "\nMaestro: " << jugador->guardian->maestro;

                    cout << "\nQue accion desea realizar?: \n";
                    cout << "1. Luchar\n";
                    cout << "2. Viajar\n";
                    cin >> opcion2;
                    cin.ignore();
                    if (opcion2 == 1)
                    {
                        cout << "\nGuardianes dentro de la ciudad: \n";
                        aux = mostrarGuardianesdelaCiudadPelea(raizMaestros, jugador);
                        cout << endl;
                        if (aux == true)
                        {
                            cout << "\nIngrese el nombre del guardian con el que desea pelear: ";
                            getline(cin, linea);
                            cin.ignore();
                            enemigo = buscar(raizMaestros, linea);
                            if (enemigo != NULL && enemigo->guardian->poder < 90)
                            {
                                system("cls");
                                cout << "\nResultado de la pelea:\n";
                                resultado = resultadoPelea();
                                if (resultado == true)
                                {
                                    cout << "Has ganado!!!\n";
                                    
                                    if (enemigo->aprendices.empty() == false)
                                    {
                                        raizRank = eliminarNodo(raizRank, jugador->guardian->poder, jugador->guardian->nombre);
                                        jugador->guardian->poder += 5;
                                        arbolRanking* nuevo_nodo = new arbolRanking;
                                        nuevo_nodo->guardian = jugador->guardian;
                                        insertarNodo(raizRank, nuevo_nodo->guardian);
                                        maestroJugador = buscar(raizMaestros, jugador->guardian->maestro);
                                        maestroEnemigo = buscar(raizMaestros, enemigo->guardian->maestro);
                                    }
                                    else 
                                    {
                                        raizRank = eliminarNodo(raizRank, jugador->guardian->poder, jugador->guardian->nombre);
                                        jugador->guardian->poder += 3;
                                        arbolRanking* nuevo_nodo = new arbolRanking;
                                        nuevo_nodo->guardian = jugador->guardian;
                                        insertarNodo(raizRank, nuevo_nodo->guardian);
                                    }
                                    raizRank = eliminarNodo(raizRank, enemigo->guardian->poder, enemigo->guardian->nombre);
                                    arbolRanking* nuevo_nodoEnemigo = new arbolRanking;
                                    nuevo_nodoEnemigo->guardian = enemigo->guardian;
                                    enemigo->guardian->poder -= 1;
                                    insertarNodo(raizRank, nuevo_nodoEnemigo->guardian);
                                    ciclo2 = false;
                                }
                                else
                                {
                                    cout << "Has perdido...\n";
                                    if (jugador->aprendices.empty() == false)
                                    {
                                        raizRank = eliminarNodo(raizRank, enemigo->guardian->poder, enemigo->guardian->nombre);
                                        arbolRanking* nuevo_nodoEnemigo = new arbolRanking;
                                        nuevo_nodoEnemigo->guardian = enemigo->guardian;
                                        enemigo->guardian->poder += 5;
                                        insertarNodo(raizRank, nuevo_nodoEnemigo->guardian);
                                    }
                                    else
                                    {
                                        raizRank = eliminarNodo(raizRank, enemigo->guardian->poder, enemigo->guardian->nombre);
                                        arbolRanking* nuevo_nodoEnemigo = new arbolRanking;
                                        nuevo_nodoEnemigo->guardian = enemigo->guardian;
                                        enemigo->guardian->poder += 3;
                                        insertarNodo(raizRank, nuevo_nodoEnemigo->guardian);
                                    }
                                    raizRank = eliminarNodo(raizRank, jugador->guardian->poder, jugador->guardian->nombre);
                                    arbolRanking* nuevo_nodo = new arbolRanking;
                                    nuevo_nodo->guardian = jugador->guardian;
                                    jugador->guardian->poder -= 1;
                                    insertarNodo(raizRank, nuevo_nodo->guardian);
                                    ciclo2 = false;
                                }
                            }
                            else if (enemigo == NULL)
                            {
                                cout << "El nombre ingresado es invalido...\n";
                            }
                            else
                            {
                                cout << "No puedes enfrentarte a los guardianes del reino.\n";
                            }
                        }
                        else
                        {
                            cout << "No hay guardianes en esta ciudad...\n";
                        }

                        system("pause");
                    }
                    else if (opcion2 == 2)
                    {
                        grafo.mostrarCiudadesConectadas(jugador->guardian->ciudad);
                        cout << "\nIngrese el nombre exacto de la ciudad a la que desea viajar: ";
                        getline(cin, linea);
                        cin.ignore();
                        if (grafo.validarCiudad(linea))
                        {
                            jugador->guardian->ciudad = linea;
                        }
                        else
                        {
                            cout << "Nombre de la ciudad es incorrecto...\n";
                        }

                        cout << endl;
                        system("pause");
                    }
                    else
                    {
                        cout << "Opcion invalida...\n";
                        system("pause");
                    }

                } while (ciclo2);
            }
            else
            {
                cout << "\nEl guardian no fue encontrado...\n";
            }
            system("pause");
            break;
        case 5:
            system("cls");
            delete raizMaestros;
            delete raizRank;
            exit(1);
            break;
        default:
            system("cls");
            cout << "Opcion invalida...\n";
            system("pause");
            break;
        }
    } while (ciclo1 == 1);
    return 0;
}
