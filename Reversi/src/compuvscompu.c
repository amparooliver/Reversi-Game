#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "declaraciones.h"
#include <gtk/gtk.h>

int compu_vs_compu(){

	  FILE *infile;
	  char *inname = "./src/gonzalo.txt";
	  char coordenada[100];
	  char line[100];
	  char f,c;
	  int fila,columna;
	  char aux[4]="PASO";

	  //ABRIMOS EL ARCHIVO
	  infile = fopen(inname, "r");
	  do{
		  while(fgets(line, sizeof(line), infile) != NULL){
			  printf("\nENTRA AL WHILE");
			  //almacenamos la linea
			  sscanf(line, "%s",coordenada);
		  }
		 rewind(infile);
		 c= getc(infile);
		 f= getc(infile);

	  }while (!infile);
	  //prueba en consola de lo que guarda
	  printf("COORDENADA %s\n",coordenada);
	  fclose(infile);

	  if((strcmp(aux,coordenada))==0){
		  printf("\nEntra en pasar turno.");
	  }else{
		  printf("\nIngreso coordenadas");
		  printf("\nfila: %c",f);
		  fila=conversion_fila(f);
		  columna=conversion_columna(c);
		  printf("\nFILA: %d COLUMNA: %d",fila,columna);
	  }
	  int del = remove("./src/gonzalo.txt");
	  if (!del)
		  printf("\nThe file is Deleted successfully");
	  else
	      printf("\nthe file is not Deleted");


		return 0;
}
int conversion_columna(char aux){
	if(aux=='A'){
		return 1;
	}else if(aux=='B'){
		return 2;
	}else if(aux=='C'){
		return 3;
	}else if(aux=='D'){
		return 4;
	}else if(aux=='E'){
		return 5;
	}else if(aux=='F'){
		return 6;
	}else if(aux=='G'){
		return 7;
	}else if(aux=='H'){
		return 8;
	}else{
		return -1;
	}
}
int conversion_fila(char aux){
	if(aux=='1'){
		return 1;
	}else if(aux=='2'){
		return 2;
	}else if(aux=='3'){
		return 3;
	}else if(aux=='4'){
		return 4;
	}else if(aux=='5'){
		return 5;
	}else if(aux=='6'){
		return 6;
	}else if(aux=='7'){
		return 7;
	}else if(aux=='8'){
		return 8;
	}else{
		return -1;
	}
}
