#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

// #include <omp.h>

using namespace std;

float mu(const vector<float> & col)
{
    float sum = 0;
    for (const float & a : col)
    {
        sum += a;
    }
    return sum/col.size();
}

float sigma(const vector<float> & col)
{
    float m = mu(col);
    float vars = 0;
    for (const float & a : col)
    {
        vars += (a-m)*(a-m);
    }
    return sqrt(vars/col.size());
}

float corr(const vector<float> & x, const vector<float> & y)
{
    float mean_x = mu(x);
    float mean_y = mu(y);
    float std_x = sigma(x);
    float std_y = sigma(y);

    if (x.size() != y.size())
    {
        cerr << "Len of x != y." << endl;
        return 0;
    }
    float covs = 0;
    for (size_t i = 0; i < x.size(); i++)
    {
        covs += (x[i] - mean_x)*(y[i] - mean_y);
    }
    return covs/(x.size()*std_x*std_y);
}

int main()
{
    ifstream file("data.csv");
    if (!file.is_open())
    {
        return -1;
    }
    vector <string> timestamp;
    vector <float> value;
    string line;

    while (getline(file, line))
    {
        istringstream ss(line);
        {
            // Take 2 values based on comma
            string ts, val;
            getline(ss, ts, ',');
            getline(ss, val, ',');
            timestamp.push_back(ts);
            value.push_back(stof(val));
        }
    }
    file.close();

    cout << "Mu: " << mu(value) << endl;
    cout << "Sigma: " << sigma(value) << endl;
    cout << "Corr: " << corr(value, value) << endl;

    // Wait for key to close
    cout << "Press Enter to exit...";
    cin.ignore();
    return 0;
}