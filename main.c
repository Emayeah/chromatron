#include "raylib.h"
#include <stdio.h>

void init(int, int[10][10], int[4][3]); // parameter for level id
void getDir(int, int*, int*);
int mod(int, int);

int main() {
	InitWindow(800, 600, "Chromatron");
	SetTargetFPS(60);
	int board[10][10]; // board del gioco, [height][width]
	int tool[4][3]; // tall 4, wide 3
	init(1, board, tool);
	int dir, dirx, diry, posx, posy, tempDir, bakWincount, winCount, flag;
	int mousex, mousey;
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);
		winCount = 0;
		flag = 0;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				DrawRectangleLines(j * 40 + 10, i * 40 + 10, 40, 40, LIGHTGRAY);
			}
		}
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (mod(board[i][j] / 10 - 1, 10) < 8) {
					dir = board[i][j] / 10 - 1;
					getDir(dir, &dirx, &diry);
					dir *= 45;
					posx = i;
					posy = j;
					bakWincount = winCount;
					while (posx + dirx < 10 && posx + dirx >= 0 && posy + diry < 10 && posy + diry >= 0 && bakWincount == winCount && flag == 0) {
						posx += dirx;
						posy += diry;
						if (board[posx][posy] == 0) {
							DrawRectanglePro((Rectangle){posy * 40 + 30, posx * 40 + 30, (40 + 28.28f * ((dirx & 0x7fffffff) == (diry & 0x7fffffff))), 10}, (Vector2){20 + 14.14f * ((dirx & 0x7fffffff) == (diry & 0x7fffffff)), 5}, 360 - dir, BLACK);
							// true == 1, false == 0, if both are 1 then the line needs to be longer
						}
						else if (board[posx][posy] <= 8) {
							DrawRectanglePro((Rectangle){posy * 40 + 30, posx * 40 + 30, (20 + 14.14f * ((dirx & 0x7fffffff) == (diry & 0x7fffffff))), 10}, (Vector2){20 + 14.14f * ((dirx & 0x7fffffff) == (diry & 0x7fffffff)), 5}, 360 - dir, BLACK);
							tempDir = board[posx][posy] - 1;
							dir /= 45;
							if (mod(dir + 1, 8) == tempDir || mod(dir + 2, 8) == tempDir || mod(dir + 3, 8) == tempDir) {
								dir = tempDir * 2 - dir;
								dir = mod(dir, 8);
								getDir(dir, &dirx, &diry);
								dir *= 45;
								DrawRectanglePro((Rectangle){posy * 40 + 30, posx * 40 + 30, (20 + 14.14f * ((dirx & 0x7fffffff) == (diry & 0x7fffffff))), 10}, (Vector2){20 + 14.14f * ((dirx & 0x7fffffff) == (diry & 0x7fffffff)), 5}, 180 - dir, BLACK);
							}
							else {
								flag = 1;
							}
						}
						else if (board[posx][posy] / 10 == 9) {
							winCount++;
						}
						else {
							flag = 1;
						}
					}
				}
				else if (board[i][j] != 0 && board[i][j] <= 8) {
					tempDir = (board[i][j] - 1) * 45;
					DrawRectanglePro((Rectangle){j * 40 + 30, i * 40 + 30, 40, 10}, (Vector2){20, 5}, 360 - tempDir, BLACK);
					DrawRectanglePro((Rectangle){j * 40 + 30, i * 40 + 30, 50, 5}, (Vector2){25, -5}, 360 - tempDir, RED);
				}
			}
		}
		if (winCount == 1) {
			DrawText("you win!!", 400, 400, 20, BLACK);
		}
		EndDrawing();
		if (IsMouseButtonReleased(1)) {
			mousey = GetMouseX();
			mousex = GetMouseY();
			mousey -= 10;
			mousex -= 10;
			mousey /= 40;
			mousex /= 40;
			if (mousex < 10 && mousey < 10) {
				if (board[mousex][mousey] != 0 && board[mousex][mousey] <= 8) {
					board[mousex][mousey] %= 8;
					board[mousex][mousey]++;
				}
			}
		}
	}
	CloseWindow();
}

void init(int id, int board[10][10], int tool[4][3]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			board[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			tool[i][j] = 0;
		}
	}
	if (id == 1) {
		board[5][3] = 10;
		board[5][8] = 2;
		board[1][8] = 90;
		tool[0][0] = 1;
	}
}

void getDir(int dir, int* dirx, int* diry) {
	if (mod(dir + 1, 8) <= 2) {
		*diry = 1;
	}
	else if (mod(dir - 3, 8) <= 2) {
		*diry = -1;
	}
	else {
		*diry = 0;
	}
	if (mod(dir - 1, 8) <= 2) {
		*dirx = -1;
	}
	else if (mod(dir - 5, 8) <= 2) {
		*dirx = 1;
	}
	else {
		*dirx = 0;
	}
	//printf("x: %d; y: %d\n", *dirx, *diry);
	//printf("%d\n", mod(dir - 1, 8));
}

int mod(int a, int b) {
	return ((a % b) + b) % b;
}
