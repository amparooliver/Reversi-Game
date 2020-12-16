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

	  //ABRIMOS EL ARCHIVO
	  infile = fopen(inname, "r");
	  do{
		  while(fgets(line, sizeof(line), infile) != NULL){
			  printf("\nENTRA AL WHILE");
			  //almacenamos la linea
			  sscanf(line, "%s",coordenada);
		  }

	  }while (!infile);
	  //prueba en consola de lo que guarda
	  printf("COORDENADA %s\n",coordenada);
	  fclose(infile);
	  if(strcmp('PASO',coordenada)==0){
		  printf("\nEntra en pasar turno.");
	  }else{
		  printf("\nIngreso coordenadas");
	  }
	  int del = remove("./src/gonzalo.txt");
	  if (!del)
		  printf("\nThe file is Deleted successfully");
	  else
	      printf("\nthe file is not Deleted");


		return 0;
}
