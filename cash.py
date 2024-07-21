# Variables
quarters = 25
dimes = 10
nickels = 5
pennies = 1

# Main function
def main():
    count = 0
    while True:
        try:
            amount = float(input("Cash: "))
            if amount > 0:
                break
        except:
            print("Enter amount in float cents")
    
    amount = round(amount * 100)
        
    # Calculate quarters
    while amount >= quarters:
        amount -= quarters
        count += 1
    # Calculate pennies
    while amount >= dimes:
        amount -= dimes
        count += 1
    # Calculate nickels
    while amount >= nickels:
        amount -= nickels
        count += 1
    # Calculate pennies
    while amount >= pennies:
        amount -= pennies
        count += 1
    
    print(f"{count}")
    

if __name__=="__main__":
    main()
