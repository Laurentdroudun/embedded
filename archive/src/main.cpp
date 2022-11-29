#include <iostream>
#include <fstream>
#include <cstdio>
#include <cassert>

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
}


	// datafile.read((char*)&aufile.nombreMagique,sizeof(aufile.nombreMagique));
	// assert(aufile.nombreMagique==0x2e736e64);
	// datafile.read((char*)&aufile.dataShift,sizeof(aufile.dataShift));
	// datafile.read((char*)&aufile.dataLength,sizeof(aufile.dataLength));
	// datafile.read((char*)&aufile.encodage,sizeof(aufile.encodage));