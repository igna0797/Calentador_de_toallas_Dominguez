//=====[#include guards - begin]===============================================

#ifndef _MAQUINA_H_
#define _MAQUINA_H_

//=====[Declaration of public defines]=========================================

#define TIEMPO_MAXIMO_ENCENDIDO  1000 *60 *60  *1 // EL ULTIMO NUMERO ES EL TIEMPO EN HORAS
#define TIEMPO_COOLDOWN  1000*60*60    *0.5
#define TIEMPO_HOLD_TO_TURN_OFF 2 //s
/*creo que esta en milisegundos 
1000 para segundos 
60 para minutos
60 para horas
*/

// @note {a partir de cuanto prende}
#define HUMIDITY_THRESHOLD  60 
#define TEMPERATURE_THRESHOLD   30

// @note {cuanto puede bajar desde el max para apagarse solo}
#define TEMP_OFF_THRESHOLD   5  
#define HUM_OFF_THRESHOLD    5 
//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================
    void maquina_de_estados_init();
    void maquina_de_estados_update();
//=====[#include guards - end]=================================================

#endif // _MAQUINA_H_
