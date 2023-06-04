#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include "game.h"

#define SIZE 4

int score;
int board[SIZE][SIZE];

void initialize() {
    score = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

void printBoard() {
    system("cls"); // 清空終端機
    printf("Score: %d\n", score); // 印出當前得分
    printf("---------------------\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                printf("|    "); // 空格子
            } else {
                printf("|%4d", board[i][j]); // 印出數字
            }
        }
        printf("|\n");
        printf("---------------------\n");
    }
}

bool isBoardFull() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return false; // 盤面還有空格子
            }
        }
    }
    return true; // 盤面已滿
}

void generateRandomTile() {
    if (isBoardFull()) {
        return; // 如果盤面已滿，則不生成新方塊
    }

    int row, col;
    do {
        row = rand() % SIZE; // 隨機生成行索引
        col = rand() % SIZE; // 隨機生成列索引
    } while (board[row][col] != 0); // 直到找到一個空格子

    int value = (rand() % 2 + 1) * 2; // 隨機生成2或4
    board[row][col] = value; // 在空格子上放置方塊
}

bool isGameOver() {
    if (!isBoardFull()) {
        return false; // 如果盤面還有空格子，遊戲未結束
    }

    // 檢查相鄰的格子是否有相同數字
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if ((i < SIZE - 1 && board[i][j] == board[i + 1][j]) ||
                (j < SIZE - 1 && board[i][j] == board[i][j + 1])) {
                return false; // 如果存在相鄰相同數字的格子，遊戲未結束
            }
        }
    }

    return true; // 沒有相鄰相同數字的格子，遊戲結束
}

void shiftLeft() {
    for (int i = 0; i < SIZE; i++) {
        int writeIdx = 0;
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 0) {
                board[i][writeIdx] = board[i][j]; // 向左移動方塊
                if (writeIdx != j) {
                    board[i][j] = 0; // 將原位置設為空
                }
                writeIdx++;
            }
        }
    }
}

void mergeLeft() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            if (board[i][j] == board[i][j + 1]) {
                board[i][j] *= 2; // 合併相鄰相同數字的方塊
                score += board[i][j]; // 更新得分
                board[i][j + 1] = 0; // 清空下一個方塊
            }
        }
    }
}

void moveLeft() {
    shiftLeft();
    mergeLeft();
    shiftLeft();
}

void shiftUp() {
    for (int j = 0; j < SIZE; j++) {
        int writeIdx = 0;
        for (int i = 0; i < SIZE; i++) {
            if (board[i][j] != 0) {
                board[writeIdx][j] = board[i][j]; // 向上移動方塊
                if (writeIdx != i) {
                    board[i][j] = 0; // 將原位置設為空
                }
                writeIdx++;
            }
        }
    }
}

void mergeUp() {
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE - 1; i++) {
            if (board[i][j] == board[i + 1][j]) {
                board[i][j] *= 2; // 合併相鄰相同數字的方塊
                score += board[i][j]; // 更新得分
                board[i + 1][j] = 0; // 清空下一個方塊
            }
        }
    }
}

void moveUp() {
    shiftUp();
    mergeUp();
    shiftUp();
}

void shiftRight() {
    for (int i = 0; i < SIZE; i++) {
        int writeIdx = SIZE - 1;
        for (int j = SIZE - 1; j >= 0; j--) {
            if (board[i][j] != 0) {
                board[i][writeIdx] = board[i][j]; // 向右移動方塊
                if (writeIdx != j) {
                    board[i][j] = 0; // 將原位置設為空
                }
                writeIdx--;
            }
        }
    }
}

void mergeRight() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = SIZE - 1; j > 0; j--) {
            if (board[i][j] == board[i][j - 1]) {
                board[i][j] *= 2; // 合併相鄰相同數字的方塊
                score += board[i][j]; // 更新得分
                board[i][j - 1] = 0; // 清空下一個方塊
            }
        }
    }
}

void moveRight() {
    shiftRight();
    mergeRight();
    shiftRight();
}

void shiftDown() {
    for (int j = 0; j < SIZE; j++) {
        int writeIdx = SIZE - 1;
        for (int i = SIZE - 1; i >= 0; i--) {
            if (board[i][j] != 0) {
                board[writeIdx][j] = board[i][j]; // 向下移動方塊
                if (writeIdx != i) {
                    board[i][j] = 0; // 將原位置設為空
                }
                writeIdx--;
            }
        }
    }
}

void mergeDown() {
    for (int j = 0; j < SIZE; j++) {
        for (int i = SIZE - 1; i > 0; i--) {
            if (board[i][j] == board[i - 1][j]) {
                board[i][j] *= 2; // 合併相鄰相同數字的方塊
                score += board[i][j]; // 更新得分
                board[i - 1][j] = 0; // 清空下一個方塊
            }
        }
    }
}

void moveDown() {
    shiftDown();
    mergeDown();
    shiftDown();
}

int getKey() {
    int key = getch();
    if (key == 0 || key == 224) { // 檢測特殊按鍵
        key = getch();
        switch (key) {
            case 72:
                return 1; // 上
            case 80:
                return 2; // 下
            case 75:
                return 3; // 左
            case 77:
                return 4; // 右
        }
    }
    return key;
}
