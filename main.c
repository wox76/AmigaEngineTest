#include <intuition/intuition.h>
#include <proto/intuition.h>
#include <proto/exec.h>
#include <proto/graphics.h>

// Configurazione base dello schermo
struct NewScreen myScreenSettings = {
    0, 0,              // LeftEdge, TopEdge (Parte da in alto a sinistra)
    320, 256,          // Width, Height (Standard LowRes PAL)
    5,                 // Depth (5 bitplanes = 32 colori)
    0, 1,              // DetailPen, BlockPen (Colori base interfaccia)
    0,                 // ViewModes (0 = LowRes)
    CUSTOMSCREEN,      // Type (Schermo proprietario, non Workbench)
    NULL,              // Font (Default)
    "Mio Engine v0.1", // Titolo sulla barra in alto
    NULL,              // Gadgets
    NULL               // CustomBitMap (Qui metteremo la nostra grafica dopo!)
};

int main() {
    struct Screen *screen;
    struct Window *window;
    
    // 1. Apriamo lo schermo
    screen = OpenScreen(&myScreenSettings);
    
    if (!screen) {
        return 20; // Errore: fallimento apertura
    }

    // 2. Apriamo una finestra trasparente "invisibile" per catturare l'input
    // (L'Amiga ha bisogno di una finestra per sentire il mouse/tastiera)
    struct NewWindow myWindowSettings = {
        0, 0, 320, 256,
        0, 1,
        MOUSEBUTTONS, // Vogliamo sentire solo i click del mouse
        WFLG_BACKDROP | WFLG_BORDERLESS | WFLG_RMBTRAP | WFLG_ACTIVATE,
        NULL, NULL, NULL, NULL, screen, 0, 0, 0, 0,
        CUSTOMSCREEN
    };

    window = OpenWindow(&myWindowSettings);

    if (window) {
        // 3. Loop principale: Aspetta un segnale
        // Wait() mette in pausa la CPU finché non arriva un messaggio (risparmia batteria/cicli!)
        Wait(1L << window->UserPort->mp_SigBit);
        
        CloseWindow(window);
    }

    // 4. Pulizia
    CloseScreen(screen);
    
    return 0;
}
