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

void addLista2P(char* palIngles, char* palEspanol)
{}


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