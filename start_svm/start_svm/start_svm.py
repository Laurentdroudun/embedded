import numpy as np
from scipy import signal, fft
from matplotlib import pyplot as plt

path = "disco.00050.au"

data = ""
with open(path, 'rb') as au:
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
print(data[0], data[-1])
print(data.shape)
fs = 22050
f, t, Zxx = signal.stft(data, 22050, nperseg=512, noverlap=256, window='hamming', return_onesided=False)
Z = np.abs(Zxx)
print(Z.shape)
m = np.mean(Z, axis=1)
e = np.std(Z, axis=1)
print(m.shape)
print(e.shape)

plt.pcolormesh(t, f, np.abs(Zxx), shading='gouraud')
plt.title('STFT Magnitude')
plt.ylabel('Frequency [Hz]')
plt.xlabel('Time [sec]')
plt.show()

