//
// Created by tsv on 09.05.16.
//

#include "Runner.hpp"

Direction Runner::step()
{
	go = 0;

	if (current_status.up == BlockType::EXIT)
	{
	// 	cout << " UP " << cnt[Direction::UP];
	// 	cout << " RIGHT " << cnt[Direction::RIGHT];
	// 	cout << " LEFT " << cnt[Direction::LEFT];
	// 	cout << " DOWN " << cnt[Direction::DOWN] << endl;

		freeMap();
		return Direction::UP;
	}
	else if (current_status.down == BlockType::EXIT)
	{
		freeMap();
		return Direction::DOWN;
	}
	else if (current_status.left == BlockType::EXIT)
	{
		freeMap();
		return Direction::LEFT;
	}
	else if (current_status.right == BlockType::EXIT)
	{
		freeMap();
		return Direction::RIGHT;
	}

	if (position.was_here and position.crossway)
	{
		--cnt[position.step];
	}

	if (map_size > 1)
	{
		// setPriority();
	}

	RUN_FASTER(1,3,2,3);

	Direction next_step;
	Point next_position;

	// if (position.crossway and position.was_here and position.step != clockwise(clockwise(prev_step, 0), 0))
	// {
	// 	go = 1;
	// 	next_step = clockwise(clockwise(prev_step, 0), 0);
	// 	next_position = getPoint(next_step);
	// 	next_position.wall = 1;
	// 	savePosition(next_position);

	// 	priority[0] = next_step;
	// 	priority[1] = clockwise(next_step, 1);
	// 	priority[2] = clockwise(next_step, 0);
	// 	priority[3] = prev_step;
	// }

	photo();

	Point some_point;

	for (int i = 0; i < 4; ++i)
	{
		some_point = getPoint(priority[i]);
		if (!some_point.wall and !some_point.was_here and !go)
		{
			next_position = some_point;
			next_step = priority[i];
			go = 1;
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		some_point = getPoint(priority[i]);
		if (!some_point.wall and !go)
		{
			next_position = some_point;
			next_step = priority[i];
		}

	}

	position.step = next_step;
	savePosition(position);

	prev_step = next_step;
	
	if (position.crossway)
	{
		++crosses;
		++cnt[next_step];
	}

	position = next_position;
	++steps;

	// printStep(next_step);
	// getchar();

	return next_step;
}

void Runner::photo()
{
	if (lab_map == NULL)
	{
		lab_map = new Point*[map_size];
		for (int i = 0; i < map_size; ++i)
		{
			lab_map[i] = new Point[map_size];
		}
	}

	if (position.x == max_crd or position.y == max_crd or position.x == min_crd or position.y == min_crd)
	{
		resize_map();
	}

	int x_ind = position.x - min_crd;
	int y_ind = position.y - min_crd;

	lab_map[y_ind][x_ind + 1].fog = 0;
	lab_map[y_ind][x_ind - 1].fog = 0;
	lab_map[y_ind + 1][x_ind].fog = 0;
	lab_map[y_ind - 1][x_ind].fog = 0;

	if (current_status.up == BlockType::WALL)
	{
		lab_map[y_ind + 1][x_ind].wall = 1;
	}
	if (current_status.down == BlockType::WALL)
	{
		lab_map[y_ind - 1][x_ind].wall = 1;
	}
	if (current_status.left == BlockType::WALL)
	{
		lab_map[y_ind][x_ind - 1].wall = 1;
	}
	if (current_status.right == BlockType::WALL)
	{
		lab_map[y_ind][x_ind + 1].wall = 1;
	}

	if (position.was_here)
	{
		position.was_here_again = 1;
	}

	position.was_here = 1;
	position.fog = 0;

	int walls = lab_map[y_ind + 1][x_ind].wall + lab_map[y_ind - 1][x_ind].wall \
		+ lab_map[y_ind][x_ind - 1].wall + lab_map[y_ind][x_ind + 1].wall;

	if (walls < 2)
	{
		position.crossway = 1;
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

	lab_map[y_ind][x_ind] = position;

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
			new_map[i + map_size][j + map_size] = lab_map[i][j];
		}
	}

	for (int i = 0; i < map_size; ++i)
	{
		delete[] lab_map[i];
	}
	delete[] lab_map;

	lab_map = new_map;
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
			cout << lab_map[map_size - 1 - i][j].fog << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void Runner::freeMap()
{
	for (int i = 0; i < map_size; ++i)
	{
		delete[] lab_map[i];
	}
	delete[] lab_map;
}

void Runner::setPriority()
{
	// USE LEFT-HAND RULE

	// priority[0] = clockwise(prev_step, 0);
	// for (int i = 1; i < 4; ++i)
	// {
	// 	priority[i] = clockwise(priority[i - 1], 1);
	// }

	map<Direction, int>::iterator it;
	int i = 0;
	pair<Direction, int> cnt_array[4];

	for (it = cnt.begin(); it != cnt.end(); ++it)
	{
		cnt_array[i++] = *it;
	}

	pair<Direction, int> tmp;

	for (i = 0; i < 4; ++i)
	{
		for (int j = i + 1; j < 4; ++j)
		{
			if (cnt_array[j].second > cnt_array[i].second)
			{
				tmp = cnt_array[i];
				cnt_array[i] = cnt_array[j];
				cnt_array[j] = tmp;
			}
		}
	}

	for (i = 0; i < 4; ++i)
	{
		priority[i] = cnt_array[i].first;
	}

	// priority[0] = prev_step;
	// priority[1] = clockwise(prev_step, 1);
	// priority[2] = clockwise(prev_step, 0);
	// priority[3] = clockwise(clockwise(prev_step, 0), 0);
}

Direction Runner::clockwise(Direction step, bool way)
{
	switch (step)
	{
		case Direction::RIGHT:
			if (way)
				return Direction::DOWN;
			else
				return Direction::UP;
			break;
		case Direction::DOWN:
			if (way)
				return Direction::LEFT;
			else
				return Direction::RIGHT;
			break;
		case Direction::LEFT:
			if (way)
				return Direction::UP;
			else
				return Direction::DOWN;
			break;
		case Direction::UP:
			if (way)
				return Direction::RIGHT;
			else
				return Direction::LEFT;
			break;
	}
}

Runner::Point Runner::getPoint(Direction step)
{
	int x_ind = position.x - min_crd;
	int y_ind = position.y - min_crd;

	switch (step)
	{
		case Direction::RIGHT:
			return lab_map[y_ind][x_ind + 1];
		case Direction::LEFT:
			return lab_map[y_ind][x_ind - 1];
		case Direction::UP:
			return lab_map[y_ind + 1][x_ind];
		case Direction::DOWN:
			return lab_map[y_ind - 1][x_ind];
	}
}

void Runner::printStep(Direction step)
{
	switch (step) 
	{
		case Direction::RIGHT:
			cout << "Right" << endl;
			break;
		case Direction::DOWN:
			cout << "Down" << endl;
			break;
		case Direction::LEFT:
			cout << "Left" << endl;
			break;
		case Direction::UP:
			cout << "Up" << endl;
			break;
	}
}

void Runner::savePosition(Point pos)
{
	int x_ind = pos.x - min_crd;
	int y_ind = pos.y - min_crd;

	lab_map[y_ind][x_ind] = pos;
}

void Runner::RUN_FOREST(int i)
{
	switch (i)
	{
		case 1:
			priority[0] = Direction::RIGHT;
			priority[1] = Direction::LEFT;
			priority[2] = Direction::DOWN;
			priority[3] = Direction::UP;
			break;
		case 2:
			priority[0] = Direction::RIGHT;
			priority[1] = Direction::DOWN;
			priority[2] = Direction::UP;
			priority[3] = Direction::LEFT;
			break;
		case 3:
			priority[0] = Direction::RIGHT;
			priority[1] = Direction::DOWN;
			priority[2] = Direction::LEFT;
			priority[3] = Direction::UP;
			break;
	}
}

void Runner::RUN_FASTER(int q1, int q2, int q3, int q4)
{
	if (steps <= 500000)
		RUN_FOREST(q1);

	if (steps > 500000 and steps <= 1000000 )
		RUN_FOREST(q2);

	if (steps > 1000000 and steps <= 1500000)
		RUN_FOREST(q3);

	if (steps > 1500000)
		RUN_FOREST(q4);
}