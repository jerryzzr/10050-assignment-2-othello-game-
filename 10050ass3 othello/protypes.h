//
// Created by 75729 on 2021/5/16.
//

#ifndef INC_10050ASS3_OTHELLO_PROTYPES_H
#define INC_10050ASS3_OTHELLO_PROTYPES_H
void initBoard();// initialize the board
void printBoard();// print the current place of board
void start();//start game
int getSign();//get the player input
int isDown(int i , int j ,int a);// judge the place whether or not available due to the Othello rules
void overturnPlayCurrent();
int playChess(int a);//judge whether or not have place to input
void count();//count each player score
void swap(int i ,int j , int a);//change the piece
#endif //INC_10050ASS3_OTHELLO_PROTYPES_H
