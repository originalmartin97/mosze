#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Table {
private:
	std::vector<std::vector<std::string>> cellcontainer;
	int row;
	int column;
	char sep = ';';

public:
	Table() : row(1), column(1) {
		cellcontainer.push_back(std::vector<std::string>());
		cellcontainer[0].push_back("-");
	}
	void setSep(char charToSet) { sep = charToSet; }
	char getSep() { return sep; }
	int getRow() { return row; }
	int getColumn() { return column; }
	void setRow(int rowToSet) { row = rowToSet; }
	void setColumn(int columnToSet) { column = columnToSet; }
	void addRow(int rowToAdd);
	void addColumn(int columnToAdd);
	void deleteRow(int rowToDelete);
	void deleteColumn(int columnToDelete);
	void insertRow(int rowPosition, int n, std::string beforafter);
	void r_insert(int rowPosition, int n);
	void c_insert(int columnPosition, int n);
	void insertColumn(int columnPosition, int n, std::string beforafter);
	void visualizer();
	void read_file(std::string f_string);
	bool isNumber(const std::string& str);
	void edit(int row, int col, std::string s);
	int cellSize(int col);
	void spaces(Table &temp);
	void cLines(Table &tmp);
	void out_file(std::string filename, char sep);
};