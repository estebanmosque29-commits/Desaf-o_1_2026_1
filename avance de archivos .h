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

// Arquitectura orientada a objetos clasica de Motor de Videojuego
class Juego {
public:
    // El constructor recibe parametros inyectables
    Juego(int ancho, int alto);
    
    // El destructor limpiara la memoria del tablero
    ~Juego();
    
    // Desata el Game Loop principal infinito (hasta que se muera)
    void Iniciar();

private:
    Tablero* m_tablero;
    PiezaActiva m_activa;
    int m_puntaje;
    int m_lineasCompletadas;
    bool m_gameOver;
    
    // Funciones Helper de Mantenimiento de Estado "Single Responsibility"
    void GenerarNuevaPieza();
    void Dibujar();
    void ManejarEntradaAsincrona();
    void BajarPiezaGravedad();
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
