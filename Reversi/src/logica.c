#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "declaraciones.h"
#include <gtk/gtk.h>

void jugar(){
	int aux;
	if(juego_terminado()==FALSE){
		aux=turno_jugador();
		if(aux==TRUE){
			printf("entra en jugar compu");
			g_timeout_add(1500,turno_computadora,NULL);
		}
	}
	if(juego_terminado()==TRUE){
		puntos(jugador);
	}
	printf("sale de la funcion jugar");

}
void inicializar_tablero() {
    int i, j;

    for(i=0 ; i<9 ; ++i) {
        for (j = 0; j < 9; ++j)
            tablero_c[i][j] = ' ';
    }

   	tablero_c[4][4]= 'B';
    tablero_c[4][5]= 'N';
    tablero_c[5][4]= 'N';
    tablero_c[5][5]= 'B';

}

void ficha_tipo(int color){
	if(color==1){
		jugador= 1;
		computadora= 2;
		printf("\nEres Santa!\n");
	}else if(color==2){
		jugador= 2;
		computadora=1;
		printf("\nEres Reno!\n");
	}
}

void turno_orden(int turno){
	if(turno==1){
		printf("\nUsted tiene el 1er turno!\n");
	}else if(turno==2){
		printf("\nLa computadora tiene el 1er turno!\n");
	}
}


int turno_jugador(){
	printf("\nEntra en turno jugador");
	gchar *turno_de = g_strdup_printf("Turno de: %s", nombre);
	gtk_label_set_text(GTK_LABEL(label_turno), turno_de);
	g_free(turno_de);
	if(pierde_turno(jugador)==FALSE){
		printf("\nEntra en el primer if de turno jugador");

		if (verifica_validez(fila, columna, jugador)==TRUE){
			printf("\ninserta la ficha");
			insertar_ficha(fila,columna,jugador);
			remplaza_imagenes(fila,columna,jugador);
			gchar *temp = g_strdup_printf("Presiono la imagen coordenada [%c,%d]", ('A'+fila-1),columna);
			gtk_label_set_text(GTK_LABEL(label_estado), temp);
			g_free(temp);
			gchar *pasa_turno = g_strdup_printf("Turno de la computadora %s",rival);
			gtk_label_set_text(GTK_LABEL(label_turno), pasa_turno);
			g_free(pasa_turno);

			return TRUE;
		}
		else if (verifica_validez(fila, columna, jugador)==FALSE){
			gchar *temp = g_strdup_printf("Casilla Invalida [%c,%d]", ('A'+fila-1),columna);
			gtk_label_set_text(GTK_LABEL(label_estado), temp);
			g_free(temp);

			return FALSE;
		}


	}else{
		printf("\nNo hay movimiento posible. \n");
		return TRUE;

	}

	return TRUE;


}


void insertar_ficha(int f, int c, int col)
{
	if(col==1){
		tablero_c[f][c] = 'B';
	}else if(col==2){
		tablero_c[f][c] = 'N';
	}

}

int verifica_validez(guint i, guint j,int col){
	printf("\nEntra en verifica validez");
	printf("\nFILA %d COLUMNA %d",i,j);
	int k,aux=0,auxiliar=0;;
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
							tablero_c[aux][aux2]=player;
							remplaza_imagenes(aux,aux2,col);
							aux--;
							aux2--;
							auxiliar++;
						}
					}
				}
			}

			if(auxiliar>0){ //Si ingresa en una de las posibilidades anteriores, entonces hay jugada posible.
				return TRUE;
			}
			else{ //No hay posibilidad de jugar en ese lugar
				return FALSE;
			}
		}else{
			return FALSE;
		}
	}else{
		return FALSE;
	}
}

