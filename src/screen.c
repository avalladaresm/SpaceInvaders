#include "../include/screen.h"

//#define TO_STR(ch) ( ( ((ch) >= 0 ) && ((ch) <= 9) )? (48 + (ch)) : ('a' + ((ch) - 10)) )

char TO_STR(int ch){
    if(ch >= 0  && ch <= 9){
        return (48 + (ch));
    }
    else {
        return ('a' + ((ch) - 10));
    }
}

struct Player{
    uint8_t row;
    uint8_t col;
    uint8_t destroyedEnemies;
    char *sprites;
} player;

struct Invader{
    uint8_t row;
    uint8_t col;
    bool isDestroyed;
    char *sprites;
}; 
struct Invader invader1[5];
struct Invader invader2[5];
struct Invader invader3[5];

struct Bullet{
    uint8_t row;
    uint8_t col;
    char *sprite;
} bullet;

// void displayMenu(){
//     uint8_t f, b;
//     get_color(&f, &b);
//     set_color(BRIGHT_WHITE, BLACK);
//     set_cursor(10, 32);
//     puts("SPACE INVADERS");
//     set_cursor(13, 31);
//     puts("Press p to play");
//     set_cursor(29, 55);
//     puts("By: Alejandro Valladares");
// }

void movePlayerRight(uint8_t row, uint8_t col){
    player.row = row;
    player.col = col;
    player.sprites = "\x2\x3\x4";
    uint8_t f, b;
    get_color(&f, &b);

    set_color(LIGHT_GREEN, BLACK);
    set_cursor(player.row, player.col);
    puts(player.sprites);
    set_cursor(player.row, player.col-1);
    put_char(255);
    set_cursor(player.row, player.col-2);
    put_char(255);
    set_color(f, b);
    setPlayerPosition(player.row, player.col);
}

void movePlayerLeft(uint8_t row, uint8_t col){
    player.row = row;
    player.col = col;
    player.sprites = "\x2\x3\x4";
    uint8_t f, b;
    get_color(&f, &b);

    set_color(LIGHT_GREEN, BLACK);
    set_cursor(player.row, player.col);
    puts(player.sprites);
    set_cursor(player.row, player.col+3);
    put_char(255);
    set_cursor(player.row, player.col+4);
    put_char(255);
    set_color(f, b);
    setPlayerPosition(player.row, player.col);
}

// void setPlayerPosition(uint8_t row, uint8_t col){
//     player.row = row;
//     player.col = col;
// }

// uint8_t getPlayerRow(){
//     return player.row;
// }

// uint8_t getPlayerCol(){
//     return player.col;
// }

