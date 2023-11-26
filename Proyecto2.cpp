#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Guardian 
{
    char nombre[50];
    int poder;
    string ciudad;
    string maestro;
    vector<Guardian*> hijos;

};

struct Ciudad
{
    string nombre;
};

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
    ifstream file("C:/Users/acer/Desktop/Proyecto2/Proyecto2/cities.txt");

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            // Crear un stringstream para facilitar la separación
            istringstream ss(line);

            string antesComa, despuesComa;

            // Leer hasta la coma
            if (getline(ss, antesComa, ','))
            {
                // Leer después de la coma
                getline(ss, despuesComa);
            }
            else
            {
                cerr << "Error al leer la línea: " << line << endl;
            }
            grafo.agregarArista(antesComa, despuesComa);
        }
        file.close();
    }
    else
    {
        cerr << "No se pudo abrir el archivo: " << "Cities.txt" << endl;
    }
}

int main()
{
    vector<string> nombres = leerCiudades();
    GrafoLista grafo(nombres.size());
    grafo.setNames(nombres);
    leerConexiones(grafo);
    grafo.mostrarGrafo();
    return 0;
}
