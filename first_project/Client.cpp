//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include "windows.h"
#include "conio.h"
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

const int ID_LENGTH = 10;
char ID[ID_LENGTH];
char COM[1];

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

void StartMenu(int switcher)
{
    system("cls");
	cout << "\n\t\t You're in CommandService, Welcome!\n\t\t\t  Your ID: " << ID << "\n\n";
    switch (switcher)
    {
    case 1:
        cout << "\n\n\n                   << Greet >>\n\n                      Write to Admin\n\n                      Today's date and time\n\n                      Close session ";
        break;
    case 2:
        cout << "\n\n\n                      Greet\n\n                   << Write to Admin >>\n\n                      Today's date and time\n\n                      Close session ";
        break;
    case 3:
        cout << "\n\n\n                      Greet\n\n                      Write to Admin\n\n                   << Today's date and time >>\n\n                      Close session ";
        break;
    case 4:
        cout << "\n\n\n                      Greet\n\n                      Write to Admin\n\n                      Today's date and time\n\n                   << Close session >>";
        break;
    }

    int choice = _getch();


    if (choice == 224)
        choice = _getch();

    cout << "\n\n\t\t\t\t\t" << choice << endl;

    if (choice == 80)
        if (switcher != 4)
            StartMenu(switcher + 1);
        else
            StartMenu(1);

    if (choice == 72)
        if (switcher != 1)
            StartMenu(switcher - 1);
        else
            StartMenu(4);

    if (choice == 13 || choice == 32)
    {
        if (switcher == 1)
        {
            system("cls");
			strcpy(COM, "1");
        }
        if (switcher == 2)
        {
            system("cls");
			strcpy(COM, "2");
        }
        if (switcher == 3)
        {
            system("cls");
			strcpy(COM, "3");
        }
        if (switcher == 4)
        {
            system("cls");
			strcpy(COM, "4");
        }
    }
}

int main()
{
    system("title Client");//задание описания окна консоли
    system("color 0A");//задание цвета консоли (0-задний фон; А-передний фон)
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);//получение хендла
    CONSOLE_CURSOR_INFO cursor = { 100, false };//число от 1 до 100 размер курсора в процентах; false\true - видимость
    SetConsoleCursorInfo(hCons, &cursor);//применение заданных параметров курсора

	srand(time(0));
	get_id();
	ofstream f(ID);
	f.close();
	while ("connect")
	{
		message message;
		strcpy(message.id, ID);
		StartMenu(1);
		char command[100];
		strcpy(message.command, COM);
		//cin.getline(message.command, sizeof(message.command));

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
			Sleep(2000);
			break;
		case cmds::admin_msg:
			write_to_adm();
			Sleep(2000);
			break;
		case cmds::error:
			cout << "Undefined command, please try again!\n";
			break;
		case cmds::date_time:
			todays_time_date();
			Sleep(2000);
			break;
		case cmds::close_session:
			cout << "See you!\n";
			close_ses();
			Sleep(2000);
			break;
		default:
			cout << "Undefined command, please try again!\n";
			Sleep(2000);
			break;
		}
	}
	system("pause");
}