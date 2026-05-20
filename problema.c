#include <stdio.h>

#define MAX_OYENTES 100
#define NUM_CANCIONES 10

// Declaracion de funciones 
int leervotos(int votos[][3]);
void calculartopcanciones(int votos[][3], int numoyentes, int puntuaciones[], int *primlugar, int *seglugar);
void determinaroyenteganador(int votos[][3], int numoyentes, int primlugar, int seglugar);


// FUNCIÓN PRINCIPAL
void main() 
{
    // Variables locales
    int votos[MAX_OYENTES][3], puntuaciones[NUM_CANCIONES] = {0}, numoyentes = 0, primlugar = -1, seglugar = -1;

    printf("SISTEMA DE CONCURSO DE RADIO \n\n");

    numoyentes = leervotos(votos);
    
    if (numoyentes == 0) 
    {
        printf("\nNo se registraron oyentes válidos.\n");
        return; 
    }

    calculartopcanciones(votos, numoyentes, puntuaciones, &primlugar, &seglugar);

    determinaroyenteganador(votos, numoyentes, primlugar, seglugar);
}


int leervotos(int votos[][3]) 
{
    int contoyentes = 0;

    printf("Ingrese las votaciones por tríos (Ej: 6 2 1).\n");
    printf("Introduzca -1 en el primer dato.\n\n");

    while (contoyentes < MAX_OYENTES) 
    {
        printf("Oyente %d: ", contoyentes);
        scanf("%d", &votos[contoyentes][0]);

        if (votos[contoyentes][0] == -1) 
        {
            break;
        }

        scanf("%d %d", &votos[contoyentes][1], &votos[contoyentes][2]);
        contoyentes++;
    }

    return contoyentes;
}


void calculartopcanciones(int votos[][3], int numoyentes, int puntuaciones[], int *primlugar, int *seglugar) 
{
    for (int i = 0; i < numoyentes; i++) 
    {
        int cancion1 = votos[i][0];
        int cancion2 = votos[i][1];
        int cancion3 = votos[i][2];

        if (cancion1 >= 0) 
        {
            if (cancion1 < NUM_CANCIONES) 
            {
                puntuaciones[cancion1] += 3;
            }
        }

        if (cancion2 >= 0) 
        {
            if (cancion2 < NUM_CANCIONES) 
            {
                puntuaciones[cancion2] += 2;
            }
        }

        if (cancion3 >= 0) 
        {
            if (cancion3 < NUM_CANCIONES) 
            {
                puntuaciones[cancion3] += 1;
            }
        }
    }

    printf("\n Resultado d elas canciones \n");
    for (int i = 0; i < NUM_CANCIONES; i++) 
    {
        printf("Cancion %d: %d votos\n", i, puntuaciones[i]);
    }

    int max1 = -1, max2 = -1;
    for (int i = 0; i < NUM_CANCIONES; i++) 
    {
        if (puntuaciones[i] > max1) 
        {
            max2 = max1;
            *seglugar = *primlugar;
            max1 = puntuaciones[i];
            *primlugar = i;
        } 
        else if (puntuaciones[i] > max2) 
        {
            max2 = puntuaciones[i];
            *seglugar = i;
        }
    }

    printf("1a cancion mas votada: %d\n", *primlugar);
    printf("2a cancion mas votada: %d\n", *seglugar);
}


void determinaroyenteganador(int votos[][3], int numoyentes, int primlugar, int seglugar) 
{
    printf("\n Puntaje de los oyentes\n");

    int maxpuntosoyente = -1, oyenteganador = 0;

    for (int i = 0; i < numoyentes; i++) 
    {
        int tienetop1 = 0;
        int tienetop2 = 0;
        int puntosacumulados = 0;

        for (int j = 0; j < 3; j++) 
        {
            if (votos[i][j] == primlugar) 
            {
                tienetop1 = 1;
            }
            if (votos[i][j] == seglugar) 
            {
                tienetop2 = 1;
            }
        }

        if (tienetop1) 
        {
            puntosacumulados += 30;
        }
        
        if (tienetop2)
        {
            puntosacumulados += 20;
        }

        if (tienetop1)
        {
            if (tienetop2) 
            {
                puntosacumulados += 10;
            }
        }
        
        printf("Oyente %d: %d puntos\n", i, puntosacumulados);
        if (puntosacumulados > maxpuntosoyente) 
        {
            maxpuntosoyente = puntosacumulados;
            oyenteganador = i;
        }
    }

    printf("\nGanador: el oyente número %d con %d puntos!\n", oyenteganador, maxpuntosoyente);
}
