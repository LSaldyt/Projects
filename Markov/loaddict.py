from test_book  import test_book
from random     import uniform
import math
import pickle

class Node(object):
    def __init__(self, word):
        self.words = {}
        self.words[word] = 1

    def add(self, word):
        if word in self.words:
            self.words[word] += 1
        else:
            self.words[word] = 1

def sigmoid(val):
    return val / math.sqrt(1.0 + (val * val))

def inverse(val):
    return 1 / val


def weigh(count1, count2):
    return sigmoid(sigmoid(inverse(count1)) + count2)

def reloadDict():

    exclude = "\"\'?()!,;:."
    no_punctuation = ''.join(char for char in test_book.lower() if char not in exclude)

    words = no_punctuation.split()
    word_dict = {}
    occurance_set = {}

    for i in range(len(words) - 1):

        if words[i] in occurance_set:
            occurance_set[words[i]] += 1
        else:
            occurance_set[words[i]] = 1

        if words[i] in word_dict:
            word_dict[words[i]].add(words[i+1])
        else:
            word_dict[words[i]] = Node(words[i+1])

    for item in word_dict:
        for word in word_dict[item].words:
            if word in occurance_set:
                word_dict[item].words[word] = weigh(word_dict[item].words[word], occurance_set[word])
            else:
                word_dict[item].words[word] = weigh(word_dict[item].words[word], 0)

    pickle.dump(word_dict, open("markovDict.p", "wb"))
