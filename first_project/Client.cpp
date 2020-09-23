#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

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
    int id;
};

void write_cmd(message cmd)
{
    ofstream f("f1", ostream::binary | ostream::app);
    f.write((char *)&cmd, sizeof(cmd));
    f.close();
}

cmds read_answer(int new_size)
{
    ifstream f("f2", ostream::binary | ostream::in);
    f.seekg(new_size, ostream::beg);
    cmds result;
    f.read((char *)&result, sizeof(result));
    f.close();
    return result;
}

int lst_size_check()
{
    ifstream file("f2", ostream::binary | ostream::ate);
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
    int new_size = lst_size_check();
    write_cmd(message);
}

void todays_time_date()
{
    // Текущие дата/время используемой системы
    time_t now = time(0);
    // Преобразуем в структуру tm для локальной временной зоны
    tm *localtm = localtime(&now);
    cout << "Local date and time: " << asctime(localtm) << endl;
}

void close_ses()
{
    ofstream file("f1", ostream::trunc);
    file.close();
    exit(0);
}

int main()
{
    cout << "You're in CommandService, Welcome!\n\n";
    cout << "List of command:\n\n 1) Greetings: (1)\n 2) Write to admin: (2)\n 3) Today's date and time: (3)\n 4) Close session: (4)\n";
    message message;
    message.id = rand() % 11;

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
        }
    }
<<<<<<< HEAD:Client.cpp
}

=======
    system("pause");
}
>>>>>>> 24c2a38746ccd8d5bd22daeaac630082f669134f:first_project/Client.cpp