int juego_terminado(){
	printf("Entra en juego terminado");
	int aux1,aux2;
	aux1=pierde_turno(1);
	aux2=pierde_turno(2);
	//Termina si ninguno de los dos tienen jugadas posibles
	if(aux1==TRUE && aux2==TRUE){
		//puntos(jugador);
		return TRUE;
	}else{
		return FALSE;
	}
}
int pierde_turno(int col){
	int i,j,aux=0;
	for(i=1; i<9 ;i++){
		for(j=1; j<9;j++){
			if (jugadas_posibles(i,j,col)==TRUE){
				aux++;
			}
		}
	}
	if(aux>0){
		return FALSE;
	}else{
		return TRUE;
	}
}
int jugadas_posibles(int i, int j,int col){
	int k,auxiliar=0;;
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
			//Para arriba
			if(tablero_c[i-1][j]==enemy){//Posibilidad de jugar por verificar arriba arriba
				k=i-1;
				while (tablero_c[k][j]==enemy && k>0){ //Si hay enemigo recorre hasta que haya un player o un espacio
					k--;
					if (tablero_c[k][j]==player){ //Si hay player, jugada valida
						auxiliar++;
					}
				}
			}

			//Para abajo
			if(tablero_c[i+1][j]==enemy){ //Posibilidad de jugar por verificar hacia abajo
				k=i+1;
				while (tablero_c[k][j]==enemy && k<9){
					k++;
					if (tablero_c[k][j]==player){
							auxiliar++;

					}
				}
			}

			//Para la derecha
			if(tablero_c[i][j+1]==enemy){ //Posibilidad de jugar por verificar la derecha
				k=j+1;
				while (tablero_c[i][k]==enemy && k<9){
					k++;
					if (tablero_c[i][k]==player){
						auxiliar++;
					}
				}
			}

			//Para la izquierda
			if(tablero_c[i][j-1]==enemy){ //Posibilidad de jugar por verificar la izquierda
				k=j-1;
				while (tablero_c[i][k]==enemy && k>0){
					k--;
					if (tablero_c[i][k]==player){
						auxiliar++;
					}
				}
			}

			//Para diagonal derecha arriba
			if(tablero_c[i-1][j+1]==enemy){ //Posibilidad de jugar por verificar diagonal derecha arriba
				int z;
				k=i-1;
				z=j+1;
				while (tablero_c[k][z]==enemy && k>0 && z<9){
					k--;
					z++;
					if (tablero_c[k][z]==player){
						auxiliar++;
					}
				}
			}

			//Para diagonal izquierda arriba
			if(tablero_c[i-1][j-1]==enemy){ //Posibilidad de jugar por verificar diagonal izquierda arriba
				int z;
				k=i-1;
				z=j-1;
				while (tablero_c[k][z]==enemy && k>0 && z>0){
					k--;
					z--;
					if (tablero_c[k][z]==player){
							auxiliar++;
					}
				}
			}

			//Para diagonal izquierda abajo
			if(tablero_c[i+1][j-1]==enemy){ //Posibilidad de jugar por verificar diagonal izquierda abajo
				int z;
				k=i+1;
				z=j-1;
				while (tablero_c[k][z]==enemy && k<9 && z>0){
					k++;
					z--;
					if (tablero_c[k][z]==player){
						auxiliar++;
					}
				}
			}

			//Para diagonal derecha abajo
			if(tablero_c[i+1][j+1]==enemy){//Posibilidad de jugar por verificar diagonal derecha abajo
				int z;
				k=i+1;
				z=j+1;
				while (tablero_c[k][z]==enemy && k<9 && z<9){
					k++;
					z++;
					if (tablero_c[k][z]==player){
							auxiliar++;
					}
				}
			}

			if(auxiliar>0){
				return TRUE;
			}
			else{ //No hay posibilidad de jugar en ese lugar
				return FALSE;
			}
		}else{
			return FALSE;
		}
	}else{
		return FALSE;
	}
}

