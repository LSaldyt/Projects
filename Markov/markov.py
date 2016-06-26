from __future__   import print_function
from collections  import defaultdict, Counter
from loaddict     import reloadDict
from random       import randint, choice
import pickle
import os.path

if(not os.path.isfile("markovDict.p")):
    reloadDict()

markovDict = pickle.load( open( "markovDict.p", "rb" ) )

weigh_chance = 65

def getNextPhrase(word, markov_dict, depth=1):
    s = ""
    for i in range(depth):
        if word in markov_dict:
            if randint(0, 100) > weigh_chance:
                word = choice( markov_dict[word].words.keys() )
            else:
                word = min(markov_dict[word].words, key=markov_dict[word].words.get) # Word with the lowest weight
            s += (word + " ")
        else:
            word = choice(markov_dict.keys())                        # If we hit a dead end, start over
            s += ("! " + getNextPhrase(word, markov_dict, i)[0])  # End our last phrase with a period

    s += ". \n"
    return s, word


    # current_word = choice(wordDict.keys()) # Likely to choose a more popular word
for x in range(3):
    current_word = input("Choose a starting word:")
    phrase_depth = randint(5, 20) # Vary phrase length
    phrase = getNextPhrase(current_word, markovDict, phrase_depth)
    print(phrase[0], sep=' ', end=' ')
    current_word = phrase[1]
