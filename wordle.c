#include "wordle.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "cs136-trace.h"                             

// see wordle.h
bool evaluate_guess(const char *secret, const char *guess, char *result) {
  assert(secret);
  assert(guess);
  assert(result);
  int len1 = strlen(secret);
  int len2 = strlen(guess);
  assert(len1 == len2);
  bool found = false;
  int i = 0;
  for (i = 0; guess[i] != '\0'; i++) {
    found = false;
    for (int j = 0; secret[j] != '\0'; j++) {

      if ((guess[i] == secret[j]) && (i == j)) {
        result[i] = (guess[i] - ' ');
        found = true;
        break;
      } if (guess[i] == secret[j]) {
        result[i] = guess[i];
        found = true;
      }
    }
    if (!found) {
      result[i] = '.';
    }
  }
  if (strcmp(secret, guess) == 0) {
    return true;
  } else {
    return false;
  }
}


// see wordle.h
int find_in_list(const char *guess, char *word_list[], int num_words) {
  assert(guess);
  assert(word_list);
  int low = 0;
  int high = 2309;
  
  while (low <= high) {
    int mid = (low + high) / 2;
    if (strcmp(word_list[mid], guess) == 0) {
      return mid;
    } else if (strcmp(word_list[mid], guess) < 0) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return -1;
}


// see wordle.h
void available_letters(char *guesses[], char *results[], int num_guesses,
                       char *alphabet) {
  assert(guesses);
  assert(results);
  assert(num_guesses >= 0);
  
  //filling array
  for (int i = 0; i < 26; ++i) {
    alphabet[i] = i + 'a';
  }

  for (int i = 0; i < num_guesses; ++i) {
    for (int j = 0; (guesses[i])[j] != '\0'; j++) {
      assert(guesses[i][j]);
      assert(results[i][j]);
      if (results[i][j] == '.') {
        alphabet[(guesses[i])[j] - 97] = '.';

      } else if (((results[i])[j] >= 'A' && (results[i])[j] <= 'Z') 
                 || ((results[i])[j] >= 'a' && (results[i])[j] <= 'z')) {
        alphabet[(guesses[i])[j] - 97] = (guesses[i])[j] - 32;
      }
    }
  }
}


// see wordle.h
bool valid_hard_guess(char *guesses[], char *results[], int num_guesses,
                      const char *next_guess) {
  assert(guesses);
  assert(results);
  assert(num_guesses >= 0);
  int nextlen = strlen(next_guess);
  assert(nextlen == strlen(*guesses));
  for (int i = 0; i < num_guesses; i++) {
    trace_printf(results[i]);
    for (int a = 0; a < nextlen; a++) {
      assert(results[i][a]);
      assert(guesses[i][a]);
      //trace_char(results[i][a]);
      if (results[i][a] >= 'A' && results[i][a] <= 'Z') {
        if (guesses[i][a] != next_guess[a]) {
          return false;
        }
      } else if (results[i][a] >= 'a' && results[i][a] <= 'z') {
        if (results[i][a] == next_guess[a]) {
          return false;
        }
        int counter = 0;
        for (int pos = 0; pos < nextlen; pos++) {
          if (pos == a) {
            continue;
          } else {
            if (next_guess[pos] == results[i][a]) {
              counter++;
            }
          }
        }
        if (!counter) {
          return false;
        }
      } else if ((results[i])[a] == '.') {
        char invalid = guesses[i][a];
        for (int z = 0; z < nextlen; z++) {
          if (next_guess[z] == invalid) {
            return false;
          }
        }
      }
    }
  }
  return true;
}


// see wordle.h
int find_solution(char *guesses[], char *results[], int num_guesses,
                  char *word_list[], int num_words,
                  char *solutions[], int max_solutions) {
  assert(num_guesses >= 0);
  assert(max_solutions >= 1);
  //int len = strlen(guesses[0]);
  int count = 0;
  for (int i = 0; i < num_words; i++) {
    //word_list[i] // "aback"
    if (valid_hard_guess(guesses, results, num_guesses, word_list[i]) && 
        count <= max_solutions) {
      solutions[count] = word_list[i];
      count++;
    }
    /*
    for (int a = 0; a < num_guesses; a++) {
      for (int x = 0; x < len; x++) { // .....
        assert(results[a][x]);
        assert(guesses[a][x]);
        assert(word_list[i][x]);
        if (results[a][x] >= 'A' && results[a][x] <= 'Z') {
          if (word_list[i][x] != results[a][x]) {
            break;
          }
        } else if (results[a][x] >= 'a' && results[a][x] <= 'z') {
          if (word_list[i][x] == results[a][x]) {
            break;
          }
          int counter = 0;
        for (int pos = 0; pos < nextlen; pos++) {
          if (pos == a) {
            continue;
          } else {
            if (next_guess[pos] == results[i][a]) {
              counter++;
            }
          }
        }
        if (!counter) {
          break;
        }
        } else if (results[a][x] == '.') {
          
        }
      }
    }*/
  }
   return count;
}
