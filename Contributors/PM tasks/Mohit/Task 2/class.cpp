#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <chrono>

using namespace std;

class Analyzer {

    // Objects of this class can load in a csv file, 
    // and compute basic statistics on the dataset.

private:
    vector<string> timestamps;
    vector<double> values;
    vector<double> sorted;

    size_t cached_count = 0;
    double cached_mean = NAN;
    double cached_variance = NAN;
    double cached_std = NAN;
    double cached_min = NAN;
    double cached_max = NAN;
    double cached_median = NAN;

public:
    bool load_csv(const string& filepath, bool header = true) {

        // function to load in the csv file

        ifstream file(filepath);
        if (!file.is_open()) return false;

        string line;
        if (header) getline(file, line); // Skip header

        while (getline(file, line)) {
            stringstream ss(line);
            string ts, val;
            getline(ss, ts, ',');
            getline(ss, val, ',');
            try {
                timestamps.push_back(ts);
                values.push_back(stod(val));
            } catch (...) {
                continue;
            }
        }

        sorted = values;
        sort(sorted.begin(), sorted.end());

        compute_all_stats();
        return true;
    }

    void compute_all_stats() {

        // function to calculate all the basic stats

        cached_count = values.size();
        if (cached_count == 0) return;

        // Mean
        cached_mean = accumulate(values.begin(), values.end(), 0.0) / cached_count;

        // Variance
        double sum_sq = 0.0;
        for (double v : values) sum_sq += (v - cached_mean) * (v - cached_mean);
        cached_variance = sum_sq / cached_count;

        // Standard Deviation
        cached_std = sqrt(cached_variance);

        // Min & Max
        auto [min_it, max_it] = minmax_element(values.begin(), values.end());
        cached_min = *min_it;
        cached_max = *max_it;

        // Median
        cached_median = ((cached_count & 1 == 0)) ? (sorted[cached_count / 2 - 1] + sorted[cached_count / 2]) / 2.0 : sorted[cached_count / 2];
    }

    // in-direct access functions

    size_t count() const { return cached_count; }
    double mean() const { return cached_mean; }
    double variance() const { return cached_variance; }
    double stddev() const { return cached_std; }
    double minimum() const { return cached_min; }
    double maximum() const { return cached_max; }
    double range() const { return cached_max - cached_min; }
    double median() const { return cached_median; }
    double coeff_of_var() const { return cached_std/cached_mean; }

};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Analyzer analyzer;
    if (!analyzer.load_csv("./Datasets/ambient_temperature_system_failure.csv")) {
        cerr << "Failed to load CSV file.\n";
        return 1;
    }

    cout << "Count: " << analyzer.count() << '\n';
    cout << "Mean: " << analyzer.mean() << '\n';
    cout << "Variance: " << analyzer.variance() << '\n';
    cout << "Standard Deviation: " << analyzer.stddev() << '\n';
    cout << "Min: " << analyzer.minimum() << '\n';
    cout << "Max: " << analyzer.maximum() << '\n';
    cout << "Range: " << analyzer.range() << '\n';
    cout << "Median: " << analyzer.median() << '\n';

    auto end = chrono::high_resolution_clock::now();
    chrono::duration <double> duration = end-start;
    cout << "Time taken: " << duration.count() << '\n';

    return 0;
}
