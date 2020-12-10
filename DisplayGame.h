#ifndef DISPLAYGAME_H_
#define DISPLAYGAME_H_

int i, j;

void PrintWeapon(int posx, int posy){
    Nokia5110_PrintBMP2(posx,posy,Weapon,1,1);
}

void PrintNPC(int posxnpc, int posynpc, int rotationnpc){
    switch(rotationnpc){
        case 1:
            Nokia5110_PrintBMP2(posxnpc,posynpc,NPCew,5,5);
            break;
        case 2:
            Nokia5110_PrintBMP2(posxnpc,posynpc,NPCns,5,5);
            break;

        case 3:
            Nokia5110_PrintBMP2(posxnpc,posynpc,NPCew,5,5);
            break;

        default:
            Nokia5110_PrintBMP2(posxnpc,posynpc,NPCns,5,5);
            break;
    }
}

void PrintGame(int position[8][5], int level){

    Nokia5110_ClearBuffer();

    SysCtlDelay(3000000);

    if(level == 1){
        Nokia5110_PrintBMP2(0,0,Level1Map,84,48);
    }
    else{
        Nokia5110_PrintBMP2(0,0,Level0Map,84,48);
    }
    Nokia5110_PrintBMP2(36,40,Deer,12,7);

    switch(position[0][2]){
        case 1:
            Nokia5110_PrintBMP2(position[0][0],position[0][1],TankE,5,5);
            break;
        case 2:
            Nokia5110_PrintBMP2(position[0][0],position[0][1],TankS,5,5);
            break;

        case 3:
            Nokia5110_PrintBMP2(position[0][0],position[0][1],TankW,5,5);
            break;

        default:
            Nokia5110_PrintBMP2(position[0][0],position[0][1],TankN,5,5);
            break;
    }
    for (i = 2; i <= 7; i++){
        if (position[i][3] == 1){
            PrintNPC(position[i][0], position[i][1], position[i][2]);
        }
    }
    if (position[1][3] == 1){
        PrintWeapon(position[1][0], position[1][1]);
    }
    Nokia5110_DisplayBuffer();
}

void PrintVictory(){
    Nokia5110_ClearBuffer();
    Nokia5110_PrintBMP2(0,0,VictoryScreen,84,48);
    Nokia5110_DisplayBuffer();
}

void PrintGameOver(){
    Nokia5110_ClearBuffer();
    Nokia5110_PrintBMP2(0,0,GameOverScreen,84,48);
    Nokia5110_DisplayBuffer();
}

void PrintLevel(int level){
    Nokia5110_ClearBuffer();
    if(level == 1){
         Nokia5110_PrintBMP2(0,0,Level1Start,84,48);
     }
     else{
         Nokia5110_PrintBMP2(0,0,Level0Start,84,48);
     }
    Nokia5110_DisplayBuffer();
}

#endif
