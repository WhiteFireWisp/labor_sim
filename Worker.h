//
// Created by Dario on 1/16/2023.
//

#include <random>
#include "Job.h"

#ifndef LABOR_SIM_WORKER_H
#define LABOR_SIM_WORKER_H

class Worker {
public:
    Worker(std::mt19937 *r, std::vector<Job *> *jl);

    Job* pickJob();
    double findEfficiency(Job * j);

private:
    std::mt19937 * randomEngine;

    Job * job; // Current job

    std::vector<Job*> * jl; // Pointer to job list, stored in economy.
    std::vector<double> efficiency; // How many hours it takes this worker to produce a product
    std::vector<double> desireRatios; // In comparison to the first job, how many hours of each is equivalent to the worker
};


#endif //LABOR_SIM_WORKER_H
