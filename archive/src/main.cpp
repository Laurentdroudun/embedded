#include <iostream>
#include <fstream>
#include <iterator>
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
	string filename="../genres/hiphop/hiphop.00002";
	string csv_filename=filename+".csv";
	string au_filename=filename+".au";
	ifstream datafile;
	ofstream datafile_csv;
	datafile.open(au_filename);
	datafile_csv.open(csv_filename);
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

	for (int i=0; i<6; i++) cout<<read32bits(datafile)<<endl;

	std::vector<float> mu_prev, sigma_prev;
	for (int j=0; j<N; j++) mu_prev.push_back(0.);
	for (int j=0; j<N; j++) sigma_prev.push_back(0.);

	for (int i=0; i<K; i++) {
		std::vector<Complex> x = {};
		std::vector<float> mu_now = {}, sigma_now = {};

		for (int j=0; j<N; j++) x.push_back(readSample(datafile));
		ite_dit_fft(x);

		for (int j=1; j<=N; j++) {
			float a = ((j-1.)/j)*mu_prev[j-1];
			float b = (1./j)*norm(x[j-1]);
			mu_now.push_back(a+b);
		}
		for (int j=0; j<N; j++)	mu_prev[j] = mu_now[j];

		auto c = sigma_prev[0];
		auto s = norm(x[0]);
		for (int j=2; j<=N; j++) {
			s = s + norm(x[j-1]);
			c = c + sigma_prev[j-1] + pow(j*norm(x[j-1])-s, 2)/(j*(j-1.));
			sigma_now.push_back(sqrt(c/N));
		}
		for (int j=0; j<N; j++) sigma_prev[j] = sigma_now[j];
	}
	// cout<<mu_prev[10]<<" ; "<<sigma_prev[100] << "\n" <<endl;
	
	for (int i = 0; i < N; ++i)
	{
		cout << mu_prev[i] << "," << sigma_prev[i] << endl;
	}
}

