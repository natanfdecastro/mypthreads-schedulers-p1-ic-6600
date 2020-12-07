/*======================================================================
Copyright (C) 2020 Natan & Kenny

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Instituto Tecnologico de Costa Rica
    Principios de Sistemas Operativos - IC-6600

    Remember Remember (mypthreads-schedulers-p1-ic-6600)
    Disponible en: https://github.com/natanfdecastro/mypthreads-schedulers-p1-ic-6600

    Natan Fernandez de Castro - 2017105774
    Kenneth Rodriguez Murillo - 2018132752
========================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include "../mypthreads/my_mutex.h"
#include "../config/my_parser.h"

config* configuration;
int fieldLock;

char Top[11] = {' ', ' ', ' ', ' ', ' ', ' ',' ',' ',' ',' ',' '};
char SecTop[11] = {' ', ' ', ' ', ' ', ' ', ' ',' ',' ',' ',' ',' '};
char mid[11] = {' ', ' ', ' ', ' ', ' ', ' ',' ',' ',' ',' ',' '};
char SecBot[11] = {' ', ' ', ' ', ' ', ' ', ' ',' ',' ',' ',' ',' '};
char Bot[11] = {' ', ' ', ' ', ' ', ' ', ' ',' ',' ',' ',' ',' '};

char TopExp[10] = {' ', ' ', ' ', ' ', ' ', ' ',' ',' ',' ',' '};
char SecTopExp[10] = {' ', ' ', '*', '*', '*', ' ',' ',' ',' ',' '};
char midExp[10] = {' ', ' ', '*', '*', '*', '*','*',' ',' ',' '};
char SecBotExp[10] = {' ', ' ', '*', '*', '*', ' ',' ',' ',' ',' '};
char BotExp[10] = {' ', ' ', ' ', ' ', ' ', ' ',' ',' ',' ',' '};

char TopExpFin[10] = {' ', ' ', ' ', '*', '*', '*',' ',' ',' ',' '};
char SecTopExpFin[10] = {' ', ' ', '*', '*', '*', '*','*',' ',' ',' '};
char midExpFin[10] = {' ', '*', '*', '*', '*', '*','*','*',' ',' '};
char SecBotExpFin[10] = {' ', ' ', '*', '*', '*', '*','*',' ',' ',' '};
char BotExpFin[10] = {' ', ' ', ' ', '*', '*', '*',' ',' ',' ',' '};

void initialize_animation_lock(){
  my_mutex_init(&fieldLock);
}

void move_figure(void *arg){
   my_mutex_lock(&fieldLock);
   item_info *figure = (item_info *) arg;
   my_mutex_unlock(&fieldLock);

   my_mutex_lock(&fieldLock);
   monitor_info *temp_monitor = (monitor_info *) malloc(sizeof(monitor_info));
   temp_monitor = configuration -> monitors_list -> head;

   while(temp_monitor -> id != figure -> monitor_id){
     temp_monitor = temp_monitor -> next;
   }
   my_mutex_unlock(&fieldLock);

   my_mutex_lock(&fieldLock);
   figure -> posicion_actual_x = figure -> posicion_inicial_x;
   figure -> posicion_actual_y = figure -> posicion_inicial_y;
   my_mutex_unlock(&fieldLock);
   while(1){
     if(time(0) < figure -> tiempo_de_inicio){
       my_thread_yield();
     }
     else{
       while(figure -> posicion_actual_x != figure -> posicion_final_x || figure -> posicion_actual_y != figure -> posicion_final_y) {

            //wclear(temp_monitor -> canvas_window); // Clear the screen of all  previously-printed characters
            if(figure -> posicion_actual_y <= figure -> posicion_final_y){
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-3, figure->posicion_actual_x-1, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-3, figure->posicion_actual_x, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-3, figure->posicion_actual_x+1, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-3, figure->posicion_actual_x+2, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-3, figure->posicion_actual_x+3, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-3, figure->posicion_actual_x+4, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-3, figure->posicion_actual_x+5, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-3, figure->posicion_actual_x+6, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-3, figure->posicion_actual_x+7, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-3, figure->posicion_actual_x+8, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-3, figure->posicion_actual_x+9, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-3, figure->posicion_actual_x+10, " ");
            }
            if(figure -> posicion_actual_x <= figure -> posicion_final_x){
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-2, figure->posicion_actual_x-1, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-1, figure->posicion_actual_x-1, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y, figure->posicion_actual_x-1, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+1, figure->posicion_actual_x-1, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+2, figure->posicion_actual_x-1, " ");

            }
            if(figure -> posicion_actual_x >= figure -> posicion_final_x){
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-2, figure->posicion_actual_x+11, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-1, figure->posicion_actual_x+11, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y, figure->posicion_actual_x+11, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+1, figure->posicion_actual_x+11, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+2, figure->posicion_actual_x+11, " ");
            }
            if(figure -> posicion_actual_y >= figure -> posicion_final_y){
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+3, figure->posicion_actual_x-1, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+3, figure->posicion_actual_x, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+3, figure->posicion_actual_x+1, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+3, figure->posicion_actual_x+2, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+3, figure->posicion_actual_x+3, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+3, figure->posicion_actual_x+4, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+3, figure->posicion_actual_x+5, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+3, figure->posicion_actual_x+6, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+3, figure->posicion_actual_x+7, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+3, figure->posicion_actual_x+8, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+3, figure->posicion_actual_x+9, " ");
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+3, figure->posicion_actual_x+10, " ");
            }
            mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-2, figure->posicion_actual_x, figure->ascii_item[0]);
            mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-1, figure->posicion_actual_x, figure->ascii_item[1]);
            mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y, figure->posicion_actual_x, figure->ascii_item[2]);
            mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+1, figure->posicion_actual_x, figure->ascii_item[3]);
            mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+2, figure->posicion_actual_x, figure->ascii_item[4]);

            if(time(0) > figure -> tiempo_de_fin){
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-2, figure->posicion_actual_x, Top);
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-1, figure->posicion_actual_x, SecTop);
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y, figure->posicion_actual_x, mid);
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+1, figure->posicion_actual_x, SecBot);
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+2, figure->posicion_actual_x, Bot);
              wrefresh(temp_monitor-> canvas_window);
              usleep(800000);
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-2, figure->posicion_actual_x, TopExp);
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-1, figure->posicion_actual_x, SecTopExp);
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y, figure->posicion_actual_x, midExp);
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+1, figure->posicion_actual_x, SecBotExp);
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+2, figure->posicion_actual_x, BotExp);
              wrefresh(temp_monitor-> canvas_window);
              usleep(800000);
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-2, figure->posicion_actual_x, TopExpFin);
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-1, figure->posicion_actual_x, SecTopExpFin);
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y, figure->posicion_actual_x, midExpFin);
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+1, figure->posicion_actual_x, SecBotExpFin);
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+2, figure->posicion_actual_x, BotExpFin);
              wrefresh(temp_monitor-> canvas_window);
              usleep(700000);
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-2, figure->posicion_actual_x, Top);
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y-1, figure->posicion_actual_x, SecTop);
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y, figure->posicion_actual_x, mid);
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+1, figure->posicion_actual_x, SecBot);
              mvwprintw(temp_monitor -> canvas_window,figure ->posicion_actual_y+2, figure->posicion_actual_x, Bot);
              wrefresh(temp_monitor-> canvas_window);
              break;
            }

            my_mutex_lock(&fieldLock);
            if(figure ->posicion_actual_y < figure->posicion_final_y)
              figure ->posicion_actual_y++;
            if(figure ->posicion_actual_x < figure ->posicion_final_x)
              figure ->posicion_actual_x++;

            if(figure ->posicion_actual_y > figure ->posicion_final_y)
              figure ->posicion_actual_y--;
            if(figure ->posicion_actual_x > figure ->posicion_final_x)
              figure ->posicion_actual_x--;
            my_mutex_unlock(&fieldLock);

        wrefresh(temp_monitor-> canvas_window);

        usleep(900000); // Shorter delay between movements
      }
      break;
    }
  }
}

/*
my_animation(){

    int x_axis_size = 0, int y_axis_size = 0;
    int initial_time = 0; int ending_time = 0;

    printf(">>> Digite ancho y largo del canvas: ");
    scanf("%d %d", x_axis_size, y_axis_size);

    printf(">>> Digite tiempo inicial y final: ");
    scanf("%d %d", initial_time, ending_time);

}
*/
