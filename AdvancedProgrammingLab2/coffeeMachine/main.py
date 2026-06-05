from coffee_machine import CoffeeMachine
from coffee_machine_cons import MENU
from coin_processor import CoinProcessor

def main():
    machine = CoffeeMachine()
    processor = CoinProcessor()

    while machine.is_on:
        choice = input("What would you like? (espresso/latte/cappuccino): ").lower()

        if choice == "off":
            machine.is_on = False
        elif choice == "report":
            machine.print_report()
        elif choice in MENU:
            if machine.check_resources(choice):
                if machine.check_transaction(choice, processor):
                    machine.make_coffee(choice)
        else:
            print("Invalid choice. Please try again.")


if __name__ == "__main__":    main()