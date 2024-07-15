# A simple program to draw a pyramid between 1-8 blocks reciving the height from the user
def main():
    height = 0

    while height <= 0 or height > 8:
        try:
            height = int(input("Enter height of the pyramid between 1-8: "))

        except:
            print("Enter an integer")

    draw(height)


def draw(height):

    for i in range(height):
        for j in range(height):
            if i + j < height - 1:
                print(" ", end="")
            else:
                print("#", end="")
        print("")


if __name__ == "__main__":
    main()