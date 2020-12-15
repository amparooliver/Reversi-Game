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
	int aux_compu=0; //Contador de cuantos ENEMY puede encerrar en total
	int encerrados; //Contador de cuantos ENEMY puede encerrar de forma horizontal/vertical/diagonal
	char enemy,player;

	//Para determinar ficha del que tiene el turno y su contrincante
	if(col==1){
		player='B';
		enemy='N';
	}else{
		player='N';
		enemy='B';
	}

	//Si es una casilla distinta de letras o numeros del tablero
	if(i!=0 && j!=0){
	//Si es una casilla vacia
		if(tablero_c[i][j]==' '){
			//Si puede comer HACIA ARRIBA
			if(tablero_c[i-1][j]==enemy){
				k=i-1;
				encerrados=0;
				while (tablero_c[k][j]==enemy && k>0){ //Si hay un ENEMY recorre hasta que haya un PLAYER o una casilla VACIA
					k--;
					encerrados++;
					if (tablero_c[k][j]==player){ //Si hay PLAYER --> jugada valida
						for (x=0; x<encerrados; x++){
							aux_compu++;
						}
					}
				}
			}

			//Si puede comer HACIA ABAJO
			if(tablero_c[i+1][j]==enemy){
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

			//Si puede comer HACIA LA DERECHA
			if(tablero_c[i][j+1]==enemy){
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

			//Si puede comer HACIA LA IZQUIERDA
			if(tablero_c[i][j-1]==enemy){
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

			//Si puede comer en DIAGONAL DERECHA ARRIBA
			if(tablero_c[i-1][j+1]==enemy){
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

			//Si puede comer en DIAGONAL IZQUIERDA ARRIBA
			if(tablero_c[i-1][j-1]==enemy){
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

			//Si puede comer en DIAGONAL IZQUIERDA ABAJO
			if(tablero_c[i+1][j-1]==enemy){
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

			//Si puede comer en DIAGONAL DERECHA ABAJO
			if(tablero_c[i+1][j+1]==enemy){
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
			//Guarda las coordenadas con mayor posibilidad de comer
			if(aux_compu>0){
				if(mayor<=aux_compu){
					mayor=aux_compu;
					i_aux=i;
					j_aux=j;
				}
			}
		}
	}

	//Reiniciamos el contador para la proxima coordenada
	aux_compu=0;
}

void verifica_validez1(guint i, guint j,int col){
	int k,aux=0;
	char enemy,player;

	//Para determinar ficha del que tiene el turno y su contrincante
	if(col==1){
		player='B';
		enemy='N';
	}else{
		player='N';
		enemy='B';
	}

	//si no selecciono una coordenada donde hay letras o numeros
	if(i!=0 && j!=0){
		//Si es una casilla vacia
		if(tablero_c[i][j]==' '){
			//Si puede comer HACIA ARRIBA
			if(tablero_c[i-1][j]==enemy){
				k=i-1;
				while (tablero_c[k][j]==enemy && k>0){ //Si hay un ENEMY recorre hasta que haya un PLAYER o una casilla VACIA
					k--;
					if (tablero_c[k][j]==player){ //Si hay PLAYER --> jugada valida
						aux=k+1;
						while(tablero_c[aux][j]==enemy){
							tablero_c[aux][j]=player;
							remplaza_imagenes(aux,j,col);
							aux++;
						}
					}
				}
			}

			//Si puede comer HACIA ABAJO
			if(tablero_c[i+1][j]==enemy){
				k=i+1;
				while (tablero_c[k][j]==enemy && k<9){
					k++;
					if (tablero_c[k][j]==player){
						aux=k-1;
						while(tablero_c[aux][j]==enemy){
							tablero_c[aux][j]=player;
							remplaza_imagenes(aux,j,col);
							aux--;
						}
					}
				}
			}

			//Si puede comer HACIA LA DERECHA
			if(tablero_c[i][j+1]==enemy){
				k=j+1;
				while (tablero_c[i][k]==enemy && k<9){
					k++;
					if (tablero_c[i][k]==player){
						aux=k-1;
						while(tablero_c[i][aux]==enemy){
							tablero_c[i][aux]=player;
							remplaza_imagenes(i,aux,col);
							aux--;
						}
					}
				}
			}

			//Si puede comer HACIA LA IZQUIERDA
			if(tablero_c[i][j-1]==enemy){
				k=j-1;
				while (tablero_c[i][k]==enemy && k>0){
					k--;
					if (tablero_c[i][k]==player){
						aux=k+1;
						while(tablero_c[i][aux]==enemy){
							tablero_c[i][aux]=player;
							remplaza_imagenes(i,aux,col);
							aux++;
						}
					}
				}
			}

			//Si puede comer en DIAGONAL DERECHA ARRIBA
			if(tablero_c[i-1][j+1]==enemy){
				int z, aux2;
				k=i-1;
				z=j+1;
				while (tablero_c[k][z]==enemy && k>0 && z<9){
					k--;
					z++;
					if (tablero_c[k][z]==player){
						aux=k+1;
						aux2=z-1;
						while(tablero_c[aux][aux2]==enemy){
							tablero_c[aux][aux2]=player;
							remplaza_imagenes(aux,aux2,col);
							aux++;
							aux2--;
						}
					}
				}
			}

			//Si puede comer en DIAGONAL IZQUIERDA ARRIBA
			if(tablero_c[i-1][j-1]==enemy){
				int z, aux2;
				k=i-1;
				z=j-1;
				while (tablero_c[k][z]==enemy && k>0 && z>0){
					k--;
					z--;
					if (tablero_c[k][z]==player){
						aux=k+1;
						aux2=z+1;
						while(tablero_c[aux][aux2]==enemy){
							tablero_c[aux][aux2]=player;
							remplaza_imagenes(aux,aux2,col);
							aux++;
							aux2++;
						}
					}
				}
			}

			//Si puede comer en DIAGONAL IZQUIERDA ABAJO
			if(tablero_c[i+1][j-1]==enemy){
				int z, aux2;
				k=i+1;
				z=j-1;
				while (tablero_c[k][z]==enemy && k<9 && z>0){
					k++;
					z--;
					if (tablero_c[k][z]==player){
						aux=k-1;
						aux2=z+1;
						while(tablero_c[aux][aux2]==enemy){
							tablero_c[aux][aux2]=player;
							remplaza_imagenes(aux,aux2,col);
							aux--;
							aux2++;
						}
					}
				}
			}

			//Si puede comer en DIAGONAL DERECHA ABAJO
			if(tablero_c[i+1][j+1]==enemy){
				int z, aux2;
				k=i+1;
				z=j+1;
				while (tablero_c[k][z]==enemy && k<9 && z<9){
					k++;
					z++;
					if (tablero_c[k][z]==player){
						aux=k-1;
						aux2=z-1;
						while(tablero_c[aux][aux2]==enemy){
							tablero_c[aux][aux2]=player;
							remplaza_imagenes(aux,aux2,col);
							aux--;
							aux2--;
						}
					}
				}
			}
		}
	}

}

