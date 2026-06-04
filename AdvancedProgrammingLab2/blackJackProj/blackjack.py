import random
import blackjack_art
import time

"""
Game rules:
- The goal is to get as close to 21 as possible without going over.
- J, Q, K are worth 10 points, and A can be worth 1 or 11 points.
- The user starts with one card, and then the dealer gets one card.
- Then the user gets the second card
- The user can choose to get another card (hit) or stop (stand), until they either lose or decide to stand.
- Then the dealer will draw cards until they have 17 or more.
- If the dealer goes over 21, the user wins.
- if the dealer stands, then the winner is the one with the highest score that is 21 or less.
"""

# Calculate the value of a hand
def hand_value(hand):
    total = sum(hand)
    aces = hand.count(11)
    while total > 21 and aces > 0:
        total -= 10
        aces -= 1
    return total

# Ace(11) handling
def format_hand(hand):
    aces_reduced = (sum(hand) - hand_value(hand)) // 10
    result = []
    for card in hand:
        if card == 11 and aces_reduced > 0:
            result.append("11(1)")
            aces_reduced -= 1
        else:
            result.append(str(card))
    return result


deck = [2,3,4,5,6,7,8,9,10,10,10,10,11] * 4
player_hand = []
dealer_hand = []

print(blackjack_art.logo)
print("Welcome to the Blackjack Game!")
print("shuffling the deck...")
random.shuffle(deck)
time.sleep(2)

# First round of cards
player_hand.append(deck.pop())
print(f"Your cards: {format_hand(player_hand)}")
dealer_hand.append(deck.pop())
print(f"Dealer's cards: {format_hand(dealer_hand)}")

# Second round of cards
print("Dealing the second card...")
time.sleep(1)
player_hand.append(deck.pop())

# The dealer's second card is hidden until the player's turn is over
dealer_hand.append(deck.pop())

print(f"Your cards: {format_hand(player_hand)}")
answer = 'y'
while hand_value(player_hand) < 21 and answer == 'y':
    answer = input("Would you like another card? (y/n): ")
    if answer == "n":
        break
    else :
        player_hand.append(deck.pop())
        
    print(f"Your cards: {format_hand(player_hand)}, score: {hand_value(player_hand)}")

# Dealer's turn
while hand_value(dealer_hand) < 17:
    dealer_hand.append(deck.pop())
print(f"Dealer's cards: {format_hand(dealer_hand)}, score: {hand_value(dealer_hand)}")

# Determine the winner
player_score = hand_value(player_hand)
dealer_score = hand_value(dealer_hand)

if player_score > 21:
    print("You went over 21. You lose!")
elif dealer_score > 21:
    print("Dealer went over 21. You win!")
elif player_score > dealer_score:
    print("Congratulations! You win!")
elif player_score == dealer_score:
    print("It's a tie!")
else:
    print("Dealer wins!")