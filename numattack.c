/* Copyright 2019 Noah M. Walker - All Rights Reserved

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

int *wall;
int score=0;
//enemy
int enemyx;
int enemyy;
int enemyval;
bool has_wand;
int play=1;
int enemydelay=5000;
int tmp;
int counter;
int level=1;
int wands=0;
bool debug=0;
WINDOW *canvas;
time_t startstamp;
time_t endstamp;
int width=22;
int height=7;
int main(int argc, char *argv[])
{
printf("[10;100][11;50]");
if(argc>1){
if(!strcmp(argv[1],"-d")){
debug=1;
}
for(int i=1;i<argc;i++){
//printf("%s\n",argv[i]);
	if(!strcmp(argv[i],"-d")){
	debug=1;
	}
	if(!strcmp(argv[i],"-w")){
		if(argc<i+1){
		return 0;
		}
	width=atoi(argv[i+1]);
	}
	if(!strcmp(argv[i],"-h")){
		if(argc<i+1){
		return 0;
		}
	height=atoi(argv[i+1]);
	}
}
}
//printf("%i,%i\n",width,height);
//exit(0);
wall=malloc(sizeof(int)*height);
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
draw_wall();
while(play){
enemyx--;
draw();
refresh();
if(enemyx==0){
//draw();
draw_wall();
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
int draw_wall(){
clear();
for(int a=0;a<height;a++){
move(a,0);
	if(wall[a]==0){ //draw wall
	printw("#");
	}else{
	printw(" ");
	}
}
mvprintw(height,0,"score: %d level: %d wands: %d",score,level,wands);
if(debug){
mvprintw(height+1,0,"enemy delay: %d", enemydelay);
}
//draw();
}
int draw(){
move(enemyy,enemyx);
if(has_wand){
printw("%d¥ ",enemyval);
}else{
printw("%d ",enemyval);
}
}
int newenemy(){
enemyval=(rand()%10);
enemyx=width;
enemyy=(rand()%height);
has_wand=0;
if(!(rand()%(level*10))){ //give enemy wand depending on level.
has_wand=1;
}
}
int attack(){
if((tmp==48)&&(enemyval==0)){ //winning
draw_wall();
score++;
if(has_wand){
wands++;
}
beep();
if((score%10)==0){
level++;
if(enemydelay>1000){ //speed things up on new level
enemydelay-=200;
}else{
enemydelay=1000;
}
}
newenemy();
}
if((tmp==49)&&(enemyval==1)){//1
enemyval--;
}
if((tmp==50)&&(enemyval==2)){//2
enemyval--;
}
if((tmp==51)&&(enemyval==3)){//3
enemyval--;
}
if((tmp==52)&&(enemyval==4)){//4
enemyval--;
}
if((tmp==53)&&(enemyval==5)){//5
enemyval--;
}
if((tmp==54)&&(enemyval==6)){//6
enemyval--;
}
if((tmp==55)&&(enemyval==7)){ //7
enemyval--;
}
if((tmp==56)&&(enemyval==8)){ //8
enemyval--;
}
if((tmp==57)&&(enemyval==9)){ //key 9
enemyval--;
}
if((tmp==10)&&(wands>0)){ //use wand: enter key
for(int i=0;i<7;i++){
wall[i]=0;
}
wands--;
}
draw();
}
