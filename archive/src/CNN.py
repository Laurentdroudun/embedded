import numpy as np
import pandas as pd

from sklearn.model_selection import train_test_split

import tensorflow as tf
import tensorflow.keras as keras
from keras.models import Sequential
from keras.layers import Dense



dataset = pd.read_csv('dataset_fft.csv', header=None)

X = dataset.iloc[:, 0:-1]
Y = dataset.iloc[:, -1:]
Y = np.ravel(Y)
y = []
for i in Y:
    s = i.split(".")
    y.append(s[0])


X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)
X_train, X_val, y_train, y_val = train_test_split(X_train, y_train, test_size=0.2)

# print('Shape : ', X_train.shape + X_test.shape + X_val.shape)

ds_train = tf.data.Dataset.from_tensor_slices((X_train, y_train))
ds_val = tf.data.Dataset.from_tensor_slices((X_val, y_val))
ds_test = tf.data.Dataset.from_tensor_slices((X_test, y_test))


#Paramètres
BATCH_SIZE = 32
NB_EPOCHS = 20
LEARNING_RATE = 0.001
DECAY = 0.01
label_nb = 10
dataset_size = 1000

model = Sequential()

model.add(keras.layers.Conv2D(32, (3, 3), padding='same', input_shape=(1024, 1024, 1), activation = 'relu'))
model.add(keras.layers.MaxPooling2D((2, 2)))
model.add(keras.layers.Conv2D(64, (3, 3), padding='same', activation='relu'))
model.add(keras.layers.Conv2D(64, (3, 3), padding='same', activation='relu'))
model.add(keras.layers.MaxPooling2D((2, 2)))

model.add(keras.layers.Flatten())
model.add(keras.layers.Dense(64, activation = 'relu'))
model.add(keras.layers.Dropout(0.5))
model.add(keras.layers.Dense(32, activation = 'relu'))
model.add(keras.layers.Dropout(0.5))
model.add(keras.layers.Dense(label_nb, activation = 'softmax'))


loss_fcn = tf.keras.losses.SparseCategoricalCrossentropy()
optimizer_fcn = keras.optimizers.Adam(learning_rate=LEARNING_RATE, decay=DECAY)
metrics_fcn = tf.keras.metrics.SparseCategoricalAccuracy()
model.compile(loss=loss_fcn, optimizer=optimizer_fcn, metrics=metrics_fcn)

history = model.fit(ds_train, steps_per_epoch=int(0.75 * dataset_size / BATCH_SIZE), validation_data=ds_val, validation_steps=int(0.15 * dataset_size / BATCH_SIZE), epochs=NB_EPOCHS)

score = model.evaluate(X_test, y_test, batch_size=32)
print('Scores : ', score)
