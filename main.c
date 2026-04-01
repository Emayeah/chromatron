#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

void init(int, int[15][15], int[4][6]); // parameter for level id
void getDir(int, int*, int*);
int mod(int, int);
void drawMirror(int, int, int);
void drawReflector(int, int, int);
void drawLaser(int, int, int);

int main() {
	InitWindow(800, 600, "Chromatron");
	SetTargetFPS(60);
	int board[15][15]; // board del gioco, [height][width]
	int tools[4][6]; // tall 4, wide 6
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
	int levelAmount = 6;
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
			for (int j = 0; j < 6; j++) {
				DrawRectangle((800 - (6 - j) * 25) - 10, i * 25 + 10, 25, 25, GRAY);
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 6; j++) {
				DrawRectangleLines((800 - (6 - j) * 25) - 10, i * 25 + 10, 25, 25, BROWN);
			}
		}
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				if (board[i][j] / 10 <= 8 && board[i][j] >= 10) {
					drawLaser(j * 25, i * 25, board[i][j]);
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
							DrawRectanglePro((Rectangle){posy * 25 + 22, posx * 25 + 22, (25 + 17.7f * ((dirx * dirx) == (diry * diry))), 2}, (Vector2){12.5 + 8.84f * ((dirx * dirx) == (diry * diry)), 1}, 360 - dir, color);
							// true == 1, false == 0, if both are 1 then the line needs to be longer
						}
						else if (board[posx][posy] <= 8) {
							DrawRectanglePro((Rectangle){posy * 25 + 22, posx * 25 + 22, (12.5 + 8.84f * ((dirx * dirx) == (diry * diry))), 2}, (Vector2){12.5 + 8.84f * ((dirx * dirx) == (diry * diry)), 1}, 360 - dir, color);
							tempDir = board[posx][posy] - 1;
							dir /= 45;
							if (mod(dir + 1, 8) == tempDir || mod(dir + 2, 8) == tempDir || mod(dir + 3, 8) == tempDir) {
								dir = tempDir * 2 - dir;
								dir = mod(dir, 8);
								getDir(dir, &dirx, &diry);
								dir *= 45;
								DrawRectanglePro((Rectangle){posy * 25 + 22, posx * 25 + 22, (12.5 + 8.84f * ((dirx * dirx) == (diry *  diry))), 2}, (Vector2){12.5f + 8.84f * ((dirx * dirx) == (diry * diry)), 1}, 180 - dir, color);
							}
							else {
								flag = 1;
							}
						}
						else if (board[posx][posy] / 10 == 10) {
							DrawRectanglePro((Rectangle){posy * 25 + 22, posx * 25 + 22, (12.5 + 8.84f * ((dirx * dirx) == (diry * diry))), 2}, (Vector2){12.5 + 8.84f * ((dirx * dirx) == (diry * diry)), 1}, 360 - dir, color);
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
								DrawRectanglePro((Rectangle){posy * 25 + 22, posx * 25 + 22, (12.5 + 8.84f * ((dirx * dirx) == (diry *  diry))), 2}, (Vector2){12.5f + 8.84f * ((dirx * dirx) == (diry * diry)), 1}, 180 - dir, color);
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
					DrawRectangleLines(j * 25 + 10, i * 25 + 10, 23, 23, LIGHTGRAY);
					DrawRectangleLines(j * 25 + 11, i * 25 + 11, 23, 23, BLACK);
					DrawPixel(j * 25 + 33, i * 25 + 9, BLACK);
					DrawPixel(j * 25 + 9, i * 25 + 33, BLACK);
					DrawRectangle(j * 25 + 10, i * 25 + 10, 23, 23, GRAY);
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
			for (int j = 0; j < 6; j++) {
				if (tools[i][j] != 0 && tools[i][j] <= 8) {
					tempDir = tools[i][j] - 1;
					tempDir *= 45;
					drawMirror((800 - (6 - j) * 25) + 2, i * 25 + 20, tempDir);
//					DrawRectangle((800 - (3 - j) * 80) + 25, i * 60 + 30, 10, 40, BLACK);
//					DrawRectangle((800 - (3 - j) * 80) + 35, i * 60 + 25, 5, 50, RED);
				}
				else if (tools[i][j] != 0 && tools[i][j] / 10 == 10) {
					tempDir = tools[i][j] - 101;
					tempDir *= 45;
					drawReflector((800 - (6 - j) * 25) + 2, i * 25 + 20, tempDir + 22.5);
				}
			}
		}
		for (int i = 1; i <= levelAmount; i++) {
			if (i <= maxLevel) {
				DrawText(TextFormat("%d ", i), 800 - 460 + 80 * ((float)((float)(-levelAmount)/2) + i), 600 - 100, 80, RED);
			}
			else {
				DrawText(TextFormat("%d ", i), 800 - 460 + 80 * ((float)((float)(-levelAmount)/2) + i), 600 - 100, 80, BLACK);
			}
		}
		if (cantWin == 0) {
			if (maxLevel == currentLevel) {
				maxLevel++;
			}
		}
		else if (maxLevel > currentLevel) {
			DrawText("(won)", 360, 430, 20, BLACK);
		}
		if (IsMouseButtonPressed(0)) {
			mousey = GetMouseX();
			mousex = GetMouseY();
			mousey -= 10;
			mousex -= 10;
			if (mod(mousex, 600) <= 320 && mod(mousey, 800) >= 625) {
				mousey -= 625;
				if (mousex / 25 >= 0 && mousex / 25 < 4 && mousey / 25 >= 0 && mousey / 25 < 6) {
					mousex /= 25;
					mousey /= 25;
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
				if (mousex / 25 >= 0 && mousex / 25 < 4 && (mousey - 640) / 25 >= 0 && (mousey - 640) / 25 < 6) {
					mousey -= 640;
					mousey /= 25;
					mousex /= 25;
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
			else if (mousey >= 400 + 80 * (float)((float)(-levelAmount)/2) && mousey <= 400 + 80 * (float)((float)(levelAmount)/2) && mousex >= 500 && mousex <= 580) {
			//else if (mousex >= 500 && mousex <= 580 && mousey >= 250 && mousey <= 570) {
				mousey -= 400 + 80 * (float)((float)(-levelAmount)/2);
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
			else if (mousex / 25 >= 0 && mousex / 25 < 4 && (mousey - 640) / 25 >= 0 && (mousey - 640) / 25 < 6) {
				mousey -= 640;
				mousey /= 25;
				mousex /= 25;
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

void init(int id, int board[15][15], int tool[4][6]) {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			board[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
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
		for (int i = 0; i < 15; i++) {
			board[i][0] = 120;
			board[i][14] = 120;
			board[0][i] = 120;
			board[14][i] = 120;
		}
		board[1][3] = 70;
		board[1][10] = 72;
		board[10][5] = 90;
		board[5][4] = 92;
		board[3][7] = 92;
		board[4][11] = 90;
		tool[0][0] = 101;
		tool[0][1] = 101;
		tool[0][2] = 101;
	}
	else if (id == 5) {
		board[1][0] = 10;
		for (int i = 0; i <= 11; i++) {
			board[3][i] = 120;
		}
		for (int i = 2; i <= 11; i++) {
			board[12][i] = 120;
		}
		for (int i = 2; i <= 8; i++) {
			board[6][i] = 120;
		}
		for (int i = 4; i <= 8; i++) {
			board[10][i] = 120;
		}
		for (int i = 4; i <= 6; i++) {
			board[8][i] = 120;
		}
		for (int i = 3; i <= 12; i++) {
			board[i][11] = 120;
		}
		for (int i = 6; i <= 12; i++) {
			board[i][2] = 120;
		}
		for (int i = 6; i <= 10; i++) {
			board[i][8] = 120;
		}
		board[9][4] = 120;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 6; j++) {
				tool[i][j] = 101;
			}
		}
		tool[3][0] = 101;
		tool[0][0] = 1;
		board[1][12] = 90;
		board[2][13] = 90;
		board[13][11] = 90;
		board[14][7] = 90;
		board[9][1] = 90;
		board[5][2] = 90;
		board[5][7] = 90;
		board[8][10] = 90;
		board[9][5] = 90;
	}
	else if (id == 6) {
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
		tool[0][3] = 1;
		tool[0][4] = 1;
		tool[0][5] = 1;
		tool[1][0] = 1;
		tool[1][1] = 101;
		tool[1][2] = 101;
		tool[1][3] = 101;
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
	DrawRectanglePro((Rectangle){y, x, 8, 6}, (Vector2){4, 0}, 360 - dir, BLACK);
	DrawRectanglePro((Rectangle){y, x, 16, 2}, (Vector2){8, 1}, 360 - dir, RED);
}


void drawMirror(int y, int x, int dir) {
	DrawRectanglePro((Rectangle){y, x, 16, 4}, (Vector2){8, 2}, 360 - dir, BLACK);
	DrawRectanglePro((Rectangle){y, x, 12, 2}, (Vector2){6, 2}, 360 - dir, RED);
}

void drawLaser(int y, int x, int id) {
	Color colors[] = {RED, GREEN, BLUE, WHITE};
	int dirx, diry;
	getDir((id / 10 - 1), &dirx, &diry);
	DrawCircle(y + 22 - (5 * diry), x + 22 - (5 * dirx), 6, LIGHTGRAY);
	DrawCircle(y + 22 - (5 * diry), x + 22 - (5 * dirx), 3, colors[id % 10]);
	DrawRectanglePro((Rectangle){y + 22, x + 22, 14, 4}, (Vector2){2, 2}, 360 - ((id / 10 - 1) * 45), LIGHTGRAY);
}
