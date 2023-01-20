//
// Created by Dario on 1/16/2023.
//

#include "Job.h"
#include "Worker.h"
#include "truncated_normal.hpp"
#include <limits.h>

Job::Job(std::mt19937 *r, double meanEfficiency, double sdEfficiency, double meanStrain, double sdStrain) {
    randomEngine = r;
    this->meanEfficiency = meanEfficiency;
    this->sdEfficiency = sdEfficiency;
    this->meanStrain = meanStrain;
    this->sdStrain = sdStrain;
    this->jobHours = 35;
}

Job::Job(std::mt19937 *r, double meanEfficiency, double sdEfficiency, double meanStrain, double sdStrain, double hours) {
    randomEngine = r;
    this->meanEfficiency = meanEfficiency;
    this->sdEfficiency = sdEfficiency;
    this->meanStrain = meanStrain;
    this->sdStrain = sdStrain;
    this->jobHours = hours;
}

double Job::sampleStrain() {
    std::uniform_int_distribution<int> seeder(INT_MAX, INT_MIN);
    int seed = seeder(*randomEngine);
    return truncated_normal_a_sample(meanStrain, sdStrain, 0, seed);
}

double Job::sampleEfficiency() {
    std::uniform_int_distribution<int> seeder(INT_MAX, INT_MIN);
    int seed = seeder(*randomEngine);
    return truncated_normal_a_sample(meanEfficiency, sdEfficiency, 0, seed);
}

double Job::averageLaborValue() {
    double sum = 0;
    double count = 0;
    for (auto & i : workerList) {
        sum += i->findEfficiency(this);
        count++;
    }

    return sum/count;
}

void Job::setJobHours(double h) {
    jobHours = h;
}

double Job::getJobHours() const {
    return jobHours;
}

void Job::pushWorker(Worker *w) {
    workerList.insert(w);
}

void Job::popWorker(Worker *w) {
    workerList.erase(w);
}

double Job::productQuota() {
    return getJobHours()/averageLaborValue();
}



