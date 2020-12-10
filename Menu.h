#ifndef MENU_H_
#define MENU_H_
int i;

void PrintMenu(int select){

    Nokia5110_ClearBuffer();

    SysCtlDelay(3000000);
    Nokia5110_PrintBMP2(0,0,MenuScreen,84,12);

    switch(select){
        case 0:

            Nokia5110_PrintBMP2(14,25,TankE,5,5);
            Nokia5110_DisplayBuffer();
            break;
        case 1:
            Nokia5110_PrintBMP2(14,33,TankE,5,5);
            Nokia5110_DisplayBuffer();
            break;

        case 2:
            Nokia5110_PrintBMP2(14,41,TankE,5,5);
            Nokia5110_DisplayBuffer();
            break;

        default:
            break;
    }

    Nokia5110_SetCursor(3,3);
    Nokia5110_OutString("Start");
    Nokia5110_SetCursor(3,4);
    Nokia5110_OutString("Stats");
    Nokia5110_SetCursor(3,5);
    Nokia5110_OutString("Help");
}

void PrintStats(int record, int recordkills, int t, int kills){

    Nokia5110_Clear();
    Nokia5110_ClearBuffer();

    SysCtlDelay(3000000);
    Nokia5110_PrintBMP2(0,0,TankE,5,5);
    Nokia5110_PrintBMP2(0,25,TankE,5,5);
    Nokia5110_DisplayBuffer();

    Nokia5110_SetCursor(1,0);
    Nokia5110_OutString("High Score");
    if(record > 0){
        char HighScore[11] = "00K T000000";

        uint32_t aux =  record;
        for(i = 9; i >= 5; i--){
            HighScore[i] = aux%10+48;
            aux = aux/10;
        }
        HighScore[1] = recordkills%10 + 48;
        HighScore[0] = (recordkills/10)%10 + 48;

        Nokia5110_SetCursor(0,1);
        Nokia5110_OutString(HighScore);

        char LastScore[11] = "00K T000000";

        aux =  t;
        for(i = 9; i >= 5; i--){
            LastScore[i] = aux%10+48;
            aux = aux/10;
        }
        LastScore[1] = kills%10 + 48;
        LastScore[0] = (kills/10)%10 + 48;

        Nokia5110_SetCursor(1,3);
        Nokia5110_OutString("Last Score");

        Nokia5110_SetCursor(0,4);
        Nokia5110_OutString(LastScore);
    }
    else{
        Nokia5110_SetCursor(0,3);
        Nokia5110_OutString("No scores");
    }
}

void PrintHelp(){

    Nokia5110_Clear();
    Nokia5110_ClearBuffer();

    SysCtlDelay(3000000);
    Nokia5110_PrintBMP2(0,0,TankE,5,5);
    Nokia5110_DisplayBuffer();

    Nokia5110_SetCursor(1,0);
    Nokia5110_OutString("Help");

    Nokia5110_SetCursor(0,1);
    Nokia5110_OutString("Destroy the");
    Nokia5110_SetCursor(0,2);
    Nokia5110_OutString("other tanks");
    Nokia5110_SetCursor(0,3);
    Nokia5110_OutString("before they");
    Nokia5110_SetCursor(0,4);
    Nokia5110_OutString("get to your");
    Nokia5110_SetCursor(0,5);
    Nokia5110_OutString("deer.     +");
}

void PrintHelp2(){

    Nokia5110_Clear();
    Nokia5110_ClearBuffer();

    SysCtlDelay(3000000);
    Nokia5110_PrintBMP2(0,0,TankE,5,5);
    Nokia5110_DisplayBuffer();

    Nokia5110_SetCursor(1,0);
    Nokia5110_OutString("Help");

    Nokia5110_SetCursor(0,1);
    Nokia5110_OutString("Dont touch");
    Nokia5110_SetCursor(0,2);
    Nokia5110_OutString("the borders");
    Nokia5110_SetCursor(0,3);
    Nokia5110_OutString("Buttons");
    Nokia5110_SetCursor(0,4);
    Nokia5110_OutString("< = Rotate");
    Nokia5110_SetCursor(0,5);
    Nokia5110_OutString("> = Shoot");
}

#endif