void remplaza_imagenes(int i, int j, int col){
	if(col==1){
		gtk_image_set_from_file(tablero_imagenes[i][j], "./IMG/santa.jpg");
		gtk_grid_attach(GTK_GRID(tablero), GTK_WIDGET(tablero_imagenes[i][j]), j, i, 1, 1);
	}
	else if(col==2){
		gtk_image_set_from_file(tablero_imagenes[i][j], "./IMG/reno.jpg");
		gtk_grid_attach(GTK_GRID(tablero), GTK_WIDGET(tablero_imagenes[i][j]), j, i, 1, 1);
	}
}

void puntos(int col){
	int blancas=0, negras=0;
	int i, j;
	for (i=1; i<9; i++){
		for (j=1; j<9; j++){
			if (tablero_c[i][j]=='B'){
				blancas++;
			}
			if (tablero_c[i][j]=='N'){
				negras++;
			}
		}
	}
	printf ("\n Puntos obtenidos: \n Blancas: %d\n Negras: %d\n", blancas, negras);


	if(blancas>negras){
		if (col==1){
			printf("FELICIDADES GANASTE \n");
			gano=1;
			gtk_widget_hide(GTK_WIDGET(window));
			gtk_widget_show(ventana_ganaste1);


			gchar *ganador1 = g_strdup_printf("JOJOJO! FELICIDADES %s!\n SANTA: %d puntos\n RENO: %d puntos", nombre, blancas, negras);
			gtk_label_set_text(GTK_LABEL(label_resultados1), ganador1);
			g_free(ganador1);

			actualizacion_estadisticas();
			g_signal_connect (ventana_ganaste1, "destroy", G_CALLBACK (gtk_main_quit), NULL);
		}
		else{
			printf("COMPUTADORA GANA \n");
			gano=0;
			gtk_widget_hide(GTK_WIDGET(window));
			gtk_widget_show(GTK_WIDGET(ventana_perdiste));


			gchar *perdedor1 = g_strdup_printf("SERA LA PROXIMA :( %s!\n SANTA: %d puntos\n RENO: %d puntos", nombre, blancas, negras);
			gtk_label_set_text(GTK_LABEL(label_resultados2), perdedor1);
			g_free(perdedor1);
			actualizacion_estadisticas();
			g_signal_connect (ventana_perdiste, "destroy", G_CALLBACK (gtk_main_quit), NULL);
		}
	}
	else if(negras>blancas){
		if (col==1){
			printf("COMPUTADORA GANA \n");
			gano=0;
			gtk_widget_hide(GTK_WIDGET(window));
			gtk_widget_show(GTK_WIDGET(ventana_perdiste));


			gchar *perdedor1 = g_strdup_printf("SERA LA PROXIMA %s!\n SANTA: %d puntos\n RENO: %d puntos", nombre, blancas, negras);
			gtk_label_set_text(GTK_LABEL(label_resultados2), perdedor1);
			g_free(perdedor1);

			g_signal_connect (ventana_perdiste, "destroy", G_CALLBACK (gtk_main_quit), NULL);
		}
		else{
			printf("FELICIDADES GANASTE \n");
			gano=1;

			gtk_widget_hide(GTK_WIDGET(window));
			gtk_widget_show(GTK_WIDGET(ventana_ganaste1));


			gchar *ganador1 = g_strdup_printf("JOJOJO! FELICIDADES %s!\n SANTA: %d puntos\n RENO: %d puntos", nombre, blancas, negras);
			gtk_label_set_text(GTK_LABEL(label_resultados1), ganador1);
			g_free(ganador1);

			g_signal_connect (ventana_ganaste1, "destroy", G_CALLBACK (gtk_main_quit), NULL);
		}
	}
	if(blancas==negras){
		gtk_widget_hide(GTK_WIDGET(window));
		gtk_widget_show(GTK_WIDGET(ventana_empataron));


		gano=2;
		gchar *empataron = g_strdup_printf("QUE LOCURA %s!\n SANTA: %d puntos\n RENO: %d puntos", nombre, blancas, negras);
		gtk_label_set_text(GTK_LABEL(label_resultados3), empataron);
		g_free(empataron);
		g_signal_connect (ventana_empataron, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	}

	actualizacion_estadisticas();

}




