#include <lfpRatiometer>

int main () {

    // instantiate an object
    int N = 10;
    double sampling = 200;
    lfpRatiometer lfpratiometer(N, sampling);

    // apply a Hamming window
    lfpratiometer.window_hamming();

    // setting LF/HF parameters
    double lf_low = 1;
    double lf_high = 25;
    double hf_low = 30;
    double hf_high = 90;
    lfpratiometer.setRatioParams(lf_low, lf_high, hf_low, hf_high);

    // inputting a specific time series...
    std::vector<double> in_raw;
    for (int j=0; j<N; j++) {
        in_raw.push_back(1);
    }
    in_raw.at(1) = 2;
    in_raw.at(8) = 2;

    // ... by pushing values one by one
    for (int j=0; j<N; j++) {
        lfpratiometer.pushTimeSample(in_raw[j]);
    }

    // calculating lf/hf ratio
    lfpratiometer.calcRatio();

    // grabbing variables from object
    double lf_hf_ratio = lfpratiometer.getRatio();
    std::vector<double> allfreqs = lfpratiometer.getFreqs();
    std::vector<double> psd = lfpratiometer.getPSD();

    // printing the results
    std::cout << "freq, psd\n";
    for (int i=0; i<N/2+1; i++) {
        std::cout << allfreqs[i] << "," << psd[i] << "\n";
    }
    std::cout << "LF/HF Ratio: " << lf_hf_ratio << "\n";

    // inputting the same time series ...
    // ...by setting object time series directly
    lfpratiometer.setTimeSeries(in_raw);

    // calculating lf/hf ratio
    lfpratiometer.calcRatio();

    // grabbing variables from object
    lf_hf_ratio = lfpratiometer.getRatio();
    allfreqs = lfpratiometer.getFreqs();
    psd = lfpratiometer.getPSD();

    // printing the results...again
    std::cout << "\nfreq, psd\n";
    for (int i=0; i<N/2+1; i++) {
        std::cout << allfreqs[i] << "," << psd[i] << "\n";
    }
    std::cout << "LF/HF Ratio: " << lf_hf_ratio << "\n";

    return 0;

}