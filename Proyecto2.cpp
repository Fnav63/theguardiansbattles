#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Guardian 
{
    string nombre;
    int poder = 0;
    string ciudad;
    string maestro;
    vector<Guardian> hijos;
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
        for (int i = 0; i < contador; i++)
        {
            cout << "   ";
        }
        cout << arbol->guardian->poder << endl;
        mostrarArbol(arbol->izq, contador + 1);
    }
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
        for (int i = 0; i < ciudades.size(); i++)
        {
            if (origen == ciudades[i].nombre)
            {
                ciudadInicio = ciudades[i];
                inicio = i;
            }
        }
        for (int i = 0; i < ciudades.size(); i++)
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
    void mostrarGrafo()
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
void leerGuardianes(arbolRanking *&raiz)
{
    ifstream archivo("C:/Users/acer/Desktop/Proyecto2/Proyecto2/guardians.txt");
    vector<Guardian*> guardianes;

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

            guardianes.push_back(nuevoguardian);
        }
        archivo.close();
    }
    else
    {
        cerr << "No se pudo abrir el archivo: " << "Cities.txt" << endl;
    }
    for (int i = 0; i < guardianes.size(); i++)
    {
        insertarNodo(raiz, guardianes[i]);
    }
}

int main()
{
    arbolRanking *raiz = NULL;
    vector<string> nombres = leerCiudades();
    GrafoLista grafo(nombres.size());
    grafo.setNames(nombres);
    leerConexiones(grafo);
    //grafo.mostrarGrafo();
    leerGuardianes(raiz);
    mostrarArbol(raiz, 0);
    return 0;
}
