#include "Labirint.h"
#include "Stack.h"
#include "Colours.h"

Cell::Cell()
{
	return;
}

Cell::~Cell()
{
	return;
}

Cell::States Cell::get_state()
{
	return state;
}

void Cell::set_state(Cell::States state)
{
	this->state = state;
	return;
}

bool Cell::is_wall()
{
	if (state == WALL)
	{
		return true;
	}
	else return false;
}

bool Cell::is_pass()
{
	if (state == PASS)
	{
		return true;
	}
	else return false;
}

void Cell::set_wall()
{
	state = WALL;
	return;
}


void Cell::set_pass()
{
	state = PASS;
	return;
}

void Cell::set_begin_pos()
{
	state = START;
	return;
}
void Cell::set_end_pos()
{
	state = END;
	return;
}

void Cell::set_trace()
{
	state = TRACE;
	return;
}


bool Cell::is_visited()
{
	if (visited)
	{
		return true;
	}
	else return false;
}

void Cell::set_visited()
{
	visited = true;
	return;
}

void Cell::unset_visited()
{
	visited = false;
	return;
}

Labirint::Labirint(int height, int width)
{	
	enum Direction {LEFT, UP, RIGHT, DOWN};
	int direction = -1;
	srand(time(NULL));
	this->width = width;
	this->height = height;

	grid = new Cell * [height];
	for (int i = 0; i < height; i++)
	{
		grid[i] = new Cell[width];
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((i % 2) && (j % 2))
			{
				grid[i][j].set_pass();
			}
			else
			{
				grid[i][j].set_wall();
			}
		}
	}

	

	Position start_pos;
	start_pos.X = 1; // должно быть нечетным.
	start_pos.Y = 1; // должно быть нечетным.
	if (start_pos.X >= width || start_pos.Y >= height) //на случай ошибки выбора начальной позиции.
	{
		std::cout << "Incorrect start pos" << std::endl;
		return;
	}

	Stack stack;
	stack.push(start_pos);
	grid[start_pos.X][start_pos.Y].set_visited(); // неважно, откуда начинать.


	Position current_pos;
	current_pos.X = start_pos.X;
	current_pos.Y = start_pos.Y;
	
	int delta = 2;
	int value_checked_dir;
	//std::cout << direction << std::endl;

	while (!stack.is_empty()) //ќн будет пуст тогда, когда уже нельз€ будет никуда пройти, то есть лабиринт построитс€.
	{
		current_pos = stack.take_top();
		value_checked_dir = 0;
		
		bool up_checked = false;
		bool left_checked = false;
		bool down_checked = false;
		bool right_checked = false;

		while (true) // ѕока все направлени€ не будут просмотрены.
		{ //вниз идет Oy, вправо Ox

			if (value_checked_dir == 4) // если попробовали пойти во все стороны, но не смогли найти подход€щую клетку.
			{
				Position buff; // UNUSED.
				stack.pop(buff);
				break;
			}

			direction = rand() % 4;
			if (direction == LEFT) 
			{
				if (left_checked)
				{
					continue;
				}

				left_checked = true;
				value_checked_dir++;

				if ((current_pos.Y - delta) < 0) // “о есть выход за границу лабиринта.  >= заменить
				{
					continue;
				}
				if (grid[current_pos.X][current_pos.Y - delta].is_visited())
				{
					continue;
				}
				
				
				grid[current_pos.X][current_pos.Y - 1].set_pass();
				current_pos.Y = current_pos.Y - delta;
				grid[current_pos.X][current_pos.Y].set_visited();
				//this->PrintLabirint();
				stack.push(current_pos);
				break;
				
			}
			else if (direction == UP)
			{
				if (up_checked)
				{
					continue;
				}

				up_checked = true;
				value_checked_dir++;

				if ((current_pos.X - delta) < 0) // “о есть выход за границу лабиринта. >= заменить.
				{
					continue;
				}

				if (grid[current_pos.X - delta][current_pos.Y].is_visited())
				{
					continue;
				}

				
				grid[current_pos.X - 1][current_pos.Y].set_pass();
				current_pos.X = current_pos.X - delta;
				grid[current_pos.X][current_pos.Y].set_visited();
				//this->PrintLabirint();
				stack.push(current_pos);
				break;
			}
			else if (direction == RIGHT)
			{
				if (right_checked)
				{
					continue;
				}

				right_checked = true;
				value_checked_dir++;

				if ((current_pos.Y + delta) > (this->width - 1)) // “о есть выход за границу лабиринта. >= заменить
				{
					continue;
				}
				if (grid[current_pos.X][current_pos.Y + delta].is_visited())
				{
					continue;
				}

				
				grid[current_pos.X][current_pos.Y + 1].set_pass();
				current_pos.Y = current_pos.Y + delta;
				grid[current_pos.X][current_pos.Y].set_visited();
				//this->PrintLabirint();
				stack.push(current_pos);
				break;
			}
			else if (direction == DOWN) 
			{
				if (down_checked)
				{
					continue;
				}

				down_checked = true;
				value_checked_dir++;

				if ((current_pos.X + delta) > (this->height - 1)) // “о есть выход за границу лабиринта. >= width заменить
				{
					continue;
				}
				if (grid[current_pos.X + delta][current_pos.Y].is_visited())
				{
					continue;
				}

				
				grid[current_pos.X + 1][current_pos.Y].set_pass();
				current_pos.X = current_pos.X + delta;
				grid[current_pos.X][current_pos.Y].set_visited();
				//this->PrintLabirint();
				stack.push(current_pos);
				break;
			}

		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			grid[i][j].unset_visited();
		}
	}
	return;
}

