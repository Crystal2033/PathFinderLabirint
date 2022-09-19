#pragma once
#include <iostream>
class Stack;

class Cell // ������ � ���������
{
	enum States { WALL = 219, PASS = 32, START = 251, END = 88, TRACE = 249 }; // ��� ������ ��������� �������������� // 32 178
	States state; // ����� ���� ��������, ���� ������
	bool visited = false; // ������� � �������
	
public:
	Cell();
	bool is_wall();
	bool is_pass();
	void set_wall();
	void set_pass();
	bool is_visited();
	void set_visited();
	void unset_visited();
	States get_state(); // ��������, �������� �� ������ ������ ������, ���� ��������
	void set_state(States); // ������������� ��� ������ �������� ����� ���, ���� ������

	void set_trace();
	void set_begin_pos();
	void set_end_pos();
	~Cell();
};

class Labirint
{

private:
	Cell** grid; // ��������� ������� - ���� ���������, ��������� �� ������
	int width;
	int height;

public:
	struct Position
	{
		int X;
		int Y;
	};
	int FindPath(Position begin_path, Position end_path, Stack& stack);
	Labirint(int height, int width); // � ������������ ���������� ��������� ���������
	//void set_position(int i, int j);
	void PrintLabirint();
	void PrintSolveLabirint(Position begin_path, Position end_path, Stack& stack); // ����� ���������� ���� � ��������� �� ��������� �� ������
	int get_width();
	int get_height();
	~Labirint();
	
};

std::ostream& operator<<(std::ostream& cout, Labirint::Position& pos);
bool operator==(const Labirint::Position& l_pos, const Labirint::Position& r_pos);
bool operator!=(const Labirint::Position& l_pos, const Labirint::Position& r_pos);

