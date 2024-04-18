#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

// Add your implementation of schedule() and other helper functions here

bool scheduleHelper(const size_t workNeed, std::vector<size_t>& when, size_t m, const AvailabilityMatrix& available, const size_t total, DailySchedule& sched) {
    if (m == available.size()) {
        return true;
    }

    for (Worker_T worker = 0; worker < available[m].size(); ++worker) {
        if (limit(available, when, m, worker, total)) {
            if (!scheduled(sched[m], worker)) { 
                
                sched[m].push_back(worker); 
                when[worker]++;

                
                if (fully(sched, m, workNeed)) {
                    if (scheduleHelper(workNeed, when, m + 1, available, total, sched) == true) {
                        return true;
                    }
                } else {
                   
                    if (scheduleHelper(workNeed, when, m, available, total, sched) == true) {
                        return true;
                    }
                }

                
                sched[m].pop_back();
                when[worker]--;
            }
        }
    }

    return false; // Unable to schedule for this day
}



bool schedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched) {
    if (avail.empty()) {
        return false;
    }
    sched.clear();

      std::vector<size_t> shifts(avail[0].size());
      size_t i = 0;
      while (i < shifts.size()) {
          shifts[i] = 0;
          ++i;
      }


      sched.resize(avail.size());
      for (size_t i = 0; i < sched.size(); ++i) {
          sched[i] = std::vector<Worker_T>();
      }

    return scheduleHelper(dailyNeed, shifts, 0, avail, maxShifts, sched);
   // workNeed, when, m, available, total, sched
}



bool scheduled(const std::vector<Worker_T>& schedule, Worker_T worker) {
    for (Worker_T scheduledWorker : schedule) {
        if (scheduledWorker == worker) {
            return true; 
        }
    }
    return false;
}



bool limit(const AvailabilityMatrix& available, const std::vector<size_t>& shifts, size_t when, Worker_T worker, size_t total) {
    return available[when][worker] && shifts[worker] < total;
}


bool fully(const DailySchedule& sched, size_t when, size_t needs) {
    return sched[when].size() == needs;
}
