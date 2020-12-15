#include <gtk/gtk.h>
#define MAX_FILA 9
#define MAX_COLUMNA 9


GObject *dialogAyuda; // identificador de la ventana de diálogo AYUDA
GObject *dialogAcerca; // identificador de la ventana de diálogo ACERCA

//LABELS
GtkWidget *label_turno;
GtkWidget *label_estado;
GtkWidget *label_resultados1;
GtkWidget *label_resultados2;
GtkWidget *label_resultados3;
GtkWidget *label_estadisticas;

//TABLERO
GtkWidget *tablero_imagenes[MAX_FILA][MAX_COLUMNA];
GtkWidget *tablero;
GtkWidget *eventbox;
GtkWidget *ficha1;
GtkWidget *ficha2;
const gchar *nombre;
const gchar *rival;
guint fila;
guint columna;

//VENTANAS
GtkWidget *ventana_modo;
GtkWidget *window;
GtkWidget *ventana_inicial;
GtkWidget *ventana_perdiste;
GtkWidget *ventana_ganaste;
GtkWidget *ventana_ganaste1;
GtkWidget *ventana_empataron;
GtkWidget *ventana_estadisticas;

//VARIABLES DE LOGICA, INTELIGENCIA, ESTADISTICAS
int color, computadora, jugador, turno, i, j;
int gano;
char buffer;
char tablero_c[9][9];
struct statistics{
  char nombre_estadisticas[20];
  int parJugadas;
  int parGanadas;
  int parPerdidas;
};

//FUNCIONES
void inicializar_tablero();
void ficha_tipo (int color);
void turno_orden(int turno);
int juego_terminado();
int turno_computadora();
int turno_jugador();
void insertar_ficha(int f, int c, int col); //Inserta la ficha seleccionada
int verifica_validez(guint i,guint j, int col); //Verifica y remplaza los ENEMY del jugador
void verifica_validez1(guint i,guint j, int col); //Reemplaza los ENEMY encerrados de la compu en el tablero_C
int jugadas_posibles(int i,int j, int col);
void inteligencia_compu(int i,int j, int col); //Obtiene las coordenadas con mayor posibilidad de encierro
int pierde_turno(int col);// Verifica si (Usuario/Compu) pierde el turno o no
void puntos(int col); //Contador de fichas en el tablero
void remplaza_imagenes(int i, int j, int col); //Actualiza las imagenes del tablero GTK
void jugar();
int impresion_estadisticas(); //Lee el txt y crea el struct statistics
void ordenar(int nroPalabras, struct statistics *ptr); //Ordena el struct statistics en Partidas Ganadas (De mayor a menor)
void impresion_estadisticas_enGTK(struct statistics *ptr,int nroPalabras); //Imprime en ventana GTK los top 10 jugadores
int actualizacion_estadisticas(); //Actualiza el archivo txt

