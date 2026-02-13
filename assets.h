#include <exec/types.h>

// 1. La Palette (32 colori)
UWORD myPalette[32] = {
    0x0000, 0x0FFF, 0x0D00, 0x0F00, 0x00D0, 0x00F0, 0x000D, 0x000F,
    0x0DD0, 0x0FF0, 0x00DD, 0x00FF, 0x0D0D, 0x0F0F, 0x0DDD, 0x0FFF,
    0x0999, 0x0AAA, 0x0888, 0x0777, 0x0666, 0x0555, 0x0444, 0x0333,
    0x0222, 0x0111, 0x0300, 0x0500, 0x0700, 0x0900, 0x0B00, 0x0D00
};

// 2. I dati Grafici (Un semplice pattern a scacchiera generato matematicamente)
// 320 pixel larghezza / 8 bit = 40 bytes per riga
// 256 righe altezza
// 5 bitplanes
// Totale: 40 * 256 * 5 = 51200 bytes
// Nota: __chip è fondamentale! Dice all'Amiga di mettere questi dati nella RAM Video.

#define PLANE_SIZE (40 * 256)

__chip UBYTE plane1[PLANE_SIZE]; // Riserviamo spazio in Chip RAM
__chip UBYTE plane2[PLANE_SIZE];
__chip UBYTE plane3[PLANE_SIZE];
__chip UBYTE plane4[PLANE_SIZE];
__chip UBYTE plane5[PLANE_SIZE];

// Funzione per generare un pattern al volo (per non incollare 50kb di codice qui)
void generatePattern() {
    int x, y, i;
    int offset = 0;
    for(y = 0; y < 256; y++) {
        for(x = 0; x < 40; x++) {
            // Crea un pattern a scacchiera/barre
            plane1[offset] = (y % 32 < 16) ? 0xFF : 0x00; // Righe orizzontali
            plane2[offset] = (x % 4 < 2) ? 0xFF : 0x00;   // Righe verticali
            plane3[offset] = ((x+y) % 8 < 4) ? 0xFF : 0x00; // Diagonali
            plane4[offset] = 0x00; // Vuoto
            plane5[offset] = 0x00; // Vuoto
            offset++;
        }
    }
}
