// Final Project
// Team 5

#include <stdlib.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>

const int LEFT_BUTTON = 12;
const int LEFT_LED = 11;
const int UP_BUTTON = 10;
const int UP_LED = 9;
const int DOWN_BUTTON = 8;
const int DOWN_LED = 7;
const int RIGHT_BUTTON = 6;
const int RIGHT_LED = 5;
const int ENTER_BUTTON = 4;
const int ENTER_LED = 3;

const int BUTTON_ARRAY[] = {LEFT_BUTTON, UP_BUTTON, DOWN_BUTTON, RIGHT_BUTTON, ENTER_BUTTON};
const int LED_ARRAY[] = {LEFT_LED, UP_LED, DOWN_LED, RIGHT_LED, ENTER_LED};

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Menu variables
int mainMenuLineForArrow = 0;
int previousLine = -1; // -1 symbolizes a unset value for previousLine


void setup() {
  Serial.begin(9600);

  lcd.begin(20, 4);
  lcd.backlight();
  lcd.clear();

  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(ENTER_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_LED, OUTPUT);
  pinMode(UP_LED, OUTPUT);
  pinMode(RIGHT_LED, OUTPUT);
  pinMode(DOWN_LED, OUTPUT);
  pinMode(ENTER_LED, OUTPUT);

  // Random number seed.
  randomSeed(analogRead(0));
}

void loop() {
  int choice = 0;
  mainMenuLineForArrow = menuButtonDetection(mainMenuLineForArrow, &choice);
  mainMenuLineForArrow %= 3;
  writeMenu(mainMenuLineForArrow, previousLine);
  switch (choice) {
    case 1:
      lcd.clear();
      hangman();
      previousLine = -1;
      choice = 0;
      lcd.clear();
      break;
    case 2:
      lcd.clear();
      ticTacToe();
      previousLine = -1;
      choice = 0;
      lcd.clear();
      break;
    case 3:
      lcd.clear();
      matching();
      previousLine = -1;
      choice = 0;
      lcd.clear();
      break;
  }
  previousLine = mainMenuLineForArrow;
}

//----------------------------------------------------------------------------------//
//
//                                   Menu Management
//
// functions associated with the hangman game:
//   - writeMenu()            | This function writes the main menu to the lcd.
//
//   - menuButtonDetection()  | This function gets the input from the board and
//                              moves the arrow on the lcd and if the enter is
//                              pushed then the menu is changed to be the one
//                              corresponding with the selection for where the
//                              cursor is.
//
//   - writeHangmanMenu()     | This function writes out the "game board" of
//                              the hangman game including lives, guessed letters
//                              and the progress on the current word to guess.
//
//   - getTTTGameType()       | This function determines the game type of Tic Tac
//                              Toe between the choice of Player vs Player or
//                              Player vs Computer.
//
//   - getTTTPlayerOne()      | This function prompts the player to choose even or
//                              odd. If the player chooses even it returns 2, if
//                              they choose odd then it returns 1.
//
//
//----------------------------------------------------------------------------------//

// Main Menu
int menuButtonDetection(int lineForArrow, int *choice) {
  bool leftPushed, upPushed, downPushed, rightPushed, enterPushed;
  leftPushed = digitalRead(LEFT_BUTTON);
  upPushed = digitalRead(UP_BUTTON);
  downPushed = digitalRead(DOWN_BUTTON);
  rightPushed = digitalRead(RIGHT_BUTTON);
  enterPushed = digitalRead(ENTER_BUTTON);
  if (!upPushed) {
    --lineForArrow;
    if (lineForArrow < 0) {
      lineForArrow = 0;
    }
    delay(250);
  } else if (!downPushed) {
    ++lineForArrow;
    if (lineForArrow > 3) {
      lineForArrow = 3;
    }
    delay(250);
  } else if (!enterPushed) {
    *choice = lineForArrow + 1;
    delay(250);
  }
  return lineForArrow;
}

