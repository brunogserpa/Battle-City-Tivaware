#ifndef GAME_H_
#define GAME_H_

uint8_t ui8IntSource2;
int i, j;

void CheckDeer(int position[8][5], int n){
    if (position[n][0] >= 36-4 && position[n][0] <= 36+12 && position[n][1] >= 40-4){
        position[0][3] = 0;
    }
}

void Spawn(int matrix[84][48], int position[8][5], int n){
    int m;
    if(n == 0){
        m = 9;
    }
    else{
        m = n;
    }
    for(i = 0; i <=4; i++){
        for(j = 0; j <=4; j++){
            matrix[position[n][0]+i][position[n][1]+j] = m;
        }
    }
}

void Erase(int matrix[84][48], int position[8][5], int n){
    for(i = 0; i <=4; i++){
        for(j = 0; j <=4; j++){
            matrix[position[n][0]+i][position[n][1]+j] = 0;
        }
    }
}

void MovementMatrix(int matrix[84][48], int position[8][5], int n){
    int m;
    if(n == 0){
        m = 9;
    }
    else{
        m = n;
    }
    switch(position[n][2]){
    case 0:
        matrix[position[n][0]][position[n][1]+2-3] = m;
        matrix[position[n][0]+1][position[n][1]+2-3] = m;
        matrix[position[n][0]+2][position[n][1]+2-3] = m;
        matrix[position[n][0]+3][position[n][1]+2-3] = m;
        matrix[position[n][0]+4][position[n][1]+2-3] = m;
        matrix[position[n][0]][position[n][1]+2+2] = 0;
        matrix[position[n][0]+1][position[n][1]+2+2] = 0;
        matrix[position[n][0]+2][position[n][1]+2+2] = 0;
        matrix[position[n][0]+3][position[n][1]+2+2] = 0;
        matrix[position[n][0]+4][position[n][1]+2+2] = 0;
        break;

    case 1:
        matrix[position[n][0]+2+3][position[n][1]] = m;
        matrix[position[n][0]+2+3][position[n][1]+1] = m;
        matrix[position[n][0]+2+3][position[n][1]+2] = m;
        matrix[position[n][0]+2+3][position[n][1]+3] = m;
        matrix[position[n][0]+2+3][position[n][1]+4] = m;
        matrix[position[n][0]+2-2][position[n][1]] = 0;
        matrix[position[n][0]+2-2][position[n][1]+1] = 0;
        matrix[position[n][0]+2-2][position[n][1]+2] = 0;
        matrix[position[n][0]+2-2][position[n][1]+3] = 0;
        matrix[position[n][0]+2-2][position[n][1]+4] = 0;
        break;

    case 2:
        matrix[position[n][0]][position[n][1]+2+3] = m;
        matrix[position[n][0]+1][position[n][1]+2+3] = m;
        matrix[position[n][0]+2][position[n][1]+2+3] = m;
        matrix[position[n][0]+3][position[n][1]+2+3] = m;
        matrix[position[n][0]+4][position[n][1]+2+3] = m;
        matrix[position[n][0]][position[n][1]+2-2] = 0;
        matrix[position[n][0]+1][position[n][1]+2-2] = 0;
        matrix[position[n][0]+2][position[n][1]+2-2] = 0;
        matrix[position[n][0]+3][position[n][1]+2-2] = 0;
        matrix[position[n][0]+4][position[n][1]+2-2] = 0;
        break;

    case 3:
        matrix[position[n][0]+2-3][position[n][1]] = m;
        matrix[position[n][0]+2-3][position[n][1]+1] = m;
        matrix[position[n][0]+2-3][position[n][1]+2] = m;
        matrix[position[n][0]+2-3][position[n][1]+3] = m;
        matrix[position[n][0]+2-3][position[n][1]+4] = m;
        matrix[position[n][0]+2+2][position[n][1]] = 0;
        matrix[position[n][0]+2+2][position[n][1]+1] = 0;
        matrix[position[n][0]+2+2][position[n][1]+2] = 0;
        matrix[position[n][0]+2+2][position[n][1]+3] = 0;
        matrix[position[n][0]+2+2][position[n][1]+4] = 0;
        break;
    }
}

