

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool alreadyWorked(
  DailySchedule& sched,
  unsigned int day,
  unsigned int worker,
  const size_t dailyNeed);
bool schedHelper(
  const AvailabilityMatrix& avail,
  const size_t dailyNeed,
  const size_t maxShifts,
  DailySchedule& sched,
  unsigned int row,
  unsigned int col,
  std::vector<unsigned int>& daysWorked
);
bool isComplete(
  const AvailabilityMatrix& avail, 
  const size_t dailyNeed, 
  DailySchedule& sched);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0){
        return false;
    }
    sched.clear();

    for(unsigned int i = 0; i<avail.size(); i++){
      std::vector<Worker_T> schedVect;
      for(unsigned int j = 0; j<dailyNeed; j++){
        schedVect.push_back(INVALID_ID);
      }
      sched.push_back(schedVect);
    }
    // Add your code below
  // std::cout<<"workers: "<<(avail[0]).size()<<std::endl;
  // std::cout<<"days: "<<(avail).size()<<std::endl;
  std::vector<unsigned int> daysWorked;
  for(unsigned int i = 0; i<(avail[0]).size(); i++){
    daysWorked.push_back(0);
  }
  return schedHelper(avail, dailyNeed, maxShifts, sched, 0, 0, daysWorked);

}

bool schedHelper(
  const AvailabilityMatrix& avail,
  const size_t dailyNeed,
  const size_t maxShifts,
  DailySchedule& sched,
  unsigned int row,
  unsigned int col,
  std::vector<unsigned int>& daysWorked
){
  if(col >= dailyNeed){
    col = 0;
    row++;
  }
  if(row == sched.size()){
    return true;
  }
  for(unsigned int i = 0; i<(avail[0]).size(); i++){
    if(avail[row][i] == 1){
      if(!alreadyWorked(sched, row, i, dailyNeed)){
        if(daysWorked[i] < maxShifts){
          sched[row][col] = i;
          daysWorked[i]++;
          bool found = schedHelper(avail, dailyNeed, maxShifts, sched, row, col + 1, daysWorked);
          if(found) return true;
          sched[row][col] = INVALID_ID;
          daysWorked[i]--;
        }
      }
    }
  }
  return false;
}

bool alreadyWorked(
  DailySchedule& sched,
  unsigned int day,
  unsigned int worker,
  const size_t dailyNeed)
{
    for(unsigned int i = 0; i<dailyNeed; i++){
      if(sched[day][i]==worker){
        return true;
      }
    }
    return false;
}

bool isComplete(
  const AvailabilityMatrix& avail, 
  const size_t dailyNeed, 
  DailySchedule& sched)
{
  for(unsigned int i = 0; i < avail.size(); i++){
    for(unsigned int j=0; j<dailyNeed; j++){
      if(sched[i][j]==INVALID_ID){
        return false;
      }
    }
  }
  return true;
}

// bool isValid(
//     const AvailabilityMatrix& avail,
//     const size_t dailyNeed,
//     const size_t maxShifts,
//     DailySchedule& sched){
//       //correct number of workers
//       unsigned int working = 0;
//       for(unsigned int i = 0; i<sched.size(); i++){
//         for(unsigned int j = 0; j<(sched[0]).size(); j++){
//           if(avail[i][j] == 1){
//             working++;
//           }
//         }
//         if(working > dailyNeed){
//           return false;
//         }
//         working = 0;
//       }
//       //correct number of shifts 
//       //sched.size() = number of days
//       //(sched[0]).size() = number of workers
//       unsigned int numShifts = 0;
//       for(unsigned int j = 0; j<(sched[0]).size(); j++){
//         for(unsigned int i = 0; i<sched.size(); i++){
//           if(avail[i][j] == 1){
//             numShifts++;
//           }
//         }
//         if(numShifts > maxShifts){
//           return false;
//         }
//         numShifts = 0;
//       }
//       return true;
// }

