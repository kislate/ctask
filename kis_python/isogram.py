'''
An isogram is a word that has no repeating letters, consecutive or non-consecutive. Implement a function that determines whether a string that contains only letters is an isogram. Assume the empty string is an isogram. Ignore letter case.

Example: (Input --> Output)

"Dermatoglyphics" --> true
"aba" --> false
"moOse" --> false (ignore letter case)
'''
def is_isogram(string):
    #your code here
    return len(string) == len(set(string.lower()))

def is_isogram(string):
    string = string.lower()
    for letter in string:
        if string.count(letter) > 1: return False
    return True

def is_isogram(string): 
    return len(set(string.lower())) == len(string)

def is_isogram(string):
    #your code here
    char_dict = {}
    string = string.lower()
    
    for char in string:
        if char in char_dict:
            # increment count of this character
            char_dict[char] = char_dict[char] + 1
        else:
            char_dict[char] = 1
    
    # loop over the characters in dictionary, if any have
    # more than 1 found, this string is not an isogram, so break
    # the loop and function and return False.
    for key in char_dict:
        if char_dict[key] > 1:
            return False
            
    # If no duplicates were found in the loop directly above,
    # this must be an isogram, so return true!
    return True