void NPCMovement (int matrix[84][48], int counternpc, int position[8][5], int i){ //, *matrix){
    if((counternpc*position[i][0]+position[i][1]*i)%10 == 1 || position[i][4] == 1){
        if (position[i][2] == 3){
            position[i][2] = 0;
        }
        else position[i][2]++;
        position[i][4] = 0;
    }
    switch(position[i][2]){
    case 0:
        if(position[i][1] > 2 &&
                matrix[position[i][0]][position[i][1]+2-3] < 2 &&
                matrix[position[i][0]+1][position[i][1]+2-3] < 2 &&
                matrix[position[i][0]+2][position[i][1]+2-3] < 2 &&
                matrix[position[i][0]+3][position[i][1]+2-3] < 2 &&
                matrix[position[i][0]+4][position[i][1]+2-3] < 2){
            MovementMatrix(matrix, position, i);
            position[i][1]--;
        }
        else {
            position[i][4] = 1;
        }
        break;

    case 1:
        if(position[i][0] < 77 &&
                matrix[position[i][0]+2+3][position[i][1]] < 2 &&
                matrix[position[i][0]+2+3][position[i][1]+1] < 2 &&
                matrix[position[i][0]+2+3][position[i][1]+2] < 2 &&
                matrix[position[i][0]+2+3][position[i][1]+3] < 2 &&
                matrix[position[i][0]+2+3][position[i][1]+4] < 2){
            MovementMatrix(matrix, position, i);
            position[i][0]++;
        }
        else {
            position[i][4] = 1;
        }
        break;

    case 2:
        if(position[i][1] < 41 &&
                matrix[position[i][0]][position[i][1]+2+3] < 2 &&
                matrix[position[i][0]+1][position[i][1]+2+3] < 2 &&
                matrix[position[i][0]+2][position[i][1]+2+3] < 2 &&
                matrix[position[i][0]+3][position[i][1]+2+3] < 2 &&
                matrix[position[i][0]+4][position[i][1]+2+3] < 2 ){
            MovementMatrix(matrix, position, i);
            position[i][1]++;
        }
        else {
            position[i][4] = 1;
        }
        break;

    case 3:
        if(position[i][0] > 2 &&
                matrix[position[i][0]+2-3][position[i][1]] < 2 &&
                matrix[position[i][0]+2-3][position[i][1]+1] < 2 &&
                matrix[position[i][0]+2-3][position[i][1]+2] < 2 &&
                matrix[position[i][0]+2-3][position[i][1]+3] < 2 &&
                matrix[position[i][0]+2-3][position[i][1]+4] < 2 ){
            MovementMatrix(matrix, position, i);
            position[i][0]--;
        }
        else {
            position[i][4] = 1;
        }
        break;
    }
    CheckDeer(position, i);
}

