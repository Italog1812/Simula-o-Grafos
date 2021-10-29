#include <iostream>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "File.h"

using namespace std;

int main(int argc, char const *argv[])
{

    FILE *archive;
    char *Result;
    //testando com a Grafo não-direcionado nao-ponderado.txt
    ReadFile(archive, "Grafo nao-direcionado nao-ponderado.txt", Result);
    return 0;
}
