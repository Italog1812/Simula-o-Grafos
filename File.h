#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "CelulaGrafo.h"
#include "GrafoDirecionado.h"
#include "GrafoNaoDirecionado.h"

struct Valor
{
    int primeiro_vertice[100];
    int segundo_vertice[100];
    int peso[100];
};

void Add(GrafoDirecionado Grafo1, GrafoNaoDirecionado Grafo2, int Id1, int Id2, int primeiro_vertice, int segundo_vertice, int peso)
{
    if (Id1 == 1)
    {
        if (Id2 == 1)
        {
            Grafo1.AdicionarAresta(primeiro_vertice, segundo_vertice, peso);
        }
        else
        {
            Grafo1.AdicionarAresta(primeiro_vertice, segundo_vertice);
        }
    }
    else
    {
        if (Id2 == 1)
        {
            Grafo2.AdicionarAresta(primeiro_vertice, segundo_vertice, peso);
        }
        else
        {
            Grafo2.AdicionarAresta(primeiro_vertice, segundo_vertice);
        }
    }
}

void ReadFile(FILE *archive, char *NameFile, char *Result)
{
    GrafoDirecionado Grafo1;
    GrafoNaoDirecionado Grafo2;
    char Conversor1[100];
    char Conversor2[100];
    int controla_conversao;
    char line[100];
    int i = 1;
    int Id1;
    int Id2;
    int Num_vertices;
    int posicao;
    Valor Valores;
    int Controla_Valores = 0;
    int Controla_Pesos = 0;
    archive = fopen(NameFile, "rt");

    if (archive == NULL)
    {
        printf("Arquivo nao encontrado.\n");
        return;
    }

    while (!feof(archive))
    {
        Result = fgets(line, 100, archive);
        if (i == 1)
        {
            //Ver se o grafo é direcionado ou não
            Id1 = atoi(Result);
            if (Id1 == 1)
            {
                printf("Grafo direcionado ");
            }
            else
            {
                printf("Grafo nao-direcionado ");
            }
        }
        if (i == 2)
        {
            //Ver se o grafo é ponderado ou não
            Id2 = atoi(Result);
            if (Id2 == 1)
            {
                printf("ponderado \n");
            }
            else
            {
                printf("nao-ponderado \n");
            }
        }
        if (i == 3)
        {
            //Quantidade de vertices
            Num_vertices = atoi(Result);
            if (Id1 == 1)
            {
                Grafo1 = GrafoDirecionado(Num_vertices);
            }
            else
            {
                Grafo2 = GrafoNaoDirecionado(Num_vertices);
            }
        }
        if (Result[0] == '{')
        {
            controla_conversao = 1;
            posicao = 0;
            std::fill_n(Conversor1, 100, 0);
            std::fill_n(Conversor2, 100, 0);
            while (Result[controla_conversao] != ',')
            {
                Conversor1[posicao] = Result[controla_conversao];
                controla_conversao++;
                posicao++;
            }
            posicao = 0;
            controla_conversao++;
            while (Result[controla_conversao] != '}')
            {
                Conversor2[posicao] = Result[controla_conversao];
                controla_conversao++;
                posicao++;
            }
            Valores.primeiro_vertice[Controla_Valores] = atoi(Conversor1);
            Valores.segundo_vertice[Controla_Valores] = atoi(Conversor2);
            Controla_Valores++;
        }

        if (Result[0] != '{' && i > 4 && Id2 == 1)
        {
            Valores.peso[Controla_Pesos] = atoi(Result);
        }
        i++;
    }
    fclose(archive);
    for (int a = 0; a <= Controla_Valores; a++)
    {
        Add(Grafo1, Grafo2, Id1, Id2, Valores.primeiro_vertice[a], Valores.segundo_vertice[a], Valores.peso[a]);
    }
    if (Id1 == 1)
    {
        Grafo1.ImprimirGrafo();
    }
    else
    {
        Grafo2.ImprimirGrafo();
        printf("\n----------- \n");
        printf("Ciclos pelo Caminhamento: \n");
        clock_t Ticks[2];
        Ticks[0] = clock();
        Grafo2.EnumeraCiclosPorCaminhamento();
        Ticks[1] = clock();
        double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
        printf("Tempo gasto: %g ms.", Tempo);
        Ticks[0] = clock();
        printf("\n----------- \n");
        printf("Ciclos pela Permutacao: \n");
        int *vetor;
        vetor = (int *)malloc(Num_vertices * sizeof(int));
        Preenche(Num_vertices, vetor);
        int cont = 3;
        while (cont <= Num_vertices)
        {
            permutacaoHeap(Grafo2, vetor, Num_vertices, cont);
            cont++;
        }
        free(vetor);
        Ticks[1] = clock();
        Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
        printf("Tempo gasto: %g ms.", Tempo);
    }
}
