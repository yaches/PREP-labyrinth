//
// Created by tsv on 09.05.16.
//

#ifndef LABYRINTH_FIELD_HPP
#define LABYRINTH_FIELD_HPP

#include <vector>
#include <istream>

#include "Runner.hpp"
#include "utils.hpp"


using std::vector;

class Field {
    private:
        struct Position {
            size_t x;
            size_t y;
        };

        size_t tic_count = 0;
        bool done = false;

        vector<vector<BlockType>> field;
        Runner runner;

        Position current_position;

        void set_runner_current_status();

    public:

        friend std::istream& operator>>(std::istream& is, Field& field);

        void tic();
        bool is_done();

        void result(std::ostream& os);
};

std::istream& operator>>(std::istream& is, Field& field);
std::istream& operator>>(std::istream& is, BlockType& block_type);


#endif //LABYRINTH_FIELD_HPP
