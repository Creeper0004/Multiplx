/*
    Multiplx - A multiplication game
    Copyright (C) 2022 Creeper0004

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <algorithm>

int min, max, gamemode, questions, lives;
int total_correct_answers, total_questions_answered, classic_correct_answers, classic_questions_answered;
int score, survival_high_score; //__ mode variables

bool play_again;

void showStart();
void promptSettings();
void showSelectedGamemode();
void genQuestion();
void showRoundEnd();
void showScore();
//void isPlayAgain();

int main() {
  showStart();
  std::srand(time(0)); //Seed the psudo-random number generator

  do {
    lives = 0, score = 0, questions = 0, gamemode = 0;
    promptSettings();
    showSelectedGamemode();

    while ((questions > 0) || (lives > 0)) {
      genQuestion();
    }

    showRoundEnd();
  } while (play_again);

  return 0;
}

void showStart() {
  std::cout << "\n"
            << "\t    __  __       _ _   _       _       " << std::endl
            << "\t   |  \\/  |     | | | (_)     | |      " << std::endl
            << "\t   | \\  / |_   _| | |_ _ _ __ | |_  __ " << std::endl
            << "\t   | |\\/| | | | | | __| | '_ \\| \\ \\/ / " << std::endl
            << "\t   | |  | | |_| | | |_| | |_) | |>  <  " << std::endl
            << "\t   |_|  |_|\\__,_|_|\\__|_| .__/|_/_/\\_\\ " << std::endl
            << "\t                        | |            " << std::endl
            << "\t                        |_|            " << std::endl
            << "\t     A multiplication game & trainer   \n"
            << "\t             by Creeper0004            \n"
            << "\t  Licensed under GNU GPL v3.0 or later \n\n";
}

void parceGamemode() {
  std::string ans;
  std::cin >> ans;

  if ((ans == "1") || (ans == "classic") || (ans == "practice")) {
    gamemode = 1;

    std::cout << "\t  Rounds to play: ";
    std::cin >> questions;
  } else if ((ans == "2") || (ans == "arcade") || (ans == "game")) {
    gamemode = 2;
    lives = 3;
  } else {
    std::cout << "\t  Unknown Input\n\t  ";
    parceGamemode();
  }
}

void promptSettings() {
  std::cout << "\t  =====================================\n"
            << "\t  ####          SETTINGS           ####\n"
            << "\t  =====================================\n";
  std::cout << "\t  Min num: ";
  std::cin >> min;
  std::cout << "\t  Max num: ";
  std::cin >> max;

  std::cout << "\t  => 1. Classic  2. Survival\n";
  std::cout << "\t  Gamemode: ";

  parceGamemode();

}

void showSelectedGamemode() {
  std::string gamemode_name;
  switch (gamemode) {
  case 1:
    gamemode_name =     "          CLASSIC          ";
    break;
  case 2:
    gamemode_name =     "          SURVIVAL         ";
  }

  std::cout << "\n"
            << "\t  =====================================\n"
            << "\t  #### "  <<  gamemode_name  <<  " ####\n"
            << "\t  =====================================\n\n";
}

void genQuestion() {
  int n1 = std::rand() % (max + 1 - min) + min;
  int n2 = std::rand() % (max + 1 - min) + min;
  int ans;

  std::cout << "\t  How much is " << n1 << " x " << n2 << "?\n\t  ";
  std::cin >> ans;

  if (ans == n1 * n2) {
    std::cout << "\t  Correct\n\n";
    switch (gamemode) {
    case 1:
        classic_correct_answers++;
        break;
    case 2:
      score += 100 + (n1 * n2) / 2;
      break;
    }
    total_correct_answers++;
  } else {
    std::cout << "\t  Incorrect. The answer is " << n1 * n2 << ".\n\n";
    if (gamemode == 2) {
      lives--;
    }
  }

  switch (gamemode) {
  case 1:
    classic_questions_answered++;
    break;
  }

  questions--;
  total_questions_answered++;
}

void showScore() {
  switch (gamemode) {
  case 1:
    std::cout << "\t  Gamemode accuracy: " << classic_correct_answers << "/" << classic_questions_answered << " (" << (classic_correct_answers * 100 / classic_questions_answered) << "%)\n";
    std::cout << "\t  Lifetime accuracy: " << total_correct_answers << "/" << total_questions_answered << " (" << (total_correct_answers * 100 / total_questions_answered) << "%)\n";
    break;
  case 2:
    std::cout << "\t  High score: " << survival_high_score << "\n"
              << "\t  Score: " << score << "\n";
    if (survival_high_score < score) {
      survival_high_score = score;
    }
    break;
  //default:
  }
}

void parseYesNo() {
  std::string ans;
  std::cin >> ans;
  std::cout << std::endl;
  std::transform(ans.begin(), ans.end(), ans.begin(), ::tolower);

  if ((ans == "y") || (ans == "yes")) {
    play_again = true;
  }else if ((ans == "n") || (ans == "no") || (ans == "q") || (ans == "quit")) {
    play_again = false;
  }else {
    std::cout << "\t  Unknown Input: reply with \"y\" or \"n\"\n";
    parseYesNo();
  }
}

void showRoundEnd(){
  std::cout << "\t  =====================================\n"
            << "\t  ####          Game Over          ####\n"
            << "\t  =====================================\n";
  showScore();
  std::cout << "\t  Do you want to play again? [y/n]   \n\t  ";
  parseYesNo();
}
