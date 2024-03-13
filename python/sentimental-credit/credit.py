def main():
    while True:
        Num = input("Number: ")
        if len(Num) >= 13 and len(Num) <= 16:
            try:
                carNumber=int(Num)
                break
            except ValueError:
                break
        else:
            print('INVALID')
            break
    if luhnAlgorithm(Num):
        checkCards(Num)
    else:
        print('INVALID')

def checkCards(Num):
    m = len(str(Num))
    n = int(str(Num)[:2])
    if n == 37 and m == 15:
        print("AMEX")
    elif n == 30 and m == 14:
        print("Diners Club")
    elif n == 60 and m == 16:
        print("Discover")
    elif n == 35 and m == 16:
        print("JCB")
    elif (n == 22 or n == 51 or n == 52) and m == 16:
        print("MASTERCARD")
    elif (n == 22 or n == 55 or n == 51) and m == 16:
        print("MASTERCARD")
    elif (n == 41 or n == 40 or n == 42 or n == 49) and (m == 16 or m == 13):
        print("VISA")
    else:
        print("INVALID")

def luhnAlgorithm(Num):
    second_to_last=[]
    others=[]
    for i, digit_char in enumerate(Num):
        digit = int(digit_char)
        #check if the distance from i to end of string is odd or even
        #if it's odd -> mean it's not the second to last digit
        if(len(Num)-i+1)%2==0:
            others.append(digit)
        else:
            second = digit*2
            if second>= 10:
                second_to_last.extend([int(digits) for digits in str(second)])
            else:
                second_to_last.append(second)
    if (sum(second_to_last) + sum(others)) % 10 == 0:
        return True
    else:
        return False
main()