void Gaming (int position[8][5], int matrix[84][48], int* kills){
    //Tank Movement
    //Verify where the tank is facing to make the next move
    //If it reaches the borders the "else" kills it
    switch(position[0][2]){
    case 0:     //North
        if(position[0][1] > 1){
            if(
                matrix[position[0][0]][position[0][1]+2-3] < 2 &&
                matrix[position[0][0]+1][position[0][1]+2-3] < 2 &&
                matrix[position[0][0]+2][position[0][1]+2-3] < 2 &&
                matrix[position[0][0]+3][position[0][1]+2-3] < 2 &&
                matrix[position[0][0]+4][position[0][1]+2-3] < 2){
                MovementMatrix(matrix, position, 0);
                position[0][1]--;
            }
        }
        else {
            position[0][3] = 0;
        }
        break;

    case 1:     //East
        if(position[0][0] < 78){
            if(
                matrix[position[0][0]+2+3][position[0][1]] < 2 &&
                matrix[position[0][0]+2+3][position[0][1]+1] < 2 &&
                matrix[position[0][0]+2+3][position[0][1]+2] < 2 &&
                matrix[position[0][0]+2+3][position[0][1]+3] < 2 &&
                matrix[position[0][0]+2+3][position[0][1]+4] < 2){
                MovementMatrix(matrix, position, 0);
                position[0][0]++;
            }
        }
        else {
            position[0][3] = 0;
        }
        break;

    case 2:     //South
        if(position[0][1] < 42){
            if(
                matrix[position[0][0]][position[0][1]+2+3] < 2 &&
                matrix[position[0][0]+1][position[0][1]+2+3] < 2 &&
                matrix[position[0][0]+2][position[0][1]+2+3] < 2 &&
                matrix[position[0][0]+3][position[0][1]+2+3] < 2 &&
                matrix[position[0][0]+4][position[0][1]+2+3] < 2 ){
                MovementMatrix(matrix, position, 0);
                position[0][1]++;
            }
        }
        else {
            position[0][3] = 0;
        }
        break;

    case 3:     //West
        if(position[0][0] > 1){
            if(
                matrix[position[0][0]+2-3][position[0][1]] < 2 &&
                matrix[position[0][0]+2-3][position[0][1]+1] < 2 &&
                matrix[position[0][0]+2-3][position[0][1]+2] < 2 &&
                matrix[position[0][0]+2-3][position[0][1]+3] < 2 &&
                matrix[position[0][0]+2-3][position[0][1]+4] < 2 ){
                MovementMatrix(matrix, position, 0);
                position[0][0]--;
            }
        }
        else {
            position[0][3] = 0;
        }
        break;

    }
    //Bullet Movement
    //The bullet works the same way as the tank
    if(position[1][3] == 1){
        switch(position[1][2]){
        case 0:
            if(position[1][1] > 2 && matrix[position[1][0]][position[1][1]-2] != 8){
                position[1][1] -= 2;
                if((matrix[position[1][0]][position[1][1]]>1 && matrix[position[1][0]][position[1][1]]<8)){
                    position[matrix[position[1][0]][position[1][1]]][3] = 0; //Kill target
                    *kills = *kills+1;
                    Erase(matrix, position, matrix[position[1][0]][position[1][1]]);
                    position[1][3] = 0;
                }
                matrix[position[1][0]][position[1][1]-1] = 1;
                matrix[position[1][0]][position[1][1]] = 1;
                matrix[position[1][0]][position[1][1]+1] = 0;
                matrix[position[1][0]][position[1][1]+2] = 0;
            }
            else position[1][3] = 0;
            break;

        case 1:
            if(position[1][0] < 80 && matrix[position[1][0]+2][position[1][1]] != 8){
                position[1][0] += 2;
                if((matrix[position[1][0]][position[1][1]]>1 && matrix[position[1][0]][position[1][1]]<8)){
                    position[matrix[position[1][0]][position[1][1]]][3] = 0; //Kill target
                    *kills = *kills+1;
                    Erase(matrix, position, matrix[position[1][0]][position[1][1]]);
                    position[1][3] = 0;
                }
                matrix[position[1][0]+1][position[1][1]] = 1;
                matrix[position[1][0]][position[1][1]] = 1;
                matrix[position[1][0]-1][position[1][1]] = 0;
                matrix[position[1][0]-2][position[1][1]] = 0;
            }
            else position[1][3] = 0;
            break;

        case 2:
            if(position[1][1] < 46 && matrix[position[1][0]][position[1][1]+2] != 8){
                position[1][1] += 2;
                if((matrix[position[1][0]][position[1][1]]>1 && matrix[position[1][0]][position[1][1]]<8)){
                    position[matrix[position[1][0]][position[1][1]]][3] = 0; //Kill target
                    *kills = *kills+1;
                    Erase(matrix, position, matrix[position[1][0]][position[1][1]]);
                    position[1][3] = 0;
                }
                matrix[position[1][0]][position[1][1]+1] = 1;
                matrix[position[1][0]][position[1][1]] = 1;
                matrix[position[1][0]][position[1][1]-1] = 0;
                matrix[position[1][0]][position[1][1]-2] = 0;
            }
            else position[1][3] = 0;
            break;

        case 3:
            if(position[1][0] > 2 && matrix[position[1][0]-2][position[1][1]] != 8){
                position[1][0] -= 2;
                if((matrix[position[1][0]][position[1][1]]>1 && matrix[position[1][0]][position[1][1]]<8)){
                    position[matrix[position[1][0]][position[1][1]]][3] = 0; //Kill target
                    *kills = *kills+1;
                    Erase(matrix, position, matrix[position[1][0]][position[1][1]]);
                    position[1][3] = 0;
                }
                matrix[position[1][0]-1][position[1][1]] = 1;
                matrix[position[1][0]][position[1][1]] = 1;
                matrix[position[1][0]+1][position[1][1]] = 0;
                matrix[position[1][0]+2][position[1][1]] = 0;
            }
            else position[1][3] = 0;
            break;
        }
    }

    //Read the button input and verify which one is it
    ui8IntSource2 = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0);

    if ((ui8IntSource2 & 0x10) ==  0x00){                //SW1 Rotates the tank clockwise
        int debounce = 0;
        while (debounce < 1000000){
            debounce++;
        }
        if ((ui8IntSource2 & 0x10) ==  0x00){
            if (position[0][2] == 3){
                position[0][2] = 0;
            }
            else position[0][2]++;
        }
    }
    if ((ui8IntSource2 & 0x01) ==  0x00){                //SW2 Shoot
        int debounce = 0;
        while (debounce < 1000000){
            debounce++;
        }
        if ((ui8IntSource2 & 0x01) ==  0x00){
            position[1][3] = 1;
            position[1][2] = position[0][2];

            //Verify the starting point of the bullet
            switch(position[0][2]){
            case 0:
                position[1][0] = position[0][0] +2;
                position[1][1] = position[0][1];
                break;

            case 1:
                position[1][0] = position[0][0] +4;
                position[1][1] = position[0][1] +2;
                break;

            case 2:
                position[1][0] = position[0][0] +2;
                position[1][1] = position[0][1] +4;
                break;

            case 3:
                position[1][0] = position[0][0];
                position[1][1] = position[0][1] +2;
                break;
            }
        }
    }
}

#endif
