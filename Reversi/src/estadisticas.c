#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "declaraciones.h"
#include <gtk/gtk.h>

void ordenar(int nroPalabras, struct statistics *ptr){
	int i, j;
	char temp[20];
	int temp2;
	int temp3;
	int temp4;

    for(i=0; i<nroPalabras-1; i++) {
        for(j=i+1; j<nroPalabras; j++) {
            if((ptr+i)->parGanadas<=(ptr+j)->parGanadas) {
            	//cambio para el nombre
                strcpy(temp, (ptr+i)->nombre_estadisticas);
                strcpy((ptr+i)->nombre_estadisticas, (ptr+j)->nombre_estadisticas);
                strcpy((ptr+j)->nombre_estadisticas,temp);
                //cambio para partidas jugadas
                temp2=((ptr+i)->parJugadas);
                ((ptr+i)->parJugadas)=((ptr+j)->parJugadas);
                ((ptr+j)->parJugadas)=temp2;
                //cambio para partidas ganadas
                temp3=((ptr+i)->parGanadas);
                ((ptr+i)->parGanadas)=((ptr+j)->parGanadas);
                ((ptr+j)->parGanadas)=temp3;
                //cambio para partidas perdidas
                temp4=((ptr+i)->parPerdidas);
                ((ptr+i)->parPerdidas)=((ptr+j)->parPerdidas);
                ((ptr+j)->parPerdidas)=temp4;
            }
        }
    }

}

