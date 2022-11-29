#include <iostream>
#include "au_reading.h"
#include "signal.h"

using namespace std;

int main() {
    cout << "Reading" << endl;
    auto data = readAuFile("disco.00050.au");
    cout << "Converting" << endl;
    auto bins = stft(data);
    cout << "ms" << endl;
    auto ms = binsavgstd(bins);
    std::cout << ms << std::endl;
    return 0;
}
