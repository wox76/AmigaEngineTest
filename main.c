#include <intuition/intuition.h>
#include <proto/intuition.h>
#include <proto/exec.h>
#include <proto/graphics.h>
#include "assets.h" // <--- Includiamo il nostro file asset!

// Configurazione schermo
struct NewScreen myScreenSettings = {
    0, 0, 320, 256, 5, 0, 1, 0, CUSTOMSCREEN,
    NULL, "Amiga Engine Test", NULL, NULL
};

int main() {
    struct Screen *screen;
    struct Window *window;
    struct ViewPort *vp;
    int i;

    // 1. Generiamo la grafica in memoria
    generatePattern();

    // 2. Apriamo lo schermo (nero vuoto per ora)
    screen = OpenScreen(&myScreenSettings);
    
    if (!screen) return 20;

    vp = &screen->ViewPort;

    // 3. CARICHIAMO LA PALETTE
    LoadRGB4(vp, myPalette, 32);

    // 4. COPIAMO I PIANI (La magia avviene qui)
    // L'Amiga ha aperto lo schermo e ha allocato la sua memoria video (RasInfo).
    // Noi copiamo i nostri dati dentro la memoria dello schermo.
    
    // Piano 1
    struct BitMap *bm = screen->RastPort.BitMap;
    
    // Copiamo manualmente i byte dalla nostra memoria ai piani dello schermo
    // Nota: Per un gioco vero useremmo i puntatori diretti, ma questo è più sicuro per iniziare.
    CopyMem(plane1, bm->Planes[0], PLANE_SIZE);
    CopyMem(plane2, bm->Planes[1], PLANE_SIZE);
    CopyMem(plane3, bm->Planes[2], PLANE_SIZE);
    // Gli altri piani li lasciamo neri per ora
    
    // 5. Apriamo la finestra per l'input
    struct NewWindow myWindowSettings = {
        0, 0, 320, 256, 0, 1, MOUSEBUTTONS,
        WFLG_BACKDROP | WFLG_BORDERLESS | WFLG_RMBTRAP | WFLG_ACTIVATE,
        NULL, NULL, NULL, NULL, screen, 0, 0, 0, 0, CUSTOMSCREEN
    };

    window = OpenWindow(&myWindowSettings);

    if (window) {
        Wait(1L << window->UserPort->mp_SigBit);
        CloseWindow(window);
    }

    CloseScreen(screen);
    return 0;
}
