#include <iostream>
#include <fstream>
#include <string>

#include "fft_utils.h"
#include "constant.h"

#define SAMPLE_NUMBER 10

using namespace std;


int read32Bits(ifstream &file_s) {
	int result = 0;
	unsigned char byte;
	for (int i=0; i<4; i++) {
		byte = file_s.get();
		result = result<<8 | (int)byte;
	}
	return result;
}

int readSample(ifstream &file) {
	short sample = 0;
	unsigned char byte;
	for (int i=0; i<2; i++) {
		byte = file.get();
		sample = sample<<8 | (short)byte;
	}
	return (int)sample;
}



int main() {
	string name_au("../genres/hiphop/hiphop.00000.au");
	string name_csv("output.csv");

	ifstream file_s;
	ofstream file_o;

	file_s.open(name_au);
	file_o.open(name_csv);

	for (int i=0; i<6; i++) cout<<read32Bits(file_s)<<endl;

	while (!file_s.eof()) {
		std::vector<std::complex<double>> v;
		double real; 
		double imaginary = 0.;
		for (int i=0; i<K; i++) {
			for (int i=0; i<N; i++) {
				real = readSample(file_s);
			}
		}
	}
}





/*
dans constant : n, k, l (et pi)
l = n x k
n : fft

faire du 0 paving si signal trop court

on divise le signal en k, et on donne un std vector de n échantillons
le tout nous donne un f(t) appelé stft

a la fin on veut deux vecteurs de taille n : 
mu, moyenne temporelle du spectrogramme
sigma, écart-type ""

pb : stockage !
donc on caclul ces deux vecteurs de manières itératives

voir wikipédia calcul itératif pour la mise à jour de la variance
*/