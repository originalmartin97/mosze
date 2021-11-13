#include <iostream>
#include "table.cpp"
#include "table.h"
#include "main.h"

// shell indito: Documents\GitHub\2021-simps\MOSZE\Debug\MOSZE.exe - Martin

//char* argv;
int main(int argc, char** argv)
{
	if (argc == 2) {
		Table* table = new Table;
		std::string command;
		std::vector<std::string> tokens;
		std::string arg_str;
		std::string str2;
		arg_str = argv[1];
		str2 = arg_str.substr(arg_str.length() - 4, arg_str.length());
		std::cout << str2 << std::endl;
		if ((str2) == ".csv") {
			table->read_file(arg_str);
			g2g(argv);
			working_table(command, tokens, table);
		}
		else { incorrect_input(); }
	}
	else if (argc == 4) {
		Table* table = new Table;
		std::string command;
		std::vector<std::string> tokens;
		std::string file_str;
		std::string sep_str;
		file_str = argv[1];
		sep_str = argv[2];
		if ((file_str.substr(file_str.length() - 4, file_str.length() + 1)) == ".csv") {
			if ((sep_str.substr(sep_str.length() - 4, sep_str.length() + 1)) == "-sep") {
				table->setSep(argv[3][0]);
			}
			table->read_file(file_str);
			g2g(argv);
			working_table(command, tokens, table);
		}
		else { incorrect_input(); }
	}
	else {
		g2g(argv);
		newTable();
	}
	return 0;
}

void g2g(char** argv)
{
	std::cout << "Launching: " << argv[0] << std::endl;
	std::cout << "Running..." << std::endl << std::endl;
}

void newTable()
{
	Table* table = new Table;
	std::string command;
	std::vector<std::string> tokens;
	working_table(command, tokens, table);
}

void working_table(std::string& command, std::vector<std::string>& tokens, Table* table)
{
	while (command != "exit") {
		tokens.erase(tokens.begin(), tokens.end()); // secured the tokens erase
		size_t words = 1;
		table->visualizer();
		std::cout << std::endl;
		std::cout << "Commands:" << std::endl;
		std::cout << "add N(int) rows/cols" << std::endl;
		std::cout << "delete X(int) - row" << std::endl;
		std::cout << "delete Y(letter) - column" << std::endl;
		std::cout << "edit XY(cell coordinate(A2)) content" << std::endl;
		std::cout << "insert N rows/cols before/after X/Y" << std::endl;
		std::cout << "save filename.csv [-sep ;]-opcionalis" << std::endl;
		std::cout << "exit" << std::endl << std::endl;
		std::cout << "Command: ";
		getline(std::cin, command);

		if (command.substr(0, 3) == "add") {
			count_words(command, words);
			if (words < 3) { incorrect_input(); }
			else {
				process_command(tokens, words, command);
				if (tokens[1] == "rows") { table->addRow(stoi(tokens[0])); }
				else if (tokens[1] == "cols") { table->addColumn(stoi(tokens[0])); }
				else { incorrect_input(); }
			}
		}
		else if (command.substr(0, 6) == "delete") {
			count_words(command, words);
			if (words < 2) { incorrect_input(); }
			else {
				process_command(tokens, words, command);
				//vegul pedig lowercase-be tesszuk a token elso elemet szamolas miatt
				std::transform(tokens[0].begin(), tokens[0].end(), tokens[0].begin(), tolower);

				if (table->isNumber(tokens[0]) == true) {
					table->deleteRow((stoi(tokens[0])) - 1);
				}
				else {
					if (tokens[0].size() == 1) {
						char c = tokens[0][0];
						int p = c;
						table->deleteColumn(p - 97);
					}
					else { incorrect_input(); }
				}
			}
		}
		else if (command.substr(0, 6) == "insert") {
			count_words(command, words);
			if (words < 5) { incorrect_input(); }
			else {
				process_command(tokens, words, command);
				//vegul pedig lowercase-be tesszuk a token negyedik elemet szamolas miatt
				std::transform(tokens[3].begin(), tokens[3].end(), tokens[3].begin(), tolower);

				if (tokens.at(1).substr(0, 4) == "cols") {
					if (tokens[3].size() == 1) {
						char c = tokens[3][0];
						int p = c;
						table->insertColumn(p - 96, stoi(tokens[0]), tokens[2]);
					}
					else { incorrect_input(); }
				}
				else if (tokens.at(1).substr(0, 4) == "rows") {
					if (table->isNumber(tokens[3]) == true) {
						table->insertRow(stoi(tokens[3]), stoi(tokens[0]), tokens[2]);
					}
					else { incorrect_input(); }
				}
				else { incorrect_input(); }
			}
		}
		else if (command.substr(0, 4) == "edit") {
			count_words(command, words);
			if (words < 3) { incorrect_input(); }
			else {
				//elokeszitunk a pozicioknak valtozokat
				int column;
				int row;
				process_command(tokens, words, command);
				//ha a megadott oszlop karakter merete kisebb lenne mint egy akkor legyen egy ha nem akkor legyen onmaga
				//ehhez ideiglenes valtozot hivunk segitsegul
				int charVal = tokens.at(0).at(0);
				column = (charVal - 96 < 1) ? 1 : charVal - 96;
				// ha a sor pozicioja kisebb lenne mint egy akkor legyen egy ha nem akkor legyen onmaga
				row = (stoi(tokens.at(0).substr(1, tokens.at(0).size() - 1)) < 1) ? 1 : stoi(tokens.at(0).substr(1, tokens.at(0).size() - 1));
				table->edit(row, column, tokens.back());
			}
		}
		else if (command.substr(0, 4) == "save") {
			count_words(command, words);
			if (words < 2) { incorrect_input(); }
			else if (words < 4) {
				process_command(tokens, words, command);
				std::string f_name = tokens[0];
				table->out_file(f_name, ';');
			}
			else if (words == 4) {
				process_command(tokens, words, command);
				std::string cmd = tokens[1];
				if (cmd == "-sep") {
					std::string f_name = tokens[0];
					char n_sep = tokens[2][0];
					table->out_file(f_name, n_sep);
				}
				else { incorrect_input(); }
			}
			else { incorrect_input(); }
		}
		else if (command != "exit") { incorrect_input(); }
	}
}



