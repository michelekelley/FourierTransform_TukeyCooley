#include<vector>
#include<complex>




std::vector<std::complex<double>> DFT(std::vector<std::complex<double>> signal) {
    const double PI = acos(-1);
    std::complex<double> val = 0;
    int N = signal.size();
    std::complex<double> im = { 0, 1 };
    std::vector<std::complex<double>> dftsignal;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            val += exp(-im * 2.0 * PI * (double)i * (double)j / (double)N) * signal[j] / sqrt(N);
        }
        dftsignal.push_back(val);
        val = 0;
    }

    return dftsignal;
}