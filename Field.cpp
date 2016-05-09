//
// Created by tsv on 09.05.16.
//

#include "Field.hpp"


std::istream& operator>>(std::istream& is, Field& field)
{
    size_t rows = 0;
    size_t cols = 0;

    is >> rows >> cols;

    field.field.resize(rows);
    for (auto& row: field.field) {
        row.resize(cols);
    }

    BlockType block_type;

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            is >> block_type;
            field.field[i][j] = block_type;

            if (block_type == BlockType::ENTER) {
                field.current_position = {i, j};
            }
        }
    }

    field.set_runner_current_status();

    return is;
}

std::istream& operator>>(std::istream& is, BlockType& block_type)
{
    int val = 0;
    is >> val;
    block_type = static_cast<BlockType>(val);

    return is;
}

void Field::tic()
{
    ++tic_count;

    Direction direction = runner.step();

    auto i = current_position.x;
    auto j = current_position.y;

    switch (direction) {
        case Direction::UP: {
            --i;
            break;
        }
        case Direction::DOWN: {
            ++i;
            break;
        }
        case Direction::LEFT: {
            --j;
            break;
        }
        case Direction::RIGHT: {
            ++j;
            break;
        }
    }

    auto next_block_type = field[i][j];

    if (next_block_type != BlockType::WALL) {
        current_position = {i, j};
        set_runner_current_status();

        if (next_block_type == BlockType::EXIT) {
            done = true;
        }
    }
}

void Field::set_runner_current_status()
{
    auto i = current_position.x;
    auto j = current_position.y;

    Status status;
    status.up = field[i - 1][j];
    status.down = field[i + 1][j];
    status.left = field[i][j - 1];
    status.right = field[i][j + 1];

    runner.set_current_status(status);
}

bool Field::is_done()
{
    return done;
}

void Field::result(std::ostream& os)
{
    os << "Total steps: " << tic_count << std::endl;
}