void incorrect_input()
{
	std::cout << "Hibas parancssor!" << std::endl << std::endl;
}

void count_words(std::string& command, size_t& words)
{
	for (size_t s = command.size(); s > 0; s--) {
		if (command[s] == ' ' && command[s - 1] != ' ')
		{
			words++;
		}
	}
}

void process_command(std::vector<std::string>& tokens, const size_t& words, std::string& command)
{
	if (command.substr(0, 4) == "edit")
	{
		//tokensek kiuritese
		tokens.erase(tokens.begin(), tokens.end());
		//kitoroljuk a commanbol az elozo reszt
		command.erase(0, command.find_first_of(" ") + 1);
		//beletesszuk a tokensekbe a kovetkezo string r�szt amely a cella poziciot megadja karakterenkent
		tokens.push_back(command.substr(0, command.find_first_of(" ")));
		//lowercase-be tesszuk a tokens utolso elemet
		std::transform(tokens.at(0).begin(), tokens.at(0).end(), tokens.at(0).begin(), [](unsigned char c) { return std::tolower(c); });
		//kitoroljuk a commanbol az elozo reszt
		command.erase(0, command.find_first_of(" ") + 1);
		//hozz�adjuk a tokensekhez az utolso reszt
		tokens.push_back(command);
		//kiuritjuk a teljes commandunkat
		command.erase(command.begin(), command.end());
	}
	else
	{
		//uritjuk a tokens vectorunkat
		tokens.erase(tokens.begin(), tokens.end());
		for (int i = words - 1; i > 0; i--)
		{
			if (i == 1) {
				//kitoroljuk a k�vetkezo reszt a commandbol
				command.erase(0, command.find_first_of(" ") + 1);
				//hozz�adjuk a tokensekhez az utolso reszt
				tokens.push_back(command);
				//kiuritjuk a teljes commandunkat
				command.erase(command.begin(), command.end());
			}
			else {
				//kitoroljuk a k�vetkezo reszt a commandbol
				command.erase(0, command.find_first_of(" ") + 1);
				//hozz�adjuk a tokensekhez a kovetkezo reszt
				tokens.push_back(command.substr(0, command.find_first_of(" ")));
			}
		}
	}
}
