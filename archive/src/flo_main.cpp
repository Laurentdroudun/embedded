#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <map>

#include "fft_utils.h"
#include "constants.h"

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
	cout<<name_au<<endl;
	string name_csv("output.csv");

	ifstream file_s;
	ofstream file_o;

	file_s.open(name_au);
	file_o.open(name_csv);

	for (int i=0; i<6; i++) cout<<read32Bits(file_s)<<endl;

	std::vector<float> mu_prev, sigma_prev;
	for (int j=0; j<N; j++) mu_prev.push_back(0.);
	for (int j=0; j<N; j++) sigma_prev.push_back(0.);

	for (int i=0; i<K; i++) {
		std::vector<Complex> x = {};
		std::vector<float> mu_now = {}, sigma_now = {};

		for (int j=0; j<N; j++) x.push_back(readSample(file_s));
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

		cout<<mu_now[10]<<" ; "<<sigma_now[100]<<endl;
	}
	
	std::map<string, std::pair<std::vector<float>,std::vector<float>>> m = {}; //liste des coordonnées 
	m[name_au] = {mu_prev, sigma_prev};

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




entrainer le modèle linear.svm et récupérer les poids
*/