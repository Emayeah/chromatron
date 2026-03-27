#include "raylib.h"
#include <stdio.h>

void init(int, int[10][10], int[4][3]); // parameter for level id
void getCoords(int, int*, int*);

int main() {
	InitWindow(800, 600, "Chromatron");
	int board[10][10]; // board del gioco, [height][width]
	int tool[4][3]; // tall 4, wide 3
	init(1, board, tool);
	int dir, dirx, diry, posx, posy;
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (board[i][j] / 10 >= 1 && board[i][j] / 10 <= 8) {
					dir = board[i][j] / 10;
					getCoords(dir, &dirx, &diry);
					dir *= 45;
					posx = i;
					posy = j;
					while (posx + dirx < 10 && posx + dirx >= 0 && posy + diry < 10 && posy + diry >= 0) {
						posx += dirx;
						posy += diry;
						if (board[posx][posy] == 0) {
							DrawRectanglePro((Rectangle){posx * 50 + 10, posy * 50 + 10, 30, 30}, (Vector2){posx, posy}, dir, BLACK);
						}
					}
				}
			}
		}
		EndDrawing();
	}
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
		tool[0][0] = 1;
	}
}

void getCoords(int dir, int* dirx, int* diry) {
	if ((dir + 1) % 8 <= 2) {
		*diry = 1;
	}
	else if ((dir - 3) % 8 <= 2) {
		*diry = -1;
	}
	else {
		*diry = 0;
	}
	if ((dir - 1) % 8 <= 2) {
		*dirx = 1;
	}
	else if ((dir - 5) % 8 <= 2) {
		*dirx = -1;
	}
	else {
		*dirx = 0;
	}
}
