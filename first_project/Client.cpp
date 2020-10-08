#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

const int ID_LENGTH = 10;
char ID[ID_LENGTH];

char alphabet[52] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
						'h', 'i', 'j', 'k', 'l', 'm', 'n',
						'o', 'p', 'q', 'r', 's', 't', 'u',
						'v', 'w', 'x', 'y', 'z', 'A', 'B',
						'C', 'D', 'E', 'F', 'G','H', 'I', 
						'J', 'K', 'L', 'M', 'N','O', 'P',
						'Q', 'R', 'S', 'T', 'U','V', 'W',
						'X', 'Y', 'Z' };

enum cmds
{
	greet,
	admin_msg,
	user_msg,
	date_time,
	close_session,
	error
};

struct message
{
	char command[100];
	char id[ID_LENGTH];
};

void write_cmd(message cmd)
{
	ofstream f("f1", ostream::binary | ostream::app);
	f.write((char*)&cmd, sizeof(cmd));
	f.close();
}

cmds read_answer(int new_size)
{
	ifstream f(ID, ostream::binary | ostream::in);
	f.seekg(new_size, ostream::beg);
	cmds result;
	f.read((char*)&result, sizeof(result));
	f.close();
	return result;
}

int lst_size_check()
{
	ifstream file(ID, ostream::binary | ostream::ate);
	file.seekg(0, ostream::end);
	int file_size = file.tellg();
	file.close();
	return file_size;
}

void write_to_adm()
{
	cout << "Ok, now you can write to admin:\n";
	message message;
	cin.getline(message.command, sizeof(message.command));
	strcpy(message.id, ID);
	int new_size = lst_size_check();
	write_cmd(message);
}

void todays_time_date()
{
	time_t now = time(0);
	tm* localtm = localtime(&now);
	cout << "Local date and time: " << asctime(localtm) << endl;
}

void close_ses()
{
	ofstream file(ID, ostream::trunc);
	file.close();
	exit(0);
}

void get_id() {
	srand(char(time(0)));
	for (int i = 0; i < ID_LENGTH - 1; i++)
		ID[i] = alphabet[rand() % 52];
}

int main()
{
	srand(time(0));
	get_id();
	cout << ID << "\n";
	ofstream f(ID);
	f.close();
	cout << "You're in CommandService, Welcome!\n\n";
	cout << "List of command:\n\n 1) Greetings: (1)\n 2) Write to admin: (2)\n 3) Today's date and time: (3)\n 4) Close session: (4)\n";
	message message;
	strcpy_s(message.id, ID);
	while ("connect")
	{
		cout << "\nEnter your command:\n$ ";
		cin.getline(message.command, sizeof(message.command));

		int new_size = lst_size_check();
		write_cmd(message);

		while ("check")
		{
			int newSize = lst_size_check();
			if (newSize > new_size)
				break;
		}

		cmds response = read_answer(new_size);
		switch (response)
		{
		case cmds::greet:
			cout << "Hello user!\n";
			break;
		case cmds::admin_msg:
			write_to_adm();
			break;
		case cmds::error:
			cout << "Undefined command, please try again!\n";
			break;
		case cmds::date_time:
			todays_time_date();
			break;
		case cmds::close_session:
			cout << "See you!\n";
			close_ses();
			break;
		default:
			cout << "Undefined command, please try again!\n";
			break;
		}
	}
	system("pause");
}
