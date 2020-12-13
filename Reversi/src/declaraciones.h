#include <gtk/gtk.h>
#define MAX_FILA 9
#define MAX_COLUMNA 9

guint fila;
guint columna;
GObject *dialogAyuda; // identificador de la ventana de diálogo de ayuda al juego
GObject *dialogAcerca;
GtkWidget *tablero_imagenes[MAX_FILA][MAX_COLUMNA];
GtkWidget *label_turno;
GtkWidget *label_estado;
GtkWidget *label_resultados1;
GtkWidget *label_resultados2;
GtkWidget *label_resultados3;
GtkWidget *label_estadisticas;
GtkWidget *tablero;
GtkWidget *eventbox;
GtkWidget *ventana_modo;
GtkWidget *window;
GtkWidget *ventana_inicial;
GtkWidget *ventana_perdiste;
GtkWidget *ventana_ganaste;
GtkWidget *ventana_ganaste1;
GtkWidget *ventana_empataron;
GtkWidget *ventana_estadisticas;
GtkWidget *ficha1;
GtkWidget *ficha2;
const gchar *nombre;
const gchar *rival;


//VARIABLES
int color, computadora, jugador, turno, i, j;
int gano;
//char usuario[20];
//int f,c;
char buffer;
char tablero_c[9][9];
struct statistics{
  char nombre_estadisticas[20];
  int parJugadas;
  int parGanadas;
  int parPerdidas;
};

//FUNCIONES
//void menu();
void inicializar_tablero();
//void imprimir_tablero();
void ficha_tipo (int color);
void turno_orden(int turno);
int juego_terminado();
int turno_computadora();
int turno_jugador();
void insertar_ficha(int f, int c, int col);
int verifica_validez(guint i,guint j, int col);
void verifica_validez1(guint i,guint j, int col);
int jugadas_posibles(int i,int j, int col);
void inteligencia_compu(int i,int j, int col);
int pierde_turno(int col);
void puntos(int col);
void remplaza_imagenes(int i, int j, int col);
void jugar();
int impresion_estadisticas();
void ordenar(int nroPalabras, struct statistics *ptr);
void impresion_estadisticas_enGTK(struct statistics *ptr);
int actualizacion_estadisticas();

