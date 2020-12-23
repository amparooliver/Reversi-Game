/*
 ============================================================================
 Name        : ReversiGTK.c
 Author      : Amanda Maduro- Amparo Oliver
 Version     :
 Copyright   : Your copyright notice
 Description : REVERSI
 ============================================================================
 */

#include <gtk/gtk.h>
#include "declaraciones.h"
#include <time.h>
#include <unistd.h>

//Un vector de Strings, almacena ubicacion de imagenes
char *imagenes[] = {"./IMG/Imagen1.jpg", "./IMG/santa.jpg", "./IMG/reno.jpg"};
char *imagenes_letras[] = {"./IMG/grinch.jpg","./IMG/a.jpg", "./IMG/b.jpg", "./IMG/c.jpg", "./IMG/d.jpg", "./IMG/e.jpg", "./IMG/f.jpg", "./IMG/g.jpg", "./IMG/h.jpg"};
char *imagenes_nros[] = {"./IMG/uno.jpg","./IMG/dos.jpg", "./IMG/tres.jpg", "./IMG/cuatro.jpg", "./IMG/cinco.jpg", "./IMG/seis.jpg", "./IMG/siete.jpg", "./IMG/ocho.jpg"};


//Para los botones
GtkRadioButton *boton_santa;
GtkRadioButton *boton_reno;
GtkRadioButton *boton_aleatorio_ficha;
GtkRadioButton *boton_aleatorio_turno;
GtkRadioButton *boton_usuario;
GtkRadioButton *boton_computadora;
GtkButton *boton_inicio;
GtkWidget *entry_usuario;
GtkWidget *entry_rival;
GtkButton *boton_humanovscompu;
GtkButton *boton_compuvscompu;
GtkButton *boton_salir_ganaste;
GtkButton *boton_jugar_ganaste;
GtkButton *boton_salir_perdiste;
GtkButton *boton_jugar_perdiste;
GtkButton *boton_salir_empataron;
GtkButton *boton_jugar_empataron;

static void mostrar_ayuda(GtkWidget *widget, gpointer data){
	gtk_dialog_run(GTK_DIALOG(dialogAyuda));
	gtk_widget_hide(GTK_WIDGET(dialogAyuda));
}

static void mostrar_acerca(GtkWidget *widget, gpointer data){
	gtk_dialog_run(GTK_DIALOG(dialogAcerca));
	gtk_widget_hide(GTK_WIDGET(dialogAcerca));
}

static void menu_cerrar(GtkWidget *widget, gpointer data){
	gtk_main_quit();
}

static void menu_estadisticas(GtkWidget *widget, gpointer data){
	impresion_estadisticas();
	gtk_dialog_run(GTK_DIALOG(ventana_estadisticas));
	gtk_widget_hide(GTK_WIDGET(ventana_estadisticas));
}
static void menu_jugar_de_nuevo(GtkWidget *widget, gpointer data){
	gtk_widget_hide(GTK_WIDGET(window));
	main();
}

//Detecta los clicks e imprime en los labels de imagen presionada
void tablero_cb(GtkWidget *event_box, GdkEventButton *event, gpointer data){
	fila = (GUINT_FROM_LE(event->y) / 50); //las imagenes tienen son 50x50pixeles
	columna = (GUINT_FROM_LE(event->x) / 50);

	gchar *temp = g_strdup_printf("Presiono la imagen coordenada [%c,%d]", ('A'+fila-1),columna);
	gtk_label_set_text(GTK_LABEL(label_estado), temp);
	g_free(temp);

	jugar();

}

