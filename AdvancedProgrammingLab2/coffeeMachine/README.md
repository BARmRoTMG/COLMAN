# Coffee Machine Project Plan

## Overview

A command-line Python program that simulates a real coffee machine. It manages water, milk, and coffee resources, handles coin-based payments, and serves three types of drinks: espresso, latte and cappuccino. The system runs continuously until the user turns it off.

## Project Structure

```
coffee_machine/
├── README.md
├── coffee_machine_cons.py   # Menu recipes and starting resources
├── main.py                  # Main loop
├── coffee_machine.py        # Coffee Machine Logic
└── coin_processor.py        # Payment Logic
```

## Full Flow Diagram

```
START
  └─► Prompt user
        ├─ "off"        → EXIT
        ├─ "report"     → Print resources + money → re-prompt
        ├─ valid drink  → check_resources()
        │                    ├─ Not enough → Print message → re-prompt
        │                    └─ Enough     → check_transaction()
        │                                      ├─ Too little → Refund → re-prompt
        │                                      └─ Enough    → Give change (if any)
        │                                                     → make_coffee()
        │                                                     → Print success → re-prompt
        └─ invalid      → Print error → re-prompt
```

## Validate all user input

- Coin counts must be non-negative integers
- Drink choice must match a key in MENU, or be "off" / "report.
- Machine should continue serving until user turns it off

## Workflow

```bash
python main.py
```

## Example Execution

```
What would you like? (espresso/latte/cappuccino): latte
Please insert coins.
How many quarters? 10
How many dimes? 1
How many nickels? 0
How many pennies? 0
Here is $0.10 in change.
Here is your latte. Enjoy!

What would you like? (espresso/latte/cappuccino): report
Water: 100ml
Milk: 50ml
Coffee: 76g
Money: $2.5

What would you like? (espresso/latte/cappuccino): off
```