void writeMenu(int lineForArrow, int prevLine) {
  if (lineForArrow == prevLine) {
    return;
  }
  lcd.setCursor(0, 0);
  lcd.print("Choose Your Game:");
  lcd.setCursor(0, 1);
  lcd.print("  1. Hangman");
  lcd.setCursor(0, 2);
  lcd.print("  2. Tic-Tac-Toe");
  lcd.setCursor(0, 3);
  lcd.print("  3. LED Matching");
  lcd.setCursor(0, lineForArrow + 1);
  lcd.print(">");
}

// Hangman
void writeHangmanMenu(int lineForArrow, int lives) {//, char* guessedLetters, char* guessingWord) {
  lcd.setCursor(0, 0);
  lcd.print("Lives: ");
  lcd.setCursor(7, 0);
  lcd.print(lives);
  lcd.setCursor(0, 1);
  lcd.print("Guessed Letters");
  lcd.setCursor(0, 2);
  //  lcd.print(guessedLetters);
  lcd.setCursor(0, 3);
  //  lcd.print(guessingWord);
}

// Tic Tac Toe
int getTTTGameType() {
  int lineForArrow = 1;
  int prev = -1; // -1 for an unset prevLine
  lcd.setCursor(0, 0);
  lcd.print("Tic-Tac-Toe:");
  lcd.setCursor(1, 1);
  lcd.print("1. Player vs Player");
  lcd.setCursor(1, 2);
  lcd.print("2. Player vs AI");
  while (digitalRead(ENTER_BUTTON)) {
    if (prev != lineForArrow) {
      lcd.setCursor(0, lineForArrow);
      lcd.print(">");
    }
    if (!digitalRead(UP_BUTTON)) {
      --lineForArrow;
      if (lineForArrow < 1) {
        lineForArrow = 1;
      }
    }
    if (!digitalRead(DOWN_BUTTON)) {
      ++lineForArrow;
      if (lineForArrow > 2) {
        lineForArrow = 2;
      }
    }
    prev = lineForArrow;
  }
  return lineForArrow;
}

int getTTTPlayerOne() {
  int arrow = 1;
  int prevLine = -1; // -1 for an unset prevLine
  lcd.setCursor(0, 0);
  lcd.print("Even or Odd?");
  lcd.setCursor(2, 1);
  lcd.print("Even");
  lcd.setCursor(2, 2);
  lcd.print("Odd");
  while (digitalRead(ENTER_BUTTON)) {
    if (prevLine != arrow) {
      lcd.setCursor(0, arrow);
      lcd.print(">");
    }
    if (!digitalRead(UP_BUTTON)) {
      --arrow;
      if (arrow < 1) {
        arrow = 1;
      }
    }
    if (!digitalRead(DOWN_BUTTON)) {
      ++arrow;
      if (arrow > 2) {
        arrow = 2;
      }
    }
    Serial.print("prev = ");
    Serial.println(prevLine);
    Serial.print("curr = ");
    Serial.println(arrow);
    prevLine = arrow;
  }
  return arrow;
}

// Matching Game
int getMGDifficulty(int lineForArrow, int *difficulty) {
  bool leftPushed, upPushed, downPushed, rightPushed, enterPushed;
  leftPushed = digitalRead(LEFT_BUTTON);
  upPushed = digitalRead(UP_BUTTON);
  downPushed = digitalRead(DOWN_BUTTON);
  rightPushed = digitalRead(RIGHT_BUTTON);
  enterPushed = digitalRead(ENTER_BUTTON);
  if (!upPushed) {
    --lineForArrow;
    if (lineForArrow < 0) {
      lineForArrow = 0;
    }
    delay(250);
  } else if (!downPushed) {
    ++lineForArrow;
    if (lineForArrow > 3) {
      lineForArrow = 3;
    }
    delay(250);
  } else if (!enterPushed) {
    *difficulty = lineForArrow + 1;
    delay(250);
  }
  return lineForArrow;
}
void writeMatchingGameMenu(int lineForArrow, int prevLine) {
  if (lineForArrow == prevLine) {
    return;
  }
  lcd.setCursor(0, 0);
  lcd.print("Pick your difficulty:");
  lcd.setCursor(0, 1);
  lcd.print("  1. Easy");
  lcd.setCursor(0, 2);
  lcd.print("  2. Intermediate");
  lcd.setCursor(0, 3);
  lcd.print("  3. Hard");
  lcd.setCursor(0, lineForArrow + 1);
  lcd.print(">");
}
//----------------------------------------------------------------------------------//
//
//                                        Hangman
//
// functions associated with the hangman game:
//
//----------------------------------------------------------------------------------//

