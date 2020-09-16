#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

enum cmds {
    greet,
    admin_msg,
    user_msg,
    date_time,
    close_session,
    error
};

struct message {
    char command[100];
};

message readStudent(int new_size) {
    ifstream f("f1", ostream::binary | ostream::in);
    f.seekg(new_size);
    message result;
    f.read((char*)& result, sizeof(result));
    f.close();
    return result;
}

void writeScholarship(cmds data) {
    ofstream f("f2", ostream::binary | ostream::app);
    f.write((char*)& data, sizeof(data));
    f.close();
}

/* void createFiles() {
    ofstream f1("f1", ostream::binary);
    ofstream f2("f2", ostream::binary);
    f1.close();
    f2.close();
} */

int lst_size_check() {
    ifstream f("f1", ostream::binary);
    f.seekg(0, ostream::end);
    return f.tellg();
}

cmds process(message message) {
    if (strlen(message.command) < 2 && message.command[0] == '1')
        return cmds::greet;
    if (strlen(message.command) < 2 && message.command[0] == '2')
        return cmds::admin_msg;
    return cmds::error;
}

int main() {
    cout << "Server started!\n";
    while (true) {
        int new_size = lst_size_check();
        while (true)
        {
            int newSize = lst_size_check();
            if (newSize > new_size)
                break;
        }
        message message = readStudent(new_size);
        cout << message.command << " ";
        cout << endl;
        cmds result = process(message);
        writeScholarship(result);
    }
}