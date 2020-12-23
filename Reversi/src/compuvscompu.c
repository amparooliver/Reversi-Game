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
	  char *inname = "./src/jugador_externo.txt";
	  char coordenada[100];
	  char line[100];
	  char f,c;
	  int fila,columna;

	  //ABRIMOS EL ARCHIVO
	  do{
		  infile = fopen(inname, "r");
		  printf("\nESPERANDO AL ARCHIVO");

	  }while (!infile);

	  while(fgets(line, sizeof(line), infile) != NULL){
		  printf("\nENTRA AL WHILE");
		  //Almacenamos la linea
		  sscanf(line, "%s",coordenada);
	  }
	 rewind(infile);
	 c= getc(infile);
	 f= getc(infile);

	  //Prueba en consola de lo que guarda
	  printf("COORDENADA %s\n",coordenada);
	  fclose(infile);

	  if((strcmp("PASO",coordenada))==0){

		  int del = remove("./src/jugador_externo.txt");
		  if (!del){
			  printf("\nSe borro el archivo exitosamente.");
			  secuencia_juego();
		  }
		  else{
			  printf("\nNo se borro el archivo");
		  }
	  }else{
		  //Convertimos de char a su equivalente
		  fila=conversion_fila(f);
		  columna=conversion_columna(c);

		  verifica_validez1(fila,columna,computadora);
		  insertar_ficha(fila,columna,computadora);
		  remplaza_imagenes(fila,columna,computadora);

		  gchar *temp = g_strdup_printf("Presiono la imagen coordenada [%c,%d]", ('A'+fila-1),columna);
		  gtk_label_set_text(GTK_LABEL(label_estado), temp);
		  g_free(temp);
		  gchar *pasa_turno = g_strdup_printf("Turno de la computadora LOCAL");
		  gtk_label_set_text(GTK_LABEL(label_turno), pasa_turno);
		  g_free(pasa_turno);

		  //Eliminamos el archivo
		  int del = remove("./src/jugador_externo.txt");
		  if (!del){
			  printf("\nSe borro el archivo exitosamente.");
			  secuencia_juego();
		  }
		  else{
			  printf("\nNo se borro el archivo");
		  }

	  }

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
	if(juego_terminado()==FALSE){
		g_timeout_add(1000,turno_computadora,NULL);
		g_timeout_add(1500,compu_vs_compu,NULL);

	}
	if(juego_terminado()==TRUE){
		puntos(jugador);
	}
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