// lcd.noblink() and lcd.blink() to blink turn on blinking cursor for hangman
// hangman is where the implementation for the hangman game logic is going to be put.
// no arguments are passed to the function because everything that the function needs will
// declared within the function.
void hangman() {
  // While loop is for testing purposes only to ensure menu functionality.
  while (true) {
    writeHangmanMenu(1, 7);
  }
}

//----------------------------------------------------------------------------------//
//
//                                     Tic Tac Toe
//
// functions associated with the tic tac toe:
//
//   - playGamePvC()  | Allows the user to play the game against a computer.
//                      The user enters a number while the computer generates
//                      a random number. If both numbers are even, the player
//                      goes first. If they are different, the computer goes
//                      first.
//   - playGamePvP()  | Allows two users to play against eachother.
//                      Player 1 enters a number while the computer generates
//                      a random number. If both numbers are even, Player 1
//                      goes first. If they are different, Player 2 goes
//                      first.
//   - compyTurnX()   | Allows the computer to play as X. It generates a random
//                      number and checks the availability on the board. If it's
//                      available, it marks the space with 'X'. If not, it
//                      searches for another space that is until it finds one.
//   - compyTurnO()   | Allows the computer to play as O. It generates a random
//                      number and checks the availability on the board. If it's
//                      available, it marks the space with 'O'. If not, it
//                      searches for another space that is until it finds one.
//   - playerTurnX()  | Allows the player to play as X. It prompts the player
//                      for a number and checks the validity of the number.
//                      If it passes, it will check if the board space is
//                      available. If it is, it marks it with 'X'. If either
//                      case is not true, it does nothing until the player
//                      enters a valid/available number/space.
//   - playerTurnO()  | Allows the player to play as O. It prompts the player
//                      for a number and checks the validity of the number.
//                      If it passes, it will check if the board space is
//                      available. If it is, it marks it with 'O'. If either
//                      case is not true, it does nothing until the player
//                      enters a valid/available number/space.
//   - checkBoard()   | Checks the board to see if anyone has won the game.
//                      It loops through the horizontal and vertical spaces,
//                      then searches the diagonals. If none of those win,
//                      it searches the whole board to see if it's a Cat's game.
//   - printBoard()   | Prints the board to the screen.
//----------------------------------------------------------------------------------//

// ticTacToe is where the implementation for the Tic Tac Toe game logic is going to be put.
// no arguments are passed to the function because everything that the function needs will
// declared within the function.
void ticTacToe() {
  // Variables specific to tic-tac-toe
  bool keepPlaying = true;
  int gameType = 1;
  while (keepPlaying) {
    // Code specific to show menu
    gameType = getTTTGameType();
    lcd.clear();
    switch (gameType) {
      case 1:
        break;
      case 2:
        playGamePvC(getTTTPlayerOne());
        break;
    }
  }
}

