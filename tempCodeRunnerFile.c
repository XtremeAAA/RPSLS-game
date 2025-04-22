#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Function to convert the number to its corresponding gesture
const char* get_gesture_name(int gesture) {
    switch (gesture) {
        case 0: return "rock";
        case 1: return "fire";
        case 2: return "scissors";
        case 3: return "sponge";
        case 4: return "paper";
        case 5: return "air";
        case 6: return "water";
        default: return "invalid";
    }
}

// Function to determine winner
// Returns 1 if first player wins, 0 for tie, -1 if second player wins
int determine_winner(int player1, int player2) {
    if (player1 == player2) return 0; // Tie
    
    if ((player1 == 0 && (player2 == 1 || player2 == 2 || player2 == 3)) || // Rock pounds Fire, crushes Scissors & Sponge
        (player1 == 1 && (player2 == 2 || player2 == 4 || player2 == 3)) || // Fire melts Scissors, burns Paper & Sponge
        (player1 == 2 && (player2 == 4 || player2 == 3 || player2 == 5)) || // Scissors swish through Air, cut Paper & Sponge
        (player1 == 3 && (player2 == 4 || player2 == 5 || player2 == 6)) || // Sponge soaks Paper, uses Air pockets, absorbs Water
        (player1 == 4 && (player2 == 0 || player2 == 5 || player2 == 6)) || // Paper fans Air, covers Rock, floats on Water
        (player1 == 5 && (player2 == 1 || player2 == 0 || player2 == 6)) || // Air blows out Fire, erodes Rock, evaporates Water
        (player1 == 6 && (player2 == 0 || player2 == 1 || player2 == 2)))   // Water erodes Rock, puts out Fire, rusts Scissors
        return 1; // Player 1 wins
    
    return -1; // Player 2 wins
}

// Function to get input from human player
int get_human_choice() {
    int choice;
    char buffer[100]; // Buffer for input validation
    printf("Enter your gesture:\n");
    printf("0 = rock\n1 = fire\n2 = scissors\n3 = sponge\n4 = paper\n5 = air\n6 = water\n(or type -1 to exit): ");

    while (1) {
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Error reading input! Try again: ");
            continue;
        }
        if (sscanf(buffer, "%d", &choice) == 1 && choice >= -1 && choice <= 6)
            return choice;

        printf("Invalid input! Please enter a number between 0 and 6 or -1 to exit: ");
    }
}

int main() {
    int mode, player1, player2, winner;
    int score1 = 0, score2 = 0;
    srand(time(NULL));

    // Game mode selection
    printf("Select game mode:\n");
    printf("1 - Human vs Human\n2 - Human vs Computer\n3 - Computer vs Computer\n");
    printf("Enter choice (or type -1 to exit): ");

    while (1) {
        char buffer[100];
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Error reading input! Try again: ");
            continue;
        }
        if (sscanf(buffer, "%d", &mode) == 1 && mode >= -1 && mode <= 3)
            break;
        
        printf("Invalid choice! Please enter 1, 2, or 3, or -1 to exit: ");
    }

    if (mode == -1) {
        printf("Exiting game.\n");
        return 0;
    }
    
    while (score1 < 4 && score2 < 4) {
        // Determine gestures based on mode
        if (mode == 1) { // Human vs Human
            printf("----------------------------------\n");
            printf("Human 1:\n");
            player1 = get_human_choice();
            if (player1 == -1) {
                printf("Game exited early.\n");
                return 0;
            }
            printf("Human 2:\n");
            player2 = get_human_choice();
            if (player2 == -1) {
                printf("Game exited early.\n");
                return 0;
            }
        } else if (mode == 2) { // Human vs Computer
            printf("----------------------------------\n");
            printf("Human:\n");
            player1 = get_human_choice();
            if (player1 == -1) {
                printf("Game exited early.\n");
                return 0;
            }
            player2 = rand() % 7; // Computer choice
            printf("Computer chose: %s\n", get_gesture_name(player2));
        } else { // Computer vs Computer
            printf("----------------------------------\n");
            player1 = rand() % 7;
            player2 = rand() % 7;
            printf("Computer 1 chose: %s\n", get_gesture_name(player1));
            printf("Computer 2 chose: %s\n", get_gesture_name(player2));
        }

        // Determine winner
        winner = determine_winner(player1, player2);
        printf("%s vs %s\n", get_gesture_name(player1), get_gesture_name(player2));
        if (winner == 1) {
            printf("%s wins this round!\n", (mode == 3) ? "Computer 1" : (mode == 2) ? "Human" : "Human 1");
            score1++;
        } else if (winner == 0) {
            printf("It's a tie! Play again.\n");
        } else {
            printf("%s wins this round!\n", (mode == 3) ? "Computer 2" : (mode == 2) ? "Computer" : "Human 2");
            score2++;
        }
        printf("Score: %s - %d | %s - %d\n", (mode == 3) ? "Computer 1" : (mode == 2) ? "Human" : "Human 1", 
               score1, 
               (mode == 3) ? "Computer 2" : (mode == 2) ? "Computer" : "Human 2", 
               score2);
    }
    
    // Declare final winner if not exited early
    if (score1 == 4)
        printf("%s wins the game!\n", (mode == 3) ? "Computer 1" : (mode == 2) ? "Human" : "Human 1");
    else
        printf("%s wins the game!\n", (mode == 3) ? "Computer 2" : (mode == 2) ? "Computer" : "Human 2");
    
    return 0;
}
