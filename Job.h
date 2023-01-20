//
// Created by Dario on 1/16/2023.
//

#include <random>
#include <unordered_set>

#ifndef LABOR_SIM_JOB_H
#define LABOR_SIM_JOB_H

class Worker;

class Job {
public:
    Job(std::mt19937 *r, double meanEfficiency, double sdEfficiency, double meanStrain, double sdStrain);
    Job(std::mt19937 *r, double meanEfficiency, double sdEfficiency, double meanStrain, double sdStrain, double hours);

    double sampleStrain(); // Sample desire
    double sampleEfficiency();

    double averageLaborValue();
    double productQuota();

    void pushWorker(Worker * w);
    void popWorker(Worker * w);

    void setJobHours(double h);
    double getJobHours() const;

private:
    std::mt19937 * randomEngine;

    double meanEfficiency; // Efficiency is how many hours it takes to make one product or do one task cycle
    double sdEfficiency;

    double meanStrain; // ranges from 0 to infinity 0 meaning this job does not strain the worker and high number being a represent an undesired or stressful job
    double sdStrain;

    double jobHours;

    std::unordered_set<Worker*> workerList;
};


#endif //LABOR_SIM_JOB_H
