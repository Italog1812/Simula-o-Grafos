#include <iostream>
#include <list>
// bliblioteca para Grafos Nao direcionados

using namespace std;

class GrafoNaoDirecionado
{

    int numero_de_vertices; // número de vértices
    int numero_de_ciclos;
    list<CelulaGrafo> *vetor_lista_de_adjacencia; // ponteiro para um array contendo as listas de adjacências

public:
    GrafoNaoDirecionado();
    GrafoNaoDirecionado(int numero_de_vertices);                               // construtor
    bool AdicionarAresta(int primeiro_vertice, int segundo_vertice, int peso); // adiciona uma aresta no grafo
    bool AdicionarAresta(int primeiro_vertice, int segundo_vertice);
    bool ExisteRepeticao(int primeiro_vertice, int segundo_vertice);
    void ComparaListaAdjacencia(int vetor[], int Tam);
    void EnumeraCiclosPorCaminhamento();
    int get_NumeroDeCiclos();
    void AdicionaCiclo();
    void BuscaEmProfundidade(int *vertices_visitados, int vertice, int *cont, list<int> *lista);
    void ImprimirGrafo();
};

GrafoNaoDirecionado::GrafoNaoDirecionado()
{
    numero_de_vertices = 0;
    numero_de_ciclos = 0;
    vetor_lista_de_adjacencia = NULL;
}

GrafoNaoDirecionado::GrafoNaoDirecionado(int numero_de_vertices)
{

    this->numero_de_vertices = numero_de_vertices; // atribui o número de vértices
    numero_de_ciclos = 0;
    vetor_lista_de_adjacencia = new list<CelulaGrafo>[numero_de_vertices]; // cria as listas
}

bool GrafoNaoDirecionado::ExisteRepeticao(int primeiro_vertice, int segundo_vertice)
{

    list<CelulaGrafo> listaP = vetor_lista_de_adjacencia[primeiro_vertice];
    while (!listaP.empty())
    {
        if (listaP.front().getId() == segundo_vertice)
        {
            cout << "aresta ja existe";
            return true;
        }
        listaP.pop_front();
    }
    list<CelulaGrafo> listaS = vetor_lista_de_adjacencia[segundo_vertice];
    while (!listaS.empty())
    {
        if (listaS.front().getId() == primeiro_vertice)
        {
            cout << "aresta ja existe";
            return true;
        }
        listaS.pop_front();
    }
    return false;
}

bool GrafoNaoDirecionado::AdicionarAresta(int primeiro_vertice, int segundo_vertice, int peso)
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
    vetor_lista_de_adjacencia[segundo_vertice].push_back(CelulaGrafo(primeiro_vertice, peso));
    return true;
}

bool GrafoNaoDirecionado::AdicionarAresta(int primeiro_vertice, int segundo_vertice)
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
    vetor_lista_de_adjacencia[segundo_vertice].push_back(CelulaGrafo(primeiro_vertice, -1));
    return true;
}

void GrafoNaoDirecionado::ImprimirGrafo()
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

void GrafoNaoDirecionado ::ComparaListaAdjacencia(int vetor[], int Tam)
{
    bool Verifica = false;
    for (int i = 0; i < Tam; i++)
    {
        Verifica = false;
        list<CelulaGrafo> lista = vetor_lista_de_adjacencia[vetor[i]];
        if (i + 1 == Tam)
        {
            while (!lista.empty() && !Verifica)
            {
                //printf("%d --- %d\n", vetor[0], lista.front().getId());
                if (vetor[0] == lista.front().getId())
                {
                    Verifica = true;
                }
                else
                {
                    Verifica = false;
                }
                lista.pop_front();
            }
            if (!Verifica)
                return;
        }
        else
        {
            while (!lista.empty() && !Verifica)
            {
                //printf("%d --- %d\n", vetor[i + 1], lista.front().getId());
                if (vetor[i + 1] == lista.front().getId())
                {
                    Verifica = true;
                }
                else
                {
                    Verifica = false;
                }
                lista.pop_front();
            }
            if (!Verifica)
                return;
        }

        //printf("%d\n", Verifica);
    }
    for (int i = 0; i < Tam; i++)
        printf("%d ", vetor[i]);
    printf("%d \n", vetor[0]);
}
void GrafoNaoDirecionado::AdicionaCiclo()
{
    numero_de_ciclos++;
}

int GrafoNaoDirecionado::get_NumeroDeCiclos()
{
    return numero_de_ciclos;
}

void GrafoNaoDirecionado::BuscaEmProfundidade(int *vertices_visitados, int vertice, int *cont, list<int> *lista)
{

    *cont = *cont + 1;
    vertices_visitados[vertice] = *cont;
    list<CelulaGrafo>::iterator it;
    lista->push_back(vertice);

    for (it = vetor_lista_de_adjacencia[vertice].begin(); it != vetor_lista_de_adjacencia[vertice].end(); it++)
    {
        int vertice_atual = it->getId();

        if (vertices_visitados[vertice_atual] == -1)
        {

            BuscaEmProfundidade(vertices_visitados, vertice_atual, cont, lista);
        }
        else
        {

            lista->push_back(vertice_atual);
            list<int>::iterator i = lista->begin();

            if (lista->size() > 3)
            {

                if (vertice_atual == *i)
                {
                    AdicionaCiclo();

                    cout << "ciclo ";
                    while (i != lista->end())
                    {
                        cout << *i << " ";
                        i++;
                    }
                    cout << " \n";
                }
            }
            lista->pop_back();
        }
    }
    lista->pop_back();
}

void GrafoNaoDirecionado::EnumeraCiclosPorCaminhamento()
{

    int vertices_visitados[numero_de_vertices];
    list<int> lista;

    for (int i = 0; i < numero_de_vertices; i++)
    {

        for (int k = 0; k < numero_de_vertices; k++)
            vertices_visitados[k] = -1;

        int cont = 0;
        BuscaEmProfundidade(vertices_visitados, i, &cont, &lista);
        lista.clear();
    }

    cout << "\nNumero de Ciclos Encontrados por Caminhamento: " << get_NumeroDeCiclos();
    cout << "\n(Alguns ciclos se repetem pois leva-se em conta o vertice de origem e o caminhamento por busca em profundidade)\n";
}
void permutacaoHeap(GrafoNaoDirecionado Grafo_A, int a[], int size, int n)
{
    if (size == 1)
    {
        // for (int i = 0; i < n; i++)
        //printf("%d ", a[i]);
        //printf("\n");
        Grafo_A.ComparaListaAdjacencia(a, n);
        return;
    }

    for (int i = 0; i < size; i++)
    {
        permutacaoHeap(Grafo_A, a, size - 1, n);
        if (size % 2 == 1)
            swap(a[0], a[size - 1]);
        else
            swap(a[i], a[size - 1]);
    }
}

void Preenche(int a, int *vetor_preenchido)
{
    for (int i = 0; i < a; i++)
    {
        vetor_preenchido[i] = i;
    }
}