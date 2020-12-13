/*
 * Inteligencia.c
 *
 *  Created on: 11 dic. 2020
 *      Author: lp1-2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "declaraciones.h"
#include <gtk/gtk.h>

int mayor=0;
int i_aux=0;
int j_aux=0;


int turno_computadora(){
	int i,j,x,y;
	printf("\nEntra en turno compu");
	gchar *turno_de = g_strdup_printf("Turno de: %s", nombre);
	gtk_label_set_text(GTK_LABEL(label_turno), turno_de);
	g_free(turno_de);
	srand(time(NULL));
	if(pierde_turno(computadora)==FALSE){
		for(x=0;x<9;x++){
			for(y=0;y<9;y++){
				i= x;
				j= y;
				inteligencia_compu(i,j,computadora);
			}
		}
		verifica_validez1(i_aux,j_aux,computadora);
		insertar_ficha(i_aux,j_aux,computadora);
		remplaza_imagenes(i_aux,j_aux,computadora);
		mayor=0;
		gchar *temp = g_strdup_printf("Tu rival %s ha insertado una ficha en [%c,%d]", rival,('A'+ i_aux-1) ,j_aux);
		gtk_label_set_text(GTK_LABEL(label_estado), temp);
		g_free(temp);

		gchar *pasa_turno = g_strdup_printf("Turno de %s", nombre);
		gtk_label_set_text(GTK_LABEL(label_turno), pasa_turno);
		g_free(pasa_turno);
	}else{
		//printf("\nNo hay movimiento posible para la computadora. \n");

	}
return 0;
}

void inteligencia_compu(int i, int j,int col){
	int k, x;
	int aux_compu=0;
	int encerrados;
	//Para determinar ficha del que tiene el turno y su contrincante
	char enemy,player;
	printf("\nEntra inteligencia compu");
	if(col==1){
		player='B';
		enemy='N';
	}else{
		player='N';
		enemy='B';
	}
	//si no selecciono una coordenada donde hay letras o numeros
	if(i!=0 && j!=0){
	//Si selecciono un espacio vacio
		if(tablero_c[i][j]==' '){
			//Para arriba
			if(tablero_c[i-1][j]==enemy){//Posibilidad de jugar por verificar arriba arriba
				k=i-1;
				encerrados=0;
				while (tablero_c[k][j]==enemy && k>0){ //Si hay enemigo recorre hasta que haya un player o un espacio
					k--;
					encerrados++;
					if (tablero_c[k][j]==player){ //Si hay player, jugada valida
						for (x=0; x<encerrados; x++){
							aux_compu++;
						}
					}
				}
			}

			//Para abajo
			if(tablero_c[i+1][j]==enemy){ //Posibilidad de jugar por verificar hacia abajo
				k=i+1;
				encerrados=0;
				while (tablero_c[k][j]==enemy && k<9){
					k++;
					encerrados++;
					if (tablero_c[k][j]==player){
						for (x=0; x<encerrados; x++){
							aux_compu++;
						}

					}
				}
			}

			//Para la derecha
			if(tablero_c[i][j+1]==enemy){ //Posibilidad de jugar por verificar la derecha
				k=j+1;
				encerrados=0;
				while (tablero_c[i][k]==enemy && k<9){
					k++;
					encerrados++;
					if (tablero_c[i][k]==player){
						for (x=0; x<encerrados; x++){
							aux_compu++;
						}
					}
				}
			}

			//Para la izquierda
			if(tablero_c[i][j-1]==enemy){ //Posibilidad de jugar por verificar la izquierda
				k=j-1;
				encerrados=0;
				while (tablero_c[i][k]==enemy && k>0){
					k--;
					encerrados++;
					if (tablero_c[i][k]==player){
						for (x=0; x<encerrados; x++){
							aux_compu++;
						}
					}
				}
			}

			//Para diagonal derecha arriba
			if(tablero_c[i-1][j+1]==enemy){ //Posibilidad de jugar por verificar diagonal derecha arriba
				int z;
				k=i-1;
				z=j+1;
				encerrados=0;
				while (tablero_c[k][z]==enemy && k>0 && z<9){
					k--;
					z++;
					encerrados++;
					if (tablero_c[k][z]==player){
						for (x=0; x<encerrados; x++){
							aux_compu++;
						}
					}
				}
			}

			//Para diagonal izquierda arriba
			if(tablero_c[i-1][j-1]==enemy){ //Posibilidad de jugar por verificar diagonal izquierda arriba
				int z;
				k=i-1;
				z=j-1;
				encerrados=0;
				while (tablero_c[k][z]==enemy && k>0 && z>0){
					k--;
					z--;
					encerrados++;
					if (tablero_c[k][z]==player){
						for (x=0; x<encerrados; x++){
							aux_compu++;
						}
					}
				}
			}

			//Para diagonal izquierda abajo
			if(tablero_c[i+1][j-1]==enemy){ //Posibilidad de jugar por verificar diagonal izquierda abajo
				int z;
				k=i+1;
				z=j-1;
				encerrados=0;
				while (tablero_c[k][z]==enemy && k<9 && z>0){
					k++;
					z--;
					encerrados++;
					if (tablero_c[k][z]==player){
						for (x=0; x<encerrados; x++){
							aux_compu++;
						}
					}
				}
			}

			//Para diagonal derecha abajo
			if(tablero_c[i+1][j+1]==enemy){//Posibilidad de jugar por verificar diagonal derecha abajo
				int z;
				k=i+1;
				z=j+1;
				encerrados=0;
				while (tablero_c[k][z]==enemy && k<9 && z<9){
					k++;
					z++;
					encerrados++;
					if (tablero_c[k][z]==player){
						for (x=0; x<encerrados; x++){
							aux_compu++;
						}
					}
				}
			}

			if(aux_compu>0){
				if(mayor<=aux_compu){
					mayor=aux_compu;
					i_aux=i;
					j_aux=j;
				}
			}
		}
	}
	aux_compu=0;
	printf("\nEL MAYOR ES %d",mayor);
}

void verifica_validez1(guint i, guint j,int col){
	printf("\nEntra en verifica validez1");
	printf("\nFILA %d COLUMNA %d",i,j);
	int k,aux=0,auxiliar=0;
	//Para determinar ficha del que tiene el turno y su contrincante
	char enemy,player;
	if(col==1){
		player='B';
		enemy='N';
	}else{
		player='N';
		enemy='B';
	}
	//si no selecciono una coordenada donde hay letras o numeros
	if(i!=0 && j!=0){
		//Si selecciono un espacio vacio
		if(tablero_c[i][j]==' '){
			//Tiene posibilidad de jugar si es que arriba hay enemigo que pueda encerrar
			if(tablero_c[i-1][j]==enemy){
				k=i-1;
				while (tablero_c[k][j]==enemy && k>0){ //Comprueba que todo lo que recorra sea enemigo
					k--;
					if (tablero_c[k][j]==player){ //Hasta encontrar ficha del jugador
						aux=k+1;
						while(tablero_c[aux][j]==enemy){ //Cambia lo que puede encerrar
							printf("\nREMPLAZA 1");
							tablero_c[aux][j]=player;
							remplaza_imagenes(aux,j,col);
							aux++;
							auxiliar++;
						}
					}
				}
			}

			//Tiene posibilidad de jugar si es que abajo hay enemigo que pueda encerrar
			//Hace mismo procedimiento que posibilidad de jugar hacia arriba
			//Recorre filas hacia abajo
			if(tablero_c[i+1][j]==enemy){
				k=i+1;
				while (tablero_c[k][j]==enemy && k<9){
					k++;
					if (tablero_c[k][j]==player){
						aux=k-1;
						while(tablero_c[aux][j]==enemy){
							printf("\nREMPLAZA 2");
							tablero_c[aux][j]=player;
							remplaza_imagenes(aux,j,col);
							aux--;
							auxiliar++;
						}
					}
				}
			}

			//Tiene posibilidad de jugar si es que a la derecha hay enemigo que se pueda encerrar
			//Recorre columnas a la derecha y cambia
			if(tablero_c[i][j+1]==enemy){
				k=j+1;
				while (tablero_c[i][k]==enemy && k<9){
					k++;
					if (tablero_c[i][k]==player){
						aux=k-1;
						while(tablero_c[i][aux]==enemy){
							printf("\nREMPLAZA 3");
							tablero_c[i][aux]=player;
							remplaza_imagenes(i,aux,col);
							aux--;
							auxiliar++;
						}
					}
				}
			}

			//Tiene posibilidad de jugar si es que a la izquierda hay enemigo que pueda encerrar
			//Recorre columnas a la izquiera y cambia de ser posible
			if(tablero_c[i][j-1]==enemy){
				k=j-1;
				while (tablero_c[i][k]==enemy && k>0){
					k--;
					if (tablero_c[i][k]==player){
						aux=k+1;
						while(tablero_c[i][aux]==enemy){
							printf("\nREMPLAZA 4");
							tablero_c[i][aux]=player;
							remplaza_imagenes(i,aux,col);
							aux++;
							auxiliar++;
						}
					}
				}
			}

			//Tiene la posibilidad de jugar si es que en su diagonal derecha arriba hay enemigo que pueda encerrar
			//Recorre diagonal, cambia a favor del jugador de ser posible
			if(tablero_c[i-1][j+1]==enemy){
				int z, aux2;//Variables para poder ubicar columnas a recorrer
				k=i-1;
				z=j+1;
				while (tablero_c[k][z]==enemy && k>0 && z<9){
					k--;
					z++;
					if (tablero_c[k][z]==player){
						aux=k+1;
						aux2=z-1;
						while(tablero_c[aux][aux2]==enemy){
							printf("\nREMPLAZA 5");
							tablero_c[aux][aux2]=player;
							remplaza_imagenes(aux,aux2,col);
							aux++;
							aux2--;
							auxiliar++;
						}
					}
				}
			}

			//Tiene la posibilidad de jugar si es que en su diagonal izquierda arriba hay enemigo que se pueda encerrar.
			//Recorre dicha diagonal, cambia las fichas de ser posible encerrar.
			if(tablero_c[i-1][j-1]==enemy){
				int z, aux2;//Variables para poder ubicar columnas a recorrer.
				k=i-1;
				z=j-1;
				while (tablero_c[k][z]==enemy && k>0 && z>0){
					k--;
					z--;
					if (tablero_c[k][z]==player){
						aux=k+1;
						aux2=z+1;
						while(tablero_c[aux][aux2]==enemy){
							printf("\nREMPLAZA 6");
							tablero_c[aux][aux2]=player;
							remplaza_imagenes(aux,aux2,col);
							aux++;
							aux2++;
							auxiliar++;
						}
					}
				}
			}

			//Tiene la posibilidad de jugar si es que en su diagonal izquierda abajo hay enemigo que se pueda encerrar.
			//Recorre dicha diagonal, cambia las fichas, de ser posible encerrarlas.
			if(tablero_c[i+1][j-1]==enemy){
				int z, aux2;//Variables para poder ubicar columnas a recorrer.
				k=i+1;
				z=j-1;
				while (tablero_c[k][z]==enemy && k<9 && z>0){
					k++;
					z--;
					if (tablero_c[k][z]==player){
						aux=k-1;
						aux2=z+1;
						while(tablero_c[aux][aux2]==enemy){
							printf("\nREMPLAZA 7");
							tablero_c[aux][aux2]=player;
							remplaza_imagenes(aux,aux2,col);
							aux--;
							aux2++;
							auxiliar++;
						}
					}
				}
			}

			//Tiene la posibilidad de jugar si es que en su diagonal derecha abajo hay enemigo que se pueda encerrar.
			//Recorre dicha diagonal, cambia las fichas, de ser posible encerrarlas.
			if(tablero_c[i+1][j+1]==enemy){
				int z, aux2;//Variables para poder ubicar columnas a recorrer
				k=i+1;
				z=j+1;
				while (tablero_c[k][z]==enemy && k<9 && z<9){
					k++;
					z++;
					if (tablero_c[k][z]==player){
						aux=k-1;
						aux2=z-1;
						while(tablero_c[aux][aux2]==enemy){
							printf("\nREMPLAZA 8");
							tablero_c[aux][aux2]=player;
							remplaza_imagenes(aux,aux2,col);
							aux--;
							aux2--;
							auxiliar++;
						}
					}
				}
			}
		}
	}

}

