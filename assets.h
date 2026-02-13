#ifndef ASSETS_H
#define ASSETS_H

#include <exec/types.h>

// Definizioni dimensioni schermo
#define SCREEN_W 320
#define SCREEN_H 256
#define SCREEN_D 5  // 5 Bitplanes = 32 colori
#define BYTES_PER_ROW (SCREEN_W / 8) // 40 bytes per riga
#define PLANE_SIZE (BYTES_PER_ROW * SCREEN_H) // 10240 bytes per piano

// --- 1. PALETTE (32 Colori) ---
// DEBUG: Il primo colore (0x0F00) è ROSSO.
// Se vedi lo sfondo rosso, la palette è caricata correttamente!
UWORD myPalette[32] = {
    0x0F00, 0x0FFF, 0x000F, 0x00F0, 0x0F0F, 0x0FF0, 0x00FF, 0x0D00,
    0x0DD0, 0x00DD, 0x0D0D, 0x0DDD, 0x0999, 0x0AAA, 0x0888, 0x0777,
    0x0666, 0x0555, 0x0444, 0x0333, 0x0222, 0x0111, 0x0300, 0x0500,
    0x0700, 0x0900, 0x0B00, 0x0C00, 0x0E00, 0x0A00, 0x0FFF, 0x0000
};

// --- 2. BITPLANES (Grafica) ---
// __chip è essenziale: mette queste variabili nella RAM video speciale dell'Amiga
__chip UBYTE plane1[PLANE_SIZE];
__chip UBYTE plane2[PLANE_SIZE];
__chip UBYTE plane3[PLANE_SIZE];
__chip UBYTE plane4[PLANE_SIZE];
__chip UBYTE plane5[PLANE_SIZE];

// --- 3. GENERATORE DI GRAFICA ---
// Questa funzione riempie la memoria vuota con un disegno geometrico
void generatePattern() {
    int x, y;
    int offset = 0;
    
    for(y = 0; y < SCREEN_H; y++) {
        for(x = 0; x < BYTES_PER_ROW; x++) {
            
            // Calcoliamo l'indirizzo corrente in memoria
            offset = (y * BYTES_PER_ROW) + x;

            // PIANO 1: Righe orizzontali spesse (ogni 32 pixel)
            if ((y % 32) < 16) {
                plane1[offset] = 0xFF; // Tutto pieno (11111111)
            } else {
                plane1[offset] = 0x00; // Vuoto
            }

            // PIANO 2: Righe verticali fini (0xAA = 10101010 in binario)
            plane2[offset] = 0xAA; 

            // PIANO 3: Scacchiera grande
            if (((y / 16) + x) % 2 == 0) {
                plane3[offset] = 0xFF;
            } else {
                plane3[offset] = 0x00;
            }

            // PIANO 4 e 5: Lasciamo vuoti o facciamo un pattern fine
            plane4[offset] = (UBYTE)(y); // Sfumatura verticale
            plane5[offset] = 0x00;
        }
    }
}

#endif
