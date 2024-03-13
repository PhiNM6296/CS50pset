def main():
    while True:
        try:
            height = int(input("Enter the height of the pyramids (should be between 1-8): "))
            if height >= 1 and height <= 8 :
                break
        except ValueError:
            print("Enter an interger.")
    draw(height)
def draw_brick(height):
    for i in range(height):
        print('#' , end ='')
def draw_space(height):
    for i in range(height):
        print(' ', end ='')
def draw(height):
    for i in range(height):
        #left side:
        draw_space(height-i-1)
        draw_brick(i+1)
        draw_space(2)
        draw_brick(i+1)
        print()

main()

# it could be way better than this, using string concat bro