//Crea el tablero con las fichas iniciales
GtkWidget *crear_tablero(){
	int i, j;

	GtkWidget *auxiliar;

	inicializar_tablero();
	eventbox = gtk_event_box_new();
	tablero = gtk_grid_new();

	for (i = 1; i < MAX_FILA; i++) {
		for (j = 1; j < MAX_COLUMNA; j++) {

				tablero_imagenes[i][j] = gtk_image_new_from_file(imagenes[0]);
				gtk_grid_attach(GTK_GRID(tablero), GTK_WIDGET(tablero_imagenes[i][j]), j, i, 1, 1);

		}
	}

	//Fichas Iniciales
	gtk_image_set_from_file(tablero_imagenes[4][4], "./IMG/santa.jpg");
	gtk_grid_attach(GTK_GRID(tablero), GTK_WIDGET(tablero_imagenes[4][4]), 4, 4, 1, 1);
	gtk_image_set_from_file(tablero_imagenes[5][5], "./IMG/santa.jpg");
	gtk_grid_attach(GTK_GRID(tablero), GTK_WIDGET(tablero_imagenes[5][5]), 5, 5, 1, 1);

	gtk_image_set_from_file(tablero_imagenes[5][4], "./IMG/reno.jpg");
	gtk_grid_attach(GTK_GRID(tablero), GTK_WIDGET(tablero_imagenes[5][4]), 4, 5, 1, 1);
	gtk_image_set_from_file(tablero_imagenes[4][5], "./IMG/reno.jpg");
	gtk_grid_attach(GTK_GRID(tablero), GTK_WIDGET(tablero_imagenes[4][5]), 5, 4, 1, 1);

	for (i = 0; i < MAX_FILA; i++) {
		auxiliar = gtk_image_new_from_file(imagenes_letras[i]);
		gtk_grid_attach(GTK_GRID(tablero), GTK_WIDGET(auxiliar), i, 0, 1, 1);
	}
	for (j = 0; j < MAX_COLUMNA; j++) {
		auxiliar = gtk_image_new_from_file(imagenes_nros[j]);
		gtk_grid_attach(GTK_GRID(tablero), GTK_WIDGET(auxiliar), 0, j+1, 1, 1);
	}

	gtk_container_add(GTK_CONTAINER(eventbox), tablero);
	g_signal_connect(eventbox, "button-press-event", G_CALLBACK(tablero_cb), tablero);
	return eventbox;
}

void boton_santa_pressed(GtkWidget *widget, gpointer data){
	color=1;
	ficha_tipo(color);
}

void boton_reno_pressed(GtkWidget *widget, gpointer data){
	color=2;
	ficha_tipo(color);
}

void boton_usuario_pressed(GtkWidget *widget, gpointer data){
	turno=1;
	turno_orden(turno);
}

void boton_computadora_pressed(GtkWidget *widget, gpointer data){
	turno=2;
	turno_orden(turno);
}

void boton_aleatorio_ficha_pressed(GtkWidget *widget, gpointer data){
	srand(time(NULL));
	color = rand()%(2)+1;
	ficha_tipo(color);
}

void boton_aleatorio_turno_pressed(GtkWidget *widget, gpointer data){
	srand(time(NULL));
	turno = rand()%(2)+1;
	turno_orden(turno);
}
static void enter_callback( GtkWidget *widget, GtkWidget *entry ){
  nombre = gtk_entry_get_text (GTK_ENTRY (entry_usuario));
  printf ("nombre: %s\n", nombre);
}
static void enter_callback2( GtkWidget *widget, GtkWidget *entry ){
  rival = gtk_entry_get_text (GTK_ENTRY (entry_rival));
  printf ("rival: %s\n", rival);
}
//Cuando se aprieta el boton iniciar, dependiendo del modo de juego, se guardan los nombres y se visualiza el tablero
void on_boton_iniciar_clicked(GtkButton *boton_inicio, gpointer data){
	//HUMANO VS COMPUTADORA
	if(modo_juego==0){
		if (color!=0 && turno!=0){
			nombre = gtk_entry_get_text (GTK_ENTRY (entry_usuario));
			//printf ("nombre: %s\n", nombre);

			rival = gtk_entry_get_text (GTK_ENTRY (entry_rival));
			//printf ("rival: %s\n", rival);

			gtk_widget_hide(GTK_WIDGET(ventana_inicial));
			gtk_widget_show_all(window);

			if(turno==2){
				g_timeout_add(1500,turno_computadora,NULL);
			}
		}
	}
	//COMPUTADORA VS COMPUTADORA
	else if(modo_juego==1){
		if (color!=0 && turno!=0){

			//Asociamos los nombres a sus variables
			nombre = gtk_entry_get_text (GTK_ENTRY (entry_usuario));
			rival = gtk_entry_get_text (GTK_ENTRY (entry_rival));

			gtk_widget_hide(GTK_WIDGET(ventana_inicial));
			gtk_widget_show_all(window);

			if(turno==2){
				compu_vs_compu();

			}else if(turno==1){
				secuencia_juego();
			}
		}
	}

	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

}

