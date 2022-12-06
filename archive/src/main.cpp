#include <iostream>
#include <fstream>
#include <cstdio>
#include <cassert>
#include "fft_utils.h"
#include "constants.h"
#include <algorithm>

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

// void mean_std(std::vector<Complex> x, double &mean, double &ect) {
// 	double sum=0.;
// 	double sum2=0.;
// 	int n=x.size();
// 	for (int i = 0; i < n; ++i)
// 	{
// 		sum+=x[i];
// 		sum2+=x[i]*x[i];
// 	}
// 	mean=sum/n;
// 	float var=sum2/n-mean*mean;
// 	ect=sqrt(var);
// }

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
	std::vector<double> mu;
	std::vector<double> sigma;
	std::vector<double> spec;
	x.resize(N);
	mu.resize(N);
	sigma.resize(N);
	spec.resize(N);
	// initiliazer
	for (int i = 0; i < sigma.size(); ++i)
	{
		sigma[i]=0;
	}
	std::vector<double> c;
	std::vector<double> s;
	if (!datafile.eof()) {
		for (int i = 0; i < K; ++i)
		{
			for (int k = 0; k < N; ++k)
				{
					x[k]=readSample(datafile);
				}
			ite_dit_fft(x);
			// for_each(x.begin(),x.end(),norm)
			for (int k = 0; k < N; ++k)
			{
				spec[k]=norm(x[k]);
			}
			// cout << spec << endl;
			if (i==0) {
				for (int k = 0; k < N; ++k)
				{
					mu[k]=spec[k];
				}
			}
			// cout << mu[6] << endl;
			else {
				for (int k = 0; k < N; ++k)
				{
				mu[k]=(i-1)/i*mu[k]+1/i*spec[k];
				s[k]=s[k]+spec[k];
				c[k]=c[k]+pow(i*spec[k]-s[k],2)/(i*(i-1));
				sigma[k]=c[k]/i;
				}
			}
		}
	}
}

