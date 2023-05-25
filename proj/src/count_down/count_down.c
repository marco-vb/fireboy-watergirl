#include "count_down.h"
int seconds_left=0,first,second,third;
int x=0,y=10;

int(start_counter)(int time){
    if(time<0) return 1;
    seconds_left=time;
    first= (int)time/100;
    second=(int) (time-first*100)/10;
    third=(int)(time-first*100-second*10);
    
    return 0;
}
int(draw_counter)(){
    draw_number((x+30),y, first);
    draw_number((x+60),y, second);
    draw_number((x+90),y, third);
    return 0;
}

int(decrement_counter)(){
    
    return start_counter(--seconds_left);
}

int(set_timer_pos)(int x_, int y_){
    x=x_;
    y=y_;
    return 0;
}

int(clear_timer)(){
    for(int i=0; i<54;i++){
        for(int j=0; j<54;j++){
            replace_with_background(x+j,y+i);
        }
    }
    return 0;
}

