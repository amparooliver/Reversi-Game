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
		  verifica_validez1(fila,columna,computadora);
		  insertar_ficha(fila,columna,computadora);
		  remplaza_imagenes(fila,columna,computadora);
		  gchar *temp = g_strdup_printf("Presiono la imagen coordenada [%c,%d]", ('A'+fila-1),columna);
		  gtk_label_set_text(GTK_LABEL(label_estado), temp);
		  g_free(temp);
		  gchar *pasa_turno = g_strdup_printf("Turno de la computadora LOCAL");
		  gtk_label_set_text(GTK_LABEL(label_turno), pasa_turno);
		  g_free(pasa_turno);
		  printf("\niNSERTA SUS FICHAS");

	  }
	  int del = remove("./src/gonzalo.txt");
	  if (!del)
		  printf("\nThe file is Deleted successfully");
	  else
	      printf("\nthe file is not Deleted");
	  secuencia_juego();
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
void secuencia_juego(){
	printf("\nENTRA EN SECUENCIA DE JUEGO");
	if(juego_terminado()==FALSE){
		printf("\njuego terminado false de secuencia");
		g_timeout_add(1500,turno_computadora,NULL);
		printf("\nENTRA EN JUEGO COMPU TRUE");
		//compu_vs_compu();

	}
	if(juego_terminado()==TRUE){
		puntos(jugador);
	}
	printf("sale de la funcion jugar");
}
int empieza_computadora(int f, int c){
	  FILE *outfile;
	  char *inRival= "./src/amparo.txt";
	  char aux[4]="PASO";
	  char columna;

	  //creamos nuestro archivo con nuestras coordenadas
	  outfile = fopen(inRival, "w+");
	  if (!outfile) {
	  	printf("Couldn't open %s for writing\n",inRival);
	  	return 0;
	  }

	  if(f==0 && c==0){
		  fprintf(outfile,"%s",aux);
	  }else{
		  columna=('A'+(c-1));
		  fprintf(outfile,"%c%d",columna,f);
	  }

	  fclose(outfile);

	  return 0;
}
