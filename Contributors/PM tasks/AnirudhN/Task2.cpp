#include<iostream>
#include<conio.h>
#include<iomanip>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<math.h>
using namespace std;
vector<string>splt(const string& line)
{stringstream ss(line);
vector<string>Fld;
string field;
while(getline(ss,field,','))
{field.erase(0,field.find_first_not_of("\t"));
field.erase(field.find_last_not_of("\t")+1);
Fld.push_back(field);}
return Fld;
}
float mean(vector<float> l)
{float rt=0;
    for(int i=0;i<l.size();i++)
     rt+=l[i];
     return (float)rt/l.size();

}
float sd(vector<float> l)
{
    float sdv=0;
    for(int i=0;i<l.size();i++)
     sdv+=l[i]*l[i];
     sdv=(float)sqrt(sdv/l.size()-mean(l));
     return sdv;
}

int main()
{string flname="art_daily_flatmiddle.csv";
    ifstream file(flname);

   if(!file.is_open())
   {cout<<"file not open"; return 1;}
   vector<string>time;
 vector<float>value;
 string ln;
 long long int ct=1;
 getline(file,ln);
while (getline(file, ln)) {
    ct++;
    vector<string> field = splt(ln);

    if (field.size() < 2 || field[1].empty()) continue;
    try {
        value.push_back(stof(field[1]));
        time.push_back(field[0]);
    } catch (const std::exception& e) {
        cerr << "Conversion error at line " << ct << ": " << e.what() << " for value: " << field[1] << endl;
    }
}
float mn;
float sdv;

mn=mean(value);
sdv=sd(value);
cout<<mn<<" "<<sdv<<"\n";


    return 0;
}
