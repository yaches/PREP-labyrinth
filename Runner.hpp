//
// Created by tsv on 09.05.16.
//

#ifndef LABYRINTH_RUNNER_HPP
#define LABYRINTH_RUNNER_HPP

#include <cstdlib>
#include <iostream>

#include "RunnerBase.hpp"

using namespace std;

class Runner: public RunnerBase {
    public:
        Direction step();
        void photo();
        void resize_map();
        void draw();

        struct Point
        {
        	int x;
        	int y;
        	bool fog;
            bool was_here;
            bool was_here_again;
            bool crossway;
            bool wall;
        };

        int map_size = 1;
        int min_crd = 0;
        int max_crd = 0;
        Point** map = NULL;
        Point position {0, 0, 1, 1, 0, 0, 0};
};


#endif //LABYRINTH_RUNNER_HPP