/* Function to choose who goes first in PVC and play the
   game accordingly. Generates a random number when
   Player enters a number. If both are even or odd,
   Player is X and goes first. If they are different,
   then the Computer (who is O) goes first.
*/
void playGamePvC(int numP) {
  int numC = random(10), check = 0;
  char board[9] = {'_', '_', '_', '_', '_', '_', '_', '_', '_'};

  if ((((numC % 2) == 0) && ((numP % 2) == 0)) ||
      (((numC % 2) != 0) && ((numP % 2) != 0))) {
    while (check == 0) {
      // Player's turn, print the board, then check the board.
      playerTurnX(board);
      delay(500);
      printBoard(board);
      delay(500);
      check = checkBoard(board);

      // Computer's turn, print the board, then check the board.
      compyTurnO(board);
      delay(500);
      printBoard(board);
      delay(500);
      check = checkBoard(board);
    }

    // Check who won and display it.
    if (check == 1) {
      Serial.println("**********"), Serial.println("Player 1(X) Wins!"), Serial.println("**********");
    } else if (check == 2) {
      Serial.println("**********"), Serial.println("Player 2(O) Wins!"), Serial.println("**********");
    } else if (check == 3) {
      Serial.println("**********"), Serial.println("Cat Wins!"), Serial.println("**********");
    }
    delay(3000);
  } else if (((numC % 2) != 0) || ((numP % 2) != 0)) {
    while (check == 0) {
      // Player's turn, print the board, then check the board.
      compyTurnX(board);
      delay(500);
      printBoard(board);
      delay(500);
      check = checkBoard(board);

      // Computer's turn, print the board, then check the board.
      playerTurnO(board);
      delay(500);
      printBoard(board);
      delay(500);
      check = checkBoard(board);
    }

    // Check who won and display it.
    if (check == 1) {
      Serial.println("**********"), Serial.println("Player 2(O) Wins!"), Serial.println("**********");
    } else if (check == 2) {
      Serial.println("**********"), Serial.println("Player 1(X) Wins!"), Serial.println("**********");
    } else if (check == 3) {
      Serial.println("**********"), Serial.println("Cat Wins!"), Serial.println("**********");
    }
    delay(3000);
  }
}

/* Function to choose who goes first in PVP and play the
   game accordingly. Generates a random number when
   Player 1 enters a number. If both are even or odd,
   Player 1 is X and goes first. If they are different,
   then Player 2 (who is O) goes first.
*/
void playGamePvP(int numP) {
  int numC = random(10), check = 0;
  char board[9] = {'_', '_', '_', '_', '_', '_', '_', '_', '_'};

  if ((((numC % 2) == 0) && ((numP % 2) == 0)) ||
      (((numC % 2) != 0) && ((numP % 2) != 0))) {
    while (check == 0) {
      // Player 1's turn, print the board, then check the board.
      playerTurnX(board);
      delay(500);
      printBoard(board);
      delay(500);
      check = checkBoard(board);

      // Player 2's turn, print the board, then check the board.
      playerTurnO(board);
      delay(500);
      printBoard(board);
      delay(500);
      check = checkBoard(board);
    }

    // Check who won and display it.
    if (check == 1) {
      Serial.println("**********"), Serial.println("Player 1(X) Wins!"), Serial.println("**********");
    } else if (check == 2) {
      Serial.println("**********"), Serial.println("Player 2(O) Wins!"), Serial.println("**********");
    } else if (check == 3) {
      Serial.println("**********"), Serial.println("Cat Wins!"), Serial.println("**********");
    }
    delay(3000);
  } else if (((numC % 2) != 0) || ((numP % 2) != 0)) {
    while (check == 0) {
      // Player 1's turn, print the board, then check the board.
      playerTurnO(board);
      delay(500);
      printBoard(board);
      delay(500);
      check = checkBoard(board);

      // Player 2's turn, print the board, then check the board.
      playerTurnX(board);
      delay(500);
      printBoard(board);
      delay(500);
      check = checkBoard(board);
    }

    // Check who won and display it.
    if (check == 1) {
      Serial.println("**********"), Serial.println("Player 2(O) Wins!"), Serial.println("**********");
    } else if (check == 2) {
      Serial.println("**********"), Serial.println("Player 1(X) Wins!"), Serial.println("**********");
    } else if (check == 3) {
      Serial.println("**********"), Serial.println("Cat Wins!"), Serial.println("**********");
    }
    delay(3000);
  }
}

