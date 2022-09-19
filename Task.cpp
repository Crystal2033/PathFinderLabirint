#include "Labirint.h"
#include "Stack.h"
#include "Colours.h"

void get_software_developer_info();

int main(void)
{
	Stack* stack = new Stack;

	Labirint::Position begin;
	Labirint::Position end;

	get_software_developer_info();

	Labirint lab(37, 165); 
	//При динамическом выделении памяти, у нас сначала инициализируется столбец указателей, а потом уже строки.
	//Поэтому сначала пишем рахмер по оси Oy, а потом уже размер Ox. Размер тут - длина.

	std::cout << "Hello it`s a labirint." << std::endl;
	std::cout << "Create labirint. Press \"C\"." << std::endl;
	std::cout << "Solve the labirint. Press \"S\"." << std::endl;
	std::string answer;

	while (true)
	{
		answer.clear();
		std::cin >> answer;
		if (answer.length() > 1)
		{
			std::cout << "You have to choose \"C\" or \"S\"." << std::endl;
		}
		
		if (answer == "c" || answer == "C" )
		{
			lab.PrintLabirint();
			std::cout << "To solve the labirint. Press \"S\"." << std::endl;
			
			continue;
		}

		else if (answer == "s" || answer == "S")
		{
			begin.X = 1;
			begin.Y = 1;

			end.X = 35; // по вертикали (Y) // Первая цифра в размере лабиринта. Высота.
			end.Y = 163; // по горизонтали (X) ОСИ: вниз идет Oy, вправо Ox СТОЛБ - Y, СТРОКА - X. Ширина.

			if (end.X >= lab.get_height() || end.X < 0)
			{
				std::cout << "Your end position(X) is out of labirint`s range." << std::endl;
				return -1;
			}

			if (end.Y >= lab.get_width() || end.Y < 0)
			{
				std::cout << "Your end position(Y) is out of labirint`s range." << std::endl;
				return -1;
			}


			int result = lab.FindPath(begin, end, *stack);
			switch (result)
			{
			case -1:
			{
				std::cout << "Your end position is on the wall." << std::endl;
				return -1;
			}
			case -2:
			{
				std::cout << "Your start position is on the wall." << std::endl;
				return -2;
			}
			case -3:
			{
				std::cout << "Your start position matches with end position" << std::endl;
				return -3;
			}
			default:
				break;
			}
			lab.PrintSolveLabirint(begin, end, *stack);
			break;
		}
		else
		{
			std::cout << "Invalid answer, please, try again." << std::endl;
			continue;
		}
	}

	delete stack;
	return 0;
}

void get_software_developer_info()
{
	std::cout << "Software developer: " << cyan << "Kulikov Pavel, FIIT, M80-111B-20." << white << std::endl;
	return;
}