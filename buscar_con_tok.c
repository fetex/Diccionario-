#include <stdio.h>
//#include <conio.h>
#include <string.h>
#include <stdlib.h>

void main(){//Buscar archivo
    FILE * Diccionario = fopen("Diccionario.txt","r");
    char guardar[1000];
    char palabra[100];//lo que deseo buscar

    printf("Digite la palabra que desea buscar: ");
    scanf("%s",palabra);//tomo lo que me mandan  escriben.
    char *y=palabra;
    if(Diccionario==NULL){
        printf("No se pudo leer: :( .....");
        exit(0);
    }
    else{
        while(!(feof(Diccionario))){
            fgets(guardar,1000,Diccionario);//donde se guarda,espacio,de donde lo lee.
            char *x;
            char *y;
            x=strstr(guardar,palabra);
            if(strstr(guardar,palabra)!=NULL){//strstr
                strtok(x," : ");
                strtok(NULL," ");
                y=strtok(NULL,"\n");

                printf("%s",x);
                printf("\n");
                //printf("%s",y); 
            }

        }
    }
    fclose(Diccionario);
    //getch();

}

