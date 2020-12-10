// Bruno Granella Serpa
// Universidade Federal de Santa Catarina
// EMB5642 Microcontroladores  - 2020.1
// Projeto Final
//
// BATTLE CITY
//
// Nokia 5110
// ---------------
// Signal        (Nokia 5110) LaunchPad pin
// Reset         (RST, pin 1) connected to PA7
// SSI0Fss       (CE,  pin 2) connected to PA3
// Data/Command  (DC,  pin 3) connected to PA6
// SSI0Tx        (Din, pin 4) connected to PA5
// SSI0Clk       (Clk, pin 5) connected to PA2
// 3.3V          (Vcc, pin 6) power
// back light    (BL,  pin 7) ground
// Ground        (Gnd, pin 8) ground

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "driverlib/adc.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/hibernate.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "Character.h"
#include "Screens.h"
#include "Menu.h"
#include "Game.h"
#include "DisplayGame.h"

int i, j, level, t0;

int t = 0;      //Timer to count scores
int record = 0; //Record
int kills = 0;  //Kills (Record only counts if all tanks were killed)
int recordkills = 0;

int screen = 0; //Options from menu
                //0 = Menu
                //1 = Stats
                //2 = Help
                //3 = Help2
int select = 0; //Select option from menu

int counternpc = 0; //Randomize movement variable
int nRandonNumber;

//Rotation:
//0 = North
//1 = East
//2 = South
//3 = West
int position [8][5] = { //position x, position y, rotation, alive, stopped
    {28,42,0,1,0},     //Tank
    {0,0,0,0,0},       //Bullet
    {2,2,2,0,0},       //NPC1
    {18,2,2,0,0},      //NPC2
    {33,2,2,0,0},      //NPC3
    {46,2,2,0,0},      //NPC4
    {61,2,2,0,0},      //NPC5
    {76,2,2,0,0}       //NPC6
};
int initialposition [8][5] = { //position x, position y, rotation, alive, stopped
    {28,42,0,1,0},     //Tank
    {0,0,0,0,0},       //Bullet
    {2,2,2,0,0},       //NPC1
    {18,2,2,0,0},      //NPC2
    {33,2,2,0,0},      //NPC3
    {46,2,2,0,0},      //NPC4
    {61,2,2,0,0},      //NPC5
    {76,2,2,0,0}       //NPC6
};

int matrix [84][48] = {0};  //Position Matrix

