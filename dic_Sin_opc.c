#include "diccionario.h"

tipoNodo* crearNodo (tipoDict dict){
	tipoNodo *nodo = (tipoNodo *)malloc (sizeof (tipoNodo));

	strcpy (nodo->info.palIngles, dict.palIngles);
	strcpy (nodo->info.palEspanol, dict.palEspanol);
	

	nodo->siguiente = NULL;
	return nodo;
}

tipoNodo* adicionarLista (tipoNodo *lista, tipoDict dict) 
{
	tipoNodo *nuevoNodo = crearNodo (dict);

	if (lista==NULL) {
		lista = nuevoNodo;
	}else {
		tipoNodo *aptNodo = lista;
		while (aptNodo->siguiente != NULL) {
			aptNodo = aptNodo->siguiente;
		}
		aptNodo->siguiente = nuevoNodo;
	}

	return lista;
}

int buscarPos(tipoNodo *lista, char * palabra){
	int pos = 0;
	if (lista == NULL) printf("LISTA VACIA");
	tipoNodo *aptNodo = lista;

	while (aptNodo != NULL) {

		if (strcmp(palabra, aptNodo -> info.palIngles) > 0)
		{
			pos ++;
			aptNodo = aptNodo->siguiente;	
		}

		else
			break;		
	}

	return pos ;
}

void imprimirLista (tipoNodo *lista){
	tipoNodo *aptNodo = lista;
	while (aptNodo != NULL) {
		printf ("<%s>::<%s>\n", aptNodo->info.palIngles, aptNodo->info.palEspanol);
		aptNodo = aptNodo->siguiente;
	}
}

tipoNodo* cargarDictToLista (char *nombreArchivoBin, tipoNodo *lista) 
{
	FILE *manejadorBin;
	manejadorBin = fopen (nombreArchivoBin, "r"); 
	tipoDict dictTmp;
	int longitudBytes = sizeof (tipoDict);

	while (fread (&dictTmp, longitudBytes, 1, manejadorBin) == 1) {
		//printf ("<%s>:<%s>\n", dictTmp.palIngles, dictTmp.palEspanol);
		lista = adicionarLista (lista, dictTmp);
	}
	fclose (manejadorBin);

	return lista;

}


char *buscarPal (char* palBuscar, tipoNodo * lst)
{
	tipoNodo *p = lst;
	char* pI = (char*) malloc ((sizeof(char)) *50);
	char* pE = (char*) malloc ((sizeof(char)) *50);

	if (lst == NULL) return "No existe";

	else
	{
		while (p  != NULL)
		{
			strcpy(pI,p ->info.palIngles);
			strcpy(pE,p ->info.palEspanol);
			if (strcmp (palBuscar,pI) == 0)
			{
				return (pE);
			}
			else if (strcmp(palBuscar,pE) == 0)
			{
				return (pI);
			}

			else
			{
				p = p-> siguiente;
			}
		}
		return "La palabra no se encontro";

	}
}

void salirPrograma()
{}

tipoNodo* insertarLista(tipoNodo* lst, tipoDict elemento, int pos)
{
	tipoNodo* nodoTmp = crearNodo(elemento);
	tipoNodo* p = lst;
	int cont = 1;
	if(pos == 1)
	{
		nodoTmp->siguiente = lst;
		lst = nodoTmp;
	}
	else
	{
		while(cont < pos-1)
		{
			cont++;
			p = p->siguiente;
		}
		nodoTmp->siguiente = p->siguiente;
		p->siguiente = nodoTmp;
	}
	return lst;
}



int main (int argc, char* argv[]){
	tipoNodo *lista;
	tipoDict dict;
	lista = crearNodo(dict);
	lista = cargarDictToLista ("palabras.bin", lista);
	//imprimirLista (lista);
	char* respuesta = buscarPal(argv[1],lista);
	printf("<%s>:<%s>\n",argv[1],respuesta);
	return 0;
}