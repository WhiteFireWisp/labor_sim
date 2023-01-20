//
// Created by Dario on 1/16/2023.
//

#include "Economy.h"
#include "truncated_normal.hpp"
#include <limits.h>
#include <iostream>
#include "Job.h"
#include "Worker.h"

Economy::Economy(std::mt19937 *r, int numWorkers, int numJobs) {
    randomEngine = r;

    std::uniform_real_distribution<double> meanEfficiency(MIN_MEAN_EFFICIENCY, MAX_MEAN_EFFICIENCY);
    std::uniform_real_distribution<double> sdEfficiency(MIN_SD_EFFICIENCY, MAX_SD_EFFICIENCY);

    std::uniform_real_distribution<double> meanStrain(MIN_MEAN_STRAIN, MAX_MEAN_STRAIN);
    std::uniform_real_distribution<double> sdStrain(MIN_SD_STRAIN, MAX_SD_STRAIN);

    for (int i = 0; i < numJobs; i++) {
        Job * newJob = new Job(r, meanEfficiency(*randomEngine), sdEfficiency(*randomEngine),
                               meanStrain(*randomEngine), sdStrain(*randomEngine));
        jobList.push_back(newJob);
    }

    for (int i = 0; i < numWorkers; i++) {
        Worker * newWorker = new Worker(randomEngine, &jobList);
        workerList.insert(newWorker);
        newWorker->pickJob();
    }
}

Economy::Economy(std::mt19937 *r, std::string preset) {

}

Economy::Economy(std::mt19937 *r, std::istream preset) {

}

void Economy::cycle() {

}

Economy::~Economy() {

}

std::ostream &operator<<(std::ostream &out, const Economy &e) {
    return std::cout;
}

std::string Economy::serialize() {
    return std::string();
}


