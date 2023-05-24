#include "character.h"
int (create_Characters)(){
    fireboy = (Character*)malloc(sizeof(Character));

    if (fireboy == NULL) return 1;
    fireboy->sprite = create_sprite((xpm_map_t)(fire_default_xpm),100,100,10,10);
    fireboy->direction=DEFAULT;
    fireboy->animation_delay=6;
    fireboy->current_sprite=0;
    fireboy->frames_to_next_change=0;
  
    fireboy->left[0]=load_img((xpm_map_t)fireL1_xpm);
    fireboy->left[1]=load_img((xpm_map_t)fireL2_xpm);
    fireboy->left[2]=load_img((xpm_map_t)fireL3_xpm);
    fireboy->left[3]=load_img((xpm_map_t)fireL4_xpm);
    fireboy->left[4]=load_img((xpm_map_t)fireL5_xpm);
    fireboy->left[5]=load_img((xpm_map_t)fireL6_xpm);
    fireboy->right[0]=load_img((xpm_map_t)fireR1_xpm);
    fireboy->right[1]=load_img((xpm_map_t)fireR2_xpm);
    fireboy->right[2]=load_img((xpm_map_t)fireR3_xpm);
    fireboy->right[3]=load_img((xpm_map_t)fireR4_xpm);
    fireboy->right[4]=load_img((xpm_map_t)fireR5_xpm);
    fireboy->right[5]=load_img((xpm_map_t)fireR6_xpm);
    fireboy->front=load_img((xpm_map_t)fire_default_xpm);

    watergirl = (Character*)malloc(sizeof(Character));

    if (watergirl == NULL) return 1;
    watergirl->sprite = create_sprite((xpm_map_t)(water_default_xpm),100,100,10,10);
    watergirl->left[0]=load_img((xpm_map_t)waterL1_xpm);
    watergirl->left[1]=load_img((xpm_map_t)waterL2_xpm);
    watergirl->left[2]=load_img((xpm_map_t)waterL3_xpm);
    watergirl->left[3]=load_img((xpm_map_t)waterL4_xpm);
    watergirl->left[4]=load_img((xpm_map_t)waterL5_xpm);
    watergirl->left[5]=load_img((xpm_map_t)waterL6_xpm);
    watergirl->right[0]=load_img((xpm_map_t)waterR1_xpm);
    watergirl->right[1]=load_img((xpm_map_t)waterR2_xpm);
    watergirl->right[2]=load_img((xpm_map_t)waterR3_xpm);
    watergirl->right[3]=load_img((xpm_map_t)waterR4_xpm);
    watergirl->right[4]=load_img((xpm_map_t)waterR5_xpm);
    watergirl->right[5]=load_img((xpm_map_t)waterR6_xpm);
    watergirl->front=load_img((xpm_map_t)water_default_xpm);

    return 0;
}

int (setPosition)(Character * character, int x, int y){
    character->sprite->x=x;
    character->sprite->y=y;
    return 0;
}

void (moveLeft)(Character * character){
    character->sprite->x-= character->sprite->xspeed; 

    if(character->direction==LEFT){
        if((character->frames_to_next_change++)== character->animation_delay){
            character->current_sprite++;
            character->frames_to_next_change=0;
            if(character->current_sprite>5) character->current_sprite=0;
        }
    }else{
   
        character->direction=LEFT;
        character->current_sprite=0;
        character->frames_to_next_change=0;
    }
}
void (moveRight)(Character * character){
    character->sprite->x+= character->sprite->xspeed; 
    if(character->direction==RIGHT){
        if((character->frames_to_next_change++)== character->animation_delay){
            character->current_sprite++;
            character->frames_to_next_change=0;
            if(character->current_sprite>5) character->current_sprite=0;
        }
    }else{
        character->direction=RIGHT;
        character->current_sprite=0;
        character->frames_to_next_change=0;
    }
}


void  (character_current_sprite)(Character * character){
        if(character->direction==LEFT){
              character->sprite->map=character->left[character->current_sprite];
             //memcpy(character->sprite->map,character->left[character->current_sprite],sizeof(&character->sprite->map));
        }else if(character->direction==RIGHT){
           memcpy(character->sprite->map, character->right[character->current_sprite], sizeof(*character->right[character->current_sprite]));

        }else{
            character->sprite->map= character->front;
        }
}


int(draw_character)(Character * Character){
    character_current_sprite(Character);
    draw_sprite((Character->sprite));
    return 0;
}

