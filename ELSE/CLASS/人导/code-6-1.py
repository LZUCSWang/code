#code-7-1.py
import numpy as np
 
class Perceptron(object):
    def __init__(self, input_size, lr=1, epochs=100):
        self.W = np.zeros(input_size+1)# add one for bias
        self.epochs = epochs
        self.lr = lr
    
    def activation(self, x):
        return 1 if x >= 0 else 0
 
    def predict(self, x):
        z = self.W.T.dot(x)
        a = self.activation(z)
        return a
 
    def fit(self, X, d):
        for _ in range(self.epochs):
            for i in range(d.shape[0]):
                x = np.insert(X[i], 0, 1)
                y = self.predict(x)
                err = d[i] - y
                self.W = self.W + self.lr * err * x
                print(self.W)

if __name__ == '__main__':
    X = np.array([[0, 0],[0, 1],[1, 0],[1, 1]])
    y = np.array([0, 0, 0, 1])  #and运算    
 
    perceptron = Perceptron(input_size=2)
    perceptron.fit(X, y)
    print(perceptron.W)
    for x in X:
        x = np.insert(x, 0, 1)
        y_pre = perceptron.predict(x)
        print('%s and %s = %s' %(x[1],x[2],y_pre))