//Interruption from buttons (only on menus)
void IntPortalF (void){
    uint8_t ui8IntSource;

    GPIOIntDisable(GPIO_PORTF_BASE, GPIO_INT_PIN_4|GPIO_PIN_0);
    ui8IntSource = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0);

    //Verifica qual botao esta causando a interrupcao
    if ((ui8IntSource & 0x01) ==  0x00){                //SW2
        int debounce = 0;
        while (debounce < 1000000){
            debounce++;
        }
        if ((ui8IntSource & 0x01) ==  0x00){
            switch (screen){
            case 0:
                switch(select){
                    case 0:                                 //Game Start
                    t = 0;
                    kills = 0;
                    level = 0;

                    //LEVEL 0
                    PrintLevel(level);
                    SysCtlDelay(30000000);
                    Spawn(matrix, position, 0);
                    while(position[0][3] == 1 && kills < 6){             //While alive
                        if (t == 0){                        //Spawn NPCs
                            Spawn(matrix, position, 2);
                            position[2][3] = 1;
                            Spawn(matrix, position, 4);
                            position[4][3] = 1;
                            Spawn(matrix, position, 6);
                            position[6][3] = 1;
                        }
                        if (t == 20){
                            Spawn(matrix, position, 3);
                            position[3][3] = 1;
                            Spawn(matrix, position, 5);
                            position[5][3] = 1;
                            Spawn(matrix, position, 7);
                            position[7][3] = 1;
                        }
                        PrintGame(position, level);                //Print game to display
                        Gaming(position, matrix, &kills);           //Player actions
                        nRandonNumber = rand()%((9+1)-0) + 0;
                        for (i = 2; i <= 7; i++){           //NPC actions
                            if (position[i][3] == 1){
                                NPCMovement(matrix, nRandonNumber, position, i);
                            }
                        }

                        t++;
                    }

                    //LEVEL 1
                    level = 1;
                    if(kills == 6){
                        PrintLevel(level);
                        SysCtlDelay(30000000);
                        for (i = 0; i < 84; i++){               //Resets Matrix
                            for (j = 0; j < 48; j++){
                                matrix[i][j] = 0;
                            }
                        }
                        for (i = 0; i <= 7; i++){               //Resets Positions
                            for (j = 0; j <= 3; j++){
                                position[i][j] = initialposition[i][j];
                            }
                        }

                        //Create Walls
                        for(i = 15; i<= 19; i++){
                            for(j = 12; j <= 34; j++){
                                matrix[i][j] = 8;
                            }
                        }
                        for(i = 64; i<= 68; i++){
                            for(j = 12; j <= 34; j++){
                                matrix[i][j] = 8;
                            }
                        }
                        Spawn(matrix, position, 0);
                        t0 = t;
                        while(position[0][3] == 1 && kills < 12){             //While alive
                            if (t == t0){                        //Spawn NPCs
                                Spawn(matrix, position, 2);
                                position[2][3] = 1;
                                Spawn(matrix, position, 4);
                                position[4][3] = 1;
                                Spawn(matrix, position, 6);
                                position[6][3] = 1;
                            }
                            if (t == t0 + 20){
                                Spawn(matrix, position, 3);
                                position[3][3] = 1;
                                Spawn(matrix, position, 5);
                                position[5][3] = 1;
                                Spawn(matrix, position, 7);
                                position[7][3] = 1;
                            }
                            PrintGame(position, level);                //Print game to display
                            Gaming(position, matrix, &kills);           //Player actions
                            nRandonNumber = rand()%((9+1)-0) + 0;
                            for (i = 2; i <= 7; i++){           //NPC actions
                                if (position[i][3] == 1){
                                    NPCMovement(matrix, nRandonNumber, position, i);
                                }
                            }

                            t++;
                        }
                    }
                    if(kills == 12){
                        PrintVictory();                         //Victory
                    }
                    else PrintGameOver();                       //Game Over
                    for (i = 0; i < 84; i++){               //Resets Matrix
                        for (j = 0; j < 48; j++){
                            matrix[i][j] = 0;
                        }
                    }
                    for (i = 0; i <= 7; i++){               //Resets Positions
                        for (j = 0; j <= 3; j++){
                            position[i][j] = initialposition[i][j];
                        }
                    }
                    if(kills >= recordkills){
                        if(t < record || record ==0){
                            record = t;
                            recordkills = kills;
                        }
                    }
                    SysCtlDelay(30000000);
                    Nokia5110_Clear();
                    PrintMenu(0);
                    break;

                case 1:                                 //Display Record
                    screen = 1;
                    PrintStats(record, recordkills, t, kills);
                    break;

                case 2:                                 //Display Help
                    screen = 2;
                    PrintHelp();
                    break;
                default:
                    break;
                }
                break;

            case 1:                                 //If displaying Records, go back to Menu
                Nokia5110_Clear();

                PrintMenu(0);
                screen = 0;
                select = 0;

                break;

            case 2:                                 //If displaying Help page 1, go to Help page 2
                Nokia5110_Clear();

                PrintHelp2();
                screen = 3;
                break;

            case 3:                                 //If displaying Help page 2, go to Help page 1
                Nokia5110_Clear();

                PrintHelp();
                screen = 2;
                break;

            default:
                break;
            }
        }
    }

    if ((ui8IntSource & 0x10) ==  0x00){                //SW1
        int debounce = 0;                               //Changes options from Menu
        while (debounce < 1000000){
            debounce++;
        }
        if ((ui8IntSource & 0x10) ==  0x00){
            if (screen != 0){
                select = 0;
                screen = 0;
            }
            else if(select == 2){
                select = 0;
            }
            else{
                select++;
            }
            PrintMenu(select);
        }
    }
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_4|GPIO_PIN_0);
}

int main(void){

    srand(time(NULL));
    //Initialize Display
    Nokia5110_Init();
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();

    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    //Enables Port F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //Unlocks Port F
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
    GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    //Display Start Screen
    SysCtlDelay(3000000);
    Nokia5110_PrintBMP2(0,0,StartScreen,84,48);
    Nokia5110_DisplayBuffer();

    SysCtlDelay(30000000);

    Nokia5110_Clear();
    Nokia5110_ClearBuffer();

    PrintMenu(0);

    //Enables Port F Interruption
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_INT_PIN_4|GPIO_PIN_0,GPIO_FALLING_EDGE);
    IntEnable(INT_GPIOF);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_4|GPIO_PIN_0);
    IntMasterEnable();
}
