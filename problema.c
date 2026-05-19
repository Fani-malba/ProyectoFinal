#include <stdio.h>

#define MAX_OYENTES 100
#define NUM_CANCIONES 10


// Declaracion de variables globales
int leerVotos(int votos[][3]);
void calcularTopCanciones(int votos[][3], int numOyentes, int puntuaciones[], int *primerLugar, int *segundoLugar);
void determinarOyenteGanador(int votos[][3], int numOyentes, int primerLugar, int segundoLugar);


// FUNCIÓN PRINCIPAL 

void main() 
{
    // Variables locales 
    int votos[MAX_OYENTES][3];
    int puntuaciones[NUM_CANCIONES] = {0}; 
    int numOyentes = 0;
    int primerLugar = -1;
    int segundoLugar = -1;

    printf("SISTEMA DE CONCURSO DE RADIO \n\n");

    numOyentes = leerVotos(votos);
    
    if (numOyentes == 0) 
    {
        printf("\nNo se registraron oyentes válidos. Fin del programa.\n");
        return; // Al ser void, solo usamos return vacío para finalizar el programa aquí
    }

    // Inciso 2: Cálculo de puntuaciones y obtención del Top 2 de canciones
    calcularTopCanciones(votos, numOyentes, puntuaciones, &primerLugar, &segundoLugar);

    // Inciso 3: Distribución de puntos a oyentes y declaración del ganador
    determinarOyenteGanador(votos, numOyentes, primerLugar, segundoLugar);
}

// ============================================================================
// IMPLEMENTACIÓN DE LAS FUNCIONES
// ============================================================================

/**
 * INCISO 1: Lee los votos de los oyentes por orden de preferencia.
 * Detiene la lectura al ingresar -1 en la primera opción.
 */
int leerVotos(int votos[][3]) 
{
    int contOyentes = 0;

    printf("Ingrese las votaciones por tríos (Ej: 6 2 1).\n");
    printf("Para finalizar, introduzca -1 en el primer dato.\n\n");

    while (contOyentes < MAX_OYENTES) 
    {
        printf("Oyente %d: ", contOyentes);
        scanf("%d", &votos[contOyentes][0]);

        // Condición de parada simple
        if (votos[contOyentes][0] == -1) 
        {
            break;
        }

        // Si no es -1, se leen los otros dos valores restantes del trío
        scanf("%d %d", &votos[contOyentes][1], &votos[contOyentes][2]);
        contOyentes++;
    }

    return contOyentes;
}

/**
 * INCISO 2: Calcula los puntos totales acumulados por cada canción.
 * CONDICIONES 1 POR 1: Se eliminaron los operadores && para evaluar rangos.
 */
void calcularTopCanciones(int votos[][3], int numOyentes, int puntuaciones[], int *primerLugar, int *segundoLugar) 
{
    
    // 1. Acumular los puntos de las canciones según las preferencias
    for (int i = 0; i < numOyentes; i++) 
    {
        int cancion1 = votos[i][0];
        int cancion2 = votos[i][1];
        int cancion3 = votos[i][2];

        // Validación de rango para canción 1 (Una por una)
        if (cancion1 >= 0) 
        {
            if (cancion1 < NUM_CANCIONES) 
            {
                puntuaciones[cancion1] += 3;
            }
        }

        // Validación de rango para canción 2 (Una por una)
        if (cancion2 >= 0) 
        {
            if (cancion2 < NUM_CANCIONES) 
            {
                puntuaciones[cancion2] += 2;
            }
        }

        // Validación de rango para canción 3 (Una por una)
        if (cancion3 >= 0) 
        {
            if (cancion3 < NUM_CANCIONES) 
            {
                puntuaciones[cancion3] += 1;
            }
        }
    }

    // 2. Imprimir los resultados parciales de las canciones
    printf("\n--- RESULTADOS DE LAS CANCIONES ---\n");
    for (int i = 0; i < NUM_CANCIONES; i++) {
        printf("Canción %d: %d votos\n", i, puntuaciones[i]);
    }

    // 3. Buscar las dos canciones con mayor puntaje (Estructura condicional simple)
    int max1 = -1, max2 = -1;
    for (int i = 0; i < NUM_CANCIONES; i++) 
    {
        if (puntuaciones[i] > max1) 
        {
            max2 = max1;
            *segundoLugar = *primerLugar;
            max1 = puntuaciones[i];
            *primerLugar = i;
        } 
        else if (puntuaciones[i] > max2) 
        {
            max2 = puntuaciones[i];
            *segundoLugar = i;
        }
    }

    printf("1a canción más votada: %d\n", *primerLugar);
    printf("2a canción más votada: %d\n", *segundoLugar);
}

/**
 * INCISO 3: Evalúa el éxito de cada participante basándose en el Top 2.
 * CONDICIONES 1 POR 1: Puntos asignados individualmente y bonus verificado con ifs anidados.
 */
void determinarOyenteGanador(int votos[][3], int numOyentes, int primerLugar, int segundoLugar) 
{
    printf("\n--- PUNTAJES DE LOS OYENTES ---\n");

    int maxPuntosOyente = -1;
    int oyenteGanador = 0;

    for (int i = 0; i < numOyentes; i++) 
    {
        int tieneTop1 = 0;
        int tieneTop2 = 0;
        int puntosAcumulados = 0;

        // Comprobar qué canciones del podio tiene el oyente en su trío
        for (int j = 0; j < 3; j++) 
        {
            if (votos[i][j] == primerLugar) 
            {
                tieneTop1 = 1;
            }
            if (votos[i][j] == segundoLugar) 
            {
                tieneTop2 = 1;
            }
        }

        // Aplicación de reglas de puntuación una por una
        if (tieneTop1) 
        {
            puntosAcumulados += 30;
        }
        
        if (tieneTop2)
        {
            puntosAcumulados += 20;
        }

        // CONDICIÓN ANIDADA (1 por 1) para el puntaje suplementario de 10 puntos sin usar &&
        if (tieneTop1)
        {
            if (tieneTop2) 
            {
                puntosAcumulados += 10;
            }
        }

        printf("Oyente %d: %d puntos\n", i, puntosAcumulados);

        // Determinar el puntaje más alto
        if (puntosAcumulados > maxPuntosOyente) 
        {
            maxPuntosOyente = puntosAcumulados;
            oyenteGanador = i;
        }
    }

    printf("\nGanador: el oyente número %d con %d puntos!\n", oyenteGanador, maxPuntosOyente);
}
