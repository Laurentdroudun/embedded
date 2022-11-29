#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

struct AuFile {
	uint32_t nombreMagique;
	uint32_t dataShift;
	uint32_t dataLength;
	uint32_t encodage;
	uint32_t freq;
	uint32_t nbCanaux;
};


int main() {
	string filename="../genres/hiphop/hiphop.00000.au";
	ifstream datafile;
	datafile.open(filename.c_str(),ios::binary | ios::in);
	if (!datafile.is_open())
		cout << "Impossible d'ouvrir le fichier" << endl;
	AuFile aufile;
	datafile.read((char*)&aufile.nombreMagique,sizeof(aufile.nombreMagique));
	datafile.read((char*)&aufile.dataShift,sizeof(aufile.dataShift));
	datafile.read((char*)&aufile.dataLength,sizeof(aufile.dataLength));
	datafile.read((char*)&aufile.encodage,sizeof(aufile.encodage));
	cout << aufile.nombreMagique << endl;
	cout << aufile.dataShift << endl;
	cout << aufile.dataLength << endl;
	cout << aufile.encodage << endl;
}