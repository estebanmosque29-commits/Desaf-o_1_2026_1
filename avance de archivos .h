CONSOLA .H
    

#ifndef CONSOLA_H
#define CONSOLA_H

// Funciones a bajo nivel del sistema operativo (Windows)
// para manipular la consola sin usar librerias de alto nivel de GUI.

void OcultarCursor();
void MoverCursor(int x, int y);
bool LetraPresionada();
int ObtenerLetra();
void Dormir(int milisegundos);

#endif // CONSOLA_H



JUEGO .H


#ifndef JUEGO_H
#define JUEGO_H

#include "tablero.h"
#include "pieza.h"

// Clase Juego pura en C++ sin herencia de motores graficos
class Juego {
public:
    Juego(int ancho, int alto);
    ~Juego();
    
    void Iniciar();

private:
    Tablero* m_tablero;
    PiezaActiva m_activa;
    MascaraPieza m_siguientePieza;
    int m_puntaje;
    int m_lineasCompletadas;
    bool m_gameOver;
    int m_velocidad; // en milisegundos
    
    void GenerarNuevaPieza();
    void BajarPiezaGravedad();
    
    // Metodos auxilares para el Game Loop de Consola
    bool ProcesarEntrada();
    void DibujarPantalla();
    void DibujarSiguientePieza(int panelX, int panelY);
};

#endif // JUEGO_H


PIEZA .H

#ifndef PIEZA_H
#define PIEZA_H

// Usamos exactamente 16 bits sin signo para representar un bloque 4x4.
// Esto nos da un ahorro inmenso de memoria: 1 sola variable en vez de 16 booleanos.
typedef unsigned short MascaraPieza;

struct PiezaActiva {
    MascaraPieza forma;
    int x;
    int y;
};

// Genera una de las 7 piezas base usando la funcion C-style rand()
MascaraPieza GenerarPiezaAleatoria();

// Rotacion de matriz 4x4 implementada 100% con operadores logicos a nivel de bit
MascaraPieza RotarDerecha(MascaraPieza actual);
MascaraPieza RotarIzquierda(MascaraPieza actual);

#endif // PIEZA_H


TABLERO .H

#ifndef TABLERO_H
#define TABLERO_H

#include "pieza.h"

// Estructura fundamental para una matrix manejada mediante memoria de Bits (Bajo nivel en su maxima expresion)
struct Tablero {
    int ancho;
    int alto;
    int bytesPorFila;  // Al ser W multiplo de 8, este numero es perfecto (Ej: W=16 -> 2 bytes)
    
    // Puntero dinámico a la memoria RAW donde existira la matrix (100% contigua para cache CPU)
    unsigned char* datos; 
};

// Genera el heap y configura las estructuras base
Tablero* CrearTablero(int ancho, int alto);

// Liberacion de heap OBLIGATORIA al usar 'new []' de manera manual
void DestruirTablero(Tablero* tablero);

// Revisa un booleano real basado en el bit N del byte C a traves de mascaras e indices array
bool CeldaOcupada(Tablero* tablero, int x, int y);

// Fusion de mascara virtual 4x4 iterativa vs. bytes de Memoria (Colisiones)
bool ColisionPieza(Tablero* tablero, MascaraPieza pieza, int px, int py);

// "Quemar" los bits de memoria del Tablero con la Mascara usando un 'OR' a nivel bit
void FijarPieza(Tablero* tablero, MascaraPieza pieza, int px, int py);

// Detectar bytes que sean '0xFF' integramente, lo que significa 'Fila Llena'
int LimpiarFilas(Tablero* tablero);

#endif // TABLERO_H
