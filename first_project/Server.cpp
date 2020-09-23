#include <iostream>
#include <fstream>
#include <windows.h>

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
};

message read_command(int new_size)
{
    ifstream f("f1", ostream::binary | ostream::in);
    f.seekg(new_size, ostream::beg);
    message result;
    f.read((char *)&result, sizeof(result));
    f.close();
    return result;
}

void write_result(cmds data)
{
    ofstream f("f2", ostream::binary | ostream::app);
    f.write((char *)&data, sizeof(data));
    f.close();
}

int lst_size_check()
{
    ifstream f("f1", ostream::binary);
    f.seekg(0, ostream::end);
    return f.tellg();
}

cmds processing(message message)
{
    if (strlen(message.command) < 2 && message.command[0] == '1')
    {
        cout << "greet: ";
        return cmds::greet;
    }
    if (strlen(message.command) < 2 && message.command[0] == '2')
    {
        cout << "admin_msg: ";
        return cmds::admin_msg;
    }
    if (strlen(message.command) < 2 && message.command[0] == '3')
    {
        cout << "date_time: ";
        return cmds::date_time;
    }
    if (strlen(message.command) < 2 && message.command[0] == '4')
    {
        cout << "close_session: ";
        return cmds::close_session;
    }
    return cmds::error;
}

int main()
{

    cout << "Server started!\nThere are the received commands\n";
    while ("connect")
    {
        int new_size = lst_size_check();

        while ("check")
        {
            int newSize = lst_size_check();
            if (newSize > new_size)
                break;
        }

        message message = read_command(new_size);
        cmds result = processing(message);
        cout << message.command << "\n";
        write_result(result);
    }
}