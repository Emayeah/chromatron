#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

void init(int, int[15][15], int[4][3]); // parameter for level id
void getDir(int, int*, int*);
int mod(int, int);
void drawMirror(int, int, int);
void drawReflector(int, int, int);

int main() {
	InitWindow(800, 600, "Chromatron");
	SetTargetFPS(60);
	int board[15][15]; // board del gioco, [height][width]
	int tools[4][3]; // tall 4, wide 3
	int dir, dirx, diry, posx, posy, bakWincount, winCount, flag, pressed = 0, draggedWhat, draggedx, draggedy;
	float tempDir;
	int maxStars;
	int maxLevel = 1;
	int currentLevel = 1;
	int mousex, mousey;
	Color color;
	Color colors[] = {RED, GREEN, BLUE, WHITE, PURPLE, SKYBLUE, YELLOW};
	bool cantWin;
	int index;
	int flag2;
	char *colorFlags;
	init(currentLevel, board, tools);
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(LIGHTGRAY);
		maxStars = 0;
		winCount = 0;
		cantWin = 0;
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				DrawRectangle(j * 25 + 10, i * 25 + 10, 25, 25, GRAY);
				if (board[i][j] / 10 == 9) {
					maxStars++;
				}
			}
		}
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				DrawRectangleLines(j * 25 + 10, i * 25 + 10, 25, 25, BROWN);
				if (board[i][j] / 10 == 9) {
					maxStars++;
				}
			}
		}
		colorFlags = malloc(maxStars * sizeof(unsigned char) * 4);
		for (int i = 0; i < maxStars * 4; i++) {
			colorFlags[i] = 0;
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				DrawRectangle((800 - (3 - j) * 80) - 10, i * 80 + 10, 80, 80, GRAY);
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				DrawRectangleLines((800 - (3 - j) * 80) - 10, i * 80 + 10, 80, 80, BROWN);
			}
		}
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				if (board[i][j] / 10 <= 8 && board[i][j] >= 10) {
					color = colors[board[i][j] % 10];
					dir = board[i][j] / 10 - 1;
					getDir(dir, &dirx, &diry);
					dir *= 45;
					posx = i;
					posy = j;
					flag = 0;
					while (posx + dirx < 15 && posx + dirx >= 0 && posy + diry < 15 && posy + diry >= 0 && flag == 0) {
						posx += dirx;
						posy += diry;
						if (board[posx][posy] == 0) {
							DrawRectanglePro((Rectangle){posy * 25 + 22, posx * 25 + 22, (25 + 17.7f * ((dirx * dirx) == (diry * diry))), 6}, (Vector2){12.5 + 8.84f * ((dirx * dirx) == (diry * diry)), 3}, 360 - dir, color);
							// true == 1, false == 0, if both are 1 then the line needs to be longer
						}
						else if (board[posx][posy] <= 8) {
							DrawRectanglePro((Rectangle){posy * 25 + 22, posx * 25 + 22, (12.5 + 8.84f * ((dirx * dirx) == (diry * diry))), 6}, (Vector2){12.5 + 8.84f * ((dirx * dirx) == (diry * diry)), 3}, 360 - dir, color);
							tempDir = board[posx][posy] - 1;
							dir /= 45;
							if (mod(dir + 1, 8) == tempDir || mod(dir + 2, 8) == tempDir || mod(dir + 3, 8) == tempDir) {
								dir = tempDir * 2 - dir;
								dir = mod(dir, 8);
								getDir(dir, &dirx, &diry);
								dir *= 45;
								DrawRectanglePro((Rectangle){posy * 25 + 22, posx * 25 + 22, (12.5 + 8.84f * ((dirx * dirx) == (diry *  diry))), 6}, (Vector2){12.5f + 8.84f * ((dirx * dirx) == (diry * diry)), 3}, 180 - dir, color);
							}
							else {
								flag = 1;
							}
						}
						else if (board[posx][posy] / 10 == 10) {
							DrawRectanglePro((Rectangle){posy * 25 + 22, posx * 25 + 22, (12.5 + 8.84f * ((dirx * dirx) == (diry * diry))), 6}, (Vector2){12.5 + 8.84f * ((dirx * dirx) == (diry * diry)), 3}, 360 - dir, color);
							tempDir = board[posx][posy] - 101;
							dir /= 45;
							if (mod(dir + 1, 8) == tempDir || mod(dir + 2, 8) == tempDir || mod(dir + 3, 8) == tempDir || mod(dir, 8) == tempDir) {
								dir *= 45;
								tempDir *= 45;
								tempDir += 22.5;
								dir = tempDir * 2 - dir;
								dir /= 45;
								dir = mod(dir, 8);
								getDir(dir, &dirx, &diry);
								dir *= 45;
								DrawRectanglePro((Rectangle){posy * 25 + 22, posx * 25 + 22, (12.5 + 8.84f * ((dirx * dirx) == (diry *  diry))), 6}, (Vector2){12.5f + 8.84f * ((dirx * dirx) == (diry * diry)), 3}, 180 - dir, color);
							}
							else {
								flag = 1;
							}
						}
						else if (board[posx][posy] / 10 == 9) {
							index = 0;
							flag2 = 0;
							for (int k = 0; k < 15 && flag2 == 0; k++) {
								for (int l = 0; l < 15 && flag2 == 0; l++) {
									if (board[k][l] / 10 == 9) {
										index++;
									}
									if (k == posx && l == posy) {
										flag2 = 1;
										index--;
									}
								}
							}
							colorFlags[index * 4 + (board[i][j] % 10)] = 1;
						}
						else {
							flag = 1;
						}
					}
				}
				else if (board[i][j] / 10 == 9) {
					DrawText("S", j * 25 + 16, i * 25 + 14, 20, colors[board[i][j] % 10]);
				}
				else if (board[i][j] == 120) {
					DrawRectangle(j * 25 + 10, i * 25 + 10, 25, 25, LIGHTGRAY);
				}
			}
		}
		index = 0;
		cantWin = 0;
		for (int i = 0; i < 15 && cantWin == 0; i++) {
			for (int j = 0; j < 15 && cantWin == 0; j++) {
				if (board[i][j] / 10 == 9) {
					if (
						board[i][j] % 10 == 0 &&
						colorFlags[index * 4] == 1 &&
						colorFlags[index * 4 + 1] == 0 &&
						colorFlags[index * 4 + 2] == 0 &&
						colorFlags[index * 4 + 3] == 0
					) {
					}
					else if (
						board[i][j] % 10 == 1 &&
						colorFlags[index * 4] == 0 &&
						colorFlags[index * 4 + 1] == 1 &&
						colorFlags[index * 4 + 2] == 0 &&
						colorFlags[index * 4 + 3] == 0
					) {
					}
					else if (
						board[i][j] % 10 == 2 &&
						colorFlags[index * 4] == 0 &&
						colorFlags[index * 4 + 1] == 0 &&
						colorFlags[index * 4 + 2] == 1 &&
						colorFlags[index * 4 + 3] == 0
					) {
					}
					else if (
						board[i][j] % 10 == 3 &&
						((
						colorFlags[index * 4] == 1 &&
						colorFlags[index * 4 + 1] == 1 &&
						colorFlags[index * 4 + 2] == 1
						) ||
						colorFlags[index * 4 + 3] == 1
						)
					) {
					}
					else if (
						board[i][j] % 10 == 4 &&	// purple
						colorFlags[index * 4] == 1 &&
						colorFlags[index * 4 + 1] == 0 &&
						colorFlags[index * 4 + 2] == 1 &&
						colorFlags[index * 4 + 3] == 0
					) {
					}
					else if (
						board[i][j] % 10 == 5 &&	// cyan
						colorFlags[index * 4] == 0 &&
						colorFlags[index * 4 + 1] == 1 &&
						colorFlags[index * 4 + 2] == 1 &&
						colorFlags[index * 4 + 3] == 0
					) {
					}
					else if (
						board[i][j] % 10 == 6 &&	// yellow
						colorFlags[index * 4] == 1 &&
						colorFlags[index * 4 + 1] == 1 &&
						colorFlags[index * 4 + 2] == 0 &&
						colorFlags[index * 4 + 3] == 0
					) {
					}
					else {
						cantWin = 1;
					}
					index++;
				}
			}
		}
		free(colorFlags);
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				if (board[i][j] != 0 && board[i][j] <= 8) {
					tempDir = (board[i][j] - 1) * 45;
					drawMirror(j * 25 + 22, i * 25 + 22, tempDir);
				}
				else if (board[i][j] != 0 && board[i][j] / 10 == 10) {
					tempDir = (board[i][j] - 101) * 45 + 22.5;
					drawReflector(j * 25 + 22, i * 25 + 22, tempDir);
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				if (tools[i][j] != 0 && tools[i][j] <= 8) {
					tempDir = tools[i][j] - 1;
					tempDir *= 45;
					drawMirror((800 - (3 - j) * 80) + 30, i * 80 + 45, tempDir);
//					DrawRectangle((800 - (3 - j) * 80) + 25, i * 60 + 30, 10, 40, BLACK);
//					DrawRectangle((800 - (3 - j) * 80) + 35, i * 60 + 25, 5, 50, RED);
				}
				else if (tools[i][j] != 0 && tools[i][j] / 10 == 10) {
					tempDir = tools[i][j] - 101;
					tempDir *= 45;
					drawReflector((800 - (3 - j) * 80) + 30, i * 80 + 50, tempDir + 22.5);
				}
			}
		}
		for (int i = 1; i <= 4; i++) {
			if (i <= maxLevel) {
				DrawText(TextFormat("%d ", i), 800 - 550 + 80 * (i - 1), 600 - 100, 80, RED);
			}
			else {
				DrawText(TextFormat("%d ", i), 800 - 550 + 80 * (i - 1), 600 - 100, 80, BLACK);
			}
		}
		if (cantWin == 0) {
			if (maxLevel == currentLevel) {
				maxLevel++;
			}
		}
		if (IsMouseButtonPressed(0)) {
			mousey = GetMouseX();
			mousex = GetMouseY();
			mousey -= 10;
			mousex -= 10;
			if (mod(mousex, 600) <= 320 && mod(mousey, 800) >= 540) {
				mousey -= 540;
				if (mousex / 80 >= 0 && mousex / 80 < 4 && mousey / 80 >= 0 && mousey / 80 < 3) {
					mousex /= 80;
					mousey /= 80;
					if (tools[mousex][mousey] != 0) {
						pressed = 1;
						draggedWhat = tools[mousex][mousey];
						tools[mousex][mousey] = 0;
						draggedx = mousex;
						draggedy = mousey;
					}
				}
			}
			else if (mousex / 25 >= 0 && mousex / 25 < 15 && mousey / 25 >= 0 && mousey / 25 < 15) {
				mousey /= 25;
				mousex /= 25;
				if (board[mousex][mousey] != 0 && (board[mousex][mousey] <= 8 || board[mousex][mousey] / 10 == 10)) {
					pressed = 2;
					draggedWhat = board[mousex][mousey];
					board[mousex][mousey] = 0;
					draggedx = mousex;
					draggedy = mousey;
				}
			}
		}
		if (IsMouseButtonReleased(0)) {
			mousey = GetMouseX();
			mousex = GetMouseY();
			if (pressed != 0) {
				mousey -= 10;
				mousex -= 10;
				if (mousex / 80 >= 0 && mousex / 80 < 4 && (mousey - 540) / 80 >= 0 && (mousey - 540) / 80 < 3) {
					mousey -= 540;
					mousey /= 80;
					mousex /= 80;
					if (tools[mousex][mousey] == 0) {
						tools[mousex][mousey] = draggedWhat;
					}
					else {
						if (pressed == 1) {
							tools[draggedx][draggedy] = draggedWhat;
						}
						else if (pressed == 2) {
							board[draggedx][draggedy] = draggedWhat;
						}
					}
				}
				else if (mousex / 25 >= 0 && mousex / 25 < 15 && mousey / 25 >= 0 && mousey / 25 < 15) {
					mousey /= 25;
					mousex /= 25;
					if (board[mousex][mousey] == 0) {
						board[mousex][mousey] = draggedWhat;
					}
					else {
						if (pressed == 1) {
							tools[draggedx][draggedy] = draggedWhat;
						}
						else if (pressed == 2) {
							board[draggedx][draggedy] = draggedWhat;
						}
					}
				}
				else {
					if (pressed == 1) {
						tools[draggedx][draggedy] = draggedWhat;
					}
					else if (pressed == 2) {
						board[draggedx][draggedy] = draggedWhat;
					}
				}
				pressed = 0;
			}
			else if (mousex >= 500 && mousex <= 580 && mousey >= 250 && mousey <= 570) {
				mousey -= 250;
				mousey /= 80;
				mousey++;
				if (mousey <= maxLevel) {
					currentLevel = mousey;
					init(currentLevel, board, tools);
				}
			}
		}
		else if (IsMouseButtonDown(0) && pressed != 0) {
			mousey = GetMouseX();
			mousex = GetMouseY();
			tempDir = draggedWhat - 1;
			if (draggedWhat >= 100) {
				tempDir -= 100;
				tempDir *= 45;
				drawReflector(mousey, mousex - 3, tempDir + 22.5);
			}
			else {
				tempDir *= 45;
				drawMirror(mousey, mousex - 3, tempDir);
			}
		}
		EndDrawing();
		if (IsMouseButtonReleased(1)) {
			mousey = GetMouseX();
			mousex = GetMouseY();
			mousey -= 10;
			mousex -= 10;
			if (mousex / 25 < 15 && mousex / 25 >= 0 && mousey / 25 < 15 && mousey / 25 >= 0) {
				mousey /= 25;
				mousex /= 25;
				if (board[mousex][mousey] != 0 && board[mousex][mousey] <= 8) {
					board[mousex][mousey] %= 8;
					board[mousex][mousey]++;
				}
				else if (board[mousex][mousey] != 0 && board[mousex][mousey] / 10 == 10) {
					board[mousex][mousey] -= 100;
					board[mousex][mousey] %= 8;
					board[mousex][mousey] += 101;
				}
			}
			else if (mousex / 80 >= 0 && mousex / 80 < 4 && (mousey - 540) / 80 >= 0 && (mousey - 540) / 80 < 3) {
				mousey -= 540;
				mousey /= 80;
				mousex /= 80;
				if (tools[mousex][mousey] != 0 && tools[mousex][mousey] <= 8) {
					tools[mousex][mousey] %= 8;
					tools[mousex][mousey]++;
				}
				else if (tools[mousex][mousey] != 0 && tools[mousex][mousey] / 10 == 10) {
					tools[mousex][mousey] -= 100;
					tools[mousex][mousey] %= 8;
					tools[mousex][mousey] += 101;
				}
			}
		}
	}
	CloseWindow();
}

