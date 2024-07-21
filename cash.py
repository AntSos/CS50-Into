# Main function
def main():
    count = 0
    coins_values = [25, 10, 5, 1]
    while True:
        try:
            amount = float(input("Cash: "))
            if amount > 0:
                break
        except:
            print("Enter amount in float cents")

    amount = round(amount * 100)

    # Calculate for each value in the list of coins values
    for value in coins_values:

        while amount >= value:
            amount -= value
            count += 1

    print(f"{count}")


if __name__ == "__main__":
    main()