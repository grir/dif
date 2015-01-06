#include <iostream>
#include <chrono>
#include <array>
#include <random>

using namespace std;

int main ()
{
  // obtain a seed from the system clock:
  unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
  
  // obtain a seed from the user:

  std::mt19937_64 g1 (seed1);  // mt19937 is a standard mersenne_twister_engine

  std::array<double,4> intervals {-2.0, -1.0, 1.0, 2.0};
  std::array<double,3> weights {1, 0, 1};
  std::piecewise_constant_distribution<double>
    d (intervals.begin(),intervals.end(),weights.begin());



  normal_distribution<double> d1(0.0,1.0);
  std::cout << "A time seed produced: " << g1() << std::endl;
  cout << g1.min() << " - " << g1.max() << endl;
  for(int i=0;i<100;i++)
     std::cout << d(g1) << std::endl;
  

  return 0;
}
