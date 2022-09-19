#pragma once
#include <iostream>
class Stack;

class Cell // Клетка в лабиринте
{
	enum States { WALL = 219, PASS = 32, START = 251, END = 88, TRACE = 249 }; // Для вывода лабиринта псевдографикой // 32 178
	States state; // Может быть проходом, либо стеной
	bool visited = false; // Отметка о проходе
	
public:
	Cell();
	bool is_wall();
	bool is_pass();
	void set_wall();
	void set_pass();
	bool is_visited();
	void set_visited();
	void unset_visited();
	States get_state(); // Проверка, является ли данная клетка стеной, либо проходом
	void set_state(States); // Устанавливает для клетки значение стена это, либо проход

	void set_trace();
	void set_begin_pos();
	void set_end_pos();
	~Cell();
};

class Labirint
{

private:
	Cell** grid; // Двумерная матрица - поле лабиринта, состоящее из клеток
	int width;
	int height;

public:
	struct Position
	{
		int X;
		int Y;
	};
	int FindPath(Position begin_path, Position end_path, Stack& stack);
	Labirint(int height, int width); // В конструкторе происходит генерация лабиринта
	//void set_position(int i, int j);
	void PrintLabirint();
	void PrintSolveLabirint(Position begin_path, Position end_path, Stack& stack); // После нахождения пути в лабиринте он выводится на печать
	int get_width();
	int get_height();
	~Labirint();
	
};

std::ostream& operator<<(std::ostream& cout, Labirint::Position& pos);
bool operator==(const Labirint::Position& l_pos, const Labirint::Position& r_pos);
bool operator!=(const Labirint::Position& l_pos, const Labirint::Position& r_pos);

