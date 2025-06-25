#include <iostream>
#include <Eigen/Dense>
#include <fstream>

void calcwithEigen(Eigen::VectorXd& a, Eigen::VectorXd b)
{
    double y_mean=b.sum()/4032;
    double x_mean=a.sum()/4032;
    double y_stddev=sqrt(b.dot(b)/4032 - y_mean*y_mean);
    double x_stddev=sqrt(a.dot(a)/4032 - x_mean*x_mean);
    double covxy=(a.array()-x_mean).matrix().dot((b.array()-y_mean).matrix())/4032;
    double corr=covxy/(y_stddev*x_stddev);
    std::cout<<"Mean of y: "<<y_mean<<std::endl;
    //std::cout<<"Mean of x: "<<x_mean<<std::endl;
    std::cout<<"Standard deviation of y: "<<y_stddev<<std::endl;
    // std::cout<<"Standard deviation of x: "<<x_stddev<<std::endl;
    //std::cout<<"Correlation "<<corr<<std::endl;

}


int main()
{
    std::ifstream file("art_daily_small_noise.csv");
    Eigen::VectorXd x(4032);
    Eigen::VectorXd y(4032);
    std::string a="";
    getline(file, a);
    for(int i=0; i<4032; i++)
    { 
        getline(file, a, ',');
        getline(file, a, '\n');
        x(i)=i*5;
        y(i)=std::stod(a);
    }
    calcwithEigen(x, y);
}
