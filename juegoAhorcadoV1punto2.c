#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define MAX_INTENTOS 6
#define MAX_LONGITUD 50

// === ESTRUCTURA DE JUGADOR ===
typedef struct Jugador {
    char nombre[50];
    int jugadas;
    int ganadas;
    int perdidas;
    struct Jugador *siguiente;
} Jugador;

Jugador *listaJugadores = NULL;
char nombreJugador[50];

// === FUNCIONES DE GESTION DE JUGADORES ===
Jugador *buscarJugador(char nombre[]) {
    Jugador *actual = listaJugadores;
    while (actual != NULL) {
        if (strcmp(actual->nombre, nombre) == 0) return actual;
        actual = actual->siguiente;
    }
    return NULL;
}

void agregarOActualizarJugador(char nombre[], int gano) {
    Jugador *jugador = buscarJugador(nombre);
    if (jugador == NULL) {
        jugador = (Jugador *)malloc(sizeof(Jugador));
        strcpy(jugador->nombre, nombre);
        jugador->jugadas = jugador->ganadas = jugador->perdidas = 0;
        jugador->siguiente = listaJugadores;
        listaJugadores = jugador;
    }
    jugador->jugadas++;
    if (gano) jugador->ganadas++;
    else jugador->perdidas++;
}

void guardarEstadisticasEnArchivo() {
    FILE *archivo = fopen("estadisticas.txt", "w");
    if (archivo == NULL) return;

    Jugador *actual = listaJugadores;
    while (actual != NULL) {
        fprintf(archivo, "%s,%d,%d,%d\n", actual->nombre, actual->jugadas, actual->ganadas, actual->perdidas);
        actual = actual->siguiente;
    }
    fclose(archivo);
}

