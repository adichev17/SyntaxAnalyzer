#include "analiz.h";

void Analyzer::name_file(string& name_of_file) {
	ifstream in;
	while (1) {
		cout << "������� �������� �����" << endl;
		cin >> name_of_file;
		in.open(name_of_file);
		if (!in) {
			cout << "���� �� ������!" << endl;
			getch();
			system("cls");
		}
		else
			break;
	}
	in.close();
}

void Analyzer::writing_file_to_var() {//��������� �� ����� � �������� text
	ifstream in(name_of_file);
	char c;

	while (in) {
		c = in.get();
		text += c;
	}
	in.close();
}

bool Analyzer::Checking_for_initialization_var(const string& var, const int& count_var) {

	char temp[5] = { ' ', '\n', ';', '{', '}' };

	int index = 0;
	while (text[index] != '\0') {
		int index_2 = index;

		bool flag = find_var(count_var, index_2, var);//����� ����������

		if (flag) {
			index_2 = 1;
			while (text[index - index_2] == ' ') {
				index_2++;//���������� ������� ����� ����������
			}
			//while ((text[index - index_2] != ' ') && (text[index - index_2] != '\n') && (text[index - index_2] != ';') && (text[index - index_2] != '{') && (text[index - index_2] != '}')) {
			//	index_2++;//��������� � ������ ������
			//}

			while (true) {
				bool fl = false;
				for (int temp_count = 0; temp_count < 5; temp_count++) {
					if (text[index - index_2] == temp[temp_count]) {
						fl = true;
					}
				}
				if (!fl) {
					index_2++;
				}
				else { break; false; };
			}

			index_2--;//��������� �� ������ ������ ����

			string types[] = { "int" , "float", "double", "string" };
			int count_types[] = { 3, 5, 6, 6 };
			bool flag_types;
			for (int i = 0; i < 4; i++) {
				flag_types = true;
				for (int j = 0; j < count_types[i]; j++, index_2--) {
					if (text[index - index_2] != types[i][j]) {//���������� ����
						flag_types = false;
						break;
					}
					if (flag_types == false) break;
				}
				if ((flag_types) && (text[index - index_2] != ' ')) return false;//�������� �� ������ ����� int
				if (flag_types) return true;
			}
		}
		index++;
	}
	return false;
}


bool Analyzer::find_var(const int& count_var, int& index_2, const string var) {
	bool flag = true;
	for (int i = 0; i < count_var; i++, index_2++) {//���� ����������
		if (text[index_2] != var[i]) {
			flag = false;
			break;
		}
	}

	if (flag) {
		flag = is_function(index_2);//��������� �� ������� �� ���
	}

	if ((flag) && ((text[index_2 - count_var - 1] != ' ') || ((text[index_2] != ' ') && (text[index_2] != '=') && (text[index_2] != ';')))) {
		flag = false;//�������� ����� � ������ �� ����������
	}

	return flag;
}

bool Analyzer::is_function(int index) {
	while (text[index] == ' ') {//���������� ������� ����� ����������
		index++;
	}
	if (text[index] == '(') {
		return false;
	}
	return true;
}

