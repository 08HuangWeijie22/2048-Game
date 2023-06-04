#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include "game.h"

int main() {
    initialize(); // 初始化遊戲
    srand(time(NULL)); // 設定隨機數種子
    generateRandomTile(); // 生成一個隨機方塊
    generateRandomTile(); // 生成一個隨機方塊

    int move;
    while (1) {
        printBoard(); // 印出當前遊戲盤面

        if (isGameOver()) { // 檢查遊戲是否結束
            printf("遊戲結束！得分：%d\n", score); // 印出最終得分
            break; // 跳出遊戲迴圈
        }

        printf("請輸入移動方向 (上: ↑, 下: ↓, 左: ←, 右: →, Enter: 結束): ");
        move = getKey(); // 獲取玩家輸入的移動方向

        if (move == 13) { // 檢查是否按下 Enter 鍵（ASCII 碼為 13）
            break; // 跳出遊戲迴圈
        }

        switch (move) {
            case 1:
                moveUp(); // 向上移動方塊
                break;
            case 2:
                moveDown(); // 向下移動方塊
                break;
            case 3:
                moveLeft(); // 向左移動方塊
                break;
            case 4:
                moveRight(); // 向右移動方塊
                break;
            default:
                printf("無效的輸入！\n"); // 處理無效的輸入
                break;
        }

        generateRandomTile(); // 生成一個隨機方塊
    }

    return 0;
}
