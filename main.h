#pragma once

void incorrect_input();

void newTable();

void g2g(char** argv);

void working_table(std::string& command, std::vector<std::string>& tokens, Table* table);

void count_words(std::string& command, size_t& words);

void process_command(std::vector<std::string> & tokens, const size_t & words, std::string & command);
