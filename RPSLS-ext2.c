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

// Function to determine the winner using modular arithmetic
// Returns 1 if player1 wins, 0 for tie, -1 if player2 wins
// Recursive function to determine the winner
int determine_winner_recursive(int player1, int player2, int num_gestures, int step) {
    // Base case: if both players chose the same gesture, it's a tie
    if (player1 == player2) return 0;

    // Recursive case: simulate checking the win condition step by step
    if (step == num_gestures / 2) return -1; // If we reach the halfway mark, player2 wins

    // If player1 beats player2 in this step, return 1 (player1 wins)
    if ((player1 - player2 + num_gestures) % num_gestures == step) return 1;

    // Recursively check the next step
    return determine_winner_recursive(player1, player2, num_gestures, step + 1);
}


// Function to get input from human player
int get_human_choice() {
    int choice;
    printf("\nChoose your gesture:\n");
    printf("0 = rock, 1 = fire, 2 = scissors, 3 = sponge, 4 = paper, 5 = air, 6 = water\n");
    printf("(or type -1 to exit): ");
    
    while (1) {
        if (scanf("%d", &choice) == 1 && (choice >= -1 && choice <= 7)) {
            return choice;
        } else {
            printf("Invalid input! Enter a number between 0 and 6 or -1 to exit: ");
            while (getchar() != '\n'); // Clear buffer
        }
    }
}

int main() {
    int mode, player1, player2, winner;
    int score1 = 0, score2 = 0;
    const int num_gestures = 7; // Number of gestures (can be increased)
    srand(time(NULL));

    // Game mode selection
    printf("Select game mode:\n");
    printf("1 - Human vs Human\n2 - Human vs Computer\n3 - Computer vs Computer\n");
    printf("Enter choice (or type -1 to exit): ");

    while (scanf("%d", &mode) != 1 || (mode < -1 || mode > 3)) {
        printf("Invalid choice! Please enter 1, 2, 3, or -1 to exit: ");
        while (getchar() != '\n'); // Clear input buffer
    }
    
    if (mode == -1) {
        printf("Exiting game.\n");
        return 0;
    }
    
    while (score1 < 4 && score2 < 4) {
        printf("\n----------------------------------\n");
        
        // Determine gestures based on mode
        if (mode == 1) { // Human vs Human
            printf("Human 1: ");
            player1 = get_human_choice();
            if (player1 == -1) break;
            printf("Human 2: ");
            player2 = get_human_choice();
            if (player2 == -1) break;
        } else if (mode == 2) { // Human vs Computer
            printf("Human: ");
            player1 = get_human_choice();
            if (player1 == -1) break;
            player2 = rand() % num_gestures; // Computer choice
            printf("Computer chose: %s\n", get_gesture_name(player2));
        } else { // Computer vs Computer
            player1 = rand() % num_gestures;
            player2 = rand() % num_gestures;
            printf("Computer 1 chose: %s\n", get_gesture_name(player1));
            printf("Computer 2 chose: %s\n", get_gesture_name(player2));
        }

        // Determine winner
        winner = determine_winner_recursive(player1, player2, num_gestures, 0); // Pass the total number of gestures
        printf("\n%s vs %s\n", get_gesture_name(player1), get_gesture_name(player2));
        
        if (winner == 1) {
            printf("%s wins this round!\n", 
                (mode == 3) ? "Computer 1" : (mode == 2) ? "Human" : "Human 1");
            score1++;
        } else if (winner == 0) {
            printf("It's a tie! Play again.\n");
        } else {
            printf("%s wins this round!\n", 
                (mode == 3) ? "Computer 2" : (mode == 2) ? "Computer" : "Human 2");
            score2++;
        }

        printf("Score: %s - %d | %s - %d\n", 
            (mode == 3) ? "Computer 1" : (mode == 2) ? "Human" : "Human 1", score1, 
            (mode == 3) ? "Computer 2" : (mode == 2) ? "Computer" : "Human 2", score2);
    }
    
    // Declare final winner if not exited early
    if (score1 == 4)
        printf("\n%s wins the game!\n", (mode == 3) ? "Computer 1" : (mode == 2) ? "Human" : "Human 1");
    else if (score2 == 4)
        printf("\n%s wins the game!\n", (mode == 3) ? "Computer 2" : (mode == 2) ? "Computer" : "Human 2");
    else
        printf("\nGame exited before completion.\n");
    
    return 0;
}
