#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;
int b=4032; //number of observations

void calc(vector<double> a, double& y_mean, double& stddev_y) //function to calculate mean and stddev
{   
    double ss=0;
    for(int i=0; i<b; i++)
    {
        y_mean+=a[i];
        ss+=a[i]*a[i];
    }

    y_mean=y_mean/b;
    stddev_y=sqrt(ss/b-y_mean*y_mean);
}

int main()
{   
    ifstream file("art_daily_small_noise.csv"); //loading the file
    vector<double> y(b);
    string a;
    getline(file, a); //header line
    for(int i=0; i<b; i++)
    {
       getline(file, a, ','); //reads the values of timestamp
       getline(file, a, '\n'); //stores the value of entry
       y[i]=stod(a); //stores value of entry
    }
    file.close();
    double y_mean=0;
    double y_stddev=0;
    calc(y, y_mean, y_stddev);
 
    cout<<"Mean: "<<y_mean<<std::endl;
    cout<<"Standard Deviation: "<<y_stddev<<std::endl;
}