void displayInvaders(uint8_t row, uint8_t col, bool isGoingRight){
    uint8_t basePositions1[] = {col, col+12, col+24, col+36, col+48};
    uint8_t basePositions2[] = {col+4, col+16, col+28, col+40, col+52};
    uint8_t basePositions3[] = {col+8, col+20, col+32, col+44, col+56};

    for (uint8_t i = 0; i < 5; i++){
        invader1[i].row = row;
        invader1[i].col = basePositions1[i];
        if (invader1[i].isDestroyed){
            invader1[i].sprites = "\xff\xff\xff";
        } else{
            invader1[i].sprites = "\x5\x6\x7";
        }

        invader2[i].row = row+2;
        invader2[i].col = basePositions2[i];
        if (invader2[i].isDestroyed){
            invader2[i].sprites = "\xff\xff\xff";
        } else{
            invader2[i].sprites = "\x19\xb\xc";
        }

        invader3[i].col = basePositions3[i];
        invader3[i].row = row+4;
        if (invader3[i].isDestroyed){
            invader3[i].sprites = "\xff\xff\xff";
        } else{
            invader3[i].sprites = "\x10\x11\x12";
        }
    }
    uint8_t f, b;
    get_color(&f, &b);

    for (uint8_t i = 0; i < 5; i++){
        if (isGoingRight){
            set_color(CYAN, BLACK);
            set_cursor(invader1[i].row, invader1[i].col-1);
            put_char(255);
            set_cursor(invader1[i].row, invader1[i].col);
            puts(invader1[i].sprites);

            set_color(BROWN, BLACK);
            set_cursor(invader2[i].row, invader2[i].col-1);
            put_char(255);
            set_cursor(invader2[i].row, invader2[i].col);
            puts(invader2[i].sprites);

            set_color(MAGENTA, BLACK);
            set_cursor(invader3[i].row, invader3[i].col-1);
            put_char(255);
            set_cursor(invader3[i].row, invader3[i].col);
            puts(invader3[i].sprites);

            for (uint8_t j = 0; j < 5; j++){
                if (invader1[j].col == 5 || invader1[j].col == col + 5){
                    set_cursor(invader1[i].row-1, invader1[i].col+1);
                    puts("\xff\xff\xff");
                    set_cursor(invader2[i].row-1, invader2[i].col+1);
                    puts("\xff\xff\xff");
                    set_cursor(invader3[i].row-1, invader3[i].col+1);
                    puts("\xff\xff\xff");
                }
            }
            if ((invader1[i].row == getBulletRow() && 
                (invader1[i].col == getBulletCol() || 
                invader1[i].col+1 == getBulletCol() ||
                invader1[i].col+2 == getBulletCol()))){
                    invader1[i].isDestroyed = true;
                    invader1[i].sprites = "\xff\xff\xff";
            }
            if ((invader2[i].row == getBulletRow() && 
                (invader2[i].col == getBulletCol() || 
                invader2[i].col+1 == getBulletCol() ||
                invader2[i].col+2 == getBulletCol()))){
                    invader2[i].isDestroyed = true;
                    invader2[i].sprites = "\xff\xff\xff";
            }
            if ((invader3[i].row == getBulletRow() && 
                (invader3[i].col == getBulletCol() || 
                invader3[i].col+1 == getBulletCol() ||
                invader3[i].col+2 == getBulletCol()))){
                    invader3[i].isDestroyed = true;
                    invader3[i].sprites = "\xff\xff\xff";
            }
        }
        else{
            set_color(CYAN, BLACK);
            set_cursor(invader1[i].row, invader1[i].col+3);
            put_char(255);
            set_cursor(invader1[i].row, invader1[i].col);
            puts(invader1[i].sprites);

            set_color(BROWN, BLACK);
            set_cursor(invader2[i].row, invader2[i].col+3);
            put_char(255);
            set_cursor(invader2[i].row, invader2[i].col);
            puts(invader2[i].sprites);

            set_color(MAGENTA, BLACK);
            set_cursor(invader3[i].row, invader3[i].col+3);
            put_char(255);
            set_cursor(invader3[i].row, invader3[i].col);
            puts(invader3[i].sprites);

            for (uint8_t j = 0; j < 5; j++){
                if (invader1[j].col == 15 || invader1[j].col == col + 5){
                    set_cursor(invader1[i].row, invader1[i].col-3);
                    puts("\xff\xff\xff");
                    set_cursor(invader2[i].row, invader2[i].col-3);
                    puts("\xff\xff\xff");
                    set_cursor(invader3[i].row, invader3[i].col-3);
                    puts("\xff\xff\xff");
                }
            }
            if ((invader1[i].row == getBulletRow() && 
                (invader1[i].col == getBulletCol() || 
                invader1[i].col+1 == getBulletCol() ||
                invader1[i].col+2 == getBulletCol()))){
                    invader1[i].sprites = "\x1a\x1b\x1c";
                    invader1[i].isDestroyed = true;
                    invader1[i].sprites = "\xff\xff\xff";
            }
            if ((invader2[i].row == getBulletRow() && 
                (invader2[i].col == getBulletCol() || 
                invader2[i].col+1 == getBulletCol() ||
                invader2[i].col+2 == getBulletCol()))){
                    invader2[i].isDestroyed = true;
                    invader2[i].sprites = "\xff\xff\xff";
            }
            if ((invader3[i].row == getBulletRow() && 
                (invader3[i].col == getBulletCol() || 
                invader3[i].col+1 == getBulletCol() ||
                invader3[i].col+2 == getBulletCol()))){
                    invader1[i].sprites = "\x1a\x1b\x1c";
                    invader3[i].isDestroyed = true;
                    invader3[i].sprites = "\xff\xff\xff";
            }
        }
    }
    set_color(f, b);
}

// void shootBullet(uint8_t row, uint8_t col){
//     bullet.row = row;
//     bullet.col = col;
//     bullet.sprite = "\x1";

//     set_color(YELLOW, BLACK);
//     set_cursor(bullet.row--, bullet.col);
//     puts(bullet.sprite);
//     set_cursor(bullet.row+2, bullet.col);
//     put_char(255);
//     setBulletPosition(bullet.row, bullet.col);
// }

// void setBulletPosition(uint8_t row, uint8_t col){
//     bullet.row = row;
//     bullet.col = col;
// }

// uint8_t getBulletRow(){
//     return bullet.row;
// }

// uint8_t getBulletCol(){
//     return bullet.col;
// }

uint8_t getDestroyedEnemies(){
    int destroyedEnemies = 0;
    for (uint8_t i = 0; i < 5; i++){
        if (invader1[i].isDestroyed == true){
            destroyedEnemies++;
        }
        if (invader2[i].isDestroyed == true){
            destroyedEnemies++;
        }
        if (invader3[i].isDestroyed == true){
            destroyedEnemies++;
        }
    }

    return destroyedEnemies;
}

// void displayScore(uint8_t score){
//     set_cursor(1, 1);
//     set_color(BRIGHT_WHITE, BLACK);
//     puts("Score");
//     uint8_t f, b;
//     get_color(&f, &b);
    
//     set_color(LIGHT_GREEN, BLACK);
//     set_cursor(1, 7);
//     put_char(TO_STR(score & 0xf));
// }

// void displayLives(uint8_t lives){
//     set_cursor(1, 60);
//     set_color(BRIGHT_WHITE, BLACK);
//     puts("Lives");
    
//     set_color(LIGHT_GREEN, BLACK);
//     if (lives == 2) {
//         set_cursor(1, 66);
//         puts("\x2\x3\x4");
//         set_cursor(1, 70);
//         puts("\x2\x3\x4");
//     } else if(lives == 1){
//         set_cursor(1, 66);
//         puts("\x2\x3\x4");
//         set_cursor(1, 70);
//         puts("\xff\xff\xff");
//     } else if(lives == 0){
//         set_cursor(1, 66);
//         puts("\xff\xff\xff");
//         set_cursor(1, 70);
//         puts("\xff\xff\xff");
//     }
// }