// Final Project
// Team 5

#include <stdlib.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  Serial.begin(9600);

  lcd.begin(20,4);
  lcd.backlight();

}

void loop() {
int choice = 0;
  switch(choice) {
    case 1:
      hangman();
      break;
    case 2:
      ticTacToe();
      break;
    case 3:
      matching();
      break;
  }
}

// lcd.noblink() and lcd.blink() to blink turn on blinking cursor for hangman
// hangman is where the implementation for the hangman game logic is going to be put.
// no arguments are passed to the function because everything that the function needs will
// declared within the function.
void hangman() {

}

// ticTacToe is where the implementation for the Tic Tac Toe game logic is going to be put.
// no arguments are passed to the function because everything that the function needs will
// declared within the function.
void ticTacToe() {
  // Variables specific to tic-tac-toe
  bool keepPlaying = true;
  int gameType = 0;
  while (keepPlaying) {
  // Code specific to show menu
    switch(gameType) {
    case 1:
      break;
    case 2:
      break;
    }
  }
}

//----------------------------------------------------------------------------------//
//
//                                     Matching Game
//
// functions associated with the matching game:
//   - matching()         | Mainly focuses on the creation of the light pattern as 
//                          well as controlling game difficulty.
//   - promptPlayer()     | This function is designed to just be putting out a 
//                          prompt to the user asking if they are ready to play.
//                          If they are not ready to play then they will be taken
//                          back to the main menu. Other information to be printed
//                          to the screen include the stage number, remaining tries
//                          and the difficulty chosen.
//   - playMatchingGame() | This is the function that controls the main game logic
//                          regarding a winning message to be printed to the user
//                          after completing all stages, manages the players lives
//                          and handles to output from promptPlayer() to exit the 
//                          game if the player chooses to do so.
//   - playLightPattern() | This function will loop through the lights to show the
//                          pattern to the player that they will then need to copy.
//   - verifyMatch()      | This function is designed to be called within
//                          playMatchingGame to get the user's attempt to match the
//                          pattern that was displayed to them from playLightPattern()
//   - fillPattern()      | This function's purpose is to take in an argument pattern
//                          and fill it with a random value from 1-5(i.e. 0, 1, 2, 3, 4)
//                          to ensure a random version every time someone plays a game.
//   - getButton()        | This function will check to see which of the 5 buttons are
//                          actively being pushed for the pattern.
//----------------------------------------------------------------------------------//

// matching is where the implementation for the matching game's logic is going to be put.
// no arguments are passed to the function because everything that the function needs will
// declared within the function.
void matching() {
  // Variables specific to the matching game
  bool keepPlaying = true;
  int gameDifficulty = 1;
  int *pattern;
  int lives = 3;
  int stage = 1;
  
  
  while (keepPlaying) {
    keepPlaying = playMatchingGame(&lives, gameDifficulty, &stage,  pattern);
    stage++;

    // Prints a winning message to the player if they successfully beat all 3 stages.
    if (stage > 3) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   Congratulations");
      lcd.setCursor(0, 2);
      lcd.print("Stages Cleared:    ");
      lcd.setCursor(19, 2);
      lcd.print(stage);
      lcd.setCursor(0,3);
      lcd.print("Remaining Lives:   ");
      lcd.setCursor(19, 3);
      lcd.print(lives);
    }
  }
  delete [] pattern;
} 

// promptPlayer will print out to the LCD the number of lives, the difficulty
// and the stage number. This function also include a prompt to the player to 
// ask if they are ready. 
// lcd is a 20 x 4 screen.
// Returns whether or not the player is ready to play.
bool promptPlayer(int lives, int difficulty, int stage) {
  lcd.clear();
  lcd.setCursor(0, 0);
}

// playMatchingGame contains the logic for calling the functions that control the smaller
// parts of the game. It controls prompting the player, setting the pattern, playing the
// pattern for the player, and determining whether or not the player is 
// returns whether or not the player has any lives remaining.
bool playMatchingGame(int *lives, int difficulty, int *stage, int * pattern) {
  // Variables for the function
  bool stageComeplete = false;
  if (!promptPlayer(lives, difficulty, stage)) {
    return false;
  }
  fillPattern(pattern, difficulty);
  while(lives > 0) {
    playLightPattern(pattern);
    if (verifyMatch(pattern, difficulty)) {
      return true;
    }
    --lives;
  }
  return false;
}

// playLightPattern
void playLightPattern(int *pattern) {
  
}

// verifyMatch is the function that validates the 
bool verifyMatch(int *pattern, int difficulty) {
  bool found = false;
  switch (difficulty) {
  case 1:
    for (int i = 0; i < 5; ++i) {
      int input = getButton();
      if (pattern[i] != input) {
        found = true;
      }
    }
    break;
  case 2:
    for (int i = 0; i < 7; ++i) {
        int input = getButton();
        if (pattern[i] != input) {
          found = true;
        }
      }
    break;
  case 3:
    for (int i = 0; i < 9; ++i) {
      int input = getButton();
      if (pattern[i] != input) {
        found = true;
      }
    }
    break;
  }
 if (found) {
  return false;
 }
 return true;
}

// fillPattern
void fillPattern(int *pattern, int difficulty) {
  srand((unsigned) millis());

  switch (difficulty) {
  case 1:
    pattern = new int[5];
    for (int i = 0; i < 5; ++i) {
      pattern[i] = rand() % 5;
    }
    break;
  case 2:
    pattern = new int[7];
    for (int i = 0; i < 7; ++i) {
      pattern[i] = rand() % 5;
    }
    break;
  case 3:
    pattern = new int[9];
    for (int i = 0; i < 9; ++i) {
      pattern[i] = rand() % 5;
    }
    break;
  }
}

// getButton
int getButton() {
  return 0;
}