void Labirint::PrintLabirint()
{
	std::cout << std::endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout << (char)grid[i][j].get_state();
		}
		std::cout << std::endl;
	}

}

void Labirint::PrintSolveLabirint(Position begin_path, Position end_path, Stack& stack)
{
	grid[begin_path.X][begin_path.Y].set_begin_pos();
	grid[end_path.X][end_path.Y].set_end_pos();

	while (!stack.is_empty())
	{
		Position curr_pos;
		stack.pop(curr_pos);
		if (curr_pos == end_path || curr_pos == begin_path)
		{
			continue;
		}
		grid[curr_pos.X][curr_pos.Y].set_trace();
	}

	std::cout << std::endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (grid[i][j].get_state() == 249) //если путь
			{
				std::cout << azure <<(char)4 << white;
				continue;
			}
			else if (grid[i][j].get_state() == 251 || grid[i][j].get_state() == 88) //если начальна€ точка или конечна€
			{
				std::cout << red << (char)219 << white;
				continue;
			}
			std::cout << (char)grid[i][j].get_state();
		}
		std::cout << std::endl;
	}
}

int Labirint::FindPath(Position begin_path, Position end_path, Stack& stack)
{
	enum Direction { LEFT, UP, RIGHT, DOWN };

	if (grid[end_path.X][end_path.Y].is_wall())
	{
		return -1;
	}

	if (grid[begin_path.X][begin_path.Y].is_wall())
	{
		return -2;
	}
	if (begin_path == end_path)
	{
		return -3;
	}

	stack.push(begin_path);
	grid[begin_path.X][begin_path.Y].set_visited();

	Position current_pos;
	current_pos.X = begin_path.X;
	current_pos.Y = begin_path.Y;

	int delta = 1;
	int value_checked_dir;
	//std::cout << direction << std::endl;

	while (stack.take_top() != end_path) //≈сли нашли выход, вываливаемс€.
	{
		int direction = -1;
		current_pos = stack.take_top();
		value_checked_dir = 0;

		bool up_checked = false;
		bool left_checked = false;
		bool down_checked = false;
		bool right_checked = false;

		while (true) // ѕока все направлени€ не будут просмотрены.
		{ //вниз идет Oy, вправо Ox

			if (value_checked_dir == 4) // если попробовали пойти во все стороны, но не смогли найти подход€щую клетку.
			{
				Position buff; // UNUSED.
				stack.pop(buff);
				break;
			}

			direction = rand() % 4;
			if (direction == LEFT)
			{
				if (left_checked)
				{
					continue;
				}

				left_checked = true;
				value_checked_dir++;

				if (grid[current_pos.X][current_pos.Y - delta].is_wall()) // ¬ стенку не можем идти.
				{
					continue;
				}
				if (grid[current_pos.X][current_pos.Y - delta].is_visited()) 
				{
					continue;
				}


				//grid[current_pos.X][current_pos.Y - 1].set_pass();
				current_pos.Y = current_pos.Y - delta;
				grid[current_pos.X][current_pos.Y].set_visited();
				//this->PrintLabirint();
				stack.push(current_pos);
				break;

			}
			else if (direction == UP)
			{
				if (up_checked)
				{
					continue;
				}

				up_checked = true;
				value_checked_dir++;

				if (grid[current_pos.X - delta][current_pos.Y].is_wall()) // ¬ стенку не можем идти.
				{
					continue;
				}

				if (grid[current_pos.X - delta][current_pos.Y].is_visited()) // ¬ стенку не можем идти.
				{
					continue;
				}


				//grid[current_pos.X - 1][current_pos.Y].set_pass();
				current_pos.X = current_pos.X - delta;
				grid[current_pos.X][current_pos.Y].set_visited();
				//this->PrintLabirint();
				stack.push(current_pos);
				break;
			}
			else if (direction == RIGHT)
			{
				if (right_checked)
				{
					continue;
				}

				right_checked = true;
				value_checked_dir++;

				if (grid[current_pos.X][current_pos.Y + delta].is_wall()) // ¬ стенку не можем идти.
				{
					continue;
				}
				if (grid[current_pos.X][current_pos.Y + delta].is_visited())
				{
					continue;
				}


				//grid[current_pos.X][current_pos.Y + 1].set_pass();
				current_pos.Y = current_pos.Y + delta;
				grid[current_pos.X][current_pos.Y].set_visited();
				//this->PrintLabirint();
				stack.push(current_pos);
				break;
			}
			else if (direction == DOWN)
			{
				if (down_checked)
				{
					continue;
				}

				down_checked = true;
				value_checked_dir++;

				if (grid[current_pos.X + delta][current_pos.Y].is_wall()) // ¬ стенку не можем идти.
				{
					continue;
				}
				if (grid[current_pos.X + delta][current_pos.Y].is_visited())
				{
					continue;
				}


				//grid[current_pos.X + 1][current_pos.Y].set_pass();
				current_pos.X = current_pos.X + delta;
				grid[current_pos.X][current_pos.Y].set_visited();
				//this->PrintLabirint();
				stack.push(current_pos);
				break;
			}
		}
	}
	return 0;
}

Labirint::~Labirint()
{
	for (int i = 0; i < height; i++)
	{
		delete[] grid[i];
	}
	delete grid;
}

int Labirint::get_width()
{
	return width;
}
int Labirint::get_height()
{
	return height;
}


std::ostream& operator<<(std::ostream& out, Labirint::Position& pos)
{
	return out << "( " << pos.X << ", " << pos.Y << " )";
}

bool operator==(const Labirint::Position& l_pos, const Labirint::Position& r_pos)
{
	if (l_pos.X == r_pos.X)
	{
		if (l_pos.Y == r_pos.Y)
		{
			return true;
		}
	}
	return false;
}

bool operator!=(const Labirint::Position& l_pos, const Labirint::Position& r_pos)
{
	if (l_pos.X == r_pos.X)
	{
		if (l_pos.Y == r_pos.Y)
		{
			return false;
		}
	}
	return true;
}

