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
		while (p != NULL)
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

tipoNodo* insertarListaPos(tipoNodo* lst, tipoDict elemento, int pos)
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


int buscarPosInsertar(tipoNodo* lst, char* palabra)
{
	tipoNodo* aptNodo = lst;
	int pos = 1;
	while(aptNodo != NULL)
	{
		if(strcmp(palabra,aptNodo->info.palIngles) > 0)
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


tipoNodo* adicionarPr(tipoNodo* lst, tipoDict palabra)
{
	tipoNodo* aptNodo;
	tipoNodo* nodoPal = crearNodo(palabra);
	int pos = buscarPos(lst,nodoPal->info.palIngles);
	aptNodo = insertarListaPos(lst, palabra, pos);

	return aptNodo;
}


tipoNodo* eliminarPR(tipoNodo* lst, char * palabra)
{
	int pos = buscarPos(lst,palabra);
	lst = eliminarLista (lst, pos);
	return lst;
}

tipoNodo* eliminarLista(tipoNodo* lst, int pos)
{
	tipoNodo* aptNodo = lst, *q;

	int cont = 1;

	if(pos == 1)
	{
		lst = lst->siguiente;
	}
	else
	{
		while(cont < pos-1)
		{
			cont++;
			aptNodo = aptNodo->siguiente;
		}
		q = aptNodo->siguiente;
		aptNodo->siguiente = aptNodo->siguiente->siguiente;
		free(q);
	}
	return lst;
}



tipoNodo* modificar(tipoNodo* lst, char* palabra)
{
	tipoNodo* aptNodo = lst;
	int pos = buscarPos(lst,palabra);

	int cont = 1;
	printf("Escribir la traduccion correcta\n");
	char traduccion[50];
	scanf("%s",traduccion);

	if(pos == 1)
	{
		strcpy(lst->info.palEspanol,traduccion);
	}

	else
	{
		while(cont <= pos-1)
		{
			cont++;
			aptNodo = aptNodo->siguiente;
		}
		strcpy(aptNodo->info.palEspanol,traduccion);
	}
	return lst;
}

void guardarListaArchivo(tipoNodo *lst, char* nombreArchivo)
{
	FILE* archBin = fopen(nombreArchivo, "wb");
	FILE* archTxt = fopen("backup.txt", "w");
	tipoNodo* p = lst;
	tipoDict* tmpInfo;
	char cadena[150];
	while(p != NULL)
	{
		tmpInfo = &(p->info);
		fwrite(tmpInfo, sizeof(tipoDict),1,archBin);
		sprintf(cadena,"<%s>: <%s>\n", tmpInfo->palIngles, tmpInfo->palEspanol);
		fputs(cadena,archTxt);
		p = p-> siguiente;
	}
	fclose(archBin);
	fclose(archTxt);
}


int main()
{
	tipoNodo *lista;
	tipoDict dict;
	lista = crearNodo(dict);
	lista = cargarDictToLista ("palabras.bin", lista);
	int opcion;
	
	do
	{	
		printf("1. Salir del programa \n");
		printf("2. Busqueda exacta \n");
		printf("3. Adicionar palabra \n");
		printf("4. Eliminar palabra\n");
		printf("5. Modificar la traduccion de una palabra \n");
		printf("6. Busqueda inteligente \n");
		printf("Elegir una opcion\n");
		scanf("%d", &opcion);
	

			if(opcion == 2)
			{
				printf("Escribir la palabra\n");
				char palabra[50];
				scanf("%s", palabra);
				char* respuesta = buscarPal(palabra,lista);
				printf("<%s>:<%s>\n",palabra,respuesta);
			}

			else if(opcion == 3)
			{
				printf("Escribir la palabra\n");
				char ingles[50];
				printf("Escribir su traduccion\n");
				char palEspa[50];
				strcpy(dict.palIngles, ingles);
				strcpy(dict.palEspanol, palEspa);
				lista = adicionarPr(lista, dict);
			}

			else if(opcion == 4)
			{
				printf("Escribir la palabra\n");
				char ingles[50];
				scanf("%s", ingles);
				int hol = buscarPos(lista, ingles);
			}

			else if(opcion == 5)
			{
				printf("Escribir la palabra\n");
				char ingles[50];
				lista = modificar(lista, ingles);
			}

			else
			{
				printf("Fin del programa \n");
			}
	}while(opcion != 1);

	return 0;
} 
