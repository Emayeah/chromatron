#include "raylib.h"

void init(int, int[10][10], int[4][3]); // parameter for level id
void getCoords(int, int*, int*);

int main() {
	InitWindow(800, 600, "Chromatron");
	int board[10][10]; // board del gioco, [height][width]
	int tool[4][3]; // tall 4, wide 3
	init(1, board, tool);
	int dir, dirx, diry;
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (board[i][j] / 10 >= 1 && board[i][j] / 10 <= 8) {
					dir = board[i][j] / 10 * 45;
					//getCoords(dir, &dirx, &diry);
					//while (i + )
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
