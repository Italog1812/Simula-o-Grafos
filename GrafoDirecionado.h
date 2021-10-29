#include <iostream>
#include <list>

// bliblioteca para Grafos direcionados

using namespace std;

class GrafoDirecionado
{

    int numero_de_vertices;                       // número de vértices
    list<CelulaGrafo> *vetor_lista_de_adjacencia; // ponteiro para um array contendo as listas de adjacências

public:
    GrafoDirecionado();
    GrafoDirecionado(int numero_de_vertices);                                  // construtor
    bool AdicionarAresta(int primeiro_vertice, int segundo_vertice, int peso); // adiciona uma aresta no grafo
    bool AdicionarAresta(int primeiro_vertice, int segundo_vertice);
    bool ExisteRepeticao(int primeiro_vertice, int segundo_vertice);
    void ImprimirGrafo();
};

GrafoDirecionado::GrafoDirecionado()
{
}

GrafoDirecionado::GrafoDirecionado(int numero_de_vertices)
{

    this->numero_de_vertices = numero_de_vertices;                         // atribui o número de vértices
    vetor_lista_de_adjacencia = new list<CelulaGrafo>[numero_de_vertices]; // cria as listas
}

bool GrafoDirecionado::ExisteRepeticao(int primeiro_vertice, int segundo_vertice)
{

    list<CelulaGrafo> lista = vetor_lista_de_adjacencia[primeiro_vertice];
    while (!lista.empty())
    {
        if (lista.front().getId() == segundo_vertice)
        {
            cout << "aresta ja existe";
            return true;
        }
        lista.pop_front();
    }
    return false;
}

bool GrafoDirecionado::AdicionarAresta(int primeiro_vertice, int segundo_vertice, int peso)
{

    if (primeiro_vertice < 0 || primeiro_vertice >= numero_de_vertices || segundo_vertice < 0 || segundo_vertice >= numero_de_vertices)
    {
        cout << "vertice invalido";
        return false;
    }
    else if (ExisteRepeticao(primeiro_vertice, segundo_vertice))
    {
        return false;
    }
    else if (peso < 0)
    {
        return false;
    }
    vetor_lista_de_adjacencia[primeiro_vertice].push_back(CelulaGrafo(segundo_vertice, peso));
    return true;
}

bool GrafoDirecionado::AdicionarAresta(int primeiro_vertice, int segundo_vertice)
{

    if (primeiro_vertice < 0 || primeiro_vertice >= numero_de_vertices || segundo_vertice < 0 || segundo_vertice >= numero_de_vertices)
    {
        cout << "vertice invalido";
        return false;
    }
    else if (ExisteRepeticao(primeiro_vertice, segundo_vertice))
    {
        return false;
    }
    vetor_lista_de_adjacencia[primeiro_vertice].push_back(CelulaGrafo(segundo_vertice, -1));
    return true;
}

void GrafoDirecionado::ImprimirGrafo()
{

    for (int i = 0; i < numero_de_vertices; i++)
    {
        cout << "\n(" << i << ") | ";
        list<CelulaGrafo> lista = vetor_lista_de_adjacencia[i];
        while (!lista.empty())
        {
            cout << "[id:" << lista.front().getId();
            if (lista.front().getPeso() != -1)
            {
                cout << " peso:" << lista.front().getPeso();
            }
            cout << "]->";
            lista.pop_front();
        }
    }
}