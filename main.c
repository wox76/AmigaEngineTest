#include <intuition/intuition.h>
#include <graphics/gfxbase.h>
#include <proto/intuition.h>
#include <proto/exec.h>
#include <proto/graphics.h>
#include "assets.h" 

// Dobbiamo dichiarare i puntatori alle librerie per essere sicuri
struct GfxBase *GfxBase;
struct IntuitionBase *IntuitionBase;

// Creiamo la nostra struttura BitMap manuale
struct BitMap myBitMap;

struct NewScreen myScreenSettings = {
    0, 0, 320, 256, 5, 0, 1, 
    0, // ViewMode
    CUSTOMSCREEN | CUSTOMBITMAP, // <--- FONDAMENTALE: Diciamo che usiamo la NOSTRA bitmap
    NULL, 
    "Engine Test v2", 
    NULL, 
    &myBitMap // <--- Qui colleghiamo i nostri dati!
};

int main() {
    struct Screen *screen;
    struct Window *window;
    
    // 1. Apriamo le librerie manualmente (Best Practice)
    GfxBase = (struct GfxBase *)OpenLibrary("graphics.library", 0);
    IntuitionBase = (struct IntuitionBase *)OpenLibrary("intuition.library", 0);
    
    if (!GfxBase || !IntuitionBase) return 20; // Se fallisce, esci

    // 2. Riempiamo la memoria con il pattern
    generatePattern();

    // 3. Configuriamo la BitMap manualmente
    // Colleghiamo i puntatori dei piani (definiti in assets.h) alla struttura BitMap
    myBitMap.BytesPerRow = 40;
    myBitMap.Rows = 256;
    myBitMap.Flags = 0;
    myBitMap.Depth = 5;
    myBitMap.Planes[0] = plane1;
    myBitMap.Planes[1] = plane2;
    myBitMap.Planes[2] = plane3;
    myBitMap.Planes[3] = plane4;
    myBitMap.Planes[4] = plane5;
    myBitMap.Planes[5] = NULL;
    myBitMap.Planes[6] = NULL;
    myBitMap.Planes[7] = NULL;

    // 4. Apriamo lo schermo
    screen = OpenScreen(&myScreenSettings);
    
    if (screen) {
        // 5. CARICHIAMO LA PALETTE (La parte critica!)
        // Usiamo LoadRGB4 sulla ViewPort dello schermo appena aperto
        LoadRGB4(&screen->ViewPort, myPalette, 32);
        
        // Apriamo la finestra trasparente per l'input (Mouse)
        struct NewWindow myWindowSettings = {
            0, 0, 320, 256, 0, 1, MOUSEBUTTONS,
            WFLG_BACKDROP | WFLG_BORDERLESS | WFLG_RMBTRAP | WFLG_ACTIVATE,
            NULL, NULL, NULL, NULL, screen, 0, 0, 0, 0, CUSTOMSCREEN
        };
        
        window = OpenWindow(&myWindowSettings);
        
        if (window) {
            // Aspetta un click
            Wait(1L << window->UserPort->mp_SigBit);
            CloseWindow(window);
        }
        
        CloseScreen(screen);
    }

    // Chiudiamo le librerie
    CloseLibrary((struct Library *)IntuitionBase);
    CloseLibrary((struct Library *)GfxBase);
    
    return 0;
}
