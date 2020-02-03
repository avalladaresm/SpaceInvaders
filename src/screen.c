#include "../include/screen.h"
#include "../include/keypad.h"

struct Player{
    uint8_t row;
    uint8_t col;
    char *sprites;
} player;

struct Enemy1{
    uint8_t row;
    uint8_t col;
    char *sprites;
};

struct Bullet{
    uint8_t row;
    uint8_t col;
    char *sprite;
};

struct shipPosition{
    uint8_t row;
    uint8_t col;
};


void displayScore(){
    set_color(WHITE, BLACK);
    set_cursor(1, 2);
    for(int i = 21; i < 31; i++)
    {
        put_char(i);
    }
}

void menu(){
    uint8_t f, b;
    get_color(&f, &b);
    set_color(WHITE, BLACK);
    set_cursor(10, 32);
    puts("SPACE INVADERS");
    set_cursor(13, 31);
    puts("Press p to play");
    set_cursor(14, 31);
    puts("Press q to quit");
    set_cursor(29, 55);
    puts("By: Alejandro Valladares");
}

void displayTest(){    
    set_cursor(5, 10);
    uint8_t f, b;
    get_color(&f, &b);

    set_color(GREEN, BLACK);
    puts("\x2\x3\x4");
    set_color(f, b);
    
    set_color(WHITE, BLACK);
    set_cursor(10, 10);
    puts("\x5\x6\x7");
    set_color(f, b);

    set_color(WHITE, BLACK);
    set_cursor(10, 18);
    puts("\x8\x6\x9");
    set_color(f, b);

    set_color(WHITE, BLACK);
    set_cursor(15, 10);
    puts("\x19\xb\xc");
    set_color(f, b);

    set_color(WHITE, BLACK);
    set_cursor(15, 18);
    puts("\xd\xe\xf");
    set_color(f, b);

    set_color(WHITE, BLACK);
    set_cursor(20, 10);
    puts("\x10\x11\x12");
    set_color(f, b);

    set_color(WHITE, BLACK);
    set_cursor(20, 18);
    puts("\x13\x14\x15");
    set_color(f, b);

    set_color(RED, BLACK);
    set_cursor(25, 10);
    puts("\x16\x17\x18");
    set_color(f, b);
}

void moveShipRight(uint8_t row, uint8_t col){
    player.row = row;
    player.col = col;
    player.sprites = "\x2\x3\x4";
    uint8_t f, b;
    get_color(&f, &b);

    set_color(GREEN, BLACK);
    set_cursor(player.row, player.col);
    delay_ms(40);
    puts(player.sprites);
    set_cursor(player.row, player.col-1);
    put_char(255);
    set_color(f, b);
    setShipPosition(player.row, player.col);
}

void moveShipLeft(uint8_t row, uint8_t col){
    player.row = row;
    player.col = col;
    player.sprites = "\x2\x3\x4";
    uint8_t f, b;
    get_color(&f, &b);

    set_color(GREEN, BLACK);
    set_cursor(player.row, player.col);
    delay_ms(40);
    puts(player.sprites);
    set_cursor(player.row, player.col+3);
    put_char(255);
    set_color(f, b);
    setShipPosition(player.row, player.col);
}

void initSprites(uint8_t row, uint8_t col, bool goingRight){
    struct Enemy1 enemy1[2];
    for (uint8_t i = 0; i < 2; i++){
        enemy1[i].row = row;
        enemy1[i].col = col*i*2;
        enemy1[i].sprites = "\x5\x6\x7";
    }
    uint8_t f, b;
    get_color(&f, &b);

    for (uint8_t i = 0; i < 2; i++){
        if (goingRight){
            set_color(WHITE, BLACK);
            set_cursor(enemy1[i].row, enemy1[i].col);
            delay_ms(200);
            puts(enemy1[i].sprites);
            set_cursor(enemy1[i].row, enemy1[i].col-1);
            put_char(255);
            set_color(f, b);
            
        }else{
            set_color(WHITE, BLACK);
            set_cursor(enemy1[i].row, enemy1[i].col);
            delay_ms(200);
            puts(enemy1[i].sprites);
            set_cursor(enemy1[i].row, enemy1[i].col+3);
            put_char(255);
            set_color(f, b);
        }
    }
}

