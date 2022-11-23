//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "DHT.h"
#include "maquina.h"

//=====[Declaration of private defines]========================================


//=====[Declaration of private data types]=====================================
typedef enum {
    APAGADO,
    WAITING,
    PRENDIDO
} state_t;

//=====[Declaration and initialization of public global objects]===============


//=====[Declaration of external public global variables]=======================

state_t estado;

//=====[Declaration and initialization of public global variables]=============

DHT sensor(D7, DHT11);
DigitalOut rele(D6);

//=====[Declaration and initialization of private global variables]============
int temperatura_media =25;
time_t tiempoEncendido;
DigitalIn boton(D2); 
//=====[Declarations (prototypes) of private functions]========================


//=====[Implementations of public functions]===================================
void maquina_de_estados_init(){
        estado=WAITING;
    }

void maquina_de_estados_update(){
        switch(estado){
            case WAITING:
                sensor.readData();
                if(sensor.ReadHumidity() > HUMIDITY_THRESHOLD || sensor.ReadTemperature(CELCIUS) > temperatura_media || boton==1 ){
                    estado=PRENDIDO;
                    rele=ON;
                }
            
            case PRENDIDO:
                tiempoEncendido=time(NULL);
                
                int temperaturaActual=sensor.ReadTemperature(CELCIUS);
                int humedadActual=sensor.ReadTemperature(CELCIUS);
                static int Tmax=0;
                static int Hmax=0;
                sensor.ReadHumidity();
                Tmax=max(temperaturaActual,Tmax);
                Hmax=max(humedadActual,Hmax);

                if (boton || temperaturaActual< Tmax-TEMP_OFF_THRESHOLD || humedadActual < Hmax- HUM_OFF_THRESHOLD ){
                    estado=WAITING;
                    Tmax=0;
                    Hmax=0;
                    rele = OFF;

                }

        }

}

//=====[Implementations of private functions]==================================


int timerinterrupt(){
    return 0;
}
