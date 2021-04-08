#pragma once
#include <iostream>;
#include <fstream>;
#include <conio.h>;
using namespace std;

class Analyzer {
	string name_of_file, text = "\0";
	void name_file(string& name_of_file);
	void writing_file_to_var();
	void search_key();
	void end_of_work();
	int main_change(int &count);
	bool Checking_for_comments(int& count, bool& should_change);
	bool Checking_for_initialization_var(const string &var, const int& count_var);
	bool Checking_for_quotation_marks(int& count, bool& shouold_change);
	bool find_var(const int& count_var, int& index_2, const string var);
	bool is_digit(const string& var);
	bool is_function(int index);
	void print_text();
	void writing_to_a_file();
public:
	Analyzer() {
		name_file(name_of_file);
		writing_file_to_var();
		search_key();
		end_of_work();
	}

};