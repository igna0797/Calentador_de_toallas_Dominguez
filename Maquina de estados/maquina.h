//=====[#include guards - begin]===============================================

#ifndef _MAQUINA_H_
#define _MAQUINA_H_

//=====[Declaration of public defines]=========================================

#define TIEMPO_PRENDIDO = 1000 * 1*60  * 1*60
#define HUMIDITY_THRESHOLD=60
#define TEMPERATURE_THRESHOLD = 30
//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================
    maquina_de_estados_init();
    maquina_de_estados_update();
//=====[#include guards - end]=================================================

#endif // _AUDIO_H_
