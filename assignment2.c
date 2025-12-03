#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define HEIGHT 10   // obstacle falling height

// ---------- Sound helpers ----------
void soundMove()  { Beep(700, 30); }
void soundScore() { Beep(900, 50); }
void soundCrash() { Beep(300, 400); }
void soundSpeedUp(){ Beep(1100, 80); }

// ---------- High score file ----------
int highScore = 0;

void loadHighScore(void) {
    FILE *fp = fopen("highscore.txt", "r");
    if (!fp) { highScore = 0; return; }
    if (fscanf(fp, "%d", &highScore) != 1) highScore = 0;
    fclose(fp);
}

void saveHighScore(int score) {
    FILE *fp = fopen("highscore.txt", "w");
    if (!fp) return;
    fprintf(fp, "%d", score);
    fclose(fp);
}

// ---------- GAME ----------
int playGame(void) {
    int x = 1;                       // player lane 0–2
    int step = 0;                    // vertical obstacle position
    int obstaclePos = rand() % 3;    // lane 0–2
    int score = 0;
    int speed = 150;

    while (1) {

        // ---- INPUT ----
        if (_kbhit()) {
            int ch = getch();
            if (ch == 0 || ch == 224) {
                ch = getch();
                if (ch == 75 && x > 0) {   // left
                    x--;
                    soundMove();
                } else if (ch == 77 && x < 2) { // right
                    x++;
                    soundMove();
                }
            }
            else if (ch == 'q' || ch == 'Q')
                return score;
        }

        // ---- DRAW ----
        system("cls");
        printf("\n   Simple Lane Runner Game\n");
        printf("   Score: %d   High Score: %d\n", score, highScore);
        printf("---------------------------------\n");


        // falling rows
        for (int i = 0; i < HEIGHT; i++) {
            printf("|");
            for (int lane = 0; lane < 3; lane++) {
                if (i == step && lane == obstaclePos)
                    printf(" + ");   // obstacle
                else
                    printf("   ");
                printf("|");
            }
            printf("\n");
        }

        // PLAYER ROW
        printf("|");
        for (int lane = 0; lane < 3; lane++) {
            if (lane == x)
                printf(" | ");       // player
            else
                printf("   ");
            printf("|");
        }
        printf("\n");

        // ---- COLLISION ----
        if (step == HEIGHT - 1 && x == obstaclePos) {
            soundCrash();
            printf("\n GAME OVER!\n");
            return score;
        }

        Sleep(speed);
        step++;

        // reached bottom → reset obstacle
        if (step >= HEIGHT) {
            step = 0;
            obstaclePos = rand() % 3;
            score++;
            soundScore();

            if (speed > 40) {
                speed -= 5;
                soundSpeedUp();
            }
        }
    }
}

// ---------- clear stdin ----------
void clear_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// ---------- MAIN ----------
int main(void) {
    srand((unsigned) time(NULL));
    loadHighScore();

    while (1) {
        int score = playGame();

        printf("\nYour Score: %d\n", score);

        if (score > highScore) {
            printf("NEW HIGH SCORE!\n");
            highScore = score;
            saveHighScore(highScore);
        }

        printf("\nWanna Play Again? (y/n): ");
        int ch = getchar();
        clear_stdin();
        if (ch != 'y' && ch != 'Y') {
            printf("\nThanks for playing!\n");
            break;
        }
        system("cls");
    }

    return 0;
}