int impresion_estadisticas(){

	  char line[100];
	  struct statistics *ptr;
	  int i=0, nroPalabras;
	  FILE *infile;
	  char *inname = "./src/estadisticas.txt";
	  char aux[20];
	  char aux2[20];
	  char aux3[20];

	  //ABRIMOS EL ARCHIVO
	  infile = fopen(inname, "r");
	  if (!infile) {
	    printf("Couldn't open %s for reading\n",inname);
	    return 0;
	  }

		//reservamos un espacio en la memoria para la estructura
	    ptr = (struct statistics *)malloc(sizeof(struct statistics));
		while(i < 100 && fgets(line, sizeof(line), infile) != NULL){
	    	//almacenamos el nombre,  partidas jugadas, partidas ganadas, partidas perdidas
	    	sscanf(line, "%s\t%s\t%s\t%[^\n]",(ptr + i)->nombre_estadisticas,aux,aux2,aux3);

	        ((ptr + i)->parJugadas)=atoi(aux);
	        ((ptr + i)->parGanadas)=atoi(aux2);
	        ((ptr + i)->parPerdidas)=atoi(aux3);

	        i++;

	        //incrementamos el espacio de memoria de la estructura
	        ptr = (struct statistics *)realloc(ptr,sizeof(struct statistics)*(i+1));
	    }

		nroPalabras= i;
		//Impresion sin ordenar en consola
		for (i = 0; i < nroPalabras; ++i){
	    	printf("%s\t%d\t%d\t%d\n", (ptr + i)->nombre_estadisticas,(ptr + i)->parJugadas,((ptr + i)->parGanadas),(ptr + i)->parPerdidas);
		}

		printf("\n");
		ordenar(nroPalabras,ptr);
		//Impresion ordenada en consola
		for (i = 0; i < nroPalabras; ++i){
	    	printf("%s\t%d\t%d\t%d\n", (ptr + i)->nombre_estadisticas,(ptr + i)->parJugadas,((ptr + i)->parGanadas),(ptr + i)->parPerdidas);
		}

		//impresion en gtk
		impresion_estadisticas_enGTK(ptr);

		fclose(infile);

		return 0;
}
void impresion_estadisticas_enGTK(struct statistics *ptr){
		gchar *estadisticas = g_strdup_printf("%s\t\t%d\t\t%d\t\t%d\n%s\t\t%d\t\t%d\t\t%d\n%s\t\t%d\t\t%d\t\t%d\n%s\t\t%d\t\t%d\t\t%d\n%s\t\t%d\t\t%d\t\t%d\n%s\t\t%d\t\t%d\t\t%d\n%s\t\t%d\t\t%d\t\t%d\n%s\t\t%d\t\t%d\t\t%d\n%s\t\t%d\t\t%d\t\t%d\n%s\t\t%d\t\t%d\t\t%d\n",
		(ptr + 0)->nombre_estadisticas,(ptr + 0)->parJugadas,((ptr + 0)->parGanadas),(ptr + 0)->parPerdidas,
		(ptr + 1)->nombre_estadisticas,(ptr + 1)->parJugadas,((ptr + 1)->parGanadas),(ptr + 1)->parPerdidas,
		(ptr + 2)->nombre_estadisticas,(ptr + 2)->parJugadas,((ptr + 2)->parGanadas),(ptr + 2)->parPerdidas,
		(ptr + 3)->nombre_estadisticas,(ptr + 3)->parJugadas,((ptr + 3)->parGanadas),(ptr + 3)->parPerdidas,
		(ptr + 4)->nombre_estadisticas,(ptr + 4)->parJugadas,((ptr + 4)->parGanadas),(ptr + 4)->parPerdidas,
		(ptr + 5)->nombre_estadisticas,(ptr + 5)->parJugadas,((ptr + 5)->parGanadas),(ptr + 5)->parPerdidas,
		(ptr + 6)->nombre_estadisticas,(ptr + 6)->parJugadas,((ptr + 6)->parGanadas),(ptr + 6)->parPerdidas,
		(ptr + 7)->nombre_estadisticas,(ptr + 7)->parJugadas,((ptr + 7)->parGanadas),(ptr + 7)->parPerdidas,
		(ptr + 8)->nombre_estadisticas,(ptr + 8)->parJugadas,((ptr + 8)->parGanadas),(ptr + 8)->parPerdidas,
		(ptr + 9)->nombre_estadisticas,(ptr + 9)->parJugadas,((ptr + 9)->parGanadas),(ptr + 9)->parPerdidas);
		gtk_label_set_text(GTK_LABEL(label_estadisticas), estadisticas);
		g_free(estadisticas);

}
int actualizacion_estadisticas(){
	printf("\n Entra en actualizaciion estad");
	char line[100];
	struct statistics *ptr;
	int i=0, nroPalabras;
	FILE *infile;
	char *inname = "./src/estadisticas.txt";
	char aux[20];
	char aux2[20];
	char aux3[20];

	//ABRIMOS EL ARCHIVO PARA LEER Y ESCRIBIR
	infile = fopen(inname, "r+");
	if (!infile) {
		printf("Couldn't open %s for reading and writing\n",inname);
		return 0;
	}

	//reservamos un espacio en la memoria para la estructura
    ptr = (struct statistics *)malloc(sizeof(struct statistics));
	while(i < 100 && fgets(line, sizeof(line), infile) != NULL){
    	//almacenamos el nombre,  partidas jugadas, partidas ganadas, partidas perdidas
    	sscanf(line, "%s\t%s\t%s\t%[^\n]",(ptr + i)->nombre_estadisticas,aux,aux2,aux3);

        ((ptr + i)->parJugadas)=atoi(aux);
        ((ptr + i)->parGanadas)=atoi(aux2);
        ((ptr + i)->parPerdidas)=atoi(aux3);

        i++;

        //incrementamos el espacio de memoria de la estructura
        ptr = (struct statistics *)realloc(ptr,sizeof(struct statistics)*(i+1));
    }

	nroPalabras= i;

	for(i=0; i<nroPalabras-1; i++) {
		if(strcmp(((ptr+i)->nombre_estadisticas),nombre)==0){
			printf("\nEncuentra el nombre Y LE SUMA A PARTIDA JUGADA");
			((ptr + i)->parJugadas)=((ptr + i)->parJugadas+1);
			printf("%d jugadas \n", (ptr+i)->parJugadas);
			   if(gano==1){
				   ((ptr + i)->parGanadas)++;
				   printf("%d ganadas \n", (ptr+i)->parGanadas);
			   }else if(gano==0){
				   ((ptr + i)->parPerdidas)++;
				   printf("%d perdidas \n", (ptr+i)->parPerdidas);
			   }else if(gano==2){
				   //empato, no aumenta
			   }
		   }
	}

	//Impresion sin ordenar en consola
	for (i = 0; i < nroPalabras; ++i){
    	printf("%s\t%d\t%d\t%d\n", (ptr + i)->nombre_estadisticas,(ptr + i)->parJugadas,((ptr + i)->parGanadas),(ptr + i)->parPerdidas);
	}

	fclose(infile);


	return 0;
}