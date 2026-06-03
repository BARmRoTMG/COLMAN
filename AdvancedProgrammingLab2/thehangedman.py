import random

# TODO
# 1. Randomly choose a word from the word_list.
# 2. Ask the user to guess a letter and assign the their answer to a variable.
# 3. Check if the letter the user guessed (guess) is one of the letters in the chosen_word.
# 4. Print progress.
# 5. Create a "placeholder" with the same number of blanks as the chosen_word.
# 6. Create a "display" that puts the guess letter in the right positions and _ in the rest.
# 7. Use a while loop to let the user guess again.
# 8. Change the for loop so that you keep the previous correct guessed letters in the display.

stages = [
    # 0 wrong guesses
    """
  +---+
  |   |
      |
      |
      |
      |
=========
""",
    # 1 wrong guess
    """
  +---+
  |   |
  O   |
      |
      |
      |
=========
""",
    # 2 wrong guesses
    """
  +---+
  |   |
  O   |
  |   |
      |
      |
=========
""",
    # 3 wrong guesses
    """
  +---+
  |   |
  O   |
 /|   |
      |
      |
=========
""",
    # 4 wrong guesses
    """
  +---+
  |   |
  O   |
 /|\\  |
      |
      |
=========
""",
    # 5 wrong guesses
    """
  +---+
  |   |
  O   |
 /|\\  |
 /    |
      |
=========
""",
    # 6 wrong guesses - DEAD
    """
  +---+
  |   |
  O   |
 /|\\  |
 / \\  |
      |
=========
""",
]

print("Welcome to the Hangman Game!")
word_list = ["wikepedia", "python", "programming", "hangman", "challenge"]
chosen_word = random.choice(word_list)
wrong_guesses = 0
correct_letters = []
placeholder = ["_"] * len(chosen_word)

while "_" in placeholder and wrong_guesses < 6:
    user_guess = input("Guess a letter: ").lower()

    if user_guess in chosen_word:
        correct_letters.append(user_guess)
    else:
        wrong_guesses += 1

    placeholder = []
    for letter in chosen_word:
        if letter in correct_letters:
            placeholder.append(letter)
        else:
            placeholder.append("_")

    print(" ".join(placeholder))
    print(stages[wrong_guesses])

if "_" not in placeholder:
    print("You win!")
else:
    print(f"You lose! The word was: {chosen_word}")
