#include <stdio.h>
#include <conio.h>
#include <stdbool.h>

// Size of the board
#define SIZE 3


// Constants for board cell values
#define PLAYER_X 1
#define PLAYER_O 2

int sum=0;

void playAs();
bool game_over(int board[SIZE][SIZE], int *winner);
void print_board(int board[SIZE][SIZE]);
int evaluate_board(int board[SIZE][SIZE]);
int minimax(int board[SIZE][SIZE], int depth, int alpha, int beta, bool maximizing_player);
void find_best_move(int board[SIZE][SIZE], int *best_row, int *best_col);
bool isEmpty(int board[SIZE][SIZE],int p,int q);

int player,computer;
// Main function
void main()
{
    // Initialize the board
    start:{}
    int board[SIZE][SIZE] ={{0, 0, 0},
                            {0, 0, 0},
                            {0, 0, 0}
                            };

    // Print the initial board
    printf("Initial Board:\n");
    print_board(board);

    // Play the game
    int winner = 0;
    playAs();
    int current_player = PLAYER_X;

    while (!game_over(board, &winner))
    {
        if (current_player == computer)
        {
            // Computer's turn
            int row, col;

            printf("\nMy turn:\n");
            find_best_move(board, &row, &col);

            board[row][col] = computer;
            current_player = player;

            printf("I chose row %d, column %d. It took computer %d recursion to make this decision\n", row+1, col+1,sum);
            print_board(board);
        }
        else
        {
            // Player's turn
            int row, col,z,y;

            printf("Your turn:");
               label: {
                    printf("\nEnter the number of box that you want to choose(1-%d):",SIZE*SIZE);
                    scanf("%d",&y);
                    row=(y-1)/SIZE;
                    col=(y-1)%SIZE;
                    z = isEmpty(board,row,col);
                }
                if(z==false || (y<1 || y>(SIZE*SIZE)))
                    goto label;

            board[row][col] = player;
            current_player = computer;

            printf("You chose row %d, column %d.\n", row+1, col+1);
            print_board(board);
        }
    }

    // Print the final board
    printf("Final Board:\n");
    print_board(board);

    // Print the winner
    if (winner == computer)
    {
        printf("You lose\n");
    }
    else if (winner == player)
    {
        printf("You win!\n");
    }
    else
    {
        printf("It's a tie!\n");
    }
    printf("\n\n Press Enter key to play again.\n Press any other key to exit.\n");
    char key=getch();
    if(key==13){
        goto start;}
    else
        exit(1);
}

void playAs()//non return type without argument
{
    printf("What do you want to play as(X/O):");
    char opt=getch();
    putch(opt);
    if(opt=='X' || opt=='x')
     {
        player=PLAYER_X;//player_x=1
        computer=PLAYER_O;//player_o=2
     }
    else if(opt=='O' || opt=='o')
      {
        computer=PLAYER_X;
        player=PLAYER_O;
      }
    else
    {
        printf("\nPlease enter a valid option.\n");
        playAs();
    }
    printf("\n");
}

// Function to print the board
void print_board(int board[SIZE][SIZE])
{
    printf("\n");
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == PLAYER_X)//player_X=1
            {
                printf("X ");
            }
            else if (board[i][j] == PLAYER_O)//player_O=2
            {
                printf("O ");
            }
            else
            {
                printf("| ");
            }
        }
        printf("\n");
    }
}

// Function to check if the game is over
bool game_over(int board[SIZE][SIZE], int *winner)
{
    // Check rows
    for (int i = 0; i < SIZE; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0)
        {
            *winner = board[i][0];
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < SIZE; j++)
    {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != 0)
        {
            *winner = board[0][j];
            return true;
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0)
    {
        *winner = board[0][0];
        return true;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != 0)
    {
        *winner = board[0][2];
        return true;
    }

    //The game is still running/ not over
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == 0)
            {
                return false;
            }
        }
    }

    // If we get here, the board is full but there is no winner
    *winner = 0;
    return true;
}

// Function to evaluate the board
int evaluate_board(int board[SIZE][SIZE])
{
    // Check rows
    for (int i = 0; i < SIZE; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            if (board[i][0] == computer)
            {
                return 10;
            }
            else if (board[i][0] == player)
            {
                return -10;
            }
        }
    }

    // Check columns
    for (int j = 0; j < SIZE; j++)
    {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j])
        {
            if (board[0][j] == computer)
            {
                return 10;
            }
            else if (board[0][j] == player)
            {
                return -10;
            }
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == computer)
        {
            return 10;
        }
        else if (board[0][0] == player)
        {
            return -10;
        }
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == computer)
        {
            return 10;
        }
        else if (board[0][2] == player)
        {
            return -10;
        }
    }

    // If we get here, no one has won yet
    return 0;
    }

// Function to find the best move using the minimax algorithm with alpha-beta pruning
int minimax(int board[SIZE][SIZE], int depth, int alpha, int beta, bool maximizing_player)
{
    int winner;
    if (game_over(board, &winner))
    {   sum+=depth;
        int score = evaluate_board(board);
        if(score>0)
            return score-depth;
        else
            return score+depth;
    }
    if (maximizing_player)
    {
        int best_score = -1000;

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (board[i][j] == 0)
                {
                    board[i][j] = computer;

                    int score = minimax(board, depth + 1, alpha, beta, false);

                    board[i][j] = 0;//removes the previously made move

                    if (score > best_score)
                    {
                        best_score = score;
                    }

                    if (alpha > best_score)
                    {
                        alpha = best_score;
                    }

                    if (beta <= alpha)
                    {
                        break;
                    }
                }
            }
        }

    return best_score;
    }
    else
    {
        int best_score = 1000;

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (board[i][j] == 0)
                {
                    board[i][j] = player;

                    int score = minimax(board, depth + 1, alpha, beta, true);

                    board[i][j] = 0;

                    if (score < best_score)
                    {
                        best_score = score;
                    }

                    if(beta < best_score)
                    {
                        beta = best_score;
                    }

                    if (beta <= alpha)
                    {
                        break;
                    }
                }
            }
        }

        return best_score;
        }
    }

// Function to find the best move for the given board using the minimax algorithm with alpha-beta pruning
void find_best_move(int board[SIZE][SIZE], int *best_row, int *best_col) {
int best_score = -1000;//limits.h
for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
        if (board[i][j] == 0) {
            board[i][j] = computer;

            int score = minimax(board, 0, -1000, 1000, false);

            board[i][j] = 0;

            if (score > best_score)
            {
                best_score = score;
                *best_row = i;
                *best_col = j;
            }
        }
        }
    }
}


bool isEmpty(int board[3][3],int p,int q)
{
    int l = board[p][q];
    if(l==PLAYER_O || l==PLAYER_X)
        return false;
    else
        return true;
}


