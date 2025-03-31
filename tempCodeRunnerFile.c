#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Function to convert the number to its corresponding gesture
const char* get_gesture_name(int gesture) {
    switch (gesture) {
        case 0: return "rock";
        case 1: return "paper";
        case 2: return "scissors";
        case 3: return "lizard";
        case 4: return "spock";
        default: return "invalid";
    }
}

// Function to determine winner
// Returns 1 if first player wins, 0 for tie, -1 if second player wins
int determine_winner(int player1, int player2) {
    if (player1 == player2) return 0; // Tie
    
    if ((player1 == 0 && (player2 == 2 || player2 == 3)) || // Rock crushes Scissors/Lizard
        (player1 == 1 && (player2 == 0 || player2 == 4)) || // Paper covers Rock / disproves Spock
        (player1 == 2 && (player2 == 1 || player2 == 3)) || // Scissors cuts Paper / decapitates Lizard
        (player1 == 3 && (player2 == 1 || player2 == 4)) || // Lizard eats Paper / poisons Spock
        (player1 == 4 && (player2 == 0 || player2 == 2)))   // Spock vaporizes Rock / smashes Scissors
        return 1; // Player 1 wins
    
    return -1; // Player 2 wins
}

// Function to get input from human player
int get_human_choice() {
    int choice;
    printf("Enter your gesture (0=rock, 1=paper, 2=scissors, 3=lizard, 4=spock or type -1 to exit): ");
    while (scanf("%d", &choice) != 1 || (choice < -1 || choice > 4)) {
        printf("Invalid input! Please enter a number between 0 and 4 or -1 to exit: ");
        while (getchar() != '\n'); // Clear input buffer
    }
    return choice;
}

int main() {
    int mode, player1, player2, winner;
    int score1 = 0, score2 = 0;
    srand(time(NULL));

    // Game mode selection
    printf("Select game mode:\n");
    printf("1 - Human vs Human\n");
    printf("2 - Human vs Computer\n");
    printf("3 - Computer vs Computer\n");
    printf("Enter choice (or type -1 to exit): ");
    while (scanf("%d", &mode) != 1 || (mode < -1 || mode > 3)) {
        printf("Invalid choice! Please enter 1, 2, or 3, or -1 to exit: ");
        while (getchar() != '\n'); // Clear input buffer
    }
    if (mode == -1) {
        printf("Exiting game.\n");
        return 0;
    }
    
    while (score1 < 4 && score2 < 4) {
        // Determine gestures based on mode
        if (mode == 1) { // Human vs Human
            printf("----------------------------------\n");
            printf("Human 1: ");
            player1 = get_human_choice();
            if (player1 == -1) break;
            printf("Human 2: ");
            player2 = get_human_choice();
            if (player2 == -1) break;
        } else if (mode == 2) { // Human vs Computer
            printf("----------------------------------\n");
            printf("Human: ");
            player1 = get_human_choice();
            if (player1 == -1) break;
            player2 = rand() % 5; // Computer choice
            printf("Computer chose: %s\n", get_gesture_name(player2));
        } else { // Computer vs Computer
            printf("----------------------------------\n");
            player1 = rand() % 5;
            player2 = rand() % 5;
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
        printf("Score: %s - %d | %s - %d\n", (mode == 3) ? "Computer 1" : (mode == 2) ? "Human" : "Human 1", score1, (mode == 3) ? "Computer 2" : (mode == 2) ? "Computer" : "Human 2", score2);
        
        // If in computer mode, wait for user input to continue or exit
        if (mode == 3) {
            printf("Type 'cont' to continue or 'exit' to quit: ");
            char cont[10];
            while (scanf("%s", cont) != 1 || (strcmp(cont, "cont") != 0 && strcmp(cont, "exit") != 0)) {
                printf("Invalid input! Type 'cont' to continue or 'exit' to quit: ");
                while (getchar() != '\n'); // Clear input buffer
            }
            if (strcmp(cont, "exit") == 0) break;
        }
    }
    
    // Declare final winner if not exited early
    if (score1 == 4)
        printf("%s wins the game!\n", (mode == 3) ? "Computer 1" : (mode == 2) ? "Human" : "Human 1");
    else if (score2 == 4)
        printf("%s wins the game!\n", (mode == 3) ? "Computer 2" : (mode == 2) ? "Computer" : "Human 2");
    else
        printf("Game exited before completion.\n");
    
    return 0;
}