#include <iostream>
#include <vector>
#include <array>
#include <chrono>
#include <random>

using namespace std;

// Globals:
unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();

  // obtain a seed from the user:

std::mt19937_64 g1 (seed1);  // mt19937 is a standard mersenne_twister_engine

std::array<double,4> intervals {-2.0, -1.0, 1.0, 2.0};
std::array<double,3> weights {1, 0, 1};
std::piecewise_constant_distribution<double>
     d (intervals.begin(),intervals.end(),weights.begin());

std::normal_distribution<double>   nd (0,1);
std::bernoulli_distribution bd(0.05);


void generateOuter(int n, vector<double>& outer){

   for(int i = 0;i < n; i++)
      outer.push_back( d(g1) );


}

bool transferIsValid(vector<double>& outer, vector<double>& inner){

  return true;

}


bool isDead(vector<double>& inner){

  return bd(g1);

}


void timeStep(double dt, double vOuter, double vInner, vector<double>& outer, vector<double>& inner){

    // update outers:
    for(int i = 0;i < outer.size(); i++){
       double old = outer[i];
       outer[i] += nd(g1) * sqrt(dt) * vOuter;
       if (outer[i] < -2.0)
          outer[i] = 4 + outer[i];
       else if (outer[i] > 2.0)
          outer[i] = -4 +  outer[i];
       else if ((outer[i] > -1) && (outer[i] < 1)){
          if(transferIsValid(outer,inner)){
             inner.push_back(outer[i]);
             outer.erase(outer.begin()+i);
             outer.push_back( d(g1) );
          } else outer[i] = old;
       }
     }

    // update inners:


    for(int i = 0;i < inner.size(); i++){

       if( isDead(inner)) {
         inner.erase(inner.begin()+i);
       }
       else {
         double old = inner[i];
         inner[i] += nd(g1) * sqrt(dt) * vInner;

         if ( (inner[i] > 1.0) || (inner[i] < -1.0))
          inner[i] = old;
       }
     }


}




int main(){

   double a=-1, b=1;
   double A=a-1, B=b+1;
   vector<double> outer;
   vector<double> inner;
   double T=1;
   double dt = T/1000;
   double vInner=0.1;
   double vOuter=0.1;
   

   int N = 10000;
   generateOuter(N, outer);
   
   int maxI = 0;
   int minI = N;
   for(double t=0; t<=T;t+=dt)   {
   
      timeStep(dt,  vOuter,  vInner,  outer,  inner);
      if(maxI < inner.size()) maxI = inner.size();
      if(minI > inner.size()) minI = inner.size();
      
   
   }

   cout << minI << " <-> " << maxI << endl;
    
  return 0;
}
