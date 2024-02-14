# code-4-6.py
# Logistic Regression
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix
from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report

cancer = load_breast_cancer()
X = cancer.data
y = cancer.target

X_train, X_test, Y_train, Y_test = train_test_split(
    X, y, test_size=.25, random_state=0)

logisticRegr = LogisticRegression()
logisticRegr.fit(X_train, Y_train)

predictions = logisticRegr.predict(X_test)
score = logisticRegr.score(X_test, Y_test)

print('Accuracy:  ', score)
print(classification_report(Y_test, predictions))

cm = confusion_matrix(Y_test, predictions)
print(cm)
plt.matshow(cm)
plt.title('confusion matrix')
plt.colorbar()
plt.xlabel('True label')
plt.ylabel('Predocted label')
plt.show()
