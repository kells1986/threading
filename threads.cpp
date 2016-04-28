#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <cmath> 
#include <time.h>
#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif


void prime1(int x) 
{
  for (int j=2; j < x; j++) {
    for (int f = 2; f*f <= j; f++) {
        if (j % f == 0) {
            break;
        }
        else if (f+1 > sqrt(j)) {
            //std::cout << j << " ";
        }
    }   
  }
}

double time_please()
{
  struct timespec ts;

  #ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);
  ts.tv_sec = mts.tv_sec;
  ts.tv_nsec = mts.tv_nsec;

  #else
  clock_gettime(CLOCK_REALTIME, &ts);
  #endif

  return (double)ts.tv_sec + ((double)ts.tv_nsec/1.0e+9);
}


int main() 
{
  

  double start = time_please();

  int large_number1 = 2000000;
  int large_number2 = 2324500;
  std::thread first (prime1, large_number1);     
  std::thread second (prime1, large_number2);  

  first.join();                
  second.join();               
  
  double finish = time_please();
  std::cout << "threads completed in: " << finish - start << std::endl;

  start = time_please();
  prime1(large_number1);
  prime1(large_number2);
  finish = time_please();
  std::cout << "non-threads completed in: " << finish - start << std::endl;

  return 0;
}