/* Function to allow the computer to take a turn.
   It decides a random number. It then checks if it
   is available and if it is mark an 'X', if it is
   not then it decides another number and checks it.
*/
void compyTurnX (char brd[9]) {
  int num = 0, ck = 0;

  Serial.print("Compy Choice: ");
  while (ck == 0) {
    // Generate random number and print it.
    num = random(9);
    Serial.print(num + 1);
    Serial.print(" ");

    // If the number is within 1 to 9 and...
    if ((num >= 0) && (num <= 8)) {
      // If the board position is available, mark it.
      if ((brd[num] != 'O') && (brd[num] != 'X')) {
        brd[num] = 'X';
        ck = 1;
      } else {
        // Else make it pick another number.
        ck = 0;
      }
    } else {
      num = random(8);
      Serial.print(num + 1);
    }
  }
  Serial.println(" ");
}

/* Function to allow the computer to take a turn.
   It decides a random number. It then checks if it
   is available and if it is mark an 'O', if it is
   not then it decides another number and checks it.
*/
void compyTurnO (char brd[9]) {
  int num = 0, ck = 0;

  Serial.print("Compy Choice: ");
  while (ck == 0) {
    // Generate random number and print it.
    num = random(9);
    Serial.print(num + 1);
    Serial.print(" ");

    // If the number is within 1 to 9 and...
    if ((num >= 0) && (num <= 8)) {
      // If the board position is available, mark it.
      if ((brd[num] != 'O') && (brd[num] != 'X')) {
        brd[num] = 'O';
        ck = 1;
      } else {
        // Else make it pick another number.
        ck = 0;
      }
    } else {
      num = random(8);
      Serial.print(num + 1);
    }
  }
  Serial.println(" ");
}

/* Function to allow the player to take a turn.
    It prompts the player for a number from 1
    to 9 and checks if it's in the bounds and
    available. If it is, it marks an 'X' in the
    space chosen, if it is not it prompts the
    player to enter another number and checks it.
*/
void playerTurnX (char brd[9]) {
  char choice = 0;
  int check = 0, c;

  // Prompts the user for a number from 1 or 9.
  Serial.print("Turn (1-9):");
  while (Serial.available() == 0) {}
  choice = Serial.read();
  c = (int)choice - 49;
  Serial.println(choice);

  // Check if the choice is valid
  while (check == 0) {
    // If it is, mark the space as 'X' and move on.
    if ((c >= 0) && (c < 9)) {
      if ((brd[c] != 'O') && (brd[c] != 'X')) {
        brd[c] = 'X';
        check = 1;
      } else {
        // If it is not a valid number, have them enter another number.
        while (Serial.available() == 0) {}
        choice = Serial.read();
        c = (int)choice - 49;
        check = 0;
      }
    } else {
      // If it is not a valid number, have them enter another number.
      while (Serial.available() == 0) {}
      choice = Serial.read();
      c = (int)choice - 49;
      check = 0;
    }
  }
}

/* Function to allow the player to take a turn.
    It prompts the player for a number from 1
    to 9 and checks if it's in the bounds and
    available. If it is, it marks an 'O' in the
    space chosen, if it is not it prompts the
    player to enter another number and checks it.
*/
void playerTurnO (char brd[9]) {
  char choice = 0;
  int check = 0, c;

  // Prompts the user for a number from 1 or 9.
  Serial.print("Turn (1-9):");
  while (Serial.available() == 0) {}
  choice = Serial.read();
  c = (int)choice - 49;
  Serial.println(choice);

  // Check if the choice is valid
  while (check == 0) {
    // If it is, mark the space as 'X' and move on.
    if ((c >= 0) && (c < 9)) {
      if ((brd[c] != 'O') && (brd[c] != 'X')) {
        brd[c] = 'O';
        check = 1;
      } else {
        // If it is not a valid number, have them enter another number.
        while (Serial.available() == 0) {}
        choice = Serial.read();
        c = (int)choice - 49;
        check = 0;
      }
    } else {
      // If it is not a valid number, have them enter another number.
      while (Serial.available() == 0) {}
      choice = Serial.read();
      c = (int)choice - 49;
      check = 0;
    }
  }
}

