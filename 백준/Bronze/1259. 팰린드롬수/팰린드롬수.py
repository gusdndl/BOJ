def is_palindrome(number):
    number = str(number)  # Convert number to string for easier manipulation
    reversed_number = number[::-1]  # Reverse the string using slicing
    return number == reversed_number

while(True):
    number = int(input())
    if number == 0:
        break
    elif is_palindrome(number):
        print("yes")
    else:
        print("no")