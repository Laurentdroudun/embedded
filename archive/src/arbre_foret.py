import numpy as np
import pandas as pd

from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.svm import LinearSVC


dataset = pd.read_csv('output.csv', header=None)

X = dataset.iloc[:, 0:-1]
Y = dataset.iloc[:, -1:]
Y = np.ravel(Y)
y = []
for i in Y:
    s = i.split(".")
    y.append(s[0])

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

print('Entrainement ...')
clf = DecisionTreeClassifier().fit(X_train, y_train)
clf_svm = Pipeline((
    ("scaler", StandardScaler()),
    ("linear_svc", LinearSVC(C=1, loss="hinge"))
    )).fit(X_train, y_train)

score = clf.score(X_test, y_test)
score_svm = clf_svm.score(X_test, y_test)
print('Accuracy : ', score)
print('Accuracy svm : ', score_svm)