/* Function to check the board to see if anyone
    has won the game. If they have it sends a
    corresponding number for the winner. If
    no-one has, it sends the respective number.
*/
int checkBoard (char brd[9]) {
  int ck = 0, k, count = 0;

  // Ckeck horizontals for matches.
  for (int i = 0; i < 9; i += 3) {
    if ((brd[i] == 'X') && (brd[i + 1] == 'X') && (brd[i + 2] == 'X'))
      ck = 1;
    if ((brd[i] == 'O') && (brd[i + 1] == 'O') && (brd[i + 2] == 'O'))
      ck = 2;
  }

  // Check verticals for matches.
  for (int i = 0; i < 3; i++) {
    if ((brd[i] == 'X') && (brd[i + 3] == 'X') && (brd[i + 6] == 'X'))
      ck = 1;
    if ((brd[i] == 'O') && (brd[i + 3] == 'O') && (brd[i + 6] == 'O'))
      ck = 2;
  }

  // Check diagonals for matches.
  if ((brd[0] == 'X') && (brd[4] == 'X') && (brd[8] == 'X'))
    ck = 1;
  if ((brd[0] == 'O') && (brd[4] == 'O') && (brd[8] == 'O'))
    ck = 2;
  if ((brd[2] == 'X') && (brd[4] == 'X') && (brd[6] == 'X'))
    ck = 1;
  if ((brd[2] == 'O') && (brd[4] == 'O') && (brd[6] == 'O'))
    ck = 2;

  // Check for Cat's game.
  for (int i = 0; i < 9; i++) {
    if (brd[i] == 'X') {
      count++;
    } else if (brd[i] == 'O') {
      count++;
    }
  }
  if (count == 9) {
    ck = 3;
  }

  return ck;
}

/* Function to print the board to the screen.
*/
void printBoard (char brd[9]) {
  int rowOfBoard = 1;
  int column = 0;
  for (int i = 0; i < 9; i++, column++) {
    if (column == 2) {
      column = 0;
      ++rowOfBoard;
      lcd.setCursor(6, rowOfBoard);
      lcd.print("| ");
      lcd.setCursor(8, rowOfBoard);
      lcd.print(brd[i]);
      lcd.setCursor(0, rowOfBoard);
    }
    Serial.print(brd[i]);
    Serial.print(" ");
  }
  Serial.print("\n");
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
  int gameDifficulty = 0;

  int lives = 3;
  int stage = 1;

  int prevLine = -1; // -1 is an unset value
  int matchingGameLineForArrow = 0;
  while (gameDifficulty == 0) {
    matchingGameLineForArrow = getMGDifficulty(matchingGameLineForArrow, &gameDifficulty);
    writeMatchingGameMenu(matchingGameLineForArrow, prevLine);
    prevLine = matchingGameLineForArrow;
  }
  int *pattern = new int[(2 * gameDifficulty + 3)];
  while (keepPlaying) {
    keepPlaying = playMatchingGame(&lives, gameDifficulty, &stage,  pattern);
    if (!keepPlaying) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   Game Over");
      lcd.setCursor(0, 2);
      lcd.print("Stages Cleared:    ");
      lcd.setCursor(19, 2);
      lcd.print(stage - 1);
      lcd.setCursor(0, 3);
      lcd.print("Remaining Lives:   ");
      lcd.setCursor(19, 3);
      lcd.print(lives);
      delay(2000);  
    }
    stage++;

    // Prints a winning message to the player if they successfully beat all 5 stages.
    if (stage > 5) {
      keepPlaying = false;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   Congratulations");
      lcd.setCursor(0, 2);
      lcd.print("Stages Cleared:    ");
      lcd.setCursor(19, 2);
      lcd.print(stage - 1);
      lcd.setCursor(0, 3);
      lcd.print("Remaining Lives:   ");
      lcd.setCursor(19, 3);
      lcd.print(lives);
      delay(2000);
    }
  }
  delete [] pattern;
}

