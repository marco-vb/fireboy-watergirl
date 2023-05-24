#include "count_down.h"
int seconds_left=0,first,second,third;
int x=0,y=0;
xpm_map_t numbersala[10]={(xpm_map_t)n0_xpm,(xpm_map_t)n1_xpm,(xpm_map_t)n2_xpm,(xpm_map_t)n3_xpm,(xpm_map_t)n4_xpm,(xpm_map_t)n5_xpm,(xpm_map_t)n6_xpm,(xpm_map_t)n7_xpm,(xpm_map_t)n8_xpm,(xpm_map_t)n9_xpm};

int(start_counter)(int time){
    if(time<0) return 1;
    seconds_left=time;
    first= (int)time/100;
    second=(int) (time-first*100)/10;
    third=(int)(time-first*100-second*10);
    
    return 0;
}
int(draw_counter)(){
    clear_timer();
    draw_xpm(numbersala[first],x,y);
    draw_xpm(numbersala[second],x+18,y);
    draw_xpm(numbersala[third],x+36,y);
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
