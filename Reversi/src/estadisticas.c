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

		/*
		//Impresion sin ordenar en consola
		for (i = 0; i < nroPalabras; ++i){
	    	printf("%s\t%d\t%d\t%d\n", (ptr + i)->nombre_estadisticas,(ptr + i)->parJugadas,((ptr + i)->parGanadas),(ptr + i)->parPerdidas);
		}

		printf("\n");
		ordenar(nroPalabras,ptr);
		//Impresion ordenada en consola
		for (i = 0; i < nroPalabras; ++i){
	    	printf("%s\t%d\t%d\t%d\n", (ptr + i)->nombre_estadisticas,(ptr + i)->parJugadas,((ptr + i)->parGanadas),(ptr + i)->parPerdidas);
		}*/

		//impresion en gtk
		impresion_estadisticas_enGTK(ptr,nroPalabras);

		fclose(infile);

		return 0;
}
void impresion_estadisticas_enGTK(struct statistics *ptr, int nroPalabras){

		if(nroPalabras==1){
			gchar *estadisticas = g_strdup_printf("%5s\t%5d\t%5d\t%5d\n", (ptr)->nombre_estadisticas,(ptr)->parJugadas,((ptr)->parGanadas),(ptr)->parPerdidas);
			gtk_label_set_text(GTK_LABEL(label_estadisticas), estadisticas);
			g_free(estadisticas);
		}else if(nroPalabras==2){
			gchar *estadisticas = g_strdup_printf("%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n",
			(ptr + 0)->nombre_estadisticas,(ptr + 0)->parJugadas,((ptr + 0)->parGanadas),(ptr + 0)->parPerdidas,
			(ptr + 1)->nombre_estadisticas,(ptr + 1)->parJugadas,((ptr + 1)->parGanadas),(ptr + 1)->parPerdidas);
			gtk_label_set_text(GTK_LABEL(label_estadisticas), estadisticas);
			g_free(estadisticas);
		}else if(nroPalabras==3){
			gchar *estadisticas = g_strdup_printf("%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n",
			(ptr + 0)->nombre_estadisticas,(ptr + 0)->parJugadas,((ptr + 0)->parGanadas),(ptr + 0)->parPerdidas,
			(ptr + 1)->nombre_estadisticas,(ptr + 1)->parJugadas,((ptr + 1)->parGanadas),(ptr + 1)->parPerdidas,
			(ptr + 2)->nombre_estadisticas,(ptr + 2)->parJugadas,((ptr + 2)->parGanadas),(ptr + 2)->parPerdidas);
			gtk_label_set_text(GTK_LABEL(label_estadisticas), estadisticas);
			g_free(estadisticas);
		}else if(nroPalabras==4){
			gchar *estadisticas = g_strdup_printf("%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n",
			(ptr + 0)->nombre_estadisticas,(ptr + 0)->parJugadas,((ptr + 0)->parGanadas),(ptr + 0)->parPerdidas,
			(ptr + 1)->nombre_estadisticas,(ptr + 1)->parJugadas,((ptr + 1)->parGanadas),(ptr + 1)->parPerdidas,
			(ptr + 2)->nombre_estadisticas,(ptr + 2)->parJugadas,((ptr + 2)->parGanadas),(ptr + 2)->parPerdidas,
			(ptr + 3)->nombre_estadisticas,(ptr + 3)->parJugadas,((ptr + 3)->parGanadas),(ptr + 3)->parPerdidas);
			gtk_label_set_text(GTK_LABEL(label_estadisticas), estadisticas);
			g_free(estadisticas);
		}else if(nroPalabras==5){
			gchar *estadisticas = g_strdup_printf("%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n",
			(ptr + 0)->nombre_estadisticas,(ptr + 0)->parJugadas,((ptr + 0)->parGanadas),(ptr + 0)->parPerdidas,
			(ptr + 1)->nombre_estadisticas,(ptr + 1)->parJugadas,((ptr + 1)->parGanadas),(ptr + 1)->parPerdidas,
			(ptr + 2)->nombre_estadisticas,(ptr + 2)->parJugadas,((ptr + 2)->parGanadas),(ptr + 2)->parPerdidas,
			(ptr + 3)->nombre_estadisticas,(ptr + 3)->parJugadas,((ptr + 3)->parGanadas),(ptr + 3)->parPerdidas,
			(ptr + 4)->nombre_estadisticas,(ptr + 4)->parJugadas,((ptr + 4)->parGanadas),(ptr + 4)->parPerdidas);
			gtk_label_set_text(GTK_LABEL(label_estadisticas), estadisticas);
			g_free(estadisticas);
		}else if(nroPalabras==6){
			gchar *estadisticas = g_strdup_printf("%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n",
			(ptr + 0)->nombre_estadisticas,(ptr + 0)->parJugadas,((ptr + 0)->parGanadas),(ptr + 0)->parPerdidas,
			(ptr + 1)->nombre_estadisticas,(ptr + 1)->parJugadas,((ptr + 1)->parGanadas),(ptr + 1)->parPerdidas,
			(ptr + 2)->nombre_estadisticas,(ptr + 2)->parJugadas,((ptr + 2)->parGanadas),(ptr + 2)->parPerdidas,
			(ptr + 3)->nombre_estadisticas,(ptr + 3)->parJugadas,((ptr + 3)->parGanadas),(ptr + 3)->parPerdidas,
			(ptr + 4)->nombre_estadisticas,(ptr + 4)->parJugadas,((ptr + 4)->parGanadas),(ptr + 4)->parPerdidas,
			(ptr + 5)->nombre_estadisticas,(ptr + 5)->parJugadas,((ptr + 5)->parGanadas),(ptr + 5)->parPerdidas);
			gtk_label_set_text(GTK_LABEL(label_estadisticas), estadisticas);
			g_free(estadisticas);
		}else if(nroPalabras==7){
			gchar *estadisticas = g_strdup_printf("%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n",
			(ptr + 0)->nombre_estadisticas,(ptr + 0)->parJugadas,((ptr + 0)->parGanadas),(ptr + 0)->parPerdidas,
			(ptr + 1)->nombre_estadisticas,(ptr + 1)->parJugadas,((ptr + 1)->parGanadas),(ptr + 1)->parPerdidas,
			(ptr + 2)->nombre_estadisticas,(ptr + 2)->parJugadas,((ptr + 2)->parGanadas),(ptr + 2)->parPerdidas,
			(ptr + 3)->nombre_estadisticas,(ptr + 3)->parJugadas,((ptr + 3)->parGanadas),(ptr + 3)->parPerdidas,
			(ptr + 4)->nombre_estadisticas,(ptr + 4)->parJugadas,((ptr + 4)->parGanadas),(ptr + 4)->parPerdidas,
			(ptr + 5)->nombre_estadisticas,(ptr + 5)->parJugadas,((ptr + 5)->parGanadas),(ptr + 5)->parPerdidas,
			(ptr + 6)->nombre_estadisticas,(ptr + 6)->parJugadas,((ptr + 6)->parGanadas),(ptr + 6)->parPerdidas);
			gtk_label_set_text(GTK_LABEL(label_estadisticas), estadisticas);
			g_free(estadisticas);
		}else if(nroPalabras==8){
			gchar *estadisticas = g_strdup_printf("%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n",
			(ptr + 0)->nombre_estadisticas,(ptr + 0)->parJugadas,((ptr + 0)->parGanadas),(ptr + 0)->parPerdidas,
			(ptr + 1)->nombre_estadisticas,(ptr + 1)->parJugadas,((ptr + 1)->parGanadas),(ptr + 1)->parPerdidas,
			(ptr + 2)->nombre_estadisticas,(ptr + 2)->parJugadas,((ptr + 2)->parGanadas),(ptr + 2)->parPerdidas,
			(ptr + 3)->nombre_estadisticas,(ptr + 3)->parJugadas,((ptr + 3)->parGanadas),(ptr + 3)->parPerdidas,
			(ptr + 4)->nombre_estadisticas,(ptr + 4)->parJugadas,((ptr + 4)->parGanadas),(ptr + 4)->parPerdidas,
			(ptr + 5)->nombre_estadisticas,(ptr + 5)->parJugadas,((ptr + 5)->parGanadas),(ptr + 5)->parPerdidas,
			(ptr + 6)->nombre_estadisticas,(ptr + 6)->parJugadas,((ptr + 6)->parGanadas),(ptr + 6)->parPerdidas,
			(ptr + 7)->nombre_estadisticas,(ptr + 7)->parJugadas,((ptr + 7)->parGanadas),(ptr + 7)->parPerdidas);
			gtk_label_set_text(GTK_LABEL(label_estadisticas), estadisticas);
			g_free(estadisticas);
		}else if(nroPalabras==9){
			gchar *estadisticas = g_strdup_printf("%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n",
			(ptr + 0)->nombre_estadisticas,(ptr + 0)->parJugadas,((ptr + 0)->parGanadas),(ptr + 0)->parPerdidas,
			(ptr + 1)->nombre_estadisticas,(ptr + 1)->parJugadas,((ptr + 1)->parGanadas),(ptr + 1)->parPerdidas,
			(ptr + 2)->nombre_estadisticas,(ptr + 2)->parJugadas,((ptr + 2)->parGanadas),(ptr + 2)->parPerdidas,
			(ptr + 3)->nombre_estadisticas,(ptr + 3)->parJugadas,((ptr + 3)->parGanadas),(ptr + 3)->parPerdidas,
			(ptr + 4)->nombre_estadisticas,(ptr + 4)->parJugadas,((ptr + 4)->parGanadas),(ptr + 4)->parPerdidas,
			(ptr + 5)->nombre_estadisticas,(ptr + 5)->parJugadas,((ptr + 5)->parGanadas),(ptr + 5)->parPerdidas,
			(ptr + 6)->nombre_estadisticas,(ptr + 6)->parJugadas,((ptr + 6)->parGanadas),(ptr + 6)->parPerdidas,
			(ptr + 7)->nombre_estadisticas,(ptr + 7)->parJugadas,((ptr + 7)->parGanadas),(ptr + 7)->parPerdidas,
			(ptr + 8)->nombre_estadisticas,(ptr + 8)->parJugadas,((ptr + 8)->parGanadas),(ptr + 8)->parPerdidas);
			gtk_label_set_text(GTK_LABEL(label_estadisticas), estadisticas);
			g_free(estadisticas);
		}
		else{
			gchar *estadisticas = g_strdup_printf("%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n%5s\t\t%5d\t\t%5d\t\t%5d\n",
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


}
int actualizacion_estadisticas(){

	char line[100];
	struct statistics *ptr;
	int i=0, nroPalabras,existeJugador=0,existeRival=0;
	FILE *infile;
	char *inname = "./src/estadisticas.txt";
	char aux[20];
	char aux2[20];
	char aux3[20];

	// Abrimos el archivo para leer
	infile = fopen(inname, "r");
	if (!infile) {
		printf("Couldn't open %s for reading and writing\n",inname);
		return 0;
	}

	// Reservamos un espacio en la memoria para la estructura
    ptr = (struct statistics *)malloc(sizeof(struct statistics));
	while(i < 100 && fgets(line, sizeof(line), infile) != NULL){

    	// Almacenamos el nombre,  partidas jugadas, partidas ganadas, partidas perdidas
    	sscanf(line, "%s\t%s\t%s\t%[^\n]",(ptr + i)->nombre_estadisticas,aux,aux2,aux3);

        ((ptr + i)->parJugadas)=atoi(aux);
        ((ptr + i)->parGanadas)=atoi(aux2);
        ((ptr + i)->parPerdidas)=atoi(aux3);

        i++;

        // Incrementamos el espacio de memoria de la estructura
        ptr = (struct statistics *)realloc(ptr,sizeof(struct statistics)*(i+1));
    }

	nroPalabras= i;

	fclose(infile);

	//Abrimos el archivo para escribir/leer
	infile = fopen(inname, "w+");
	if (!infile) {
		printf("Couldn't open %s for reading and writing\n",inname);
		return 0;
	}

	// Recorre la estructura
	for(i=0; i<nroPalabras-1; i++) {
		//BUSCA AL USUARIO EN EL ARCHIVO
		if(strcmp(((ptr+i)->nombre_estadisticas),nombre)==0){
			existeJugador=1;
			((ptr + i)->parJugadas)++; // Encuentra el nombre e incrementa Partidas Jugadas

			if(gano==1){ // Gana el USUARIO, incrementa Partidas Ganadas
				((ptr + i)->parGanadas)++;
			}else if(gano==0){// Gana la COMPUTADORA, incrementa Partidas Perdidas
				((ptr + i)->parPerdidas)++;
			}else if(gano==2){ // Empataron
				   //no aumenta nada por ahora
			}

		}else if(strcmp(((ptr+i)->nombre_estadisticas),rival)==0){
			existeRival=1;
			((ptr + i)->parJugadas)++;

			if(gano==1){ // Gana el USUARIO, incrementa Partidas Perdidas
				((ptr + i)->parPerdidas)++;

			}else if(gano==0){// Gana la COMPUTADORA, incrementa Partidas Ganadas
				((ptr + i)->parGanadas)++;
			}else if(gano==2){
				   // Empate
			}
		}
	}

	//si es que NO existe el nombre de JUGADOR en estadisticas, agrega al struct
	if(existeJugador==0){

		nroPalabras++; //incremento el nroPalabras para el struct

		ptr = (struct statistics *)realloc(ptr,sizeof(struct statistics)*(nroPalabras+1)); //incrementamos el espacio de memoria de la estructura

		i = nroPalabras - 1; //apunta a la ult posicion en el struct

		strcpy(((ptr + i)->nombre_estadisticas),nombre); //agrega el nombre al struct
		((ptr + i)->parJugadas)= 1 ;  // agrega Partidas Jugadas = 1
		//GANA USUARIO
		if(gano==1){
			((ptr + i)->parGanadas)= 1 ; // agrega Partidas Ganadas = 1
			((ptr + i)->parPerdidas)= 0 ;
		//GANA COMPUTADORA
		}else if(gano==0){
			((ptr + i)->parPerdidas)= 1 ; // agrega Partidas Perdidas = 1
			((ptr + i)->parGanadas)= 0 ;
		//EMPATARON
		}else if(gano==2){
			((ptr + i)->parGanadas)= 0 ;
			((ptr + i)->parPerdidas)= 0 ;
		}
	}

	// Si es que NO existe el nombre de RIVAL en estadisticas, agrega al struct
	if(existeRival==0){

		nroPalabras++; // Incremento el nroPalabras para el struct

		// Incrementamos el espacio de memoria de la estructura
		ptr = (struct statistics *)realloc(ptr,sizeof(struct statistics)*(nroPalabras+1));

		i = nroPalabras-1; //apunta a la ult posicion en el struct

		strcpy(((ptr + i)->nombre_estadisticas),rival); //agrega el rival al struct
		((ptr + i)->parJugadas)= 1 ;  // agrega Partidas jugadas = 1
		//GANA USUARIO
		if(gano==1){
			((ptr + i)->parPerdidas)= 1 ; // agrega Partidas Perdidas = 1
			((ptr + i)->parGanadas)= 0 ;
		//GANA COMPUTADORA
		}else if(gano==0){
			((ptr + i)->parGanadas)= 1 ; // agrega Partidas Ganadas = 1
			((ptr + i)->parPerdidas)= 0 ;
		//EMPATARON
		}else if(gano==2){
			((ptr + i)->parGanadas)= 0 ;
			((ptr + i)->parPerdidas)= 0 ;
		}
	}

	// Se escribe el nuevo struct en el txt
	for (i = 0; i < nroPalabras; ++i){
    	fprintf(infile,"%s\t%d\t%d\t%d\n",(ptr + i)->nombre_estadisticas,(ptr + i)->parJugadas,((ptr + i)->parGanadas),(ptr + i)->parPerdidas);
	}

	fclose(infile);
	return 0;
}
