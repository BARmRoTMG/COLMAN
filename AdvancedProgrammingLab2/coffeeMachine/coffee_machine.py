from coffee_machine_cons import resources, MENU

class CoffeeMachine:
    def __init__(self):
        self.resources = resources.copy()
        self.profit = 0.0
        self.is_on = True
    
    def print_report(self):
        print(f"Water: {self.resources['water']}ml")
        print(f"Milk: {self.resources['milk']}ml")
        print(f"Coffee: {self.resources['coffee']}g")
        print(f"Money: ${self.profit:.2f}")

    def check_resources(self, drink):
        ingredients = MENU[drink]['ingredients']
        for ingredient, amount in ingredients.items():
            if self.resources[ingredient] < amount:
                print(f"Sorry, there is not enough {ingredient}.")
                return False
        return True
    
    def check_transaction(self, drink, inserted_money):
        print(f"The cost of {drink} is ${MENU[drink]['cost']:.2f}.")
        cost = MENU[drink]["cost"]
        inserted = inserted_money.process_coins()
        if inserted < cost:
            print("Sorry, that's not enough money. Money refunded.")
            return False
        change = round(inserted - cost, 2)
        if change > 0:
            print(f"Here is ${change} in change.")
        self.profit += cost
        return True
    
    def make_coffee(self, drink):
        ingredients = MENU[drink]["ingredients"]
        for ingredient, amount in ingredients.items():
            self.resources[ingredient] -= amount
        print(f"Here is your {drink}. Enjoy!")