#ifndef GAME_H
#define GAME_H

extern int score;

void initialize();
void printBoard();
bool isBoardFull();
void generateRandomTile();
bool isGameOver();
void shiftLeft();
void mergeLeft();
void moveLeft();
void shiftUp();
void mergeUp();
void moveUp();
void shiftRight();
void mergeRight();
void moveRight();
void shiftDown();
void mergeDown();
void moveDown();
int getKey();

#endif
