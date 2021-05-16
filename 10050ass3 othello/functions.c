//
// Created by 75729 on 2021/5/16.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "protypes.h"
#define Player1 1//Player1
#define Player2 2//Player2

int playCurrent;// current player
int sign = 1;//player 1 sign
int board[8][8];// the board with 8x8
char playername[2][50];//store the name of each player it can set by player
int numberplay1 = 0; //player 1 score
int numberplay2 = 0; //player 2 score
void start()//start the game
{
    initBoard();//put board first
    while(1)
    {
        count();//count each player score after each play
        printBoard();// output the place and showing the board
        if(getSign())//get the place input
        {
            printBoard();// show the board
            printf("GAME OVER\n\n");
            if(numberplay1 > numberplay2){
                printf("%s WIN\n\n",playername[0]);
            }else if(numberplay1 < numberplay2){
                printf("%s WIN\n\n",playername[1]);
            }else{
                printf("Tie\n\n");
            }
            break;
        }
        overturnPlayCurrent();//turn to next player
    }
}

void initBoard()
{
    int i;
    int j;
    printf("\t***  Welcome to Othello!  ***\n");
    printf("\nEnter name of Player 1 (Black): ");
    scanf("%s",playername[0]);
    printf("\nEnter name of Player 2 (White): ");
    scanf("%s",playername[1]);
    playCurrent = Player1;
    for (i = 0; i<8; i++)
    {
        for (j = 0; j<8; j++)
        {
            board[i][j] = 0; //initialize each point on board with 0
        }
    }
    board[3][3] = 1;
    board[3][4] = 2;
    board[4][3] = 2;
    board[4][4] = 1;
}

void printBoard()
{
    int i ,j;
    system("cls");
    printf("\t***  Welcome to Othello!  ***\n");
    printf("\nEnter name of Player 1 (Black): %s\n" ,playername[0]);
    printf("\nEnter name of Player 2 (White): %s\n", playername[1]);
    printf("\n\tScore: %s (Black) %d:%d %s (White)\n",
           playername[0],numberplay1,numberplay2,playername[1]);
    for(i=0;i<8;i++)
    {
        printf("\t    ");
        for(j=1;j<=8;j++){
            printf("--- ");
        }
        printf("\n\t");
        printf("%d  ",i+1);
        for(j=0;j<8;j++){
            printf("|");
            if(board[i][j] == 1){
                printf(" B ");
            }else if(board[i][j] == 2){
                printf(" W ");
            }else{
                printf("   ");
            }
        }
        printf("|\n");
    }
    printf("\t    ");
    for(j=1;j<=8;j++){
        printf("--- ");
    }
    printf("\n\t     ");
    for(j=1;j<=8;j++){
        printf("%c   ",j+96);
    }

}

int getSign()
{
    int number;
    char c[5];
    printf("\n\n");

    if(playChess(playCurrent)){//judge the place whether or not available
        overturnPlayCurrent();
        if(playChess(playCurrent)){//if 2 players can not place the piece then game over
            return 1;//game over return
        }
    }

    while(1){

        printf("Please %s input the location ",playername[playCurrent-1]);
        scanf("%d%s",&number,c);
        if((number < 1)||(number > 8)||(c[0] < 'a')||(c[0] > 'h')){
            printf("location wrong\n");
            continue;
        }
        if(isDown(number-1 , (int)(c[0]-96)-1 , playCurrent)){
            printf("you can not take it to this position\n");
            continue;
        }
        board[number - 1][(int)(c[0]-96)-1] = playCurrent;

        swap(number - 1 , (int)(c[0]-96)-1 , playCurrent);//change the piece belonging different player

        break;
    }

    return 0;
}


void count()// count currently score
{
    int i ,j;
    numberplay1 = 0; //player 1 piece num
    numberplay2 = 0; //player 2 piece num
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(board[i][j] == 1){
                numberplay1++;
            }else if(board[i][j] == 2){
                numberplay2++;
            }
        }
    }
}

int playChess(int a)
{
    int i,j;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(!isDown(i , j , a)){
                return 0;
            }
        }
    }
    return 1;
}

void overturnPlayCurrent()
{
    if(playCurrent == 1){
        playCurrent = 2;
    }else{
        playCurrent = 1;
    }
}

