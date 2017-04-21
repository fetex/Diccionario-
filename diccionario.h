#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __DICCIONARIO_H
#define __DICCIONARIO_H

struct Dict
{
	char palIngles  [50];
	char palEspanol [50];
};

typedef struct Dict tipoDict;

struct Nodo 
{
	tipoDict info;
	struct Nodo *siguiente;
};

typedef struct Nodo tipoNodo;

tipoNodo* crearNodo (tipoDict dict);
tipoNodo* adicionarLista (tipoNodo* lista, tipoDict dict);
int buscarPos(tipoNodo* lista, char* palabra);
void imprimirLista (tipoNodo* lista);
tipoNodo* cargarDictToLista (char* nombreArchivoBin, tipoNodo* lista);
char* buscarPal (char* palBuscar, tipoNodo* lst);
tipoNodo* insertarListaPos(tipoNodo* lst, tipoDict elemento, int pos);
tipoNodo* adicionarPr(tipoNodo* lst, tipoDict palabra);
int buscarPosInsertar(tipoNodo* lst, char* palabra);
tipoNodo* eliminarPR(tipoNodo* lst, tipoDict palabra);

#endif