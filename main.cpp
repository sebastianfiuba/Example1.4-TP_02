#include "mbed.h"
#include "arm_book_lib.h"

#define BUTTONS_MASK 0b0011

void print_gpio(bool alarmState_a, uint8_t sensors_byte_a, uint8_t buttons_byte_a);

int main()
{

    /*
    DigitalIn gasDetector(D2);
    DigitalIn overTempDetector(D3);

    Explicar por que elegimos busin en vez de portin

    */

    BusIn Detectors(D2, D3);

    /*
    DigitalIn gasDetector(D2);
    DigitalIn overTempDetector(D3);
    DigitalIn aButton(D4);
    DigitalIn bButton(D5);
    DigitalIn cButton(D6);
    DigitalIn dButton(D7);

    */

    BusIn Buttons (D4, D5, D6, D7);

    Buttons.mode(PullDown);

    Detectors.mode(PullDown);


    DigitalOut alarmLed(LED1);



    alarmLed = OFF;

    bool alarmState = OFF;


    uint8_t sensors_byte = 0x0;
    uint8_t buttons_byte = 0x0;
    uint8_t ant_sensors_byte = !sensors_byte;
    uint8_t ant_buttons_byte = !buttons_byte;

    while (true) {

        //explicar porque usamosl mask (pros y contras)
        if ((sensors_byte = (Detectors & Detectors.mask()))) {
            alarmState = ON;
        }



        if ( (buttons_byte = (Buttons & Buttons.mask())) == BUTTONS_MASK ) {
            alarmState = OFF;
        }

        alarmLed = alarmState;

        if((sensors_byte != ant_sensors_byte) || (buttons_byte != ant_buttons_byte)){

            print_gpio(alarmState, sensors_byte, buttons_byte);
            ant_buttons_byte = buttons_byte;
            ant_sensors_byte = sensors_byte;

        }
        
    }
}

void print_gpio(bool alarmState_a, uint8_t sensors_byte_a, uint8_t buttons_byte_a){


    if(alarmState_a)
        printf("El led esta prendido\n");
    else
        printf("El led esta apagado\n");

    if (sensors_byte_a & 0x1 )
        printf("Se detecta gas");
    else
        printf("No se detecta gas");
    printf("\n");
    
    if (sensors_byte_a & 0x2 )
        printf("Se paso la temperatura");
    else
        printf("No se paso la temperatura");
    printf("\n");

    if (buttons_byte_a & 0x1)
        printf("Se apreto el boton \"a\"");
    else
        printf("No se apreto el boton \"a\"");
    printf("\n");
    
    if (buttons_byte_a & 0x2)
        printf("Se apreto el boton \"b\"");
    else
        printf("No se apreto el boton \"b\"");
    printf("\n");
    if (buttons_byte_a & 0x4 )
        printf("Se apreto el boton \"c\"");
    else
        printf("No se apreto el boton \"c\"");
    printf("\n");

    if (buttons_byte_a & 0x8 )
        printf("Se apreto el boton \"d\"");
    else
        printf("No se apreto el boton \"d\"");
    printf("\n");






}