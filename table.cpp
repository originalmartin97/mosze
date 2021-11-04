#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include "table.h"
#include "main.h"


void Table::addRow(int rowToAdd) {
	cellcontainer.resize((getRow() + rowToAdd), std::vector<std::string>(getColumn(), "-"));
	setRow(getRow() + rowToAdd);

}

void Table::addColumn(int columnToAdd) {
	for (int i = 0; i < getRow(); i++) cellcontainer[i].resize((getColumn() + columnToAdd), "-");
	setColumn(getColumn() + columnToAdd);
}

void Table::deleteRow(int rowToDelete) {
	if ((rowToDelete < getRow()) && (rowToDelete >= 0)) {
		cellcontainer.erase(cellcontainer.begin() + rowToDelete);
		setRow(getRow() - 1);
	}
	else {
		incorrect_input();
	}
}

void Table::deleteColumn(int columnToDelete) {
	if ((columnToDelete < getColumn()) && (columnToDelete >= 0)) {
		for (auto& row : cellcontainer) row.erase(next(row.begin(), columnToDelete));
		setColumn(getColumn() - 1);
	}
	else {
		incorrect_input();
	}
}

void Table::r_insert(int rowPosition, int n)
{
	cellcontainer.insert(cellcontainer.begin() + rowPosition, n, std::vector<std::string>(getColumn(), "-"));
	setRow(getRow() + n);
}

void Table::insertRow(int rowPosition, int n, std::string beforafter) {
	if ((rowPosition - 1 < getRow()) && (rowPosition - 1 >= 0)) {
		if (beforafter == "before") {
			rowPosition -= 1;
			r_insert(rowPosition, n);
		}
		else if (beforafter == "after") {
			r_insert(rowPosition, n);
		}
		else { incorrect_input(); }
	}
	else { incorrect_input(); }
}

void Table::c_insert(int columnPosition, int n)
{
	std::string str("-");

	for (int i = 0; i < getRow(); i++) {
		cellcontainer[i].insert(cellcontainer[i].begin() + columnPosition, n, str);
	}
	setColumn(getColumn() + n);
}

void Table::insertColumn(int columnPosition, int n, std::string beforafter) {
	if ((columnPosition <= getColumn()) && (columnPosition >= 0)) {
		if (beforafter == "before") {
			columnPosition -= 1;
			c_insert(columnPosition, n);
		}
		else if (beforafter == "after") {
			c_insert(columnPosition, n);
		}
		else { incorrect_input(); }
	}
	else { incorrect_input(); }
}

void Table::edit(int row, int col, std::string s) {
	if ((row > getRow()) or (col > getColumn())) { incorrect_input(); }
	else if ((row - 1 < 0) or (col - 1 < 0)) { incorrect_input(); }
	else { cellcontainer[row - 1].at(col - 1) = s; }
}

bool Table::isNumber(const std::string& str)
{
	for (char const& c : str) {
		if (std::isdigit(c) == 0) return false;
	}
	return true;
}

void Table::cLines(Table &tmp)
{
	int lines = (tmp.cellcontainer[0].size() + 3);
	for (auto i : tmp.cellcontainer[0])
		lines += i.size();
	for (int i = 0; i < lines; i++)
		std::cout << "-";
	std::cout << std::endl;
}

void Table::visualizer() {
	Table copy;
	copy.cellcontainer = cellcontainer;
	spaces(copy);
	std::cout << " |";
	for (int i = 0; i < getColumn(); i++) {
		std::cout << (char)(i + 65);
		for (int j = 0; j < copy.cellcontainer[0][i].size() - 1; j++) {
			std::cout << " ";
		}
		std::cout << "|";
	}
	std::cout << std::endl;
	cLines(copy);
	int i = 1;
	for (auto vec : copy.cellcontainer) {
		std::cout << i << "|";
		for (auto cell : vec) std::cout << cell << "|";
		std::cout << std::endl;
		cLines(copy);
		i++;
	}
}

int Table::cellSize(int col)
{
	int max = 0;
	for (int i = 0; i < cellcontainer.size(); i++)
	{
		if (cellcontainer[i][col].size() > max)
		{
			max = cellcontainer[i][col].size();
		}
	}
	return max;
}

void Table::spaces(Table &temp)
{
	int space = 0;
	for (int i = 0; i < temp.cellcontainer.size(); i++)
	{
		for (int j = 0; j < temp.cellcontainer[i].size(); j++)
		{
			space = (cellSize(j) - temp.cellcontainer[i][j].size());
			for (int s = 0; s < space; s++)
			{
				temp.cellcontainer[i][j] += " ";
			}
		}
	}
}

void Table::read_file(std::string f_str) {
	std::fstream file;
	std::string line;
	file.open(f_str, std::ios::in);
	setRow(0); // 0, hogy az elejen ne 1x1 alaponkbol kezdjunk
	setColumn(0); // *same*
	if (!file) { incorrect_input(); }
	else {
		// a m�trix el�m�retez�s�re szolg�l
		while (std::getline(file, line))
		{
			std::istringstream iss(line);
			std::string result;
			int cols = 1; // feltetelezzuk hogy nincs ures sorunk
			while (std::getline(iss, result, sep))
			{
				cols++;
			}
			if (getColumn() < cols) { setColumn(cols); }
			setRow(getRow() + 1);
		}
		// a m�trix feltoltesere szolgal a csv filebol valo rekordokkal
		int i = 0;
		int j = 0; // i a sor j az oszlop koordinata
		while (std::getline(file, line))
		{
			std::istringstream iss(line);
			std::string result;
			while (std::getline(iss, result, sep))
			{
				cellcontainer[i][j] = result;
				j += 1;
			}
			i += 1;
		}
	}
	file.close();
}

void Table::out_file(std::string filename, char sep) {
	std::ofstream out(filename);
	for (int i = 0; i < cellcontainer.size(); i++) {
		for (int j = 0; j < cellcontainer[i].size(); j++) {
			out << cellcontainer[i][j];
			if (j != (cellcontainer[i].size() - 1))
				out << sep;
		}
		if (i != (cellcontainer.size() - 1)) { out << '\n'; }
	}
}