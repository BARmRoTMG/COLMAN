class CoinProcessor:

    COIN_VALUES = {
        "quarter": 0.25,
        "dime": 0.10,
        "nickel": 0.05,
        "penny": 0.01
    }

    def process_coins(self):
        print("Please insert coins.")
        total = 0
        for coin, value in self.COIN_VALUES.items():
            while True:
                try:
                    count = int(input(f"How many {coin}s?: "))
                    if count < 0:
                        raise ValueError
                    break
                except ValueError:
                    print("Invalid input. Please enter a non-negative integer.")
            total += count * value
        return total