// promptPlayer will print out to the LCD the number of lives, the difficulty
// and the stage number. This function also include a prompt to the player to
// ask if they are ready.
// lcd is a 20 x 4 screen.
// Returns whether or not the player is ready to play.
void promptPlayer(int lives, int difficulty, int stage) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Difficulty: ");
  switch (difficulty) {
    case 1:
      lcd.setCursor(12, 0);
      lcd.print("Easy");
      break;
    case 2:
      lcd.setCursor(12, 0);
      lcd.print("Int.");
      break;
    case 3:
      lcd.setCursor(12, 0);
      lcd.print("Hard");
      break;
  }
  lcd.setCursor(0, 1);
  lcd.print("Lives: ");
  lcd.setCursor(7, 1);
  lcd.print(lives);
  lcd.setCursor(0, 2);
  lcd.print("Stage:  /5");
  lcd.setCursor(7, 2);
  lcd.print(stage);
  lcd.setCursor(0, 3);
  delay(8000);
}

// playMatchingGame contains the logic for calling the functions that control the smaller
// parts of the game. It controls prompting the player, setting the pattern, playing the
// pattern for the player, and determining whether or not the player is
// returns whether or not the player has any lives remaining.
bool playMatchingGame(int *lives, int difficulty, int *stage, int *pattern) {
  fillPattern(pattern, difficulty);

  Serial.print("[-");
  for (int i = 0; i < (2 * difficulty + 3); ++i) {
    Serial.print(pattern[i]);
    Serial.print("-");
  }
  Serial.println("]");
  while (*lives > 0) {
    promptPlayer(*lives, difficulty, *stage);
    playLightPattern(pattern, difficulty);
    if (verifyMatch(pattern, difficulty)) {
      return true;
    }
    --*lives;
  }
  return false;
}

// playLightPattern
void playLightPattern(int *pattern, int difficulty) {
  for (int i = 0; i < (2 * difficulty + 3); ++i) {
    digitalWrite(LED_ARRAY[pattern[i]], HIGH);
    delay(200);
    digitalWrite(LED_ARRAY[pattern[i]], LOW);
    delay(200);
  }
}

// verifyMatch is the function that validates the
bool verifyMatch(int *pattern, int difficulty) {
  bool found = false;
  switch (difficulty) {
    case 1:
      for (int i = 0; i < 5; ++i) {
        int input = getButton();
        if (input == -1) {
          --i;
          continue;
        }
        if (pattern[i] != input) {
          found = true;
        }
      }
      break;
    case 2:
      for (int i = 0; i < 7; ++i) {
        int input = getButton();
        if (input == -1) {
          --i;
          continue;
        }
        if (pattern[i] != input) {
          found = true;
        }
      }
      break;
    case 3:
      for (int i = 0; i < 9; ++i) {
        int input = getButton();
        if (input == -1) {
          --i;
          continue;
        }
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
  for (int i = 0; i < (2 * difficulty + 3); ++i) {
    int randNum = random(0, 5);
    Serial.println(randNum);
    pattern[i] = randNum;
  }
}

// getButton
int getButton() {
  bool leftPushed, upPushed, downPushed, rightPushed, enterPushed;
  leftPushed = digitalRead(LEFT_BUTTON);
  upPushed = digitalRead(UP_BUTTON);
  downPushed = digitalRead(DOWN_BUTTON);
  rightPushed = digitalRead(RIGHT_BUTTON);
  enterPushed = digitalRead(ENTER_BUTTON);
  if (!leftPushed) {
    digitalWrite(LEFT_LED, HIGH);
    delay(250);
    digitalWrite(LEFT_LED, LOW);
    return 0;
  }
  if (!upPushed) {
    digitalWrite(UP_LED, HIGH);
    delay(250);
    digitalWrite(UP_LED, LOW);
    return 1;
  }
  if (!downPushed) {
    digitalWrite(DOWN_LED, HIGH);
    delay(250);
    digitalWrite(DOWN_LED, LOW);
    return 2;
  }
  if (!rightPushed) {
    digitalWrite(RIGHT_LED, HIGH);
    delay(250);
    digitalWrite(RIGHT_LED, LOW);
    return 3;
  }
  if (!enterPushed) {
    digitalWrite(ENTER_LED, HIGH);
    delay(250);
    digitalWrite(ENTER_LED, LOW);
    return 4;
  }
  return -1; // -1 means no input received from user
}

