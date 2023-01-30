# Common imports
import numpy as np
import pandas as pd

# machine learning packages
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
from sklearn.preprocessing import StandardScaler
import tensorflow as tf
import tensorflow.keras as keras
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import Dropout



df = pd.read_csv('./dataset_fft.csv', header=None)

class_list = df.iloc[:,-1]
y = []
for label in class_list:
  if (label[0:5] == "blues"):
    y.append(0)
  if (label[0:9] == "classical"):
    y.append(1)
  if (label[0:7] == "country"):
    y.append(2)
  if (label[0:5] == "disco"):
    y.append(3)
  if (label[0:6] == "hiphop"):
    y.append(4)
  if (label[0:4] == "jazz"):
    y.append(5)
  if (label[0:5] == "metal"):
    y.append(6)
  if (label[0:3] == "pop"):
    y.append(7)
  if (label[0:6] == "reggae"):
    y.append(8)
  if (label[0:4] == "rock"):
    y.append(9)
y = LabelEncoder().fit_transform(y)

fit = StandardScaler()
X = fit.fit_transform(np.array(df.iloc[:,:-1], dtype=float))
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.33)



def trainModel(model, epochs, optimizer):
  batch_size = 128
  model.compile(optimizer=optimizer,
                loss='sparse_categorical_crossentropy',
                metrics='accuracy')
  return model.fit(X_train, y_train, validation_data=(X_test, y_test), epochs=epochs,
                   batch_size=batch_size)

model = Sequential([
    Dense(512, activation='relu', input_shape=(X_train.shape[1],)),
    Dropout(0.4),
    Dense(256, activation='relu'),
    Dropout(0.4),
    Dense(128, activation='relu'),
    Dropout(0.3),
    Dense(64, activation='relu'),
    Dropout(0.2),
    Dense(10, activation='softmax'),
])

model_history = trainModel(model=model, epochs=600, optimizer='adam')

test_loss, test_acc = model.evaluate(X_test, y_test, batch_size=128)
print('Loss : ', test_loss)
print('\nAccuracy : ', test_acc*100)


converter = tf.lite.TFLiteConverter.from_keras_model(model)
tflite_model = converter.convert()
open("model.tflite", "wb").write(tflite_model)