int Analyzer::main_change(int& count) {

	char temp[5] = { ' ', '\n', ';', '{', '}' };

	bool should_change = true;
	if (!Checking_for_comments(count, should_change)) return 0;//�������� �� ��������
	if (!Checking_for_quotation_marks(count, should_change)) return 0;//�������� �� �������
	int count_var = 0;//���������� �������� ����������
	int count_whitespace = 0;//���������� ��������
	char sign = text[count];

	string var = "\0";
	int i = 1;
	while (text[count - i] == ' ') {//���������� ������� ����� ������
		i++;
		count_whitespace++;
	}
	//while ((text[count - i] != ' ') && (text[count - i] != '\n') && (text[count - i] != ';') && (text[count - i] != '{') && (text[count - i] != '}')) {//���� �� ������ ������
	//	i++;
	//}

	while (true) {
		bool fl = false;
		for (int temp_count = 0; temp_count < 5; temp_count++) {
			if (text[count - i] == temp[temp_count]) {
				fl = true;
			}
		}
		if (!fl) {
			i++;
		}
		else { break; false; }
	}

	i--;//������������ �� ������ ������ ����������
	while ((text[count - i] != ' ') && (text[count - i] != sign)) {//��������� ����� ����������
		var.append(1, text[count - i]);
		count_var++;
		i--;
	}

	bool get_init = Checking_for_initialization_var(var, count_var);//��������� ������������� ����� ����������

	string var2; int count_var2 = 0;
	i = count + 2;
	while (text[i] == ' ') {
		i++;
	}
	while ((text[i] != ' ') && (text[i] != ';')) {//��������� ������ ����������
		var2.append(1, text[i]);
		count_var2++;
		i++;
	}

	bool get_init2 = is_digit(var2);

	if (!get_init2) {
		get_init2 = Checking_for_initialization_var(var2, count_var2);//��������� ������������� ������ ����������
	}

	if ((get_init) && (get_init2)) {
		text[count] = '=';
		text.insert(count + 1, var);
		text[count + count_var + 1] = sign;
		text.erase(count - count_whitespace, count_whitespace);//������� ������� ����� �����

		int count2 = count - count_whitespace;
		count_whitespace = 0;
		int i = 2;
		while (text[count2 + count_var + i] == ' ') {
			count_whitespace++;
			i++;
		}
		text.erase(count2 + count_var + 2, count_whitespace);//������� ������� ������
	}
	else {
		cout << endl << "������: " << endl;
		if (!get_init2)
			cout << "�� ���������������� ���������� " << var2 << endl;
		if (!get_init)
			cout << "�� ���������������� ���������� " << var << endl;
	}

	count_whitespace = 0;
	count_var = 0;
}

bool Analyzer::is_digit(const string& var) {
	char digit[10] = { '0', '1', '2', '3', '4', '5', '6' ,'7', '8', '9' };
	bool flag = false;
	for (int i = 0; i < 10; i++) {
		if (var[0] == digit[i])
			flag = true;
	}
	return flag;
}


void Analyzer::search_key() {

	char temp[6] = { '+', '-', '*', '/', '%', '=' };

	int count = 0;
	//while (text[count] != '\0') {
	//	if (((text[count] == '+') || (text[count] == '-') || (text[count] == '*') || (text[count] == '/') || (text[count] == '%')) && (text[count + 1] == '=')) {
	//		main_change(count);
	//	}
	//	count++;
	//}

	while (text[count] != '\0') {
		for (int temp_count = 0; temp_count < 6; temp_count++) {
			if (text[count] == temp[temp_count] && (text[count + 1] == temp[5])) {
				main_change(count);
			}
		}
		count++;
	}


}

bool Analyzer::Checking_for_quotation_marks(int& count, bool& shouold_change) {
	int i = count;
	int count_quotation_marks = 0;
	while (text[i] != '\n') {//���� ������� �� ���� ������ �����
		if (text[i] == '"') {
			count_quotation_marks++;
			break;
		}
		i--;
	}
	i = count;
	while (text[i] != '\n') { //���� ������� �� ���� ������ ������
		if (text[i] == '"') {
			count_quotation_marks++;
			break;
		}
		i++;
	}
	if (count_quotation_marks >= 2) return false;
	return true;
}

bool Analyzer::Checking_for_comments(int& count, bool& should_change) {
	int i = count;
	while (text[i] != '\n') { //���� "//" ����� �� ���� ������
		if ((text[i] == '/') && (text[i - 1] == '/')) {
			return false;
		}
		i--;
	}
	return true;
}

void Analyzer::end_of_work() {
	//text.pop_back();
	print_text();
	//writing_to_a_file();
	getch();
}

void Analyzer::print_text() {
	cout << endl << "������������ ���: " << endl;
	cout << text << endl;
}

void Analyzer::writing_to_a_file() {
	ofstream out;
	out.open(name_of_file, ios_base::trunc);
	if (!out) {
		cout << "���� � ����� �� ����� ���� ���������!" << endl;
		getch();
		exit(1);
	}
	out << text;
	out.close();
}