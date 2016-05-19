//
// Created by tsv on 09.05.16.
//

#include "Runner.hpp"

Direction Runner::step()
{
	if (current_status.up == BlockType::EXIT)
	{
		return Direction::UP;
	}
	else if (current_status.down == BlockType::EXIT)
	{
		return Direction::DOWN;
	}
	else if (current_status.left == BlockType::EXIT)
	{
		return Direction::LEFT;
	}
	else if (current_status.right == BlockType::EXIT)
	{
		return Direction::RIGHT;
	}

	photo();

	int x_ind = position.x - min_crd;
	int y_ind = position.y - min_crd;

	Point up_point = map[y_ind + 1][x_ind];
	Point down_point = map[y_ind - 1][x_ind];
	Point right_point = map[y_ind][x_ind + 1];
	Point left_point = map[y_ind][x_ind - 1];

	if (!right_point.wall and !right_point.was_here)
	{
		position = map[y_ind][x_ind + 1];
		return Direction::RIGHT;
	}
	if (!down_point.wall and !down_point.was_here)
	{
		position = map[y_ind - 1][x_ind];
		return Direction::DOWN;
	}
	if (!left_point.wall and !left_point.was_here)
	{
		position = map[y_ind][x_ind - 1];
		return Direction::LEFT;
	}
	if (!up_point.wall and !up_point.was_here)
	{
		position = map[y_ind + 1][x_ind];
		return Direction::UP;
	}

	if (!right_point.wall and !right_point.was_here_again)
	{
		position = map[y_ind][x_ind + 1];
		return Direction::RIGHT;
	}
	if (!down_point.wall and !down_point.was_here_again)
	{
		position = map[y_ind - 1][x_ind];
		return Direction::DOWN;
	}
	if (!left_point.wall and !left_point.was_here_again)
	{
		position = map[y_ind][x_ind - 1];
		return Direction::LEFT;
	}
	if (!up_point.wall and !up_point.was_here_again)
	{
		position = map[y_ind + 1][x_ind];
		return Direction::UP;
	}

}

void Runner::photo()
{
	if (map == NULL)
	{
		map = new Point*[map_size];
		for (int i = 0; i < map_size; ++i)
		{
			map[i] = new Point[map_size];
		}
	}

	if (position.x == max_crd or position.y == max_crd or position.x == min_crd or position.y == min_crd)
	{
		resize_map();
	}

	int x_ind = position.x - min_crd;
	int y_ind = position.y - min_crd;

	map[y_ind][x_ind + 1].fog = 0;
	map[y_ind][x_ind - 1].fog = 0;
	map[y_ind + 1][x_ind].fog = 0;
	map[y_ind - 1][x_ind].fog = 0;

	if (current_status.up == BlockType::WALL)
	{
		map[y_ind + 1][x_ind].wall = 1;
	}
	if (current_status.down == BlockType::WALL)
	{
		map[y_ind - 1][x_ind].wall = 1;
	}
	if (current_status.left == BlockType::WALL)
	{
		map[y_ind][x_ind - 1].wall = 1;
	}
	if (current_status.right == BlockType::WALL)
	{
		map[y_ind][x_ind + 1].wall = 1;
	}

	if (position.was_here)
	{
		position.was_here_again = 1;
	}

	position.was_here = 1;
	position.fog = 0;

	int walls = map[y_ind + 1][x_ind].wall + map[y_ind - 1][x_ind].wall \
		+ map[y_ind][x_ind - 1].wall + map[y_ind][x_ind + 1].wall;

	if (walls < 2)
	{
		position.crossway = 1;
		position.was_here_again = 0;
	}

	if (position.crossway)
	{
		position.was_here_again = 0;
	}

	if (walls == 3)
	{
		position.was_here_again = 1;
		position.wall = 1;
	}

	map[y_ind][x_ind] = position;

}

void Runner::resize_map()
{
	int new_size = map_size * 3;
	int new_min = min_crd - map_size;
	int new_max = max_crd + map_size;

	Point** new_map = new Point*[new_size];

	for (int i = 0; i < new_size; ++i)
	{
		new_map[i] = new Point[new_size];
		for (int j = 0; j < new_size; ++j)
		{
			new_map[i][j] = {j + new_min, i + new_min, 1, 0, 0, 0, 0};
		}
	}

	for (int i = 0; i < map_size; ++i)
	{
		for (int j = 0; j < map_size; ++j)
		{
			new_map[i + map_size][j + map_size] = map[i][j];
		}
	}

	for (int i = 0; i < map_size; ++i)
	{
		delete[] map[i];
	}
	delete map;

	map = new_map;
	min_crd = new_min;
	max_crd = new_max;
	map_size = new_size;
}

void Runner::draw()
{
	for (int i = 0; i < map_size; ++i)
	{
		for (int j = 0; j < map_size; ++j)
		{
			// cout << '(' << map[i][j].x << ", " << map[i][j].y << ") ";
			// cout << map[i][j].wall << ' ';
			cout << map[map_size - 1 - i][j].fog << ' ';
		}
		cout << endl;
	}
	cout << endl;
}