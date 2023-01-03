from sklearn import svm
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.svm import LinearSVC
from sklearn.datasets import make_classification

import numpy as np
from scipy import signal, fft
from matplotlib import pyplot as plt
import os

path = "../genres/"
filenames=[]
dir_list=os.listdir(path)
print(dir_list)
for dir_ in dir_list :
	# print(file for file in os.listdir(path+dir_))
	for file in os.listdir(path+dir_) :
		filenames.append(path+dir_+"/"+file)
filenames=np.array(filenames)

def get_Xy(filename) :
	data = ""
	with open(filename, 'rb') as au:
	    magic = au.read(4)
	    dataoffset = int.from_bytes(au.read(4), byteorder='big', signed=True)
	    datasize = int.from_bytes(au.read(4), byteorder='big', signed=True)
	    print(magic, dataoffset, datasize)
	    print("Offset : ", dataoffset)
	    print("Size : ", datasize / (1 << 20), " MiB")
	    au.seek(0)
	    au.read(dataoffset)
	    data = au.read(datasize)


	d = []
	for i in range(0, datasize, 2):
	    d.append(int.from_bytes(data[i:i + 2], byteorder='big', signed=True))

	plt.plot(d)
	plt.show()



	data = np.array(d, dtype='float')
	# print(data[0], data[-1])
	# print(data.shape)
	fs = 22050
	f, t, Zxx = signal.stft(data, 22050, nperseg=512, noverlap=256, window='hamming', return_onesided=False)
	Z = np.abs(Zxx)
	# print(Z.shape)
	# print(Z)
	m = np.mean(Z, axis=1)
	e = np.std(Z, axis=1)

	return m,e
	# print(m)
	# print(e)

filename=filenames[450]
m,e=get_Xy(filename)

x,y=make_classification(n_samples=1000,n_features=1024,n_classes=10)

X=np.vstack((m,e))
y=np.array([filename])

clf=svm.LinearSVC()
clf.fit(X,y)

