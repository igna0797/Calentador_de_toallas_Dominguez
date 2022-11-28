#include "mbed.h"
#include "Maquina de estados/maquina.h"

// main() runs in its own thread in the OS
// boton 
//timer
//sensor

int main()
{
    maquina_de_estados_init();
    while (true) {
        maquina_de_estados_update();

    }
}

