#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>

using namespace std;

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
arbolRanking* crearNodo(Guardian* n)
{
    arbolRanking* nuevo_nodo = new arbolRanking;

    nuevo_nodo->guardian = n;
    nuevo_nodo->der = NULL;
    nuevo_nodo->izq = NULL;

    return nuevo_nodo;
}
void insertarNodo(arbolRanking *&arbol, Guardian* guardian)
{
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
            cout << "Nivel de poder: " << arbol->guardian->poder << endl;
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
    if (arbol == NULL)
    {
        return;
    }
    else
    {
        mostrarArbol(arbol->der, contador + 1);
        if (arbol->guardian->poder < 90)
        {
            cout << "Nombre: " << arbol->guardian->nombre << endl;
            cout << "Nivel de poder: " << arbol->guardian->poder << endl << endl;
        }
        mostrarArbol(arbol->izq, contador + 1);
    }
}
void mostrarCandidatos(arbolRanking* arbol, int contador)
{
    if (arbol == NULL)
    {
        return;
    }
    else
    {
        mostrarArbol(arbol->der, contador + 1);
        if (arbol->guardian->poder > 90)
        {
            cout << "Nombre: " << arbol->guardian->nombre << endl;
            cout << "Nivel de poder: " << arbol->guardian->poder << endl;
        }
        mostrarArbol(arbol->izq, contador + 1);
    }
}
void mostrarGuardianesdelaCiudad(arbolMaestro* arbol, string ciudad)
{
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
        for (int i = 0; i < vertices; i++)
        {
            Ciudad nuevaCiudad;
            nuevaCiudad.nombre = nombres[i];
            ciudades.push_back(nuevaCiudad);
        }
    }
    void agregarArista(string origen, string destino)
    {
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
        cout << "Ciudades:\n";
        for (const Ciudad& arista : ciudades)
        {
            cout << arista.nombre << "\n";
        }
    }
    void mostrarGrafoCompleto()
    {
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
vector<string> leerCiudades()
{
    vector<string> nombres;
    int repetido = 0;

    ifstream file("C:/Users/acer/Desktop/Proyecto2/Proyecto2/cities.txt");

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
        cerr << "No se pudo abrir el archivo: " << "Cities.txt" << endl;
    }
    return nombres;
}
void leerConexiones(GrafoLista &grafo)
{
    ifstream archivo("C:/Users/acer/Desktop/Proyecto2/Proyecto2/cities.txt");

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
        cerr << "No se pudo abrir el archivo: " << "Cities.txt" << endl;
    }
}
arbolMaestro* crearNodoMaestro(Guardian* n)
{
    arbolMaestro* nuevo_nodo = new arbolMaestro;

    nuevo_nodo->guardian = n;

    return nuevo_nodo;
}
void insertarMaestrosEnArbol(arbolMaestro*& arbol, Guardian* guardian)
{
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
    ifstream archivo("C:/Users/acer/Desktop/Proyecto2/Proyecto2/guardians.txt");
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

int main()
{
    bool ciclo1 = true, ciclo2 = true, aux = false;
    int opcion = 0, opcion2 = 0;
    arbolRanking* raizRank = NULL;
    arbolMaestro* raizMaestros = NULL;
    int indice = 0;
    string linea, linea2;
    arbolMaestro* jugador = NULL;
    arbolMaestro* enemigo = NULL;
    vector<string> nombres = leerCiudades();
    GrafoLista grafo(nombres.size());
    grafo.setNames(nombres);
    leerConexiones(grafo);
    leerGuardianes(raizRank, raizMaestros, &grafo);

    do
    {
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
            cout << "\n2. Añadir camino ";
            cout << "\n3. Ver conexiones entre ciudades: \n";
            cin >> opcion2;
            cin.ignore();
            if (opcion2 == 1)
            {
                cout << "\nEscriba el nombre de la ciudad que desea visitar: ";
                getline(cin, linea);
                grafo.mostrarCiudad(linea, raizMaestros);
                cout << endl;
                system("pause");
            }
            else if (opcion2 == 2)
            {
                cout << "\nEscriba el nombre de la ciudad de origen: ";
                getline(cin, linea);
                cout << "\nEscriba el nombre de la ciudad de destino: ";
                getline(cin, linea2);
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
                        cout << "\nGuardianes dentro de la ciudad: ";
                        aux = mostrarGuardianesdelaCiudadPelea(raizMaestros, jugador);
                        cout << endl;
                        if (aux == true)
                        {
                            cout << "\nIngrese el nombre del guardian con el que desea pelear: ";
                            getline(cin, linea);
                            enemigo = buscar(raizMaestros, linea);
                            if (enemigo != NULL)
                            {

                            }
                            else
                            {
                                cout << "El nombre ingresado es invalido...";
                                system("pause");
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