void boton_modo_humanovscompu(GtkButton *boton_modo, gpointer data){
	gtk_widget_hide(GTK_WIDGET(ventana_modo));
	gtk_widget_show_all(ventana_inicial);
	modo_juego=0;
	g_signal_connect (ventana_inicial, "destroy", G_CALLBACK (gtk_main_quit), NULL);
}
void boton_modo_compuvscompu(GtkButton *boton_modo, gpointer data){
	gtk_button_set_label(GTK_BUTTON(boton_usuario),"COMPUTADORA LOCAL");
	gtk_button_set_label(GTK_BUTTON(boton_computadora),"COMPUTADORA RIVAL");
	modo_juego=1;
	gtk_widget_hide(GTK_WIDGET(ventana_modo));
	gtk_widget_show_all(ventana_inicial);

	g_signal_connect (ventana_inicial, "destroy", G_CALLBACK (gtk_main_quit), NULL);
}

 int main (int argc, char *argv[]){

	color=0;
	turno=0;
    GtkWidget *box_tablero;

    GObject *menu_mostrar_acerca; // identificador del objeto menu item acerca
    GObject *menu_mostrar_ayuda; // identificador del objeto menu item ayuda
    GObject *menu_archivo_cerrar;
    GObject *menu_archivo_estadisticas;
    GObject *menu_archivo_jugar_de_nuevo;

    //Para el GtkBuilder
    guint ret;
    GtkBuilder *builder;
    GError *error = NULL;

    //incializamos elementos de gtk
    gtk_init (&argc, &argv);

	builder = gtk_builder_new();
	//Se carga el builder
	ret = gtk_builder_add_from_file(builder, "tablero.glade", &error);
	if (ret == 0) {
		g_print("Error en la función gtk_builder_add_from_file:\n%s", error->message);
		return 1;
	}
	g_free(error);

	//Ventana tablero
	window = GTK_WIDGET(gtk_builder_get_object(builder, "ventana"));

	//Ventana inicial
	ventana_inicial = GTK_WIDGET(gtk_builder_get_object(builder, "ventana_inicial"));

	//GANASTE
	ventana_ganaste1 = GTK_WIDGET(gtk_builder_get_object(builder, "ventana_ganaste1"));

	//PERDISTE
	ventana_perdiste = GTK_WIDGET(gtk_builder_get_object(builder, "ventana_perdiste"));

	//EMPATARON
	ventana_empataron = GTK_WIDGET(gtk_builder_get_object(builder, "ventana_empataron"));

	//Ventana modo
	ventana_modo= GTK_WIDGET(gtk_builder_get_object(builder, "ventana_modo"));

	//Ventana estadisticas
	ventana_estadisticas= gtk_builder_get_object(builder, "ventana_estadisticas");

	//Botones
	boton_santa = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "boton_santa"));
	boton_reno = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "boton_reno"));
	boton_aleatorio_ficha = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "boton_aleatorio_ficha"));
	boton_usuario = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "boton_usuario"));
	boton_computadora = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "boton_computadora"));
	boton_aleatorio_turno = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "boton_aleatorio_turno"));
	boton_inicio= GTK_BUTTON(gtk_builder_get_object(builder, "boton_iniciar"));
	boton_humanovscompu= GTK_BUTTON(gtk_builder_get_object(builder, "boton_compuvshum"));
	boton_compuvscompu= GTK_BUTTON(gtk_builder_get_object(builder, "boton_compuvscompu"));
	boton_salir_ganaste=GTK_BUTTON(gtk_builder_get_object(builder, "ganaste_salir"));
	boton_salir_perdiste=GTK_BUTTON(gtk_builder_get_object(builder, "boton_perdiste_salir"));

	//estado inicial de los botones
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (boton_santa), TRUE);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (boton_reno), FALSE);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (boton_aleatorio_ficha), FALSE);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (boton_usuario), TRUE);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (boton_computadora), FALSE);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (boton_aleatorio_turno), FALSE);

	//Para entrada de nombre
	entry_usuario = GTK_WIDGET(gtk_builder_get_object(builder, "entry_nombre"));
	entry_rival = GTK_WIDGET(gtk_builder_get_object(builder, "entry_nombre_rival"));

	//Señales de los botones
	g_signal_connect(G_OBJECT(boton_santa), "clicked", G_CALLBACK(boton_santa_pressed), NULL);
	g_signal_connect(G_OBJECT(boton_reno), "clicked", G_CALLBACK(boton_reno_pressed), NULL);
	g_signal_connect(G_OBJECT(boton_aleatorio_ficha), "clicked", G_CALLBACK(boton_aleatorio_ficha_pressed), NULL);
	g_signal_connect(G_OBJECT(boton_usuario), "clicked", G_CALLBACK(boton_usuario_pressed), NULL);
	g_signal_connect(G_OBJECT(boton_computadora), "clicked", G_CALLBACK(boton_computadora_pressed), NULL);
	g_signal_connect(entry_usuario, "activate", G_CALLBACK (enter_callback), NULL);
	g_signal_connect(entry_rival, "activate", G_CALLBACK (enter_callback2), NULL);
	g_signal_connect(G_OBJECT(boton_aleatorio_turno), "clicked", G_CALLBACK(boton_aleatorio_turno_pressed), NULL);
	g_signal_connect(G_OBJECT(boton_inicio), "clicked", G_CALLBACK(on_boton_iniciar_clicked), NULL);
	g_signal_connect(G_OBJECT(boton_humanovscompu), "clicked", G_CALLBACK(boton_modo_humanovscompu), NULL);
	g_signal_connect(G_OBJECT(boton_compuvscompu), "clicked", G_CALLBACK(boton_modo_compuvscompu), NULL);
	g_signal_connect(G_OBJECT(boton_salir_ganaste), "clicked", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(boton_salir_perdiste), "clicked", G_CALLBACK(gtk_main_quit), NULL);


	/* Conectamos las señales a los callbacks correspondientes */

	//Cuadros de diálogo
	dialogAyuda = gtk_builder_get_object(builder, "ayuda_reversi");// leemos la ventana de diálogo de ayuda para el juego
	dialogAcerca = gtk_builder_get_object(builder, "acerca_reversi");

	//Opciones de menú en ventana tablero "window"
	menu_mostrar_ayuda = gtk_builder_get_object(builder, "imagen_ayuda");
	g_signal_connect(menu_mostrar_ayuda, "activate", G_CALLBACK (mostrar_ayuda), NULL);
	menu_mostrar_acerca = gtk_builder_get_object(builder, "imagen_acerca");
	g_signal_connect(menu_mostrar_acerca, "activate", G_CALLBACK (mostrar_acerca), NULL);
	menu_archivo_cerrar = gtk_builder_get_object(builder, "imagen_cerrar");
	g_signal_connect(menu_archivo_cerrar, "activate", G_CALLBACK (menu_cerrar), NULL);
	menu_archivo_estadisticas = gtk_builder_get_object(builder, "imagen_estadisticas");
	g_signal_connect(menu_archivo_estadisticas, "activate", G_CALLBACK (menu_estadisticas), NULL);
	menu_archivo_jugar_de_nuevo = gtk_builder_get_object(builder, "imagen_jugar_de_nuevo");
	g_signal_connect(menu_archivo_jugar_de_nuevo, "activate", G_CALLBACK (menu_jugar_de_nuevo), NULL);

	//Box donde estara el Tablero
	box_tablero = GTK_WIDGET(gtk_builder_get_object(builder, "box_tablero2"));

	//Labels
	label_turno = GTK_WIDGET(gtk_builder_get_object(builder, "label_turno"));
	label_estado = GTK_WIDGET(gtk_builder_get_object(builder, "label_estado"));
	label_resultados1 = GTK_WIDGET(gtk_builder_get_object(builder, "resultados"));
	label_resultados2 = GTK_WIDGET(gtk_builder_get_object(builder, "label_resultados2"));
	label_estadisticas = GTK_WIDGET(gtk_builder_get_object(builder, "label_estadisticas"));

	gtk_box_pack_start(GTK_BOX(box_tablero), crear_tablero(), TRUE, FALSE, 20);

    /* Connect the destroy signal of the window to gtk_main_quit
     * When the window is about to be destroyed we get a notification and
     * stop the main GTK+ loop
     */
    g_signal_connect (ventana_modo, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    /* make sure that everything, window and label, are visible */
    gtk_widget_show_all (ventana_modo);

    /* start the main loop, and let it rest there until the application is closed */
    gtk_main ();

    return 0;
}

