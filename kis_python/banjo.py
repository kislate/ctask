'''
Create a function which answers the question "Are you playing banjo?".
If your name starts with the letter "R" or lower case "r", you are playing banjo!

The function takes a name as its only argument, and returns one of the following strings:

name + " plays banjo" 
name + " does not play banjo"
Names given are always valid strings.
'''
def are_you_playing_banjo(name):
    # Implement me!
    return name + " plats banjo" if name[0].Lower() == 'r' else name + " dose not play banjo"
# 错误原因：拼写错误，plats -> plays, dose -> does，Lower -> lower
# 错误示例：are_you_playing_banjo("Rikke") --> "Rikke plats banjo"


def areYouPlayingBanjo(name):
    # Implement me!
    return name + " plays banjo" if name[0].lower() == 'r' else name + " does not play banjo"