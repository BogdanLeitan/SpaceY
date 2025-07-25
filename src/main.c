#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "../include/input.h"
#include "../include/main.h"

int main(int argc, char* argv[]) {
    bool isCollision = false;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Eroare la inițializarea SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        printf("ERROR to SDL_image: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    if(TTF_Init() == -1){
        printf("Eroare TTF: %s\n", TTF_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "SpaceY",           
        SDL_WINDOWPOS_CENTERED,           
        SDL_WINDOWPOS_CENTERED,           
        width, heith,                         
        SDL_WINDOW_SHOWN                 
    );

    if (!window) {
        printf("Eroare la crearea ferestrei: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        printf("Eroare la crearea rendererului: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event e;

    Obstacole *obs = NULL;

    int *countEntry = NULL;
    bool *can = malloc(sizeof(bool));

    int rand_obj;
    int pozx;
    int pozy  = -100;
    int size;
    int runing = 1;
    int stage = 1;
    int option = 1;
    int option_arrow_X = 500;
    int option_arrow_Y = 400;
    int frameCounter = 0;
    int countTexture = 0;
    int randomY;
    int *temp = NULL;

    float backpoz1 = 0;
    float backpoz2 = -800;
    float move = -150;
    float poz_X = width / 2;

    bool isEntry = false;
    bool isAlgo = true;
    bool isArray1 = true;
    bool isArray2 = false;
    bool inDev = true;

    if(can != NULL){*can = true;}

    srand(time(NULL));
    
    SDL_Texture *rocket_img = IMG_LoadTexture(renderer, "../assets/rocket1.png");
    SDL_Texture *rocket_img2 = IMG_LoadTexture(renderer, "../assets/rocket2.png");
    SDL_Texture *rocket_img3 = IMG_LoadTexture(renderer, "../assets/rocket3.png");
    SDL_Texture *entry = IMG_LoadTexture(renderer, "../assets/entry.png");
    
    SDL_Texture *nederplanet = IMG_LoadTexture(renderer, "../assets/p2.png");
    SDL_Texture *strangemoon = IMG_LoadTexture(renderer, "../assets/p2.png");
    SDL_Texture *mars = IMG_LoadTexture(renderer, "../assets/p3.png");
    SDL_Texture *iceplanet = IMG_LoadTexture(renderer, "../assets/p4.png");
    SDL_Texture *endplanet = IMG_LoadTexture(renderer, "../assets/p5.png");
    SDL_Texture *desertplanet = IMG_LoadTexture(renderer, "../assets/p6.png");
    SDL_Texture *e1 = IMG_LoadTexture(renderer, "../assets/e1.png");

    SDL_Surface *logo = IMG_Load("../assets/logo.png");
    
    SDL_Texture *background = IMG_LoadTexture(renderer, "../assets/background.png");
    SDL_Texture *menu_back = IMG_LoadTexture(renderer, "../assets/menu.png");
    SDL_Texture *info_back = IMG_LoadTexture(renderer, "../assets/info.png");
    SDL_Texture *settings_back = IMG_LoadTexture(renderer, "../assets/settings.png");
    TTF_Font *font = TTF_OpenFont("../assets/font1.ttf", 100);
    TTF_Font *font2 = TTF_OpenFont("../assets/font2.ttf", 30);
    TTF_Font *font3 = TTF_OpenFont("../assets/font2.ttf", 20);
    
    if(!entry){return -1;}
    if(!logo){return -1;}
    if(!nederplanet){return -1;}
    if(!strangemoon){return -1;}
    if(!mars){return -1;}
    if(!iceplanet){return -1;}
    if(!endplanet){return -1;}
    if(!desertplanet){return -1;}
    if(!background){return -1;}
    if (!font) {return -1;}
    if (!font2) {return -1;}
    if (!font3) {return -1;}
    if(!rocket_img){return -1;}
    if(!rocket_img2){return -1;}
    if(!rocket_img3){return -1;}
    if(!menu_back){return -1;}

    SDL_SetWindowIcon(window, logo);

    while (runing) {
        switch(stage){
            case 1:
                if(isEntry){
                    SDL_Rect entryRect = {0, 0, 1200, 800};
                    SDL_RenderCopy(renderer, entry, NULL, &entryRect);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(16);

                    if(countEntry == NULL){
                        countEntry = malloc(sizeof(int));
                        if(countEntry != NULL && can != NULL && *can){
                            *countEntry = 0;
                            *can = false;
                        }
                    }else{(*countEntry) += 1;}

                    if(countEntry != NULL && *countEntry == 200){
                        SDL_DestroyTexture(entry);
                        free(countEntry);
                        free(can);

                        can = NULL;
                        countEntry = NULL;
                        
                        isEntry = false;
                    }
                }else{
                    menuInput(&e, &runing, &stage, &option, &option_arrow_X, &option_arrow_Y);

                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);
            
                    SDL_Color title2 = {255, 255, 255};
            
                    if(option == 1){
                        SDL_Rect menu_rect = {0, 0, 1200, 800};
                        SDL_RenderCopy(renderer, menu_back, NULL, &menu_rect);
                    }
                    else if(option == 2){
                        SDL_Rect info_rect = {0, 0, 1200, 800};
                        SDL_RenderCopy(renderer, info_back, NULL, &info_rect);
                    }
                    else if(option == 3){
                        SDL_Rect settings_rect = {0, 0, 1200, 800};
                        SDL_RenderCopy(renderer, settings_back, NULL, &settings_rect);
                    }
            
                    SDL_Surface *play = TTF_RenderText_Solid(font2, "Play", title2);
                    SDL_Surface *info = TTF_RenderText_Solid(font2, "Info", title2);
                    SDL_Surface *settings = TTF_RenderText_Solid(font2, "Settings", title2);
                    SDL_Surface *arrow = TTF_RenderText_Solid(font2, "->", title2);
            
                    SDL_Texture *texture4 = SDL_CreateTextureFromSurface(renderer, play);
                    SDL_Texture *texture5 = SDL_CreateTextureFromSurface(renderer, info);
                    SDL_Texture *texture6 = SDL_CreateTextureFromSurface(renderer, settings);
                    SDL_Texture *texture7 = SDL_CreateTextureFromSurface(renderer, arrow);
            
                    SDL_Rect rect4 = {540, 400, play->w, play->h};
                    SDL_Rect rect5 = {540, 450, info->w, info->h};
                    SDL_Rect rect6 = {500, 500, settings->w, settings->h};
                    SDL_Rect rect7 = {option_arrow_X, option_arrow_Y, arrow->w, arrow->h};
            
                    SDL_RenderCopy(renderer, texture4, NULL, &rect4);
                    SDL_RenderCopy(renderer, texture5, NULL, &rect5);
                    SDL_RenderCopy(renderer, texture6, NULL, &rect6);
                    SDL_RenderCopy(renderer, texture7, NULL, &rect7);
            
                    SDL_DestroyTexture(texture4);
                    SDL_FreeSurface(play);
                    SDL_DestroyTexture(texture5);
                    SDL_FreeSurface(info);
                    SDL_DestroyTexture(texture6);
                    SDL_FreeSurface(settings);
                    SDL_DestroyTexture(texture7);
                    SDL_FreeSurface(arrow);
            
                    SDL_RenderPresent(renderer);
                    SDL_Delay(15);
                }
               
                break;

            case 2:
                int count = 0;
                gameInput(&e, &runing, &poz_X, 450, &stage);
    
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
                SDL_Rect background_rect = {0, backpoz1, 1200, 800};
                SDL_Rect background_rect2 = {0, backpoz2, 1200, 800};
                backpoz1 += 0.7;
                backpoz2 += 0.7f;
                if(backpoz1 >= 800){backpoz1 = -800;}
                if(backpoz2 >= 800){backpoz2 = -800;}
                SDL_Rect rocket_rect = {poz_X, 450, 80, 100};
                SDL_RenderCopy(renderer, background, NULL, &background_rect);
                SDL_RenderCopy(renderer, background, NULL, &background_rect2);

                move += 3;
                
                if(obs == NULL && temp == NULL && isArray1){
                    obs = malloc(50 * sizeof(Obstacole));
                    temp = malloc(200 * sizeof(int));
                }

                //first array
                if(obs != NULL && temp != NULL && isArray1){
                    for(int i = 0; i < 50; i++){
                        if(isAlgo){
                            size = rand() % 250 + 50;
                            temp[count] = size;
                            count++;

                            rand_obj = rand() % 8;
                            temp[count] = rand_obj;
                            count++;
    
                            pozx = rand() % 1000;
                            temp[count] = pozx;
                            count++;
                            
                            if(size > 100){
                                pozy -= 300;
                            }else{
                                pozy -= 100;
                            }
                            temp[count] = pozy;
                            count++;
                        }else{
                            size = temp[count];
                            count++;
                            rand_obj = temp[count];
                            count++;
                            pozx = temp[count];
                            count++;
                            pozy = temp[count];
                            count++;
                        }
                        
                        switch(rand_obj){
                            case 0: obs[i] = obstacle(nederplanet, pozx, pozy + move, size, size, checkCollision); break;
                            case 1: obs[i] = obstacle(nederplanet, pozx, pozy + move, size, size, checkCollision); break;
                            case 2: obs[i] = obstacle(mars, pozx, pozy + move, size, size, checkCollision); break;
                            case 3: obs[i] = obstacle(iceplanet, pozx, pozy + move, size, size, checkCollision); break;
                            case 4: obs[i] = obstacle(endplanet, pozx, pozy + move, size, size, checkCollision); break;
                            case 5: obs[i] = obstacle(desertplanet, pozx, pozy + move, size, size, checkCollision); break;
                            case 6: obs[i] = obstacle(strangemoon, pozx, pozy + move, size, size, checkCollision); break;
                            case 7: obs[i] = obstacle(e1, pozx, pozy + move, size, size, checkCollision); break;
                        }
                    }
                    isAlgo = false;

                    for(int x = 0; x < 50; x++){
                        if(checkCollision(rocket_rect, obs[x].about) && !inDev){
                            free(obs);
                            free(temp);
                            obs = NULL;
                            temp = NULL;
                            isAlgo = true;
                            pozy = 0;
                            pozy = -100;
                            count = 0;
                            move = -150;
                            break;
                        }
                        if(obs[x].texture != NULL){
                            SDL_RenderCopy(renderer, obs[x].texture, NULL, &obs[x].about);
                        }
                        else{printf("Texture is NULL\n");}
                        
                    }
                }

                if(obs != NULL && temp != NULL && obs[49].poz_Y >= 800){
                    for (int i = 0; i < 50; i++) {
                        if (obs[i].texture != NULL) {
                            SDL_DestroyTexture(obs[i].texture);
                            obs[i].texture = NULL;
                        }
                    }
                    free(obs);
                    free(temp);
                    obs = NULL;
                    temp = NULL;
                    isArray1 = false;
                    printf("Deleted!");
                }

                frameCounter++;
                if (frameCounter >= 10) {
                    countTexture = (countTexture + 1) % 3;
                    frameCounter = 0;
                }
                switch(countTexture){
                    case 0: SDL_RenderCopy(renderer, rocket_img, NULL, &rocket_rect); break;
                    case 1: SDL_RenderCopy(renderer, rocket_img2, NULL, &rocket_rect); break;
                    case 2: SDL_RenderCopy(renderer, rocket_img3, NULL, &rocket_rect); break;
                }
                
                SDL_RenderPresent(renderer);
                SDL_Delay(15); 
                break;

            case 3:
                settingsInput(&e, &runing, &stage);
    
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
                SDL_RenderPresent(renderer);
                SDL_Delay(15);
                break;
            
            case 4:
                infoInput(&e, &runing, &stage);
    
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
                SDL_RenderPresent(renderer);
                SDL_Delay(15);
                break;
        }                
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

int checkCollision(SDL_Rect a, SDL_Rect b) {
    return SDL_HasIntersection(&a, &b);
}