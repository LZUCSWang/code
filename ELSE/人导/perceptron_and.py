# -*- coding: utf-8 -*-
"""
Created on Wed Jun 02 15:05:19 2021

@author: zg
"""

# and_perceptron_without_learning.py
import numpy as np


class Perceptron(object):
    """Implements a perceptron network"""

    def __init__(self, input_size):
        self.W = np.array([1, 1])
        self.b = -2

    def activation_fn(self, x):
        return 1 if x >= 0 else 0

    def predict(self, x):
        z = self.W.T.dot(x)
        a = self.activation_fn(z + self.b)
        return a


if __name__ == '__main__':
    X = np.array([
        [0, 0],
        [0, 1],
        [1, 0],
        [1, 1]
    ])

    perceptron = Perceptron(input_size=2)
    print(perceptron.W, perceptron.b)
    for x in X:
        pre = perceptron.predict(x)
        print(x[0], 'and', x[1], '=',  pre)
