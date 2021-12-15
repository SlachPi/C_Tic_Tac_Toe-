#include <stdio.h>

void display(char* game) {
    printf(" ______________ \n");
    for (int i = 0; i < 3; ++i) {
        printf("| %c  | %c  | %c  |\n", game[i*3], game[i*3+1], game[i*3+2]);
        printf("|____|____|____|\n");
    }
}

void play(char* game, int pos, int turn) {
    if (turn % 2 == 0)
        game[pos] = 'X';
    else
        game[pos] = 'O';
}

int are_equal(char* game, int a, int b, int c) {
    if (game[a] == game[b] && game[a] == game[c]) {
        if (game[a] == 'X')
            return 1;
        if (game[a] == 'O')
            return -1;
    }
    return 0;
}

int is_win(char* game) {
    int result = 0;

    result += are_equal(game, 0, 4, 8);
    result += are_equal(game, 2, 4, 6);

    for (int i = 0; i < 3 && result == 0; ++i) {
       result += are_equal(game, i*3, i*3+1, i*3+2);
       result += are_equal(game, i, i+3, i+6);;
    }
    
    return result;
}

int minimax(char* game, int turn, int* next_play) {
    /* Is it a dead end ? */
    int score = is_win(game);
    if (turn == 9 || score != 0)
        return score;

    /* Max score for a minimizer (O) / Least score for a maximizer (X) */ 
    int value = 2;
    if (turn % 2 == 0)
        value = -value;

    for (int i = 0; i < 9; ++i) {
        if (game[i] != ' ')
            continue;

        play(game, i, turn);
        
        int future = minimax(game, turn + 1, next_play + 1);

        if ((value < future && turn % 2 == 0) || (value > future && turn % 2 == 1)) {
            value = future;
            *next_play = i;
        }

        game[i] = ' '; // undo the play
    }

    return value;
}

int main() {
    char game[9];
    int turn = 0, player = 0;

    for (int i = 0; i < 9; ++i)
        game[i] = ' ';

    for (int turn = 0; turn < 9 && is_win(game) == 0; ++turn) {
        display(game);

        if (turn % 2 == 1) {
           int computer_play[9];
           minimax(game, turn, computer_play);
           play(game, computer_play[0], turn);
           continue;
        }

        int i, j;
        printf("row col : ");
        scanf("%d %d", &i, &j);
        play(game, i*3+j, turn); 
    }

    display(game);
    return 0;
}
