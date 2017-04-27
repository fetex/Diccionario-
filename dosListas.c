#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Nodo2p
{
	char palabra[50];
	struct Nodo2p * siguiente;
	struct Nodo2p * traduccion;
};

struct Dict
{
	char palIngles  [50];
	char palEspanol [50];
};

typedef struct Nodo2p TipoNodo2p;
typedef struct Dict tipoDict;


TipoNodo2p *listaIngles = NULL;
TipoNodo2p *listaEspanol = NULL;



TipoNodo2p *crearNodo2p(char *word)
{
	TipoNodo2p *nuevoNodo = (TipoNodo2p *) malloc (sizeof(TipoNodo2p));

	strcpy(nuevoNodo -> palabra, word);
	nuevoNodo -> siguiente = NULL;
	nuevoNodo -> traduccion = NULL;

	return nuevoNodo;
}

int buscarPosInsertar(TipoNodo2p* lst, char* palabra)
{
	TipoNodo2p* aptNodo = lst;
	int pos = 1;
	while(aptNodo != NULL)
	{
		if(strcmp(palabra,aptNodo->palabra) > 0)
		{
			pos++;
			aptNodo = aptNodo->siguiente;
		}
		else
		{
			break;
		}
	}
	return pos;
}

TipoNodo2p* insertarListaPos(TipoNodo2p* lst, TipoNodo2p *nodo, int pos)
{
	TipoNodo2p* p = lst;
	int cont = 1;
	if(pos == 1)
	{
		nodo->siguiente = lst;
		lst = nodo;
	}
	else
	{
		while(cont < pos)
		{
			cont++;
			p = p->siguiente;
		}
		nodo->siguiente = p->siguiente;
		p->siguiente = nodo;
	}
	return lst;
}

void addLista2P(char* palIngles, char* palEspanol)
{
	TipoNodo2p *nodoIng = crearNodo2p(palIngles);
	TipoNodo2p *nodoEsp = crearNodo2p(palEspanol);
	nodoIng->traduccion = nodoEsp;
	nodoEsp->traduccion = nodoIng;

	if((listaIngles == NULL) && (listaEspanol == NULL))
	{
		listaIngles = nodoIng;
		listaEspanol = nodoEsp;
	}

	else
	{
		int posEspa = buscarPosInsertar(listaEspanol, palEspanol);
		int posIng = buscarPosInsertar(listaIngles, palIngles);	
		listaIngles = insertarListaPos(listaIngles, nodoIng, posIng);
		listaEspanol = insertarListaPos(listaEspanol, nodoEsp, posEspa);
	}
}


void cargarArchivoListas2P (char *nomArch)
{
	FILE *mnjArch = fopen(nomArch, "rb");
	tipoDict apunRegistro;
	while(fread(&apunRegistro, sizeof(tipoDict),1,mnjArch) == 1)
	{
		addLista2P(apunRegistro.palIngles, apunRegistro.palEspanol);
	}
	fclose(mnjArch);
}

int main()
{
	/* code */
	return 0;
}