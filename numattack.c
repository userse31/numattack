/* Copyright 2019

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, Inc., 675 Mass Ave, Cambridge MA 02139,
   USA; either version 2 of the License, or (at your option) any later
   version; incorporated herein by reference.
*/

#include <stdio.h>
#include <curses.h>
#include <time.h>
#include <math.h>

int wall[7];
int score=0;
int enemyx;
int enemyy;
int enemyval;
int play=1;
int enemydelay=5000;
int tmp;
int counter;
int level=1;
bool debug=0;
WINDOW *canvas;
time_t startstamp;
time_t endstamp;
int main(int argc, char *argv[])
{
if(argc==2){
if(!strcmp(argv[1],"-d")){
debug=1;
}
}
printf("(U");
startstamp=time(NULL);
srand(time(NULL));
//init
canvas=initscr();
noecho();
cbreak();
nodelay(stdscr,TRUE);
curs_set(0);
newenemy();
//main loop
while(play){
enemyx--;
draw();
refresh();
if(enemyx==0){
draw();
beep();
if(wall[enemyy]==0){
wall[enemyy]=1;
score=score-enemyval;
newenemy();
}else{
play=0;
}
}
for(counter=0;counter<enemydelay;counter++){
usleep(1);
tmp=getch();
if(tmp != -1){
attack();
}
}
}
endwin();
printf("Your score was: %d\n",score);
endstamp=time(NULL);
printf("You have been playing for %d seconds\n",endstamp-startstamp);
printf("Thank you for playing [36m[42mNumber Attack![37m[40m\n");
return 0;
}
int draw(){
clear();
for(int a=0;a<7;a++){
move(a,0);
if(wall[a]==0){
printw("#");
}else{
printw(" ");
}
}
move(enemyy,enemyx);
printw("%d",enemyval);
mvprintw(7,0,"score: %d",score);
if(debug){
mvprintw(8,0,"enemy delay: %d", enemydelay);
}
}
int newenemy(){
enemyval=(rand()%10);
enemyx=22;
enemyy=(rand()%7);
}
int attack(){
if((tmp==48)&&(enemyval==0)){ //winning
score++;
beep();
if((score%10)==0){
level++;
}
if(enemydelay>1000){
enemydelay-=100;
}else{
enemydelay=1000;
}
newenemy();
}
if((tmp==49)&&(enemyval==1)){
enemyval--;
}
if((tmp==50)&&(enemyval==2)){
enemyval--;
}
if((tmp==51)&&(enemyval==3)){
enemyval--;
}
if((tmp==52)&&(enemyval==4)){
enemyval--;
}
if((tmp==53)&&(enemyval==5)){
enemyval--;
}
if((tmp==54)&&(enemyval==6)){
enemyval--;
}
if((tmp==55)&&(enemyval==7)){
enemyval--;
}
if((tmp==56)&&(enemyval==8)){
enemyval--;
}
if((tmp==57)&&(enemyval==9)){
enemyval--;
}
draw();
}
