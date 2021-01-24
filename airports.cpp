#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include<vector>
#include <sstream>
#include <cstring>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include<algorithm>
#include <chrono>
using namespace std;

//structure to hold the required datas from the airports.dat file
struct airport{
  string Name;
  string ICAO;
  long double latitude;
  long double longitude;
};

//function to convert latitude and longtitude degree angles to the radians
long double ConvertAngle(const long double degree)
{
      return((M_PI/180)*degree);
}

//calculate the distance between two points given latitude and longitude of the
//two points.
long double distancebetweentwo(long double la_1,long double lo_1,long double la_2,long double lo_2)
{
      la_1 = ConvertAngle(la_1);
      lo_1 = ConvertAngle(lo_1);
      la_2 = ConvertAngle(la_2);
      lo_2 = ConvertAngle(lo_2);

      long double distance_long = lo_2 - lo_1;
      long double distance_lat = la_2-la_1;

      long double actualDistance = pow(sin(distance_lat/2),2)+cos(la_1) *cos(la_2)*pow(sin(distance_long/2),2);


      return (6371*asin(sqrt(actualDistance)));
}

int main()
{
  //time to calculate the time for the initialization
    auto start_init = std::chrono::high_resolution_clock::now();

//this flags checks if the user input radius is -ve or not
    bool flag=true;
    string userinput;
    string user_radius,user_ICAO;
    //opening the data file for read
	  ifstream airportFile("airports.dat");
	  string line;

    //vectors to store each struct pointer
    vector<airport*> structvector;
    //parsing the each line of the file
        while(getline(airportFile,line))
        {
          //vector to store each tokens of the each line
            vector<string> tokens;
            stringstream airportsline(line);
            //tokenizing the each airport info
            while(airportsline.good())
            {

                string splits;
                getline(airportsline,splits,',');
                tokens.push_back(splits);
            }

              if(tokens.size()<=14)
              {
                  airport* eachairportstruct = new airport;
                  //adding required info to the structure
                  eachairportstruct->Name=tokens[1];
                  string my_str = tokens[5];

                  my_str.erase(remove(my_str.begin(), my_str.end(), '"'), my_str.end());
                  eachairportstruct->ICAO=my_str;
                  eachairportstruct->latitude=stold(tokens[6]);
                  eachairportstruct->longitude=stold(tokens[7]);
                  structvector.push_back(eachairportstruct);
              }

              tokens.clear();
        }

  // this loop terminates as user enters negative value
	while(flag)
    {
        // user input prompt
        cout<<"\nEnter the airport ICAO name and radius to look for"<<endl;
        getline(cin,userinput);
        stringstream parse_userinput(userinput);
        parse_userinput>>user_ICAO;
        parse_userinput>>user_radius;
        //converting string radius to long double for calculations
        long double radius_comp= stold(user_radius);

        if(radius_comp<0)
        {
            flag=false;
        }
        // for ICAO name standard constraint
        if(user_ICAO.length()==4)
        {
          bool ICAO_found = false;
          // initialization time stops and calculation time begins
          auto stop_init = std::chrono::high_resolution_clock::now();
          auto start_calc = std::chrono::high_resolution_clock::now();
          //variable to store user input airport longitude and latitude la_1,lo_1
          //variable to store comparison airport longitude and latitude la_2,lo_2
    			 long double la_1,lo_1,la_2,lo_2;

           //iteration over the struct vector
              for(auto &it:structvector)
              {
                //stroring user input airport longitude and latitude
                  if((*it).ICAO ==user_ICAO)
                  {
                      la_1 = (*it).latitude;
                      lo_1 = (*it).longitude;
                      ICAO_found=true;
                  }

              }

              if(ICAO_found==true)
              {
                //iteration over struct vector for all calculations
                for(auto &s:structvector)
                {
                  // user input airport is skipped
                    if((*s).ICAO !=user_ICAO)
                    {
                        la_2 = (*s).latitude;
                        lo_2 = (*s).longitude;

                        long double dist = distancebetweentwo(la_1,lo_1,la_2,lo_2);

                        if(dist<=radius_comp)
                        {
                            cout<<(*s).ICAO<<" "<<(*s).Name<<" "<<setprecision(5)<<dist<<endl;
                        }
                      }
                    }
                    //calculation time stops
                    auto  stop_calc = std::chrono::high_resolution_clock::now();
                    //calculating the time difference in microseconds
                  std::chrono::duration<double> init_duration = stop_init - start_init;
                  std::chrono::duration<double> calc_duration = stop_calc - start_calc;

                  //printing the outputs
                  if(radius_comp>0)
                  {
                      cout << "\n"<<init_duration.count()/1000<<"  "<<calc_duration.count()/1000<<" "<<structvector.size()*sizeof(structvector[0])<<endl;
                  }


          }
          else
          {
            cout<<"Input ICAO not found.\n";
          }

              }
              else
              {
                cout<<"Error:Wrong format of ICAO name\n";
              }


      }

          airportFile.close();
          return 0;
}
