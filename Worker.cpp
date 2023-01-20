//
// Created by Dario on 1/16/2023.
//

#include "Worker.h"
#include <algorithm>

Worker::Worker(std::mt19937 *r, std::vector<Job *> *jl) {
    randomEngine = r;

    this->jl = jl;
    job = jl->at(0);
    std::vector<double> strains;
    for (auto & i : *jl) {
        efficiency.push_back(i->sampleEfficiency());
        strains.push_back(i->sampleStrain());
    }

    double referenceDesire = strains[0];
    for (auto  & i : strains) {
        desireRatios.push_back(referenceDesire/i);
    }
}

Job * Worker::pickJob() {
    Job * newJob = nullptr;
    double minEH = 0;
    for (int i = 0; i < jl->size(); i++) {
        double effectiveHours = jl->at(i)->productQuota() * efficiency[i] * desireRatios[i];
        if(effectiveHours > minEH) {
            minEH = effectiveHours;
            newJob = jl->at(i);
        }
    }

    if (newJob != job) {
        if (job != nullptr) job->popWorker(this);
        newJob->pushWorker(this);
    }

    return newJob;
}

double Worker::findEfficiency(Job *j) {
    auto it = std::find(jl->begin(), jl->end(), j) - jl->begin();
    return *(efficiency.begin() + it);
}