void liberarJugadores() {
    Jugador *actual = listaJugadores;
    while (actual != NULL) {
        Jugador *temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    listaJugadores = NULL;
}

// === FUNCIONES DE SONIDO ===
void sonidoExito() {
    Beep(1000, 200); // Do
    Beep(1200, 200); // Re
    Beep(1400, 200); // Mi
    Beep(1600, 300); // Fa (más largo para cierre)
}

void sonidoFracaso() {
    Beep(400, 500);  // Nota grave
    Beep(300, 500);  // Más grave
    Beep(200, 600);  // Aún más grave y prolongado
}

// === FUNCIONES DE JUEGO ===
void dibujarAhorcado(int intentos) {
    const char *estados[] = {
        "  +---+\n  |   |\n  |     \n  |     \n  |     \n  |     \n========\n",
        "  +---+\n  |   |\n  |   😐\n  |     \n  |     \n  |     \n========\n",
        "  +---+\n  |   |\n  |   😮\n  |   | \n  |     \n  |     \n========\n",
        "  +---+\n  |   |\n  |   😮\n  |  /| \n  |     \n  |     \n========\n",
        "  +---+\n  |   |\n  |   😮\n  |  /|\\\n  |     \n  |     \n========\n",
        "  +---+\n  |   |\n  |   😵\n  |  /|\\\n  |  /   \n  |     \n========\n",
        "  +---+\n  |   |\n  |   💀\n  |  /|\\\n  |  / \\\n  |     \n========\n"
    };
    printf("%s", estados[intentos]);
}

void mostrarEstado(char palabra[], int descubiertas[]) {
    printf("\nPalabra: ");
    for (int i = 0; palabra[i] != '\0'; i++) {
        if (palabra[i] == ' ') {
            printf("  ");
        } else if (descubiertas[i]) {
            printf("%c ", palabra[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int letraYaIngresada(char letra, char letras[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        if (letras[i] == letra)
            return 1;
    }
    return 0;
}

void leerPalabraOculta(char palabra[]) {
    char c;
    int i = 0;
    printf("Jugador que escribe, ingresa la palabra: ");
    while (i < MAX_LONGITUD - 1) {
        c = getch(); // Captura la tecla sin mostrarla
        if (c == '\r' || c == '\n') { // Enter para terminar
            if (i == 0) {
                printf("\n¡La palabra no puede estar vacía!\n");
                printf("Jugador que escribe, ingresa la palabra: ");
                continue;
            }
            break;
        }
        if (c == 8) { // Tecla de retroceso (Backspace)
            if (i > 0) { // Si hay caracteres para borrar
                i--; // Retrocede el índice
                printf("\b \b"); // Mueve cursor atrás, escribe espacio, mueve cursor atrás
            }
            continue;
        }
        if (isalpha(c) || c == ' ') { // Solo letras y espacios
            palabra[i++] = c;
            printf("*");
        } else {
            printf("\nSolo se permiten letras y espacios.\n");
            printf("Jugador que escribe, ingresa la palabra: ");
            for (int j = 0; j < i; j++) {
                printf("*"); // Reimprime los * para mantener la visualización
            }
        }
    }
    palabra[i] = '\0';
    printf("\n");
    system("cls");
}

int jugar(char palabra[], int nivel) {
    int descubiertas[MAX_LONGITUD];
    char letrasUsadas[26];
    int usadas = 0, aciertos = 0, intentos = 0;

    int longitud = strlen(palabra);
    for (int i = 0; i < longitud; i++) {
        palabra[i] = toupper(palabra[i]);
        descubiertas[i] = (palabra[i] == ' ') ? 1 : 0;
        if (palabra[i] == ' ')
            aciertos++;
    }

    while (intentos < MAX_INTENTOS && aciertos < longitud) {
        system("cls");
        dibujarAhorcado(intentos);
        mostrarEstado(palabra, descubiertas);
        printf("Intentos restantes: %d\n", MAX_INTENTOS - intentos);
        printf("Letras usadas: ");
        for (int i = 0; i < usadas; i++) printf("%c ", letrasUsadas[i]);
        printf("\nIngrese una letra o palabra completa: ");

        char entrada[MAX_LONGITUD];
        fgets(entrada, MAX_LONGITUD, stdin);
        entrada[strcspn(entrada, "\n")] = '\0';

        for (int i = 0; entrada[i]; i++) {
            entrada[i] = toupper(entrada[i]);
        }

        if (strlen(entrada) > 1) {
            if (strcmp(entrada, palabra) == 0) {
                system("cls");
                dibujarAhorcado(intentos);
                printf("🎉 Ganaste! La palabra era: %s\n", palabra);
                sonidoExito();
                getch();
                return 1;
            } else {
                system("cls");
                dibujarAhorcado(MAX_INTENTOS);
                printf("💀 Perdiste. La palabra era: %s\n", palabra);
                sonidoFracaso();
                getch();
                return 0;
            }
        }

        char letra = entrada[0];
        if (!isalpha(letra)) {
            printf("Letra inválida.\n");
            getch();
            continue;
        }

        if (letraYaIngresada(letra, letrasUsadas, usadas)) {
            printf("Ya intentaste esa letra.\n");
            getch();
            continue;
        }

        letrasUsadas[usadas++] = letra;

        int encontrado = 0;
        for (int i = 0; i < longitud; i++) {
            if (palabra[i] == letra && !descubiertas[i]) {
                descubiertas[i] = 1;
                aciertos++;
                encontrado = 1;
            }
        }

        if (!encontrado) {
            intentos++;
        }
    }

    system("cls");
    dibujarAhorcado(intentos);
    if (aciertos == longitud) {
        printf("🎉 Ganaste! La palabra era: %s\n", palabra);
        sonidoExito();
        getch();
        return 1;
    } else {
        printf("💀 Perdiste. La palabra era: %s\n", palabra);
        sonidoFracaso();
        getch();
        return 0;
    }
}

void juegoUnJugador() {
    const char *palabras[] = {
        "COMPUTADORA", "VARIABLE", "PROGRAMACION", "BIBLIOTECA", "AHORCADO","SODASTEREO","NETFLIX","INSTAGRAM","FACEBOOK","MONTAÑAS","ARGENTINA","TWITTER","GUITARRA","PIANO","ESTUDIANTES",
        "CELULAR", "CAMPERA", "TECLADO", "PELOTA", "SUPERCALIFRAGILISTICOESPIALIDOSO","CIENCIAS","GRUPOS","COMISION","HARDWARE","SOFTWARE","MATE","PAPASFRITAS","MENESTER","METALLICA","MARADONA","MEDIALUNAS","STREAMING", "INTELIGENCIA ARTIFICIAL",
        "MESSIRVE","LATINOAMERICA","PLAYSTATION","BUENOS AIRES","AURICULARES","TORTAFRITA","ARQUITECTURA","LA PLATA","MATEMATICAS","BIZCOCHITO","ESTADIO","ARGENTINA","ALMAFUERTE"
    };
    int total = sizeof(palabras) / sizeof(palabras[0]);
    int usadas[MAX_LONGITUD];
    for (int i = 0; i < MAX_LONGITUD; i++) usadas[i] = 0;

    int aciertos = 0, jugadas = 0;

    srand(time(NULL));
    while (jugadas < total) {
        int idx;
        do {
            idx = rand() % total;
        } while (usadas[idx]);

        usadas[idx] = 1;
        char palabra[MAX_LONGITUD];
        strncpy(palabra, palabras[idx], MAX_LONGITUD);
        palabra[MAX_LONGITUD - 1] = '\0';

        int gano = jugar(palabra, 0);
        agregarOActualizarJugador(nombreJugador, gano);
        jugadas++;

        if (gano) aciertos++;

        int opcion;
        printf("\nSeguir jugando? (1=sí, 0=no): ");
        scanf("%d", &opcion);
        getchar();
        if (opcion == 0) break;
    }

    printf("Juego terminado. Acertaste %d de %d\n", aciertos, jugadas);
}

void juegoDosJugadores() {
    char palabra[MAX_LONGITUD];
    char jugador1[50], jugador2[50];
    int puntosJ1 = 0, puntosJ2 = 0;

    printf("Ingrese el nombre del Jugador 1: ");
    fgets(jugador1, 50, stdin);
    jugador1[strcspn(jugador1, "\n")] = '\0';

    printf("Ingrese el nombre del Jugador 2: ");
    fgets(jugador2, 50, stdin);
    jugador2[strcspn(jugador2, "\n")] = '\0';

    for (int ronda = 1; ronda <= 5; ronda++) {
        printf("\nRONDA %d - %s ingresa palabra:\n", ronda, jugador1);
        leerPalabraOculta(palabra);
        printf("%s intenta adivinar:\n", jugador2);
        int gano = jugar(palabra, 0);
        if (gano) puntosJ2++;
        agregarOActualizarJugador(jugador2, gano);

        printf("\nRONDA %d - %s ingresa palabra:\n", ronda, jugador2);
        leerPalabraOculta(palabra);
        printf("%s intenta adivinar:\n", jugador1);
        gano = jugar(palabra, 0);
        if (gano) puntosJ1++;
        agregarOActualizarJugador(jugador1, gano);
    }

    printf("Puntaje final:\n%s: %d\n%s: %d\n", jugador1, puntosJ1, jugador2, puntosJ2);
    if (puntosJ1 > puntosJ2)
        printf("%s gana!\n", jugador1);
    else if (puntosJ2 > puntosJ1)
        printf("%s gana!\n", jugador2);
    else
        printf("Empate!\n");
}

int main() {
    SetConsoleOutputCP(CP_UTF8); // Habilita UTF-8 para emojis

    int modo;
    do {
        printf("==== 🕹️ BIENVENIDO AL JUEGO DEL AHORCADO ====\n");
        printf("1. 👤 Un jugador\n2. 👥 Dos jugadores\n0. 🚪 Salir\nSeleccione un modo: ");
        scanf("%d", &modo);
        getchar();

        switch (modo) {
            case 1:
                printf("Ingrese su nombre: ");
                fgets(nombreJugador, 50, stdin);
                nombreJugador[strcspn(nombreJugador, "\n")] = '\0';
                juegoUnJugador();
                break;
            case 2:
                juegoDosJugadores();
                break;
            case 0:
                printf("Gracias por jugar! 👋\n");
                break;
            default:
                printf("❌ Opción inválida.\n");
        }
    } while (modo != 0);

    guardarEstadisticasEnArchivo();
    liberarJugadores();
    return 0;
}