#ifndef MAIN_H
#define MAIN_H

//struct
typedef struct{
    SDL_Texture *texture;
    SDL_Rect about;
    int poz_X;
    int poz_Y;
    int Scale_X;
    int Scale_Y;
    int (*checkCollision)(SDL_Rect, SDL_Rect);
}Obstacole;

//constructors
Obstacole obstacle(SDL_Texture *texture, int poz_X, int poz_Y, int Scale_X, int Scale_Y,
    int (*checkCollision)(SDL_Rect, SDL_Rect)){
    Obstacole ob;
    ob.texture = texture;

    ob.poz_X = poz_X;
    ob.poz_Y = poz_Y;
    ob.Scale_X = Scale_X;
    ob.Scale_Y = Scale_Y;

    ob.about.x = poz_X;
    ob.about.y = poz_Y;
    ob.about.w = Scale_X;
    ob.about.h = Scale_Y;

    ob.checkCollision = checkCollision;

    return ob;
}
float width = 1200.f;
float heith = 800.f;

int main(int argc, char* argv[]);
int checkCollision(SDL_Rect a, SDL_Rect b);

#endif