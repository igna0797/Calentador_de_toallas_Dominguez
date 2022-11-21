//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "Dht11.h"
#include "maquina.h"

//=====[Declaration of private defines]========================================


//=====[Declaration of private data types]=====================================
typedef enum {
    OFF,
    WAITING,
    ON
} state_t;

//=====[Declaration and initialization of public global objects]===============


//=====[Declaration of external public global variables]=======================

state_t estado;

//=====[Declaration and initialization of public global variables]=============

Dht11 sensor(D7);

//=====[Declaration and initialization of private global variables]============

int temperatura_media =25;

DigitalIn boton(D2); 
//=====[Declarations (prototypes) of private functions]========================


//=====[Implementations of public functions]===================================
void maquina_de_estados_init(){
        estado=WAITING;
        return
    }

void maquina_de_estados_update(){
        switch(estado){
            case WAITING:
                sensor.read();
                if(sensor.getHumidity() > HUMIDITY_THRESHOLD || sensor.getCelsius() > temperatura_media || boton==1 ){
                    estado=ON;
                    //rele.on();  //toDo:implementar esto
                }
            
            case ON:
                //timer(1); //1 hora seria                 
                int temperaturaActual=sensor.getCelsius();
                int humedadActual=sensor.getCelsius();                
                static int Tmax=0;
                static int Hmax=0;
                sensor.getHumidity();
                Tmax=max(temperaturaActual,Tmax);
                Hmax=max(humedadActual,Hmax);

                if (boton || temperaturaActual< Tmax-TEMP_OFF_THRESHOLD || humedadActual < Hmax- HUM_OFF_THRESHOLD ){
                    estado=WAITING;
                    Tmax=0;
                    Hmax=0;
                    //rele.off();

                }

        }
        return

}

//=====[Implementations of private functions]==================================

bool debounce(){
    return true ;
}
int timerinterrupt(){
    return 0;
}
