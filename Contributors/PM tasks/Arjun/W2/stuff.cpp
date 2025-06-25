// Version C++ 11

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
    // #include <utility> // for std::pair
    // #include <stdexcept> // for std::invalid_argument

// Parallel processing mean calculation and file reading
// #include <omp.h>

using namespace std;

// struct dataframe
// {
//     // Dataframe with attributes header and data as a vector of columns
//     vector<string> headers; // Column names
//     // Data as a dictionary of column names
//     vector<vector<string>> data; // Each column is a vector of strings
//     // Constructor to initialize dataframe with headers and data
//     dataframe(const vector<string> & headers, const vector<vector<string>> & data)
//         : headers(headers), data(data) {}
//     // Function to get a column by name
//     vector<string> get_column(const string & name) const    
// };

// Read from csv file and store as vector of columns like a pandas dataframe
vector<vector<string>> read(const string & filename, const bool & header = true)
{
    // Error handling
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file." << endl;
        return vector<vector<string>>(); // Return empty vector if file cannot be opened
    }

    // Headers and data
    vector<string> headers;
    vector<vector<string>> data;

    // Read header line (1st line)
    if (header)
    {
        string line;
        if (getline(file, line))
        {
            stringstream ss(line);
            string header;
            while (getline(ss, header, ','))
            {
                headers.push_back(header);
                data.push_back(vector<string>()); // Initialize each column
            }
        }
    }

    // Read data
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string value;
        size_t col_index = 0;
        while (getline(ss, value, ','))
        {
            if (col_index < data.size())
            {
                data[col_index].push_back(value); // Add value to the corresponding column
            }
            col_index++;
        }
    }
    return data;
    file.close();
}

// // Convert column to float if possible
// vector<float> to_float(const vector<string> & column)
// {
//     vector<float> float_column;
//     for (const string & value : column)
//     {
//         try
//         {
//             float_column.push_back(stof(value)); // stof - string to float
//         }
//         catch (const invalid_argument & e)
//         {
//             cerr << "Invalid value: " << value << endl;
//             float_column.push_back(0.0f); // Push 0 if invalid value
//         }
//     }
//     return float_column;
// }


// float mean(vector<float> & column)
// {
//     float sum = 0;
//     // Parallelise
//     #pragma omp parallel
//     for (float a: column)
//     {
//         sum += a;
//     }
//     return sum/column.size();
// }

// auto stddev(vector<float> & column)
// {
//     float mu = mean(column);
//     float vars = 0;
//     // Parallelise
//     #pragma omp parallel
//     for (float a: column)
//     {
//         vars += (a - mu) * (a - mu);
//     }
//     return sqrt(vars / column.size());
// }

// // Corr(x, y)
// float corr(vector<float> & x, vector<float> & y)
// {
//     int n = x.size();
//     if (x.size() != y.size())
//     {
//         cerr << "x, y have diff size." << endl;
//         return 0;
//     }
    
//     float mu_x = mean(x);
//     float mu_y = mean(y);
//     float std_x = stddev(x);
//     float std_y = stddev(y);
    
//     float covs = 0;
//     // Parallelise
//     #pragma omp parallel for reduction(+:cov)
//     for (size_t i = 0; i < n; i++)
//     {
//         covs += (x[i] - mu_x) * (y[i] - mu_y);
//     }
    
//     return covs / (n * std_x * std_y);
// }

int main()
{
    string fname = "data.csv";
    auto data = read(fname);
    // Print data
    for (const auto & col : data)
    {
        for (const auto & val : col)
        {
            cout << val << " ";
        }
        cout << endl;
    }
    // vector<float> col1 = to_float(data[1]);
    
    // float mu = mean(col1);
    // float sigma = stddev(col1);
    // cout << "Mean: " << mu << ", Std Dev: " << sigma << endl;
}