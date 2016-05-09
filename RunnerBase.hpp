//
// Created by tsv on 09.05.16.
//

#ifndef LABYRINTH_RUNNER_BASE_HPP
#define LABYRINTH_RUNNER_BASE_HPP

#include "utils.hpp"


class RunnerBase {
    protected:
        Status current_status;

    public:
        void set_current_status(const Status& new_status);
};


#endif //LABYRINTH_RUNNER_BASE_HPP
