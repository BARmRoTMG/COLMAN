import random

isRunning = True

while isRunning:
    user_choice = input("Enter your choice (rock, paper, scissors): ").lower()
    choices = ["rock", "paper", "scissors"]
    computer_choice = random.choice(choices)

    if user_choice not in choices:
        print("Invalid choice. Please choose rock, paper, or scissors.")
    else:
        if user_choice == computer_choice:
            print(f"Both chose {user_choice}. It's a tie!")
        elif (user_choice == "rock" and computer_choice == "scissors") or \
            (user_choice == "paper" and computer_choice == "rock") or \
            (user_choice == "scissors" and computer_choice == "paper"):
            print(f"You chose {user_choice}. Computer chose {computer_choice}. You win!")
        else:
            print(f"You chose {user_choice}. Computer chose {computer_choice}. You lose!")
    play_again = input("Do you want to play again? (yes/no): ").lower()
    if play_again != "yes":
        isRunning = False
        print("Thanks for playing! Goodbye!")