#include<complex>
#include<vector>

typedef std::complex<double> complex64;


std::vector<complex64> check(std::vector<complex64> signal) {
    int N = signal.size();
    if (N % 2 != 0) {
        signal.push_back((0, 0));
        return signal;
    }
    else {
        return signal;
    }
}