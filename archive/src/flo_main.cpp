#include <iostream>
#include <filesystem>	
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
	std::vector<string> name_au;
	std::vector<string> name_au_complete;
	string genres("../genres");
    for (const auto& entry : std::filesystem::directory_iterator(genres)) {
        if (entry.is_directory()) {
        	string dir=genres+"/"+string(entry.path().filename());
        	// cout << dir << endl;
            // // std::cout << entry.path().filename() << std::endl;
            for (const std::filesystem::directory_entry& entry_files : std::filesystem::directory_iterator(dir)) {
		        // Affiche le nom du fichier
		        string comp=dir+"/"+string(entry_files.path().filename());
		        name_au_complete.push_back(comp);
		        name_au.push_back(entry_files.path().filename());
    		}
        }
    }

	ofstream file_o;
	string name_csv("output.csv");
	file_o.open(name_csv);
	

	for (int i = 0; i < 1000; ++i)
	{
		ifstream file_s;
		file_s.open(name_au_complete[i]);
		for (int i=0; i<6; i++) cout<<read32Bits(file_s)<<endl;

		std::vector<float> mu_prev, sigma_prev;
		for (int j=0; j<N; j++) mu_prev.push_back(0.);
		for (int j=0; j<N; j++) sigma_prev.push_back(0.);
		cout << i << endl;
		for (int k=0; k<K; k++) {
			std::vector<Complex> x = {};
			std::vector<float> mu_now = {}, sigma_now = {};

			for (int j=0; j<N; j++) x.push_back(readSample(file_s));
			ite_dit_fft(x);

			// cout<<norm(x[10])<<endl;

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
		for (int j = 0; j < N; ++j)	
			file_o << mu_prev[j] << ", ";
		for (int j = 0; j < N; ++j)
			file_o << sigma_prev[j] << ", ";
		file_o << name_au[i] << "\n";
		// std::map<string, std::pair<std::vector<float>,std::vector<float>>> m = {}; //liste des coordonnées 
		// m[name_au] = {mu_prev, sigma_prev};
	}


}