void init(int id, int board[15][15], int tool[4][3]) {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			board[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			tool[i][j] = 0;
		}
	}
	if (id == 1) {
		board[7][2] = 10;
		board[2][8] = 90;
		tool[0][0] = 1;
	}
	else if (id == 2) {
		board[8][3] = 10;
		board[6][12] = 52;
		board[6][8] = 90;
		board[9][7] = 92;
		tool[0][0] = 1;
		tool[0][1] = 1;
		tool[0][2] = 1;
	}
	else if (id == 3) {
		board[3][0] = 82;
		board[11][14] = 50;
		board[14][3] = 21;
		board[4][7] = 96;
		board[6][9] = 95;
		board[8][7] = 94;
		tool[0][0] = 1;
		tool[0][1] = 1;
		tool[0][2] = 1;
	}
	else if (id == 4) {
		board[7][0] = 13;
		board[14][7] = 32;
		board[7][14] = 51;
		board[0][7] = 70;
		board[7][7] = 91;
		board[7][9] = 90;
		board[7][5] = 92;
		board[7][4] = 93;
		board[7][6] = 93;
		board[7][8] = 93;
		board[7][10] = 93;
		board[4][5] = 120;
		board[4][6] = 120;
		board[4][8] = 120;
		board[4][9] = 120;
		board[10][5] = 120;
		board[10][6] = 120;
		board[10][8] = 120;
		board[10][9] = 120;
		board[9][6] = 120;
		board[9][8] = 120;
		board[5][6] = 120;
		board[5][8] = 120;
		tool[0][0] = 1;
		tool[0][1] = 1;
		tool[0][2] = 1;
		tool[1][0] = 1;
		tool[1][1] = 1;
		tool[1][2] = 1;
		tool[2][0] = 1;
		tool[2][1] = 101;
		tool[2][2] = 101;
		tool[3][0] = 101;
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

void drawReflector(int y, int x, int dir) {
	DrawRectanglePro((Rectangle){y, x, 20, 10}, (Vector2){10, 0}, 360 - dir, BLACK);
	DrawRectanglePro((Rectangle){y, x, 30, 5}, (Vector2){15, 5}, 360 - dir, RED);
}


void drawMirror(int y, int x, int dir) {
	DrawRectanglePro((Rectangle){y, x, 30, 10}, (Vector2){15, 5}, 360 - dir, BLACK);
	DrawRectanglePro((Rectangle){y, x, 24, 5}, (Vector2){12, 5}, 360 - dir, RED);
}