void shootBullet(uint8_t row, uint8_t col){
    struct Bullet bullet;
    bullet.row = row;
    bullet.col = col;
    bullet.sprite = "\x1";
    uint8_t f, b;
    get_color(&f, &b);

    set_color(YELLOW, BLACK);
    set_cursor(bullet.row, bullet.col);
    delay_ms(200);
    puts(bullet.sprite);
    set_cursor(bullet.row+1, bullet.col);
    put_char(255);
    set_color(f, b);
}

void setShipPosition(uint8_t row, uint8_t col){
    player.row = row;
    player.col = col;
}

uint8_t getShipRow(){
    set_cursor(10, 15);
    puts("Key sdsdd");
    return player.row;
}

uint8_t getShipCol(){
    return player.col;
}


// void initSprites(uint8_t row, uint8_t col, bool goingRight){
//     struct Enemy1 enemy1;
//     enemy1.row = row;
//     enemy1.col = col;
//     enemy1.sprites = "\x5\x6\x7";
    
//     uint8_t f, b;
//     get_color(&f, &b);

//     if (goingRight){
//         set_color(WHITE, BLACK);
//         set_cursor(enemy1.row, enemy1.col);
//         delay_ms(200);
//         puts(enemy1.sprites);
//         set_cursor(enemy1.row, enemy1.col-1);
//         put_char(255);
//         set_color(f, b);
//     }else if (!goingRight){
//         set_color(WHITE, BLACK);
//         set_cursor(enemy1.row, enemy1.col);
//         delay_ms(200);
//         puts(enemy1.sprites);
//         set_cursor(enemy1.row, enemy1.col+3);
//         put_char(255);
//         set_color(f, b);
//     }
// }

// void displayLives(){
//     set_color(RED, BLACK);
//     set_cursor(1, 70);
//     put_char(3);
//     put_char(3);
// }

// void displayShip(uint8_t col){
//     set_color(GREEN, BLACK);
//     set_cursor(27, col);
//     int row = 26; //fixed initial row position for ship bullet
    
//     put_char(4);    
//     put_char(5);
//     put_char(5);
//     put_char(6);
//     put_char(7);
//     put_char(5);
//     put_char(5);
//     put_char(8);
    
//     set_cursor(28, 35);
//     for(int i = 0; i < 8; i++)
//     {
//         put_char(9);
//     }

//     while(col != 1){
//         if(keypad_getkey() != 0){
//             switch (keypad_getkey())
//             {
//             case 1:
//                 col--;
//                 set_cursor(27, col);
//                 delay_ms(40);
//                 put_char(255);
//                 put_char(4);
//                 put_char(5);
//                 put_char(5);
//                 put_char(6);
//                 put_char(7);
//                 put_char(5);
//                 put_char(5);
//                 put_char(8);
//                 put_char(255);

//                 set_cursor(28, col);
//                 put_char(255);
//                 for(int i = 0; i < 8; i++)
//                 {
//                     put_char(9);
//                 }
//                 put_char(255);
                
//                 if (col == 1) {
//                     col = 1;
//                 }
                
//                 break;
//             case 2:
//                 col++;
//                 set_cursor(27, col);
//                 delay_ms(40);
//                 put_char(255);
//                 put_char(4);
//                 put_char(5);
//                 put_char(5);
//                 put_char(6);
//                 put_char(7);
//                 put_char(5);
//                 put_char(5);
//                 put_char(8);
//                 put_char(255);

//                 set_cursor(28, col);
//                 put_char(255);
//                 for(int i = 0; i < 8; i++)
//                 {
//                     put_char(9);
//                 }
//                 put_char(255);
                
//                 if (col == 1) {
//                     col = 1;
//                 }
//                 break;
//             case 8:
//                 //displayShipBullet(row, col+3);
//                 while(row != 2){
//                     displayShipBullet(--row, col+3);
//                     delay_ms(50);
//                 }
//                 row = 26;
                
//                 break;
//             default:
//                 break;
//             }
//         }
//     }
// }

// void displayShipBullet(uint8_t row, uint8_t col){
//     set_color(YELLOW, BLACK);
//     set_cursor(row, col);
//     put_char(1);
//     put_char(2);
//     set_cursor(row+1, col);
//     put_char(255);
//     put_char(255);
//     if (row == 2) {
//         set_cursor(row, col);
//         put_char(255);
//         put_char(255);
//     }
    
// }