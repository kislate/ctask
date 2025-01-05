'''
"7777...8?!??!", exclaimed Bob, "I missed it again! Argh!" Every time there's an interesting number coming up, he notices and then promptly forgets. Who doesn't like catching those one-off interesting mileage numbers?

Let's make it so Bob never misses another interesting number. We've hacked into his car's computer, and we have a box hooked up that reads mileage numbers. We've got a box glued to his dash that lights up yellow or green depending on whether it receives a 1 or a 2 (respectively).

It's up to you, intrepid warrior, to glue the parts together. Write the function that parses the mileage number input, and returns a 2 if the number is "interesting" (see below), a 1 if an interesting number occurs within the next two miles, or a 0 if the number is not interesting.

Note: In Haskell, we use No, Almost and Yes instead of 0, 1 and 2.

"Interesting" Numbers
Interesting numbers are 3-or-more digit numbers that meet one or more of the following criteria:

Any digit followed by all zeros: 100, 90000
Every digit is the same number: 1111
The digits are sequential, incementing†: 1234
The digits are sequential, decrementing‡: 4321
The digits are a palindrome: 1221 or 73837
The digits match one of the values in the awesome_phrases array
† For incrementing sequences, 0 should come after 9, and not before 1, as in 7890.
‡ For decrementing sequences, 0 should come after 1, and not before 9, as in 3210.

So, you should expect these inputs and outputs:

# "boring" numbers
is_interesting(3, [1337, 256])    # 0
is_interesting(3236, [1337, 256]) # 0

# progress as we near an "interesting" number
is_interesting(11207, []) # 0
is_interesting(11208, []) # 0
is_interesting(11209, []) # 1
is_interesting(11210, []) # 1
is_interesting(11211, []) # 2

# nearing a provided "awesome phrase"
is_interesting(1335, [1337, 256]) # 1
is_interesting(1336, [1337, 256]) # 1
is_interesting(1337, [1337, 256]) # 2
Error Checking
A number is only interesting if it is greater than 99!
Input will always be an integer greater than 0, and less than 1,000,000,000.
The awesomePhrases array will always be provided, and will always be an array, but may be empty. (Not everyone thinks numbers spell funny words...)
You should only ever output 0, 1, or 2.
'''

# not perfect solution
def is_interesting(number, awesome_phrases):
    def is_palindrome(n):
        return str(n) == str(n)[::-1]
    
    def is_all_zeros(n):
        s = str(n)
        return s[1:] == '0' * (len(s) - 1)
    def is_sequential(n):
        inc = '1234567890'
        dec = '9876543210'
        return str(n) in inc or str(n) in dec
    if number < 100:
        return 0
    if number in awesome_phrases:
        return 2
    if is_palindrome(number) or is_all_zeros(number) or is_sequential(number):
        return 2
    if is_palindrome(number + 1) or is_all_zeros(number + 1) or is_sequential(number + 1):
        return 1
    if is_palindrome(number + 2) or is_all_zeros(number + 2) or is_sequential(number + 2):
        return 1
    if is_palindrome(number - 1) or is_all_zeros(number - 1) or is_sequential(number - 1):
        return 1
    if is_palindrome(number - 2) or is_all_zeros(number - 2) or is_sequential(number - 2):
        return 1
    return 0

# right solution
def is_interesting(number, awesome_phrases):
    def is_palindrome(n):
        s = str(n)
        return s == s[::-1]

    def is_all_zeros(n):
        s = str(n)
        return s[1:] == '0' * (len(s) - 1)

    def is_sequential(n):
        inc = '1234567890'
        dec = '9876543210'
        s = str(n)
        return s in inc or s in dec

    def is_interesting_number(n):
        if n < 100:
            return False
        if n in awesome_phrases:
            return True
        if is_palindrome(n):
            return True
        if is_all_zeros(n):
            return True
        if is_sequential(n):
            return True
        return False

    if is_interesting_number(number):
        return 2
    if is_interesting_number(number + 1) or is_interesting_number(number + 2):
        return 1
    return 0

