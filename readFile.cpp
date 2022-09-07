#include<iostream>
#include<vector>
#include<complex>
#include<fstream>
#include<string>
#include "readFile.h"


std::vector<std::complex<double>> readFile(std::string fileName) {
    std::fstream myFile;
    std::vector<std::complex<double>> signal;
    myFile.open(fileName, std::ios::in);//read from file
    if (myFile.is_open()) {
        std::string line;
        while (getline(myFile, line)) {
            signal.push_back(stod(line));
        }
    }
    myFile.close();
    return signal;
}