int isDown(int i , int j ,int a)
{
    int b;
    int p ,q ,flag;
    if(board[i][j] != 0){
        return 1;
    }

    if(a == 1){
        b = 2;
    }else{
        b = 1;
    }

    if((j+2<8)&&(board[i][j+1] == b)){
        flag = 0;
        for(p=j+2;p<8;p++){
            if(board[i][p] == 0){
                break;
            }
            if(board[i][p] == a){
                flag = 1;
            }
        }
        if(flag == 1){
            return 0;
        }
    }

    if((j-2>=0)&&(board[i][j-1] == b)){
        flag = 0;
        for(p=j-2;p>=0;p--){
            if(board[i][p] == 0){
                break;
            }
            if(board[i][p] == a){
                flag = 1;
            }
        }
        if(flag == 1){
            return 0;
        }
    }

    if((i+2<8)&&(board[i+1][j] == b)){
        flag = 0;
        for(p=i+2;p<8;p++){
            if(board[p][j] == 0){
                break;
            }
            if(board[p][j] == a){
                flag = 1;
            }
        }
        if(flag == 1){
            return 0;
        }
    }

    if((i-2>=0)&&(board[i-1][j] == b)){
        flag = 0;
        for(p=i-2;p>=0;p--){
            if(board[p][j] == 0){
                break;
            }
            if(board[p][j] == a){
                flag = 1;
            }
        }
        if(flag == 1){
            return 0;
        }
    }

    if((i+2<8)&&(j+2<8)&&(board[i+1][j+1] == b)){
        flag = 0;
        for(p=i+2 , q=j+2 ;p<8 && q<8;p++ , q++){
            if(board[p][q] == 0){
                break;
            }
            if(board[p][q] == a){
                flag = 1;
            }
        }
        if(flag == 1){
            return 0;
        }
    }

    if((i+2<8)&&(j-2>=0)&&(board[i+1][j-1] == b)){
        flag = 0;
        for(p=i+2 , q=j-2 ;p<8 && q>=0;p++ , q--){
            if(board[p][q] == 0){
                break;
            }
            if(board[p][q] == a){
                flag = 1;
            }
        }
        if(flag == 1){
            return 0;
        }
    }

    if((i-2>=0)&&(j-2>=0)&&(board[i-1][j-1] == b)){
        flag = 0;
        for(p=i-2 , q=j-2 ;p>=0 && q>=0;p-- , q--){
            if(board[p][q] == 0){
                break;
            }
            if(board[p][q] == a){
                flag = 1;
            }
        }
        if(flag == 1){
            return 0;
        }
    }

    if((i-2>=0)&&(j+2<8)&&(board[i-1][j+1] == b)){
        flag = 0;
        for(p=i-2 , q=j+2 ;p>=0 && q<8;p-- , q++){
            if(board[p][q] == 0){
                break;
            }
            if(board[p][q] == a){
                flag = 1;
            }
        }
        if(flag == 1){
            return 0;
        }
    }

    return 1;
}

void swap(int i ,int j , int a)
{
    int p,q;
    int b ,flag;

    if(a == 1){
        b = 2;
    }else{
        b = 1;
    }

    if((j+2<8)&&(board[i][j+1] == b)){
        flag = 0;
        for(p=j+2;p<8;p++){
            if(board[i][p] == 0){
                break;
            }
            if(board[i][p] == a){
                flag = 1;
            }
        }
        if(flag == 1){
            for(p=j+1;p<8;p++){
                if(board[i][p] == 0){
                    break;
                }
                board[i][p] = a;
            }
        }
    }

    if((j-2>=0)&&(board[i][j-1] == b)){
        flag = 0;
        for(p=j-2;p>=0;p--){
            if(board[i][p] == 0){
                break;
            }
            if(board[i][p] == a){
                flag = 1;
            }
        }
        if(flag == 1){
            for(p=j-1;p>=0;p--){
                if(board[i][p] == 0){
                    break;
                }
                board[i][p] = a;
            }
        }
    }

    if((i+2<8)&&(board[i+1][j] == b)){
        flag = 0;
        for(p=i+2;p<8;p++){
            if(board[p][j] == 0){
                break;
            }
            if(board[p][j] == a){
                flag = 1;
            }
        }
        if(flag == 1){
            for(p=i+1;p<8;p++){
                if(board[p][j] == 0){
                    break;
                }
                board[p][j] = a;
            }
        }
    }

    if((i-2>=0)&&(board[i-1][j] == b)){
        flag = 0;
        for(p=i-2;p>=0;p--){
            if(board[p][j] == 0){
                break;
            }
            if(board[p][j] == a){
                flag = 1;
            }
        }
        if(flag == 1){
            for(p=i-1;p>=0;p--){
                if(board[p][j] == 0){
                    break;
                }
                board[p][j] = a;
            }
        }
    }

    if((i+2<8)&&(j+2<8)&&(board[i+1][j+1] == b)){
        flag = 0;
        for(p=i+2 , q=j+2 ;p<8 && q<8;p++ , q++){
            if(board[p][q] == 0){
                break;
            }
            if(board[p][q] == a){
                flag = 1;
            }
        }
        if(flag == 1){
            for(p=i+1 , q=j+1 ;p<8 && q<8;p++ , q++){
                if(board[p][q] == 0){
                    break;
                }
                board[p][q] = a;
            }
        }
    }

    if((i+2<8)&&(j-2>=0)&&(board[i+1][j-1] == b)){
        flag = 0;
        for(p=i+2 , q=j-2 ;p<8 && q>=0;p++ , q--){
            if(board[p][q] == 0){
                break;
            }
            if(board[p][q] == a){
                flag = 1;
            }
        }
        if(flag == 1){
            for(p=i+1 , q=j-1 ;p<8 && q>=0;p++ , q--){
                if(board[p][q] == 0){
                    break;
                }
                board[p][q] = a;
            }
        }
    }

    if((i-2>=0)&&(j-2>=0)&&(board[i-1][j-1] == b)){
        flag = 0;
        for(p=i-2 , q=j-2 ;p>=0 && q>=0;p-- , q--){
            if(board[p][q] == 0){
                break;
            }
            if(board[p][q] == a){
                flag = 1;
            }
        }
        if(flag == 1){
            for(p=i-1 , q=j-1 ;p>=0 && q>=0;p-- , q--){
                if(board[p][q] == 0){
                    break;
                }
                board[p][q] = a;
            }
        }
    }

    if((i-2>=0)&&(j+2<8)&&(board[i-1][j+1] == b))
    {
        flag = 0;
        for(p=i-2 , q=j+2 ;p>=0 && q<8;p-- , q++){
            if(board[p][q] == 0){
                break;
            }
            if(board[p][q] == a){
                flag = 1;
            }
        }
        if(flag == 1){
            for(p=i-1 , q=j+1 ;p>=0 && q<8;p-- , q++){
                if(board[p][q] == 0){
                    break;
                }
                board[p][q] = a;
            }
        }
    }
}