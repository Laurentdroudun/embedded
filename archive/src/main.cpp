#include <iostream>
#include <fstream>
#include <cstdio>
#include <cassert>
#include "fft_utils.h"
#include "constants.h"

using namespace std;

struct AuFile {
	uint32_t nombreMagique;
	uint32_t dataShift;
	uint32_t dataLength;
	uint32_t encodage;
	uint32_t freq;
	uint32_t nbCanaux;
};

int read32bits(ifstream &file_s) {
	int result=0;
	unsigned char byte;
	for (int i = 0; i < 4; ++i)
	{
		byte=file_s.get();
		result = result << 8 | (int)byte;
	}
	return result;
}

int readSample(ifstream &file) {
	short sample=0;
	unsigned char byte;
	for (int i = 0; i < 2; ++i)
	{
		byte=file.get();
		sample=sample<<8 | (short)byte;
	}
	return (int)sample;
}

int main() {
	string filename="../genres/hiphop/hiphop.00002.au";
	// string csv="../genres/hiphop/hiphop.00001.csv";
	ifstream datafile;
	// ofstream datafile_csv;
	datafile.open(filename);
	// datafile_csv.open(csv);
	if (!datafile.is_open())
		cout << "Impossible d'ouvrir le fichier" << endl;
	AuFile aufile;
	aufile.nombreMagique=read32bits(datafile);
	aufile.dataShift=read32bits(datafile);
	aufile.dataLength=read32bits(datafile);
	aufile.encodage=read32bits(datafile);
	aufile.freq=read32bits(datafile);
	aufile.nbCanaux=read32bits(datafile);
	cout << aufile.nombreMagique << endl;
	cout << aufile.dataShift << endl;
	cout << aufile.dataLength << endl;
	cout << aufile.encodage << endl;
	cout << aufile.freq << endl;
	cout << aufile.nbCanaux << endl;

	std::vector<Complex> x;
	x.resize(N);
	std::vector<Complex> mu;
	mu.resize(N);
	std::vector<Complex> sigma;
	sigma.resize(N);
	if (!datafile.eof()) {
		for (int k = 0; k < N; ++k)
			{
				x[k]=readSample(datafile);
			}
		ite_dit_fft(x);
		cout << x.real() << endl;

		// for (int i = 0; i < K; ++i)
		// {
			
		// }
	}
}