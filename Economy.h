//
// Created by Dario on 1/16/2023.
//

#include <random>
#include <unordered_set>
#include "Job.h"
#include "Worker.h"

#ifndef LABOR_SIM_ECONOMY_H
#define LABOR_SIM_ECONOMY_H

class Economy {
public:
    Economy(std::mt19937 * r, std::string preset);
    Economy(std::mt19937 * r, std::istream preset);
    Economy(std::mt19937 * r, int numWorkers, int numJobs);
    ~Economy();

    void cycle(); // Economy cycle in which hours are rebalanced

    friend std::ostream& operator<<(std::ostream& out, const Economy& e); // Prints economy status
    std::string serialize(); // Outputs a string describing the economy's status

private:
    std::vector<Job*> jobList; // List of jobs
    std::unordered_set<Worker*> workerList; // List of workers
    std::vector<double> requiredProductsPerWorker; // How many products of each job are needed per worker

    std::mt19937 * randomEngine; // Random generator

    constexpr static double MIN_MEAN_EFFICIENCY = 0.03;
    constexpr static double MAX_MEAN_EFFICIENCY = 1.0;

    constexpr static double MIN_SD_EFFICIENCY = 0.03;
    constexpr static double MAX_SD_EFFICIENCY = 0.5;

    constexpr static double MIN_MEAN_STRAIN = 0;
    constexpr static double MAX_MEAN_STRAIN = 2;

    constexpr static double MIN_SD_STRAIN = 0.25;
    constexpr static double MAX_SD_STRAIN = 1;
};


#endif //LABOR_SIM_ECONOMY_H
