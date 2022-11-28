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
    INICIANDO,
    PRENDIDO,
} state_t;

//=====[Declaration and initialization of public global objects]===============


//=====[Declaration of external public global variables]=======================


//=====[Declaration and initialization of public global variables]=============

state_t estado;
DHT sensor(PD_0, DHT11);
DigitalOut rele(PG_3);
DigitalIn boton(BUTTON1); 

//=====[Declaration and initialization of private global variables]============
// int temperatura_media =25;
time_t tiempoEncendido;
time_t tiempoInicio;
time_t tiempoActual;

//=====[Declarations (prototypes) of private functions]========================


//=====[Implementations of public functions]===================================
void maquina_de_estados_init(){
        estado=WAITING;
    }

void maquina_de_estados_update(){
        static int Tmax=0;
        static int Hmax=0;
        static bool starting = 1; //medio feo hay como una rutina de starting que tiene 2 
        int temperaturaActual = 0;
        int humedadActual = 0; //leerlo aca y nunca mas?
        switch(estado){
            case APAGADO:
                if (boton==1){
                    //estado = WAITING;
                }
            case WAITING:
                starting=1;
                rele=OFF; //por si acaso se llego aca sin que se apagara.
                sensor.readData();
                if(sensor.ReadHumidity() > HUMIDITY_THRESHOLD || sensor.ReadTemperature(CELCIUS) > TEMPERATURE_THRESHOLD || boton==1 ){
                    estado=INICIANDO;
                }
                break;
            
            case INICIANDO:
                if (starting==1){
                    tiempoInicio=time(NULL);
                    Tmax=0;
                    Hmax=0;
                    starting=0;
                }
                tiempoActual=time(NULL);
                tiempoEncendido=tiempoActual - tiempoInicio;
                if (tiempoEncendido >= TIEMPO_HOLD_TO_TURN_OFF){
                    starting=0;
                    estado=APAGADO;
                    break;
                }
                if (boton == 0) {
                    rele=ON;
                    estado=PRENDIDO;
                }
                break;
            
            case PRENDIDO: 
                
                sensor.readData();
                temperaturaActual = sensor.ReadTemperature(CELCIUS);
                humedadActual = sensor.ReadHumidity();

                Tmax=max(temperaturaActual,Tmax);
                Hmax=max(humedadActual,Hmax);
                if (boton || temperaturaActual< Tmax-TEMP_OFF_THRESHOLD || humedadActual < Hmax- HUM_OFF_THRESHOLD || tiempoEncendido > TIEMPO_MAXIMO_ENCENDIDO){
                    estado=WAITING;
                    rele = OFF;
                break;
            
            }
        }

}

//=====[Implementations of private functions]==================================


int timerinterrupt(){
    return 0;
}

