#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/input.h"

void gameInput(SDL_Event *e, int *runing, float *poz_X, float poz_Y, int *stage){
    while (SDL_PollEvent(e)) {
        if (e->type == SDL_QUIT) {
            *runing = 0;
        }
        
        if(e->key.keysym.sym){
            switch(e->key.keysym.sym){
                case SDLK_d:
                    if(!rightCollision(poz_X)){
                        *poz_X += 18;
                    }
                    break;
                
                case SDLK_a:
                    if(!leftCollision(poz_X)){
                        *poz_X -= 18;
                    }
                    break;
                
                //menus navigation
                case SDLK_ESCAPE:
                *stage = 1;
                break;
            }
        }
    }
}

void menuInput(SDL_Event *e, int *runing, int *stage, int *option, int *option_arrow_X,
    int *option_arrow_Y){

    while (SDL_PollEvent(e)) {
        if (e->type == SDL_QUIT) {
            *runing = 0;
        }
        
        if(e->type == SDL_KEYDOWN && e->key.repeat == 0){
            switch(e->key.keysym.sym){
                case SDLK_RETURN:
                    if(*option == 1){*stage = 2;}
                    else if(*option == 3){*stage = 3;}
                    else if(*option == 2){*stage = 4;}
                    break;

                case SDLK_DOWN:
                    if(*option == 3){
                        *option = 1;
                    }
                    else{
                        *option += 1;
                    }
                    break;

                case SDLK_UP:
                    if(*option == 1){
                        *option = 3;
                    }
                    else{
                        *option -= 1;
                    }
                    break;

                case SDLK_2:
                    *stage = 2;
                    break;
                
                case SDLK_3:
                    *stage = 3;
                    break;
            }
        }
        else if(*option == 1){
            *option_arrow_X = 500;
            *option_arrow_Y = 400;
        }

        else if(*option == 2){
            *option_arrow_X = 500;
            *option_arrow_Y = 450;
        }
        
        else if(*option == 3){
            *option_arrow_X = 460;
            *option_arrow_Y = 500;
        }
    }
}

void settingsInput(SDL_Event *e, int *runing, int *stage){
    while (SDL_PollEvent(e)) {
        if (e->type == SDL_QUIT) {
            *runing = 0;
        }
        
        if(e->key.keysym.sym){
            switch(e->key.keysym.sym){
                case SDLK_ESCAPE:
                    *stage = 1;
                    break;
            }
        }
    }
}

void infoInput(SDL_Event *e, int *runing, int *stage){
    while (SDL_PollEvent(e)) {
        if (e->type == SDL_QUIT) {
            *runing = 0;
        }
        
        if(e->key.keysym.sym){
            switch(e->key.keysym.sym){
                case SDLK_ESCAPE:
                    *stage = 1;
                    break;
            }
        }
    }
}

bool leftCollision(float *poz_X){
    if(*poz_X <= 10){
        return true;
    }
    else{return false;}
}

bool rightCollision(float *poz_X){
    if(*poz_X >= 1110){
        return true;
    }
    else{return false;}
}