#include<iostream>
#include<complex>
#include<vector>
#include<fstream>
#include<string>
#include "readFile.h"
#include "DFT.h"

typedef std::complex<double> complex64;

//std::vector<std::complex<double>> readFile(std::string fileName) {
//    std::ofstream myFile;
//    std::vector<std::complex<double>> signal;
//    myFile.open(fileName, std::ios::in);//read from file
//    if (myFile.is_open()) {
//        std::string line;
//        while (getline(myFile, line)) {
//            signal.push_back(stod(line));
//        }
//    }
//    myFile.close();
//    return signal;
//    }

std::vector<complex64> check(std::vector<complex64> signal) {
    int N = signal.size();
    if (N % 2 != 0) {
        signal.push_back(complex64(0, 0));
        return signal;
    }
    else {
        return signal;
    }
}

//std::vector<std::complex<double>> DFT(std::vector<std::complex<double>> signal) {
//    const double PI = acos(-1);
//    std::complex<double> val = 0;
//    int N = signal.size();
//    std::complex<double> im = { 0, 1 };
//    std::vector<std::complex<double>> dftsignal;
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            val += exp(-im * 2.0 * PI * (double)i * (double)j / (double)N) * signal[j] / sqrt(N);
//        }
//        dftsignal.push_back(val);
//        val = 0;
//    }
//   
//    return dftsignal;
//}

std::vector<std::complex<double>> halfDFT(std::vector<std::complex<double>> signal) {
    const double PI = acos(-1);
    auto val = complex64(0, 0);
    int N = signal.size();
    std::complex<double> im = { 0, 1 };
    std::vector<std::complex<double>> dftsignal;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            val += exp(-im * 2.0 * PI * (double)i * (double)j / (double)N) * signal[j] / sqrt(2.0 * N);
        }
        dftsignal.push_back(val);
        val = 0;
    }

    return dftsignal;
}

std::vector<std::complex<double>> slice(std::vector<std::complex<double>> signal, int start, int end, int step) {
    std::vector<std::complex<double>> slicedvector;

    for (int i = start; i < end; i += step) {
        slicedvector.push_back(signal[i]);
    }

    return slicedvector;

}

std::vector<std::complex<double>> recombine(std::vector<std::complex<double>> fteven, std::vector<std::complex<double>> ftodd) {
    std::vector<std::complex<double>> ftsignal;
    const double PI = acos(-1);
    std::complex<double> im = { 0, 1 };
    std::complex<double> W;
    int N = fteven.size();

    for (int k = 0; k < N; k++) {
        W = exp(-2.0 * PI * im * (double)k / (double)(2.0 * N));
        ftsignal.push_back(fteven[k] + (W * ftodd[k]));
    }

    for (int k = 0; k < N; k++) {
        W = exp(-2.0 * PI * im * (double)k / (double)(2.0 * N));
        ftsignal.push_back(fteven[k] - (W * ftodd[k]));
    }

    return ftsignal;
}


int main()
{
    std::vector<std::complex<double>> signal = readFile("test.csv");
    std::vector<std::complex<double>> adjsignal = check(signal); //check if signal is divisble by 2, if not pad with a 0
    std::vector<std::complex<double>> dftsignal = DFT(adjsignal); //take the discrete fourier transform to check algorithm by

    std::cout << "DFT" << std::endl;
    for (int i = 0; i < dftsignal.size(); i++) {
        std::cout << "(" << std::ceil(100.0 * dftsignal[i].real()) / 100.0 << "," << std::ceil(100.0 * dftsignal[i].imag() / 100) << ")" << std::endl;
    }
    std::cout << std::endl;

    std::vector<std::complex<double>> evenFT = halfDFT(slice(adjsignal, 0, adjsignal.size(), 2));
    std::vector<std::complex<double>> oddFT = halfDFT(slice(adjsignal, 1, adjsignal.size(), 2));
    std::vector<std::complex<double>> tcFT = recombine(evenFT, oddFT);

    std::cout << "Tukey Cooley" << std::endl;
    for (int i = 0; i < tcFT.size(); i++) {
        std::cout << "(" << std::ceil(100.0 * tcFT[i].real()) / 100.0 << "," << std::ceil(100.0 * tcFT[i].imag() / 100) << ")" << std::endl;
    }


    system("pause>0");
}
