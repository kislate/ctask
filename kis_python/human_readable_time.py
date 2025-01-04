'''
Write a function, which takes a non-negative integer (seconds) as input and returns the time in a human-readable format (HH:MM:SS)

HH = hours, padded to 2 digits, range: 00 - 99
MM = minutes, padded to 2 digits, range: 00 - 59
SS = seconds, padded to 2 digits, range: 00 - 59
The maximum time never exceeds 359999 (99:59:59)

You can find some examples in the test fixtures.
'''
def make_readable(seconds):
    return '{:02}:{:02}:{:02}'.format(seconds // 3600, seconds // 60 % 60, seconds % 60)

def make_readable(seconds):
    h = seconds // 3600
    m = seconds // 60 % 60
    s = seconds % 60
    return f"{h:02}:{m:02}:{s:02}"