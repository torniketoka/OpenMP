#include <iostream>
#include <chrono>
#include "omp.h"
#include <cmath>
#include <thread>
#include <string>
#include "stdio.h"

using namespace std;
using namespace std::chrono;

const int N = 46080;

unsigned int parallelArray[N][N];
  
// func
unsigned int f1(unsigned int x)
{
unsigned int n=0;
unsigned int k=0;
unsigned int m=1;
for (k+=m; k<=x; k+=m)
{
n=n+1;
m=m+2;
}
return n;
}
  
int main(int argc, char *argv[]){
size_t i, j;

high_resolution_clock::time_point t0;
high_resolution_clock::time_point t1;

parallelArray[0][0] = 0;

  for (i=1; i<N; i++)
  
     for (int j=1; j<N; j++) 
     {
        parallelArray[0][j] = 250;
        parallelArray[i][0] = 150;
     }
  
    
t0 = high_resolution_clock::now();

#pragma omp parallel if (N>500) default(none) num_threads(16) shared(parallelArray) private (i,j)
  {
    for(i = 1; i < N; i++)
     {
         #pragma omp for  
         for(j = 1; j <= i; j++)
         {
            parallelArray[j][i-j+1] = ((f1(parallelArray[j-1][i-j+1-1])+
                                    f1(parallelArray[j][i-j+1-1])+
                                    f1(parallelArray[j-1][i-j+1]))*
                                    f1(parallelArray[j-1][i-j+1-1]+parallelArray[j][i-j+1-1]+parallelArray[j-1][i-j+1]))
                                    % 1000;

           if (parallelArray[j][i-j+1]==0) parallelArray[j][i-j+1]=999;
         }
     }

    for(int i = 2; i < N; i++)
   {
      #pragma omp for
      for(j = N - 1; j >= i; j--)
      {
         parallelArray[N-j+i-1][j] = ((f1(parallelArray[N-j+i-1-1][j-1])+
                                    f1(parallelArray[N-j+i-1][j-1])+
                                    f1(parallelArray[N-j+i-1-1][j]))*
                                    f1(parallelArray[N-j+i-1-1][j-1]+parallelArray[N-j+i-1][j-1]+parallelArray[N-j+i-1-1][j]))
                                    % 1000;

           if (parallelArray[N-j+i-1][j]==0) parallelArray[N-j+i-1][j]=999;

      }
   }
   
  }
    t1 = high_resolution_clock::now(); 

    // cout << parallelArray[N-1][N-1] << endl;
     cout << " ------------------------------------ " << endl;
     

   cout << " Time : " << duration_cast<milliseconds>(t1-t0).count() << " ms" << endl;
  

  if(argc >= 2)
  {
    cout << "Results: ";
    cout << "array: " << parallelArray[atoi(argv[1])][atoi(argv[2])] << " ";
    cout << "array: " << parallelArray[atoi(argv[3])][atoi(argv[4])] << " ";
    cout << "array: " << parallelArray[atoi(argv[5])][atoi(argv[6])] << endl;
  }
     return 0;
}