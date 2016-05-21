//
// Created by tsv on 09.05.16.
//

#ifndef LABYRINTH_RUNNER_HPP
#define LABYRINTH_RUNNER_HPP

#include <cstdlib>
#include <iostream>
#include <map>
#include <random>

#include "RunnerBase.hpp"

using namespace std;

class Runner: public RunnerBase {
    public:
        struct Point
        {
            int x;
            int y;
            bool fog;
            bool was_here;
            bool was_here_again;
            bool crossway;
            bool wall;
            Direction step;
        };

        Direction step();
        void photo();
        void resize_map();
        void draw();
        void freeMap();
        void setPriority();
        Direction clockwise(Direction, bool);
        Point getPoint(Direction);
        void printStep(Direction);
        void savePosition(Point);

        Direction prev_step;

        map<Direction, int> cnt = { {Direction::UP, 0}, {Direction::RIGHT, 0}, 
        {Direction::DOWN, 0}, {Direction::LEFT, 0} };

        int map_size = 1;
        int min_crd = 0;
        int max_crd = 0;
        Point** lab_map = NULL;
        Point position {0, 0, 1, 0, 0, 0, 0};
        Direction priority[4] = {Direction::RIGHT, Direction::DOWN, Direction::LEFT, Direction::UP};
        bool go = 0;
};


#endif //LABYRINTH_RUNNER_HPP
