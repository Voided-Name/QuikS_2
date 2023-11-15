#include <algorithm>
#include <cmath>
#include <conio.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <string>

using namespace std;
namespace fs = filesystem;

map<string, vector<double>> data_sets;
map<string, string> variables;

// ASCII Art
const string login_ascii =
    "            ___       ________  ________  ___  ________      \n"
    "           |\\  \\     |\\   __  \\|\\   ____\\|\\  \\|\\   ___  \\    \n"
    "           \\ \\  \\    \\ \\  \\|\\  \\ \\  \\___|\\ \\  \\ \\  \\\\ \\  \\   \n"
    "            \\ \\  \\    \\ \\  \\\\\\  \\ \\  \\  __\\ \\  \\ \\  \\\\ \\  \\  \n"
    "             \\ \\  \\____\\ \\  \\\\\\  \\ \\  \\|\\  \\ \\  \\ \\  \\\\ \\  \\ \n"
    "              \\ \\_______\\ \\_______\\ \\_______\\ \\__\\ \\__\\\\ \\__\\\n"
    "               \\|_______|\\|_______|\\|_______|\\|__|\\|__| \\|__|\n";

const string login_ascii_arrow =
    " ___         ___       ________  ________  ___  ________      \n"
    "|\\  \\       |\\  \\     |\\   __  \\|\\   ____\\|\\  \\|\\   ___  \\    \n"
    "\\ \\  \\      \\ \\  \\    \\ \\  \\|\\  \\ \\  \\___|\\ \\  \\ \\  \\\\ \\  \\   \n"
    " \\ \\  \\      \\ \\  \\    \\ \\  \\\\\\  \\ \\  \\  __\\ \\  \\ \\  \\\\ \\  \\  \n"
    "  \\/  /|      \\ \\  \\____\\ \\  \\\\\\  \\ \\  \\|\\  \\ \\  \\ \\  \\\\ \\  \\ \n"
    "  /  //        \\ \\_______\\ \\_______\\ \\_______\\ \\__\\ \\__\\\\ \\__\\\n"
    " /_ //          \\|_______|\\|_______|\\|_______|\\|__|\\|__| \\|__|\n"

    "|__|/\n";

const string sign_up_ascii_arrow =
    "\n ___          ________  ___  ________  ________           ___  ___  ________   \n"
    "|\\  \\        |\\   ____\\|\\  \\|\\   ____\\|\\   ___  \\        |\\  \\|\\  \\|\\   __  \\  \n"
    "\\ \\  \\       \\ \\  \\___|\\ \\  \\ \\  \\___|\\ \\  \\\\ \\  \\       \\ \\  \\\\\\  \\ \\  \\|\\  \\ \n"
    " \\ \\  \\       \\ \\_____  \\ \\  \\ \\  \\  __\\ \\  \\\\ \\  \\       \\ \\  \\\\\\  \\ \\   ____\\\n"
    "  \\/  /|       \\|____|\\  \\ \\  \\ \\  \\|\\  \\ \\  \\\\ \\  \\       \\ \\  \\\\\\  \\ \\  \\___|\n"
    "  /  //          ____\\_\\  \\ \\__\\ \\_______\\ \\__\\\\ \\__\\       \\ \\_______\\ \\__\\   \n"
    " /_ //          |\\_________\\|__|\\|_______|\\|__| \\|__|        \\|_______|\\|__|   \n"
    "|__|/           \\|_________|                                               \n";

const string sign_up_ascii =
    "             ________  ___  ________  ________           ___  ___  ________   \n"
    "            |\\   ____\\|\\  \\|\\   ____\\|\\   ___  \\        |\\  \\|\\  \\|\\   __  \\  \n"
    "            \\ \\  \\___|\\ \\  \\ \\  \\___|\\ \\  \\\\ \\  \\       \\ \\  \\\\\\  \\ \\  \\|\\  \\ \n"
    "             \\ \\_____  \\ \\  \\ \\  \\  __\\ \\  \\\\ \\  \\       \\ \\  \\\\\\  \\ \\   ____\\\n"
    "              \\|____|\\  \\ \\  \\ \\  \\|\\  \\ \\  \\\\ \\  \\       \\ \\  \\\\\\  \\ \\  \\___|\n"
    "                ____\\_\\  \\ \\__\\ \\_______\\ \\__\\\\ \\__\\       \\ \\_______\\ \\__\\   \n"
    "               |\\_________\\|__|\\|_______|\\|__| \\|__|        \\|_______|\\|__|   \n"
    "               \\|_________|\n";

const string arrow_ascii =
    " ___       "
    "|\\  \\    "
    "\\ \\  \\  "
    " \\ \\  \\ "
    "  \\/  /|  "
    "  /  //    "
    " /_ //     "
    "|__|/      ";

void quiks_header()
{
    cout << "+------------------------------------------------------------------------------------+" << std::endl;
    cout << "|  ________  ___  ___  ___  ___  __    ________           ___      ___  _______      |" << std::endl;
    cout << "| |\\   __  \\|\\  \\|\\  \\|\\  \\|\\  \\|\\  \\ |\\   ____\\         |\\  \\    /  /|/  ___  \\     |" << std::endl;
    cout << "| \\ \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\ \\  \\/  /|\\ \\  \\___|_        \\ \\  \\  /  / /__/|_/  /|    |" << std::endl;
    cout << "|  \\ \\  \\\\\\  \\ \\  \\\\\\  \\ \\  \\ \\   ___  \\ \\_____  \\        \\ \\  \\/  / /|__|//  / /    |" << std::endl;
    cout << "|   \\ \\  \\\\\\  \\ \\  \\\\\\  \\ \\  \\ \\  \\\\ \\  \\|____|\\  \\        \\ \\    / /     /  /_/__   |" << std::endl;
    cout << "|    \\ \\_____  \\ \\_______\\ \\__\\ \\__\\\\ \\__\\____\\_\\  \\        \\ \\__/ /     |\\________\\ |" << std::endl;
    cout << "|     \\|___| \\__\\|_______|\\|__|\\|__| \\|__|\\_________\\        \\|__|/       \\|_______| |" << std::endl;
    cout << "|           \\|__|                        \\|_________|                                |" << std::endl;
    cout << "+------------------------------------------------------------------------------------+" << std::endl;
}

void help()
{
    cout << "\t-- Commands --\n"
         << "\tquit() - exit the program\n"
         << "\t// - comments\n"
         << "\tvars() - Variable View\n"
         << "\tdatas() - Dataset view\n"
         << "\tclear() - Delete calculator history\n"
         << "\t-- Normal Operations --\n"
         << "\tThe calculator view uses FPMDAS (functions -> parentheses -> multiplication/division -> addition/subtraction) order of operations\n"
         << "\t>>> (pow(3,2)/2)+45*(67/3)\n"
         << "\t1009.499985\n"
         << "\t-- Available Functions --\n"
         << "\t\t-- Normal Functions --\n"
         << "\t\tpow\t|\tpow(3, 2)\t|\t9\n"
         << "\t\tsqrt\t|\tsqrt(4)\t\t|\t2\n"
         << "\t\tabs\t|\tabs(-5)\t\t|\t5\n"
         << "\t\tcbrt\t|\tcbrt(8)\t\t|\t2\n"
         << "\t\tcos\t|\tcos(0)\t\t|\t0\n"
         << "\t\tsin\t|\tsin(40)\t\t|\t0.745113\n"
         << "\t\ttan\t|\ttan(30)\t\t|\t-6.405331\n"
         << "\t\tfloor\t|\tfloor(3.5)\t|\t3\n"
         << "\t\tceil\t|\tceil(3.5)\t|\t4\n"
         << "\t\tround\t|\tround(3.32)\t|\t3\n"
         << "\t\ttrunc\t|\ttrunc(4.5)\t|\t4\n"
         << "\t\t-- Dataset Functions --\n"
         << "\t\t - using dataset functions sample | [x].mean\n"
         << "\t\tmean\n\t\tmedian\n\t\tmode\n\t\tstdevp - standard deviation (population)\n\t\tstdevs - standard deviation (sample)\n\t\trange\n\t\tview - show dataset values\n\t\tvarp - variance (population)\n\t\tvars - variance (sample)\n\t\tskewp - skewness (population)\n\t\tskews - skewness (sample)\n\t\tsum\n"
         << "\t\t-- Dataset Pair Functions --\n"
         << "\t\t - using dataset pair functions sample | [x][y].pcoef\n"

         << "\t\tpcoef - Pearson coefficient\n\t\tcovar - covariance\n";
}

// misc
void clear_screen()
{
    system("CLS");
}
bool is_classic_operator(char cha)
{
    if (cha == '+' || cha == '/' || cha == '*' || cha == '-')
    {
        return true;
    }
    return false;
}
bool is_a_z(char inpt)
{
    return (isalpha(inpt));
}
bool is_valid_operator(string op)
{
    string valid_op[12] = {"+", "-", "*", "/", "++", "+-",
                           "--", "-+", "*-", "*+", "/+", " /-"};
    for (int x = 0; x < 12; x++)
    {
        if (op == valid_op[x])
        {
            return true;
        }
    }
    return false;
}
string is_buffer_valid_func(string inpt)
{
    string test[] = {"pow", "sqrt", "abs", "cbrt", "cos", "sin", "tan", "floor", "ceil", "round", "trunc", "mean", "median"};
    for (const auto &x : test)
    {
        if (inpt == x)
        {
            return inpt;
        }
    }
    return "invalid";
}

void enter_to_continue()
{
    int ch;
    while (true)
    {
        cout << endl
             << "Press Enter to Continue...";

        ch = getch();

        if (ch == 13)
        {
            break;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        clear_screen();
        cout << endl;
    }
}
string remove_spaces(string inpt)
{
    string buffer;

    for (const auto &x : inpt)
    {
        if (!isspace(x))
        {
            buffer += x;
        }
    }
    return buffer;
}
string remove_trailing_zeros(string outpt)
{
    int first_trailing, decimal_pos;
    bool found;
    for (int x = 0; x < outpt.length(); x++)
    {
        if (outpt[x] == '.')
        {
            decimal_pos = x;
        }
    }
    for (int x = decimal_pos + 1; x < outpt.length(); x++)
    {
        if (outpt[x] != '0')
        {
            first_trailing = 0;
            found == false;
        }
        else if (found == false)
        {
            if (outpt[x] == '0')
            {
                first_trailing = x;
                found = true;
            }
        }
    }

    if (first_trailing == 0)
    {
        return outpt;
    }
    if (found == true)
    {
        outpt.erase(first_trailing, string::npos);
    }
    if (outpt[outpt.length() - 1] == '.')
    {

        outpt = outpt.substr(0, outpt.length() - 1);
    }
    return outpt;
}
// encryption handling
string encrypt(string password)
{
    string en_password;
    const string KEY = "CICT";
    int y = 0, key_last = KEY.length() - 1;
    int en_char;

    for (int x = 0; x < password.length(); x++)
    {
        int pass_x = password[x];
        int key_y = KEY[y];
        if (pass_x == ' ')
        {
            en_password += ' ';
            y++;
            continue;
        }
        en_char = pass_x + key_y;

        if (en_char > 125)
        {
            en_char = en_char - 125 + 32;
        }

        if (en_char == 59)
        {
            en_char = 126;
        }

        en_password += en_char;
        if (y == key_last)
        {
            y = 0;
        }
        else
        {
            y++;
        }
    }

    return en_password;
}
string decrypt(string password)
{
    string dec_password;
    const string KEY = "CICT";
    int y = 0, key_last = KEY.length() - 1;
    int en_char;

    for (int x = 0; x < password.length(); x++)
    {
        en_char = password[x];
        if (en_char == ' ')
        {
            dec_password += ' ';
            y++;
            continue;
        }

        if (en_char == 126)
        {
            en_char = 59;
        }
        if (en_char < 33 + KEY[y])
        {
            en_char = en_char - 32 + 125 - KEY[y];
        }

        dec_password += en_char;

        if (y == key_last)
        {
            y = 0;
        }
        else
        {
            y++;
        }
    }

    return dec_password;
}
struct password_ret
{
    string password;
    bool proper;
};
string get_password(string name)
{
    name = encrypt(name);
    vector<string> unames, passwords;
    string uname, pw, buffer;
    string path_pw = "pw.txt";
    ifstream pw_get(path_pw);

    while (getline(pw_get, uname, ';'))
    {
        if (uname == name)
        {
            getline(pw_get, pw);
            break;
        }
        else
        {
            getline(pw_get, buffer);
        }
    }

    pw_get.close();
    return pw;
}
password_ret password_reg()
{
    string password;
    password_ret to_ret;
    bool upper_true = false, number_true = false;
    int ch, tries = 0;

    while (true)
    {
        password = "";
        cout << "Password (at least one uppercase letter and one number, don't use "
                "whitespaces): ";
        ch = getch();

        while (ch != 13)
        {
            if (ch == 3)
            {
                abort();
            }
            if (ch == 8)
            {
                if (password.length() > 0)
                {
                    cout << "\b \b";
                    password.pop_back();
                }
                ch = getch();
                continue;
            }
            password.push_back(ch);
            cout << '*';
            ch = getch();
        }

        for (int x = 0; x < password.length(); x++)
        {
            if (password[x] >= 65 && password[x] <= 90)
            {
                upper_true = true;
            }
            if (password[x] >= 48 && password[x] <= 57)
            {
                number_true = true;
            }
        }

        if (upper_true && number_true)
        {
            break;
        }
        cin.clear();
        if (tries == 2)
        {
            to_ret.password = "";
            to_ret.proper = false;
            cout << endl
                 << "Too many failed attempts, going back to main menu...\n";
            enter_to_continue();
            return to_ret;
        }
        cout << endl
             << "Invalid Input! Please Try Again (no uppercase letter and/or no number)" << endl;

        tries++;
    }

    cout << endl;

    to_ret.password = password;
    to_ret.proper = true;
    return to_ret;
}
string menu_loop_reader()
{
    int c;

    c = getch();
    switch (c)
    {
    case 224:
        c = getch();
        switch (c)
        {
        case 72:
            return "UP";
        case 80:
            return "DOWN";
        }
        break;
    case 13:
        return "ENTER";
    case 3:
        abort();
    case 97:
        return "add";
    case 100:
        return "delete";
    case 113:
        return "quit";
    case 109:
        return "mkdir";
    case 117:
        return "update";
    default:
        return "please_warning";
    }
    return "INVALID";
}
vector<vector<string>> get_dir_files_names(vector<string> filenames)
{
    string buffer, loop_read;
    int dir_index = 0;
    vector<vector<string>> dir_files;
    vector<string> dir, file, to_check;

    for (int x = 0; x < filenames.size(); x++)
    {
        buffer = filenames[x];
        if (buffer[0] == 'f')
        {
            file.push_back(buffer);
        }
        else
        {
            dir.push_back(buffer);
        }
    }

    dir_files.push_back(dir);
    dir_files.push_back(file);
    return dir_files;
}
vector<string> scan_users()
{
    vector<string> filenames;
    fs::path p = fs::current_path() / "files";
    for (const auto &entry : fs::directory_iterator(p))
    {
        filenames.push_back(entry.path().string().substr(p.string().length() + 1));
    }

    return filenames;
}
vector<string> scan_files(string username)
{
    fs::path p = fs::current_path();
    vector<string> filenames;

    p = p / "files/" / username;

    for (const auto &entry : fs::directory_iterator(p))
    {
        filenames.push_back(entry.path().string().substr(p.string().length() + 1));
    }

    return filenames;
}

// main functions
void regform()
{
    vector<string> users;
    users = scan_users();
    string name, password, password_2, border_name, border_pass;
    bool has_space = false, username_exists, password_bool;
    password_ret password_buffer;

    do
    {
        has_space = false;
        username_exists = false;

        cout << "type quit() to exit\n\n";
        cout << "Input Username: ";
        getline(cin, name);

        clear_screen();

        for (int x = 0; x < name.length(); x++)
        {
            if (name[x] == ' ')
            {
                cout << "Don't Include Whitespaces!" << endl;
                has_space = true;
                break;
            }
        }
        for (int x = 0; x < users.size(); x++)
        {
            if (name == users[x])
            {
                username_exists = true;
                cout << "Username is already used! Please use a different username..."
                     << endl;
            }
        }
        if (name == "quit()")
        {
            return;
        }
    } while (has_space || username_exists);

    border_name.assign(name.length() + 13, '-');

    cout << "+" << border_name << "+\n";
    cout << "| Username: " + name << "  |\n";
    cout << "+" << border_name << "+\n";

    password_buffer = password_reg();

    password = password_buffer.password;
    password_bool = password_buffer.proper;

    if (!password_bool)
    {
        return;
    }

    cout << "Confirm ";

    password_buffer = password_reg();
    password_2 = password_buffer.password;
    password_bool = password_buffer.proper;

    if (password != password_2)
    {
        cout << "Password does not match!\n";
        enter_to_continue();
        return;
    }

    cout << "\nRegistered " << name << "\n";

    ofstream pw_file("pw.txt", ofstream::app);
    pw_file << encrypt(name) << ";" << encrypt(password) << endl;
    name = "files/" + name;
    fs::create_directory(name);
    pw_file.close();

    enter_to_continue();
}
struct login_struct
{
    string name;
    bool loggedin;
};
login_struct loginform()
{
    vector<string> users;
    users = scan_users();
    string name, password;
    bool username_exists, password_bool;
    password_ret password_buffer;
    login_struct is_user_logged;

    do
    {
        username_exists = false;
        cout << "type quit() to exit\n\n";
        cout << "Input Username: ";
        getline(cin, name);

        if (name == "quit()")
        {
            is_user_logged.loggedin = false;
            return is_user_logged;
        }

        password_buffer = password_reg();
        password = password_buffer.password;
        password_bool = password_buffer.proper;
        if (!password_bool)
        {
            is_user_logged.loggedin = false;
            return is_user_logged;
        }

        for (int x = 0; x < users.size(); x++)
        {
            if (name == users[x])
            {
                username_exists = true;
            }
        }

        if (username_exists == false)
        {
            cout << "Invalid Username or Password";
            enter_to_continue();
            clear_screen();
        }
    } while (!username_exists);

    if (encrypt(password) != get_password(name))
    {
        cout << "Invalid Username or Password";
        enter_to_continue();
        is_user_logged.loggedin = false;
        return is_user_logged;
    }
    cout << "Logged In";

    is_user_logged.name = name;
    is_user_logged.loggedin = true;

    enter_to_continue();
    clear_screen();

    return is_user_logged;
}
void scan_datasets(fs::path p)
{
    string dataset_name, data_value_str, buffer;
    vector<double> dataset_values;
    ifstream datasets(p);
    bool valid = true;
    if (datasets.is_open())
    {
        dataset_name = "";
        while (getline(datasets, dataset_name, '='))
        {
            dataset_name = remove_spaces(dataset_name);
            getline(datasets, data_value_str);
            {
                data_value_str = remove_spaces(data_value_str);
                for (int x = 0; x < data_value_str.size(); x++)
                {
                    if (data_value_str[x] == ',')
                    {
                        try
                        {
                            dataset_values.push_back(stold(buffer));
                            buffer = "";
                        }
                        catch (...)
                        {
                            cerr << "Invalid dataset information detected ";
                            valid = false;
                        }
                    }
                    else
                    {
                        buffer += data_value_str[x];
                    }
                }
                try
                {
                    dataset_values.push_back(stold(buffer));
                    buffer = "";
                }
                catch (...)
                {
                    cerr << "Invalid dataset information detected ";
                    valid = false;
                }
                if (valid)
                {

                    data_sets.insert({dataset_name, dataset_values});
                }
                valid = true;
                dataset_values.clear();
            }
        }
    }

    datasets.close();
}
void scan_variables(fs::path p)
{
    ifstream variables_file(p);
    string variable_name, variable_value;

    if (variables_file.is_open())
    {
        while (getline(variables_file, variable_name, '='))
        {
            getline(variables_file, variable_value);
            variables.insert({remove_spaces(variable_name), remove_spaces(variable_value)});
        }
    }
}

vector<string> get_dataset_keys()
{
    vector<string> dataset_keys;

    for (const auto &key : data_sets)
    {
        dataset_keys.push_back(key.first);
    }

    return dataset_keys;
}
vector<string> get_variables_keys()
{
    vector<string> variable_keys;

    for (const auto &key : variables)
    {
        variable_keys.push_back(key.first);
    }
    return variable_keys;
}
struct eval_ret
{
    string evaluated;
    string error;
};
eval_ret eval(string inpt);
void flush_dataset(fs::path p)
{
    ofstream file(p);

    for (const auto &entry : data_sets)
    {
        file << entry.first << "=";
        for (int x = 0; x < data_sets[entry.first].size(); x++)
        {
            file << data_sets[entry.first][x];
            if (x != data_sets[entry.first].size() - 1)
            {
                file << ",";
            }
        }
        file << "\n";
    }
}
void flush_variables(fs::path p)
{
    ofstream file(p);

    for (const auto &entry : variables)
    {
        file << entry.first << "=" << entry.second << endl;
    }
}
void data_set_update_val(fs::path p, int index, string key)
{
    double val;
    string buffer;

    cout << "Updating " << data_sets[key][index] << ", Enter Value: ";
    getline(cin, buffer);
    try
    {
        val = stold(buffer);
        data_sets[key][index] = val;
    }
    catch (...)
    {
        cout << "Invalid Input\n";
        enter_to_continue();
    }
    flush_dataset(p);
}
void data_set_add_val(fs::path p, int index, string key)
{
    double val;
    string buffer;
    int direction;

    while (direction != 1 && direction != 2)
    {
        cout << "Enter [1] above or [2] below: ";
        cin >> direction;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (direction == 1)
    {
        index--;
    }
    else
    {
        index++;
    }

    if (index < 0)
    {
        index = 0;
    }
    if (index > data_sets[key].size())
    {
        index = data_sets[key].size();
    }
    cout << "Enter Value: ";
    getline(cin, buffer);
    try
    {
        val = stold(buffer);
        data_sets[key].insert(data_sets[key].begin() + index, val);
    }
    catch (...)
    {
        cout << "Invalid Input\n";
        enter_to_continue();
    }
    flush_dataset(p);
}
int data_set_del_val(fs::path p, int index, string key)
{
    double val;
    string buffer;
    char ch;

    cout << "\nPress d again to delete";
    ch = getch();

    if (data_sets[key].size() == 1)
    {
        cout << "\nWarning deleting the last value will delete the data set, Press d again to confirm \n";
        ch = getch();
        if (ch == 'd')
        {
            map<string, vector<double>>::iterator it = data_sets.find(key);
            if (it != data_sets.end())
            {
                data_sets.erase(it);
            }
            flush_dataset(p);
            return 1;
        }
    }
    else if (ch == 'd')
    {
        data_sets[key].erase(data_sets[key].begin() + index);
    }
    flush_dataset(p);
    return 0;
}

void edit_dataset(fs::path p, string dataset)
{
    int arrow = 0, del = 9;
    string arrow_str;

    clear_screen();

    while (true)
    {
        cout << "Data Set: " << dataset << endl;
        scan_datasets(p);
        for (int x = 0; x < data_sets[dataset].size(); x++)
        {
            if (arrow == x)
            {
                cout << ">";
            }
            else
            {
                cout << " ";
            }
            cout << data_sets[dataset][x] << "\n";
        }

        cout << "- 'a' to add a new value\n- 'd' to delete a value\n- 'u' to update a value\n";

        arrow_str = menu_loop_reader();
        if (arrow_str == "UP")
        {
            arrow--;
            if (arrow < 0)
            {
                arrow = 0;
            }
        }
        else if (arrow_str == "DOWN")
        {
            arrow++;
            if (arrow > data_sets[dataset].size() - 1)
            {
                arrow = data_sets[dataset].size() - 1;
            }
        }
        else if (arrow_str == "add")
        {
            data_set_add_val(p, arrow, dataset);
        }
        else if (arrow_str == "delete")
        {
            if (!empty(data_sets[dataset]))
            {
                del = data_set_del_val(p, arrow, dataset);
            }
            if (del == 1)
            {
                return;
            }
        }
        else if (arrow_str == "update")
        {
            data_set_update_val(p, arrow, dataset);
        }
        else if (arrow_str == "quit")
        {
            break;
        }
        clear_screen();
    }
}
void data_view_add(fs::path p)
{
    string inpt, buffer;
    bool not_a_z = false, stold_error = false;
    vector<double> value_vec;
    double value;

    cout << "Enter data set name: ";
    getline(cin, inpt);

    for (int x = 0; x < inpt.length(); x++)
    {
        if (!isalpha(inpt[x]))
        {
            not_a_z = true;
        }
    }

    if (data_sets.find("[" + inpt + "]") != data_sets.end())
    {
        cout << "Data set name already used\n";
        enter_to_continue();
        return;
    }

    cout << "Enter q() to quit\n";
    if (not_a_z)
    {
        cout << "\nInvalid data set name, please only use characters from A-Z, a-z\n ";
        enter_to_continue();
        return;
    }

    while (true)
    {
        cout << "Input Value: ";
        getline(cin, buffer);
        if (buffer == "q()")
        {
            if (value_vec.size() != 0)
            {
                data_sets.insert({"[" + inpt + "]", value_vec});
            }
            flush_dataset(p);
            return;
        }
        try
        {
            value = stold(buffer);
        }
        catch (...)
        {
            cout << "\nInvalid value input!\n";
            stold_error = true;
            continue;
        }
        value_vec.push_back(value);
    }
}
void data_view_del(fs::path p, string key)
{
    char ch;
    cout << "Are you sure you want to delete data set " << key << ", Press d to delete\n";
    ch = getch();

    if (ch == 'd')
    {
        map<string, vector<double>>::iterator it = data_sets.find(key);
        if (it != data_sets.end())
        {
            data_sets.erase(it);
        }
        flush_dataset(p);
    }
}
// main program views
void data_sets_view(fs::path p)
{
    vector<string> dataset_keys;
    string arrow_str;
    int arrow = 0;

    clear_screen();

    while (true)
    {
        cout << "\t===== DATA SETS ===\n";
        scan_datasets(p);
        dataset_keys = get_dataset_keys();
        for (int x = 0; x < dataset_keys.size(); x++)
        {
            if (arrow == x)
            {
                cout << "\t\t>";
            }
            else
            {
                cout << "\t\t";
            }
            cout << dataset_keys[x] << " = ";
            for (int y = 0; y < data_sets[dataset_keys[x]].size(); y++)
            {
                cout << data_sets[dataset_keys[x]][y];
                if (y != data_sets[dataset_keys[x]].size() - 1)
                {
                    cout << ", ";
                }
            }
            cout << "\b\b\b\b\n";
        }
        cout << "\n a - add\n d - delete\n q - quit\n ENTER - update dataset\n";
        arrow_str = menu_loop_reader();
        if (arrow_str == "UP")
        {
            arrow--;
            if (arrow < 0)
            {
                arrow = 0;
            }
        }
        else if (arrow_str == "DOWN")
        {
            arrow++;
            if (arrow > dataset_keys.size() - 1)
            {
                arrow = dataset_keys.size() - 1;
            }
        }
        else if (arrow_str == "ENTER")
        {
            if (!data_sets.empty())
            {
                edit_dataset(p, dataset_keys[arrow]);
            }
        }
        else if (arrow_str == "add")
        {
            data_view_add(p);
        }
        else if (arrow_str == "delete")
        {
            if (dataset_keys.size() != 0)
            {
                data_view_del(p, dataset_keys[arrow]);
            }
        }
        else if (arrow_str == "quit")
        {
            break;
        }
        clear_screen();
    }
}
string variables_analysis(vector<string> buffer, string var_buffer)
{
    vector<string> functions;
    string analyze_buffer;
    for (int x = 0; x < var_buffer.size(); x++)
    {
        if (is_a_z(var_buffer[x]))
        {
            while (is_a_z(var_buffer[x]))
            {
                analyze_buffer += var_buffer[x];
                x++;
            }
            if (var_buffer[x] == '(')
            {
                analyze_buffer = "";
                continue;
            }
            functions.push_back(analyze_buffer);
        }
        analyze_buffer = "";
    }
    if (empty(functions))
    {
        return "valid";
    }
    for (int x = 0; x < buffer.size(); x++)
    {
        for (int y = 0; y < functions.size(); y++)
        {
            if (buffer[x] == functions[y])
            {
                return "ERR006 - Circular equation, an equation is calling itself\n";
            }
            else
            {
                if (variables.find(functions[y]) != variables.end())
                {
                    buffer.push_back(functions[y]);
                    if (variables_analysis(buffer, variables[functions[y]]) != "valid")
                    {
                        return "ERR006 - Circular equation, an equation is calling itself\n";
                    }
                    buffer.pop_back();
                }
            }
        }
    }
    return "valid";
}
void variables_view_add(fs::path p)
{
    string inpt, buffer;
    bool not_a_z = false, stold_error = false;
    string value;

    cout << "Enter variable name: ";
    getline(cin, inpt);

    for (int x = 0; x < inpt.length(); x++)
    {
        if (!isalpha(inpt[x]))
        {
            not_a_z = true;
        }
    }

    if (variables.find(inpt) != variables.end())
    {
        cout << "Variable name is already used\n";
        enter_to_continue();
        return;
    }

    cout << "Enter q() to quit\n";

    if (not_a_z)
    {
        cout << "\nInvalid variable name, please only use characters from A-Z, a-z";
        enter_to_continue();
        return;
    }

    cout << "Input value or equation: ";
    getline(cin, value);
    if (value == "q()")
    {
        return;
    }
    if (variables_analysis({inpt}, value) != "valid")
    {
        cout << "Invalid, function is cyclic, calling itself in a loop\n";
        enter_to_continue();
        return;
    }
    else
    {
        variables.insert({inpt, value});
    }
    flush_variables(p);
}

void variables_view_del(fs::path p, string key)
{
    char ch;
    cout << "Are you sure you want to delete variable " << key << ", Press d to delete\n";
    ch = getch();

    if (ch == 'd')
    {
        map<string, string>::iterator it = variables.find(key);
        if (it != variables.end())
        {
            variables.erase(it);
        }
        flush_variables(p);
    }
}

void variables_view_update(fs::path p, string key)
{
    string buffer, buffer_val;
    char ch;
    bool not_a_z;

    cout << "Updating value of " << key << "\n";

    cout << "Enter q() to quit"
         << "\n\n";

    while (ch != '1' && ch != '2')
    {
        cout << "Update the variable name [1] or the value [2]\n";
        ch = getch();
    }

    if (ch == '1')
    {
        buffer_val = variables[key];

        cout << "Enter the new variable name from " << key << "to: ";
        getline(cin, buffer);

        for (int x = 0; x < buffer.length(); x++)
        {
            if (!isalpha(buffer[x]))
            {
                not_a_z = true;
            }
        }

        if (variables.find(buffer) != variables.end())
        {
            cout << "Variable name is already used\n";
            enter_to_continue();
            return;
        }

        if (not_a_z)
        {
            cout << "\nInvalid variable name, please only use characters from A-Z, a-z";
            enter_to_continue();
            return;
        }

        if (variables_analysis({buffer}, buffer_val) != "valid")
        {
            cout << "Invalid, function is cyclic, calling itself in a loop\n";
            enter_to_continue();
            return;
        }

        map<string, string>::iterator it = variables.find(key);
        if (it != variables.end())
        {
            variables.erase(it);
        }

        variables.insert({buffer, buffer_val});
        flush_variables(p);
    }

    if (ch == '2')
    {
        cout << "Enter new value of " << key << ": ";
        getline(cin, buffer);
        if (buffer == "q()")
        {
            return;
        }
        // input validation
        if (variables_analysis({key}, buffer) != "valid")
        {
            cout << "Invalid, function is cyclic, calling itself in a loop\n";
            enter_to_continue();
            return;
        }

        variables[key] = buffer;
        flush_variables(p);
    }
}
void variables_view(fs::path p)
{
    vector<string> variables_keys;
    string arrow_str;
    int arrow = 0;

    clear_screen();

    while (true)
    {
        cout << "\t===== VARIABLES ===\n";
        scan_variables(p);
        variables_keys = get_variables_keys();
        for (int x = 0; x < variables_keys.size(); x++)
        {
            if (arrow == x)
            {
                cout << "\t\t>";
            }
            else
            {
                cout << "\t\t";
            }
            cout << variables_keys[x] << " = " << variables[variables_keys[x]] << endl;
        }
        cout << "\n a - add\n d - delete\n u - update\n q - quit\n";
        arrow_str = menu_loop_reader();
        if (arrow_str == "UP")
        {
            arrow--;
            if (arrow < 0)
            {
                arrow = 0;
            }
        }
        else if (arrow_str == "DOWN")
        {
            arrow++;
            if (arrow > variables_keys.size() - 1)
            {
                arrow = variables_keys.size() - 1;
            }
        }
        else if (arrow_str == "add")
        {
            variables_view_add(p);
        }
        else if (arrow_str == "delete")
        {

            if (variables_keys.size() != 0)
            {
                variables_view_del(p, variables_keys[arrow]);
                arrow--;
                if (arrow < 0)
                {
                    arrow = 0;
                }
            }
        }
        else if (arrow_str == "update")
        {
            variables_view_update(p, variables_keys[arrow]);
        }
        else if (arrow_str == "quit")
        {
            break;
        }
        clear_screen();
    }
}
void flush_notes(fs::path p, vector<string> note_lines)
{
    ofstream file;
    file.open(p);

    for (const auto &x : note_lines)
    {
        file << x << endl;
    }
    file.close();
}
vector<string> scan_notes(fs::path p)
{

    ifstream file(p);
    vector<string> note_lines;
    string note_line;
    if (file.is_open())
    {
        while (getline(file, note_line))
        {
            note_lines.push_back(note_line);
        }
    }

    file.close();
    return note_lines;
}
void notes_edit(fs::path p, fs::path p_d, fs::path p_v)
{
    ifstream file(p);
    vector<string> note_lines;
    string note_line;
    string arrow_inpt;
    int arrow = 0;

    if (file.is_open())
    {
        while (getline(file, note_line))
        {
            note_lines.push_back(note_line);
        }
    }

    file.close();

    while (true)
    {
        quiks_header();
        for (int x = 0; x < note_lines.size(); x++)
        {
            if (arrow == x)
            {
                cout << "\t\t\t>";
            }
            else
            {
                cout << "\t\t\t ";
            }
            cout << note_lines[x] << endl;
        }

        cout << "\n a -add\n d - delete\n u - update\n q - quit\n";
        arrow_inpt = menu_loop_reader();

        if (arrow_inpt == "UP")
        {
            arrow--;

            if (arrow < 0)
            {
                arrow = 0;
            }
        }
        else if (arrow_inpt == "DOWN")
        {
            arrow++;

            if (arrow == note_lines.size())
            {
                arrow = note_lines.size() - 1;
            }
        }
        else if (arrow_inpt == "add")
        {
            int direction = 3, index_direction;
            string note_instance;

            while (direction != 1 && direction != 2)
            {
                cout << "Enter [1] above or [2] below: ";
                cin >> direction;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout << "Input note instance: ";
            getline(cin, note_instance);

            if (note_instance.substr(0, 2) == "//")
            {
                if (direction == 1)
                {
                    index_direction = arrow - 1;
                    if (index_direction < 0)
                    {
                        index_direction = 0;
                    }
                    note_lines.insert(note_lines.begin() + index_direction, note_instance);
                }
                if (direction == 2)
                {
                    index_direction = arrow + 1;
                    if (index_direction > note_lines.size())
                    {
                        index_direction = note_lines.size();
                    }
                    note_lines.insert(note_lines.begin() + index_direction, note_instance);
                }
            }

            else if (eval(note_instance).evaluated != "(Error)")
            {
                if (direction == 1)
                {
                    index_direction = arrow - 1;
                    if (index_direction < 0)
                    {
                        index_direction = 0;
                    }
                    note_lines.insert(note_lines.begin() + index_direction, note_instance);
                }
                if (direction == 2)
                {
                    index_direction = arrow + 1;
                    if (index_direction > note_lines.size())
                    {
                        index_direction = note_lines.size();
                    }
                    note_lines.insert(note_lines.begin() + index_direction, note_instance);
                }
            }
        }
        else if (arrow_inpt == "delete")
        {
            char ch;
            cout << "Press d to delete, press any key to cancel ";
            ch = getch();

            if (ch == 'd')
            {
                note_lines.erase(note_lines.begin() + arrow);
            }
        }
        else if (arrow_inpt == "update")
        {
            string note_instance;
            cout << "Updating " << note_lines[arrow] << "\n";
            cout << "Input note instance: ";
            getline(cin, note_instance);

            if (note_instance.substr(0, 2) == "//")
            {
                note_lines[arrow] = note_instance;
            }
            else if (eval(note_instance).evaluated != "(Error)")
            {
                note_lines[arrow] = note_instance;
            }
        }
        else if (arrow_inpt == "quit")
        {
            break;
        }
        flush_notes(p, note_lines);
        note_lines = scan_notes(p);
    }
}
void notes_view_view(fs::path p)
{
    string buffer;
    ifstream file(p);

    if (file.is_open())
    {
        while (getline(file, buffer))
        {
            if (buffer.substr(0, 2) == "//")
            {
                cout << buffer << endl;
            }
            else
            {
                cout << eval(buffer).evaluated << endl;
            }
        }
    }
    file.close();
    enter_to_continue();
}
void notes_view(fs::path p, fs::path p_d, fs::path p_v)
{
    vector<string> variables_keys;
    string arrow_str;
    int arrow = 0;

    clear_screen();
    while (true)
    {
        quiks_header();
        switch (arrow)
        {
        case 0:
            cout << "\t\t\t> Edit\n";
            cout << "\t\t\t  View\n";
            break;
        case 1:
            cout << "\t\t\t  Edit\n";
            cout << "\t\t\t> View\n";
        }

        arrow_str = menu_loop_reader();
        clear_screen();
        if (arrow_str == "UP")
        {
            arrow = 0;
        }
        else if (arrow_str == "DOWN")
        {
            arrow = 1;
        }
        else if (arrow_str == "quit")
        {
            break;
        }
        else if (arrow_str == "ENTER")
        {
            if (arrow == 0)
            {
                notes_edit(p, p_d, p_v);
            }
            else if (arrow == 1)
            {
                notes_view_view(p);
            }
        }
    }
}

struct token
{
    string val;
    string type;
    string op_type;
};
vector<vector<token>> get_tokens(string inpt)
{
    inpt = remove_spaces(inpt);
    vector<vector<token>> to_return;
    vector<token> operands;
    vector<token> operators;
    int x = 0, left_par, right_par;
    string buffer, data_buffer;
    token buffer_tok;
    bool neg_1 = false;

    if (inpt[0] == '+' || inpt[0] == '-')
    {
        if (inpt[0] == '-')
        {
            neg_1 = true;
        }
        x++;
    }
    while (x < inpt.length())
    {
        if (isdigit(inpt[x]) || inpt[x] == '.')
        {
            buffer += inpt[x++];
            while (isdigit(inpt[x]) || inpt[x] == '.')
            {
                buffer += inpt[x];
                x++;
                if (x > inpt.length())
                {
                    break;
                }
            }
            x--;
            buffer_tok.val = buffer;
            buffer_tok.type = "double";
            buffer_tok.op_type = "operand";
            operands.push_back(buffer_tok);
            buffer = "";
        }
        else if (is_classic_operator(inpt[x]))
        {
            buffer += inpt[x];
            while (is_classic_operator(inpt[++x]))
            {
                buffer += inpt[x];
                if (x > inpt.length())
                {
                    break;
                }
            }
            x--;
            buffer_tok.val = buffer;
            buffer_tok.type = "classic_operator";
            buffer_tok.op_type = "operator";
            operators.push_back(buffer_tok);
            buffer = "";
        }
        else if (is_a_z(inpt[x]))
        {
            buffer += inpt[x];
            while (is_a_z(inpt[++x]))
            {
                buffer += inpt[x];
                if (x > inpt.length())
                {
                    break;
                }
            }
            if (inpt[x] == '(')
            {
                int par_left = 1, par_right = 0;
                buffer += inpt[x];
                x++;
                while (par_left != par_right)
                {
                    if (inpt[x] == '(')
                    {
                        par_left++;
                    }
                    else if (inpt[x] == ')')
                    {
                        par_right++;
                    }
                    buffer += inpt[x];
                    x++;
                    if (x > inpt.length())
                    {
                        break;
                    }
                }
                x--;
                buffer_tok.val = buffer;
                buffer_tok.type = "function";
                buffer_tok.op_type = "operand";

                operands.push_back(buffer_tok);
                buffer = "";
            }
            else
            {
                x--;
                buffer_tok.val = buffer;
                buffer_tok.type = "variable_call";
                buffer_tok.op_type = "operand";
                operands.push_back(buffer_tok);
                buffer = "";
            }
        }
        else if (inpt[x] == '(')
        {
            left_par = 1;
            right_par = 0;
            while (right_par != left_par)
            {
                x++;
                if (x > inpt.length())
                {
                    break;
                }
                if (inpt[x] == '(')
                {
                    left_par++;
                }
                else if (inpt[x] == ')')
                {
                    right_par++;
                    if (right_par == left_par)
                    {
                        break;
                    }
                }
                buffer += inpt[x];
            }
            x--;
            buffer_tok.val = buffer;
            buffer_tok.type = "parentheses";
            buffer_tok.op_type = "operand";
            operands.push_back(buffer_tok);
            buffer = "";
        }
        else if (inpt[x] == '[')
        {
            string func;
            buffer += inpt[x];
            while (is_a_z(inpt[++x]))
            {
                buffer += inpt[x];
            }
            if (inpt[x] == ']')
            {
                buffer += inpt[x];
                x++;
                if (inpt[x] == '.')
                {
                    buffer += inpt[x];
                    x++;
                    while (is_a_z(inpt[x]))
                    {
                        func += inpt[x];
                        buffer += inpt[x];
                        x++;
                    }
                    buffer_tok.val = buffer;
                    buffer_tok.type = "dataset_function";
                    buffer_tok.op_type = func;
                    operands.push_back(buffer_tok);
                    buffer = "";
                }
                else if (inpt[x] == '[')
                {
                    buffer += inpt[x];
                    x++;
                    while (is_a_z(inpt[x]))
                    {
                        buffer += inpt[x];
                        x++;
                        if (inpt[x] == ']')
                        {
                            buffer += inpt[x];
                            break;
                        }
                    }
                    x++;
                    if (inpt[x] == '.')
                    {
                        buffer += inpt[x];
                        x++;
                        while (is_a_z(inpt[x]))
                        {
                            buffer += inpt[x];
                            x++;
                        }
                        buffer_tok.val = buffer;
                        buffer_tok.type = "dataset_mul_function";
                        buffer_tok.op_type = "operand";
                        operands.push_back(buffer_tok);
                        buffer = "";
                    }
                    else
                    {
                        cout << "Invalid token"
                             << "\n";
                        buffer_tok.val = "invalid_token";
                        buffer_tok.type = "invalid_token";
                        buffer_tok.op_type = "invalid_token";
                        return {{buffer_tok}, {buffer_tok}};
                    }
                }
                else
                {
                    cout << "Invalid token"
                         << "\n";
                    buffer_tok.val = "invalid_token";
                    buffer_tok.type = "invalid_token";
                    buffer_tok.op_type = "invalid_token";
                    return {{buffer_tok}, {buffer_tok}};
                }
                x--;
            }
            else
            {
                cout << "Invalid token" << inpt[x] << "\n";
                buffer_tok.val = "invalid_token";
                buffer_tok.type = "invalid_token";
                buffer_tok.op_type = "invalid_token";
                return {{buffer_tok}, {buffer_tok}};
            };
        }
        buffer = "";
        x++;
    }
    if (neg_1)
    {
        operands[0].val = "-" + operands[0].val;
    }

    to_return.push_back(operators);
    to_return.push_back(operands);
    return to_return;
}
bool valid_data_set_function(string function_name)
{
    bool valid = false;
    string test[] = {"mean", "median", "mode", "stdevp", "stdevs", "range", "view", "varp", "vars", "skewp", "skews", "sum"};
    for (const auto &x : test)
    {
        if (function_name == x)
        {
            return true;
            valid = true;
        }
    }
    return false;
}
bool valid_data_set_mul_function(string function_name)
{
    bool valid = false;
    string test[] = {"pcoef", "covar"};
    for (const auto &x : test)
    {
        if (function_name == x)
        {
            return true;
            valid = true;
        }
    }
    return false;
}

struct token_validation
{
    bool error = false;
    string error_type;
    vector<vector<token>> tokens;
};
struct fn_return
{
    double answer;
    int index;
    string error;
    string special;
    string special_val;
};
fn_return func_eval(string func, string inputs)
{
    vector<string> answer_buffer;
    vector<double> answer_bufferD;
    int par_left = 1, par_right = 0, x = 0;
    fn_return fn_ret;
    int index = 0;
    double answer;

    answer_buffer.push_back("");
    for (int x = 1; x < inputs.size(); x++)
    {
        if (inputs[x] == '(')
        {
            answer_buffer[index] += inputs[x];

            par_left++;
        }
        else if (inputs[x] == ')')
        {
            par_right++;
            if (par_left == par_right)
            {
                break;
            }
            answer_buffer[index] += inputs[x];
        }
        else if (inputs[x] == ',')
        {
            if (par_left > 1 && par_right == par_left - 1)
            {
                index++;
                answer_buffer.push_back("");
            }
            else if (par_left == 1)
            {
                index++;
                answer_buffer.push_back("");
            }
            else
            {
                answer_buffer[index] += inputs[x];
            }
        }
        else
        {
            answer_buffer[index] += inputs[x];
        }
    }

    for (int x = 0; x < answer_buffer.size(); x++)
    {
        eval_ret buffer = eval(answer_buffer[x]);
        if (buffer.evaluated == "(Error)")
        {
            fn_ret.answer = 0;
            fn_ret.error = "ERROR";
            return fn_ret;
        }
        answer_bufferD.push_back(stold(buffer.evaluated));
    }

    if (func == "pow")
    {
        if (answer_buffer.size() != 2)
        {
            cout << "Invalid Number of Inputs for pow, must be two inputs, Ex: pow(3, 2)\n";
            fn_ret.answer = 0;
            fn_ret.index = --x;
            fn_ret.error = "ERR002";
            return fn_ret;
        }

        answer = pow(answer_bufferD[0], answer_bufferD[1]);
    }
    else if (func == "sqrt")
    {
        if (answer_buffer.size() != 1)
        {
            cout << "Invalid number of inputs for sqrt, must be one argument, Ex: sqrt(2)\n";

            fn_ret.answer = 0;
            fn_ret.index = --x;
            fn_ret.error = "ERR002";

            return fn_ret;
        }
        if (answer_bufferD[0] < 0)
        {
            cout << "Invalid input for sqrt, sqrt is unable to process negative numbers\n";

            fn_ret.answer = 0;
            fn_ret.index = --x;
            fn_ret.error = "ERR005";

            return fn_ret;
        }

        answer = sqrt(answer_bufferD[0]);
    }
    else if (func == "abs")
    {
        if (answer_buffer.size() != 1)
        {
            cout << "Invalid number of inputs for abs, must be one argument, Ex: abs(6)\n";
            fn_ret.answer = 0;
            fn_ret.index = --x;
            fn_ret.error = "ERR002";
            return fn_ret;
        }
        if (answer_bufferD[0] < 0)
        {
            answer_buffer[0].erase(0, 1);
            answer = abs(answer_bufferD[0]);
        }
        else
        {
            answer = answer_bufferD[0];
        }
    }
    else if (func == "cbrt")
    {
        if (answer_buffer.size() != 1)
        {
            cout << "Invalid number of inputs for cbrt, must be one argument, Ex: cbrt(2)\n";
            fn_ret.answer = 0;
            fn_ret.index = --x;
            fn_ret.error = "ERR002";
            return fn_ret;
        }
        answer = cbrt(answer_bufferD[0]);
    }
    else if (func == "cos")
    {
        if (answer_buffer.size() != 1)
        {
            cout << "Invalid number of inputs for cos, must be one argument, Ex: cos(2)\n";
            fn_ret.answer = 0;
            fn_ret.index = --x;
            fn_ret.error = "ERR002";
            return fn_ret;
        }
        answer = cos(answer_bufferD[0]);
    }
    else if (func == "sin")
    {
        if (answer_buffer.size() != 1)
        {
            cout << "Invalid number of inputs for sin, must be one argument, Ex: sin(2)\n";
            fn_ret.answer = 0;
            fn_ret.index = --x;
            fn_ret.error = "ERR002";
            return fn_ret;
        }
        answer = sin(answer_bufferD[0]);
    }
    else if (func == "tan")
    {
        if (answer_buffer.size() != 1)
        {
            cout << "Invalid number of inputs for tan, must be one argument, Ex: tan(2)\n";
            fn_ret.answer = 0;
            fn_ret.index = --x;
            fn_ret.error = "ERR002";
            return fn_ret;
        }
        answer = tan(answer_bufferD[0]);
    }
    else if (func == "floor")
    {
        if (answer_buffer.size() != 1)
        {
            cout << "Invalid number of inputs for floor, must be one argument, Ex: floor(2.4)\n";
            fn_ret.answer = 0;
            fn_ret.index = --x;
            fn_ret.error = "ERR002";
            return fn_ret;
        }
        answer = floor(answer_bufferD[0]);
    }
    else if (func == "ceil")
    {
        if (answer_buffer.size() != 1)
        {
            cout << "Invalid number of inputs for ceil, must be one argument, Ex: ceil(2.6)\n";
            fn_ret.answer = 0;
            fn_ret.index = --x;
            fn_ret.error = "ERR002";
            return fn_ret;
        }
        answer = ceil(answer_bufferD[0]);
    }
    else if (func == "round")
    {
        if (answer_buffer.size() != 1)
        {
            cout << "Invalid number of inputs for round, must be one argument, Ex: round(-4.5)\n";
            fn_ret.answer = 0;
            fn_ret.index = --x;
            fn_ret.error = "ERR002";
            return fn_ret;
        }
        answer = round(answer_bufferD[0]);
    }
    else if (func == "trunc")
    {
        if (answer_buffer.size() != 1)
        {
            cout << "Invalid number of inputs for trunc, must be one argument, Ex: trunc(-5.6)\n";
            fn_ret.answer = 0;
            fn_ret.index = --x;
            fn_ret.error = "ERR002";
            return fn_ret;
        }
        answer = trunc(answer_bufferD[0]);
    }
    else if (func == "mean")
    {
        if (answer_buffer.size() != 0)
        {
            double mean_sum = 0;
            for (const auto &ans_buff : answer_bufferD)
            {
                mean_sum += ans_buff;
            }
            answer = mean_sum / answer_buffer.size();
        }
    }
    else if (func == "median")
    {
        if (answer_buffer.size() == 1)
        {
            answer = answer_bufferD[0];
        }
        else if (answer_buffer.size() != 0)
        {
            double median, median_buff;
            int med_vec_size, med_vec_index;
            vector<double> median_vec;

            median_vec = answer_bufferD;

            med_vec_size = median_vec.size();

            sort(median_vec.begin(), median_vec.end());

            if (med_vec_size % 2 == 0)
            {
                med_vec_index = (med_vec_size / 2) - 1;
                answer = (median_vec[med_vec_index] + median_vec[med_vec_index + 1]) / 2;
            }
            else
            {
                med_vec_index = (med_vec_size / 2);
                answer = median_vec[med_vec_index];
            }
        }
    }
    fn_ret.answer = answer;
    fn_ret.index = x;

    return fn_ret;
}
string ds_func_eval(string key, string function)
{
    if (function == "mean")
    {
        double x_sum = 0;
        int index = 0;
        string ret_val;

        for (const auto &entry : data_sets[key])
        {
            index++;
            x_sum += entry;
        }

        ret_val = to_string(x_sum / index);
        if (stold(ret_val) - stoll(ret_val) == 0)
        {
            ret_val = to_string(stoll(ret_val));
        }
        return ret_val;
    }
    else if (function == "median")
    {
        vector<double> sorted = data_sets[key];
        string ret_val;

        sort(sorted.begin(), sorted.end());

        int sort_size = sorted.size();

        if (sort_size % 2 == 0)
        {
            int great = sort_size / 2;
            int less = (sort_size / 2) - 1;

            ret_val = to_string((sorted[great] + sorted[less]) / 2);
            if (stold(ret_val) - stoll(ret_val) == 0)
            {
                ret_val = to_string(stoll(ret_val));
            }
            return ret_val;
        }
        else
        {
            ret_val = to_string(sorted[sort_size / 2]);
            if (stold(ret_val) - stoll(ret_val) == 0)
            {
                ret_val = to_string(stoll(ret_val));
            }
            return ret_val;
        }
        // data_sets[key];
    }
    else if (function == "mode")
    {
        vector<double> vec = data_sets[key];
        vector<double> unique;
        vector<int> unique_num;
        bool append = false, equal = true;
        double greatest;
        string output;

        for (int x = 0; x < vec.size(); x++)
        {
            if (empty(unique))
            {
                unique.push_back(vec[x]);
                unique_num.push_back(1);
            }
            else
            {
                for (int y = 0; y < unique.size(); y++)
                {
                    if (vec[x] == unique[y])
                    {
                        append = true;
                        unique_num[y]++;
                    }
                }
                if (!append)
                {
                    unique.push_back(vec[x]);
                    unique_num.push_back(1);
                }
                append = false;
            }
        }
        greatest = unique_num[0];
        for (int x = 0; x < unique_num.size(); x++)
        {
            if (unique_num[x] > greatest)
            {
                equal = false;
                greatest = unique_num[x];
            }
        }
        if (equal)
        {
            return "no mode";
        }
        else
        {
            for (int x = 0; x < unique.size(); x++)
            {
                if (unique_num[x] == greatest)
                {
                    if (double(int(unique[x])) == unique[x])
                    {
                        if (!(x == unique.size() - 1))
                        {
                            output += to_string(int(unique[x])) + " ";
                        }
                        else
                        {
                            output += to_string(int(unique[x]));
                        }
                    }
                    else
                    {
                        if (!(x == unique.size() - 1))
                        {
                            output += to_string(unique[x]) + " ";
                        }
                        else
                        {
                            output += to_string(unique[x]);
                        }
                    }
                }
            }
            return output;
        }
    }
    else if (function == "varp")
    {
        vector<double> vec = data_sets[key];
        double summation = 0;
        double mean = stold(ds_func_eval(key, "mean"));
        string ret_val;

        for (int x = 0; x < vec.size(); x++)
        {
            summation += (vec[x] - mean) * (vec[x] - mean);
        }

        ret_val = to_string(summation / vec.size());
        if (stold(ret_val) - stoll(ret_val) == 0)
        {
            ret_val = to_string(stoll(ret_val));
        }
        return ret_val;
    }
    else if (function == "stdevp")
    {
        vector<double> vec = data_sets[key];
        double summation = 0;
        double mean = stold(ds_func_eval(key, "mean"));
        string ret_val;

        for (int x = 0; x < vec.size(); x++)
        {
            summation += (vec[x] - mean) * (vec[x] - mean);
        }

        ret_val = to_string(sqrt(summation / vec.size()));
        if (stold(ret_val) - stoll(ret_val) == 0)
        {
            ret_val = to_string(stoll(ret_val));
        }
        return ret_val;
    }
    else if (function == "vars")
    {
        vector<double> vec = data_sets[key];
        double summation = 0;
        double mean = stold(ds_func_eval(key, "mean"));
        string ret_val;

        for (int x = 0; x < vec.size(); x++)
        {
            summation += (vec[x] - mean) * (vec[x] - mean);
        }

        ret_val = to_string(summation / (vec.size() - 1));
        if (stold(ret_val) - stoll(ret_val) == 0)
        {
            ret_val = to_string(stoll(ret_val));
        }
        return ret_val;
    }
    else if (function == "stdevs")
    {
        vector<double> vec = data_sets[key];
        double summation = 0;
        double mean = stold(ds_func_eval(key, "mean"));
        string ret_val;

        for (int x = 0; x < vec.size(); x++)
        {
            summation += (vec[x] - mean) * (vec[x] - mean);
        }

        ret_val = to_string(sqrt(summation / (vec.size() - 1)));
        if (stold(ret_val) - stoll(ret_val) == 0)
        {
            ret_val = to_string(stoll(ret_val));
        }
        return ret_val;
    }
    else if (function == "skews")
    {
        vector<double> vec = data_sets[key];
        vector<double> standard_val;
        string ret_val;
        double standard_val_sum = 0;
        long double answer;
        double n;
        double mean = stold(ds_func_eval(key, "mean"));
        double standard_dev = stold(ds_func_eval(key, "stdevs"));

        n = vec.size();

        for (int x = 0; x < n; x++)
        {
            standard_val.push_back((vec[x] - mean) / standard_dev);
        }

        for (int x = 0; x < n; x++)
        {
            standard_val_sum += pow(standard_val[x], 3);
        }

        answer = standard_val_sum * (n / ((n - 1) * (n - 2)));

        ret_val = to_string(answer);
        if (stold(ret_val) - stoll(ret_val) == 0)
        {
            ret_val = to_string(stoll(ret_val));
        }
        return ret_val;
    }
    else if (function == "skewp")
    {
        vector<double> vec = data_sets[key];
        vector<double> standard_val;
        string ret_val;
        double standard_val_sum = 0;
        long double answer;
        double n;
        double mean = stold(ds_func_eval(key, "mean"));
        double standard_dev = stold(ds_func_eval(key, "stdevp"));

        n = vec.size();

        for (int x = 0; x < n; x++)
        {
            standard_val.push_back((vec[x] - mean) / standard_dev);
        }

        for (int x = 0; x < n; x++)
        {
            standard_val_sum += pow(standard_val[x], 3);
        }

        answer = standard_val_sum * (1 / n);

        ret_val = to_string(answer);
        if (stold(ret_val) - stoll(ret_val) == 0)
        {
            ret_val = to_string(stoll(ret_val));
        }
        return ret_val;
    }
    else if (function == "range")
    {
        vector<double> vec = data_sets[key];
        double min_val = *min_element(vec.begin(), vec.end());
        double max_val = *max_element(vec.begin(), vec.end());
        string ret_val;

        ret_val = to_string(max_val - min_val);
        if (stold(ret_val) - stoll(ret_val) == 0)
        {
            ret_val = to_string(stoll(ret_val));
        }
        return ret_val;
    }
    else if (function == "sum")
    {
        vector<double> vec = data_sets[key];
        double summation = 0;
        string ret_val;

        for (int x = 0; x < vec.size(); x++)
        {
            summation += vec[x];
        }
        ret_val = to_string(summation);
        if (stold(ret_val) - stoll(ret_val) == 0)
        {
            ret_val = to_string(stoll(ret_val));
        }
        return ret_val;
    }
    else if (function == "view")
    {
        vector<double> vec = data_sets[key];
        string view = key;

        for (int x = 0; x < vec.size(); x++)
        {
            if (vec[x] - stoll(to_string(vec[x])) == 0)
            {
                view += to_string(stoll(to_string(vec[x]))) + " ";
            }
            else
            {
                view += to_string(vec[x]) + " ";
            }
        }

        return view;
    }
}
string ds_func_mul_eval(string key, string key_2, string function)
{
    if (function == "pcoef")
    {
        vector<double> vec_1 = data_sets[key];
        vector<double> vec_2 = data_sets[key_2];
        double summation_1 = 0, summation_2 = 0, summation_3 = 0;
        double mean_1 = stold(ds_func_eval(key, "mean"));
        double mean_2 = stold(ds_func_eval(key_2, "mean"));

        for (int x = 0; x < vec_1.size(); x++)
        {
            summation_1 += (vec_1[x] - mean_1) * (vec_2[x] - mean_2);
            summation_2 += (vec_1[x] - mean_1) * (vec_1[x] - mean_1);
            summation_3 += (vec_2[x] - mean_2) * (vec_2[x] - mean_2);
        }

        return to_string(summation_1 / sqrt(summation_2 * summation_3));
    }
    else if (function == "covar")
    {
        vector<double> vec_1 = data_sets[key];
        vector<double> vec_2 = data_sets[key_2];
        double summation_1 = 0;
        double mean_1 = stold(ds_func_eval(key, "mean"));
        double mean_2 = stold(ds_func_eval(key_2, "mean"));

        for (int x = 0; x < vec_1.size(); x++)
        {
            summation_1 += (vec_1[x] - mean_1) * (vec_2[x] - mean_2);
        }

        return to_string(summation_1 / (vec_1.size() - 1));
    }
}

token_validation validate_tokens(vector<vector<token>> test)
{
    token_validation valid_token;
    vector<vector<token>> test_02;
    vector<token> operators = test[0];
    vector<token> operands = test[1];
    int index = 0;

    for (const auto &entry : operands)
    {
        // double
        if (entry.type == "double")
        {
            double buffer;
            try
            {
                stold(entry.val);
            }
            catch (...)
            {
                valid_token.error = true;
                valid_token.error_type = "Invalid number input " + entry.val;
                return valid_token;
            }
        }
        // function
        if (entry.type == "function")
        {
            string buffer, valid_func, buffer_val;
            int par_left = 0, par_right = 0;
            bool par_break = false;
            for (const char &x : entry.val)
            {
                if (!par_break && x == '(')
                {
                    par_break = true;
                }
                if (par_break)
                {
                    if (x == '(')
                    {
                        par_left++;
                    }
                    if (x == ')')
                    {
                        par_right++;
                    }
                    buffer_val += x;
                }
                else
                {

                    buffer += x;
                }
            }
            if (par_left != par_right)
            {
                valid_token.error = true;
                valid_token.error_type = "Invalid function input " + buffer + ":" + buffer_val;
                return valid_token;
            }
            else if (buffer_val[buffer_val.length() - 1] != ')')
            {
                valid_token.error = true;
                valid_token.error_type = "Invalid function input " + buffer + ":" + buffer_val;
                return valid_token;
            }
            valid_func = is_buffer_valid_func(buffer);
            if (valid_func == "invalid")
            {
                valid_token.error = true;
                valid_token.error_type = "Invalid function input " + buffer;
                return valid_token;
            }
            fn_return fn_ret = func_eval(buffer, buffer_val);
            if (fn_ret.error != "")
            {
                valid_token.error = true;
                valid_token.error_type = "Invalid function input " + buffer;
                return valid_token;
            }
        }
        // variable_call
        if (entry.type == "variable_call")
        {
            string var_to_oper;
            if (variables.find(entry.val) != variables.end())
            {
                // variable call
                var_to_oper = variables[entry.val];
                var_to_oper = eval(var_to_oper).evaluated;
                if (var_to_oper == "(Error)")
                {
                    valid_token.error = true;
                    valid_token.error_type = "Invalid variable value " + entry.val + ":" + variables[entry.val];
                    return valid_token;
                }
                operands[index].val = var_to_oper;
                operands[index].type = "double";
            }
            else
            {
                valid_token.error = true;
                valid_token.error_type = "Invalid variable " + entry.val + ", not found";
                return valid_token;
            }
        }
        // parentheses
        if (entry.type == "parentheses")
        {
            string parenth = entry.val;
            vector<token> operands_parenth = get_tokens(parenth)[1];
            for (int par_x = 0; par_x < operands_parenth.size(); par_x++)
            {
                if (operands_parenth[par_x].op_type == "view" || operands_parenth[par_x].op_type == "mode")
                {
                    valid_token.error = true;
                    valid_token.error_type = "Invalid parentheses argument " + entry.val;
                    return valid_token;
                }
            }
            parenth = eval(entry.val).evaluated;
            if (parenth == "(Error)")
            {
                valid_token.error = true;
                valid_token.error_type = "Invalid parentheses argument " + entry.val;
                return valid_token;
            }
        }
        // dataset_function
        if (entry.type == "dataset_mul_function")
        {
            string buffer, buffer_2, function;
            bool valid_function = true;
            int index, index_mul;

            for (int x = 0; x < entry.val.size(); x++)
            {
                if (entry.val[x] == '.')
                {
                    index = x + 1;
                    break;
                }
            }

            function = entry.val;
            function = function.substr(index);

            index_mul = entry.val.find("[", entry.val.find("[") + 1);
            buffer = entry.val;
            buffer = buffer.substr(0, index_mul);
            buffer_2 = entry.val;
            buffer_2 = buffer_2.substr(index_mul, index - index_mul - 1);

            if (data_sets.find(buffer) == data_sets.end())
            {
                valid_token.error = true;
                valid_token.error_type = "Invalid data set " + entry.val;
                return valid_token;
            }
            if (data_sets.find(buffer_2) == data_sets.end())
            {
                valid_token.error = true;
                valid_token.error_type = "Invalid data set " + entry.val;
                return valid_token;
            }
            if (data_sets[buffer_2].size() != data_sets[buffer].size())
            {
                valid_token.error = true;
                valid_token.error_type = "Data sets are not equal " + entry.val;
                return valid_token;
            }
            if (!(valid_function = valid_data_set_mul_function(function)))
            {
                valid_token.error = true;
                valid_token.error_type = "Invalid data set function" + entry.val;
                return valid_token;
            }
        }
        if (entry.type == "dataset_function")
        {
            string buffer, function;
            bool valid_function = true;
            int index;

            for (int x = 0; x < entry.val.size(); x++)
            {
                if (entry.val[x] == '.')
                {
                    index = x + 1;
                    break;
                }
                buffer += entry.val[x];
            }

            function = entry.val;
            function = function.substr(index);

            if (data_sets.find(buffer) == data_sets.end())
            {
                valid_token.error = true;
                valid_token.error_type = "Invalid data set " + entry.val;
                return valid_token;
            }
            if ((function == "view" || function == "mode") && operands.size() != 1)
            {
                valid_token.error = true;
                valid_token.error_type = "Invalid data set function" + entry.val + ", Cannot use mode in calculations\n";
                return valid_token;
            }

            if (!(valid_function = valid_data_set_function(function)))
            {
                valid_token.error = true;
                valid_token.error_type = "Invalid data set function" + entry.val;
                return valid_token;
            }

            if ((function == "view" || function == "mode"))
            {
                entry.op_type == "view";
            }
        }
        index++;
    }
    // classic_operator
    for (const auto &entry : operators)
    {
        if (!is_valid_operator(entry.val))
        {
            valid_token.error = true;
            valid_token.error_type = "Invalid operator input " + entry.val;
            return valid_token;
        }
    }
    valid_token.error = false;
    valid_token.error_type = "valid";
    test_02.push_back(operators);
    test_02.push_back(operands);
    valid_token.tokens = test_02;
    return valid_token;
}
eval_ret evaluate_tokens(vector<token> operators, vector<token> operands)
{
    eval_ret to_ret;
    to_ret.error = "";

    for (int x = 0; x < operands.size(); x++)
    {
        if (operands[x].type == "function")
        {
            string buffer, valid_func, buffer_val;
            int par_left = 0, par_right = 0;
            bool par_break = false;
            for (const char &x : operands[x].val)
            {
                if (!par_break && x == '(')
                {
                    par_left++;
                    par_break = true;
                }
                if (par_break)
                {
                    if (x == '(')
                    {
                        par_left++;
                    }
                    if (x == ')')
                    {
                        par_right++;
                    }
                    buffer_val += x;
                }
                else
                {

                    buffer += x;
                }
            }
            operands[x].val = to_string(func_eval(buffer, buffer_val).answer);
        }
    }
    for (int x = 0; x < operands.size(); x++)
    {
        int index;
        string dataset_str;
        if (operands[x].type == "dataset_function")
        {
            dataset_str = operands[x].val;
            index = dataset_str.find(".");
            operands[x].val = ds_func_eval(dataset_str.substr(0, index), dataset_str.substr(index + 1));
        }
    }
    for (int x = 0; x < operands.size(); x++)
    {
        int index, index_mul;
        string dataset_str, buffer, buffer_2;
        if (operands[x].type == "dataset_mul_function")
        {
            index_mul = operands[x].val.find("[", operands[x].val.find("[") + 1);
            dataset_str = operands[x].val;
            index = dataset_str.find(".");
            buffer = operands[x].val;
            buffer = buffer.substr(0, index_mul);
            buffer_2 = operands[x].val;
            buffer_2 = buffer_2.substr(index_mul, index - index_mul);

            operands[x].val = ds_func_mul_eval(buffer, buffer_2, dataset_str.substr(index + 1));
        }
    }
    for (int x = 0; x < operands.size(); x++)
    {
        if (operands[x].type == "parentheses")
        {
            operands[x].val = eval(operands[x].val).evaluated;
        }
    }
    for (int x = 0; x < operands.size(); x++)
    {
        if (operands[x].type == "variable_call")
        {
            operands[x].val = eval(variables[operands[x].val]).evaluated;
        }
    }

    if (empty(operands))
    {
        to_ret.evaluated = "(Error)";
        to_ret.error = "no operands";
        return to_ret;
    }
    if (operands[0].val == "no operands")
    {
        to_ret.evaluated = "(Error)";
        to_ret.error = "no operands";
        return to_ret;
    }
    if (operands.size() != operators.size() + 1)
    {
        to_ret.evaluated = "(Error)";
        to_ret.error = "ERR001 - Invalid Number of Operands/Operators";
        return to_ret;
    }
    if (operators.size() == 0 && operands.size() == 1)
    {
        to_ret.evaluated = operands[0].val;
        return to_ret;
    }

    for (const auto &oper : operands)
    {
        if (oper.val == "undefined")
        {
            to_ret.evaluated = "undefined";
            return to_ret;
        }
    }

    while (operators.size() > 0)
    {
        for (int x = 0; x < operators.size(); x++)
        {
            if (operators[x].val == "*" || operators[x].val == "*-" || operators[x].val == "*+")
            {
                if (operators[x].val == "*")
                {
                    operands[x].val = to_string(stold(operands[x].val) * stold(operands[x + 1].val));
                    operands.erase(operands.begin() + x + 1);
                }
                else if (operators[x].val == "*-")
                {
                    operands[x].val = to_string(stold(operands[x].val) * stold("-" + operands[x + 1].val));
                    operands.erase(operands.begin() + x + 1);
                }
                else if (operators[x].val == "*+")
                {
                    operands[x].val = to_string(stold(operands[x].val) * stold(operands[x + 1].val));
                    operands.erase(operands.begin() + x + 1);
                }
                operators.erase(operators.begin() + x);
                x--;
            }
            if (operators.size() == 0)
            {
                break;
            }
            if (operators[x].val == "/" || operators[x].val == "/-" || operators[x].val == "/+")
            {
                if (operands[x + 1].val == "0")
                {
                    to_ret.evaluated = "undefined";
                    return to_ret;
                }
                if (operators[x].val == "/")
                {
                    operands[x].val = to_string(stold(operands[x].val) / stold(operands[x + 1].val));
                    operands.erase(operands.begin() + x + 1);
                }
                else if (operators[x].val == "/-")
                {
                    operands[x].val = to_string(stold(operands[x].val) / stold("-" + operands[x + 1].val));
                    operands.erase(operands.begin() + x + 1);
                }
                else if (operators[x].val == "/+")
                {
                    operands[x].val = to_string(stold(operands[x].val) / stold(operands[x + 1].val));
                    operands.erase(operands.begin() + x + 1);
                }
                operators.erase(operators.begin() + x);
                x--;
            }
        }
        for (int x = 0; x < operators.size(); x++)
        {
            if (operators[x].val == "+" || operators[x].val == "+-" || operators[x].val == "++")
            {
                if (operators[x].val == "+")
                {
                    operands[x].val = to_string(stold(operands[x].val) + stold(operands[x + 1].val));
                    operands.erase(operands.begin() + x + 1);
                }
                else if (operators[x].val == "+-")
                {
                    operands[x].val = to_string(stold(operands[x].val) - stold(operands[x + 1].val));
                    operands.erase(operands.begin() + x + 1);
                }
                else if (operators[x].val == "++")
                {
                    operands[x].val = to_string(stold(operands[x].val) + stold(operands[x + 1].val));
                    operands.erase(operands.begin() + x + 1);
                }
                operators.erase(operators.begin() + x);
                x--;
            }
            if (operators.size() == 0)
            {
                break;
            }
            if (operators[x].val == "-" || operators[x].val == "--" || operators[x].val == "-+")
            {
                if (operators[x].val == "-")
                {
                    operands[x].val = to_string(stold(operands[x].val) - stold(operands[x + 1].val));
                    operands.erase(operands.begin() + x + 1);
                }
                else if (operators[x].val == "--")
                {
                    operands[x].val = to_string(stold(operands[x].val) + stold(operands[x + 1].val));
                    operands.erase(operands.begin() + x + 1);
                }
                else if (operators[x].val == "-+")
                {
                    operands[x].val = to_string(stold(operands[x].val) - stold(operands[x + 1].val));
                    operands.erase(operands.begin() + x + 1);
                }
                operators.erase(operators.begin() + x);
                x--;
            }
        }
    }

    if (stold(operands[0].val) - stoll(operands[0].val) == 0)
    {
        operands[0].val = to_string(stoll(operands[0].val));
    }
    to_ret.evaluated = operands[0].val;
    return to_ret;
}
eval_ret eval(string inpt)
{
    token_validation valid_tokens;
    eval_ret buffer_return;

    vector<vector<token>> test = get_tokens(inpt);
    vector<token> operators = test[0];
    vector<token> operands = test[1];

    if (operands[0].val == "invalid_token")
    {
        buffer_return.evaluated = "(Error)";
        buffer_return.error = "Invalid Token";

        return buffer_return;
    }

    valid_tokens = validate_tokens(test);

    if (valid_tokens.error == true)
    {
        buffer_return.evaluated = "(Error)";
        buffer_return.error = valid_tokens.error_type;
        cout << buffer_return.error << "\n";
        return buffer_return;
    }
    operators = valid_tokens.tokens[0];
    operands = valid_tokens.tokens[1];

    buffer_return = evaluate_tokens(operators, operands);
    return buffer_return;
}

void calculator_view(fs::path p, fs::path d, fs::path v)
{
    clear_screen();
    string inpt, oupt, inpt_stream, oupt_stream;
    eval_ret eval_return;
    vector<string> stream;
    bool var_1 = false, var_2 = false, data_set_1 = false, data_set_2 = false;

    ifstream input(p);

    if (input.is_open())
    {
        string line;

        while (getline(input, line))
        {
            // Write each line to the output file
            cout << line << "\n";
            stream.push_back(line);
        }
    }
    input.close();
    cout << "\n";
    cout << "<InCalc>\n\n";
    while (true)
    {
        scan_datasets(d);
        scan_variables(v);
        if (empty(stream))
        {
            cout << "Type help() to view the documentation\n";
        }
        cout << ">>> ";
        getline(cin, inpt_stream);

        if (inpt_stream == "quit()")
        {
            break;
        }
        else if (inpt_stream == "help()")
        {
            help();
        }
        else if (inpt_stream.substr(0, 2) == "//")
        {
            stream.push_back("[" + inpt_stream.substr(2) + "]");
            cout << "\ncomment added\n";
        }
        else if (inpt_stream == "vars()")
        {
            variables_view(v);
        }
        else if (inpt_stream == "datas()")
        {
            data_sets_view(d);
        }
        else if (inpt_stream == "clear()")
        {
            char ch;
            cout << "\nDelete history (y/n): ";
            ch = getch();

            if (ch == 'y')
            {
                ofstream file;
                clear_screen();
                file.open(p, ofstream::out | ofstream::trunc);
                file.close();
                stream.clear();
                cout << "\n";
            }
        }
        else if (inpt_stream == "")
        {
            continue;
        }
        else
        {
            stream.push_back(">>> " + inpt_stream);
            eval_return = eval(inpt_stream);
            oupt_stream = eval_return.evaluated;

            if (isdigit(oupt_stream[0]))
            {
                if (variables.find("ans") != variables.end())
                {
                    variables["ans"] = oupt_stream;
                }
                else
                {
                    variables.insert({"ans", oupt_stream});
                }
            }
            if (oupt_stream.find('.') != string::npos)
            {
                oupt_stream = remove_trailing_zeros(oupt_stream);
                cout << oupt_stream << endl;
                stream.push_back(oupt_stream);
            }
            else
            {
                cout << oupt_stream << endl;
                stream.push_back(oupt_stream);
            }
        }
    }

    if (empty(stream))
    {
        return;
    }

    ofstream output_2(p);
    for (int x = 0; x < stream.size(); x++)
    {
        output_2 << stream[x] << endl;
    }

    output_2.close();
}

void open_file(string username, string file_topen)
{
    fs::path p = fs::current_path();
    p = p / "files/" / username / file_topen;
    fs::path p_ds = p / "data_sets.txt";
    fs::path p_vs = p / "variables.txt";
    fs::path p_ca = p / "calculator.txt";
    fs::path p_ns = p / "notes.txt";
    double data_value;

    data_sets.clear();
    variables.clear();

    scan_datasets(p_ds);
    scan_variables(p_vs);
    int arrow = 0;
    string arrow_str;

    while (true)
    {
        quiks_header();
        cout << username << "\n";
        switch (arrow)
        {
        case 0:
            cout << "\t\t\t\t+--------------+\n"
                 << "\t\t\t\t| > Data Sets  |\n"
                 << "\t\t\t\t|   Variables  |\n"
                 << "\t\t\t\t|   Calculator |\n"
                 << "\t\t\t\t|   Notes      |\n"
                 << "\t\t\t\t+--------------+\n";
            break;
        case 1:
            cout << "\t\t\t\t+--------------+\n"
                 << "\t\t\t\t|   Data Sets  |\n"
                 << "\t\t\t\t| > Variables  |\n"
                 << "\t\t\t\t|   Calculator |\n"
                 << "\t\t\t\t|   Notes      |\n"
                 << "\t\t\t\t+--------------+\n";
            break;
        case 2:
            cout << "\t\t\t\t+--------------+\n"
                 << "\t\t\t\t|   Data Sets  |\n"
                 << "\t\t\t\t|   Variables  |\n"
                 << "\t\t\t\t| > Calculator |\n"
                 << "\t\t\t\t|   Notes      |\n"
                 << "\t\t\t\t+--------------+\n";
            break;
        case 3:
            cout << "\t\t\t\t+--------------+\n"
                 << "\t\t\t\t|   Data Sets  |\n"
                 << "\t\t\t\t|   Variables  |\n"
                 << "\t\t\t\t|   Calculator |\n"
                 << "\t\t\t\t| > Notes      |\n"
                 << "\t\t\t\t+--------------+\n";
            break;
        }
        arrow_str = menu_loop_reader();
        if (arrow_str == "UP")
        {
            arrow--;
            if (arrow < 0)
            {
                arrow = 0;
            }
        }
        else if (arrow_str == "DOWN")
        {
            arrow++;
            if (arrow > 3)
            {
                arrow = 3;
            }
        }
        else if (arrow_str == "ENTER")
        {
            switch (arrow)
            {
            case 0:
                data_sets_view(p_ds);
                break;
            case 1:
                variables_view(p_vs);
                break;
            case 2:
                calculator_view(p_ca, p_ds, p_vs);
                break;
            case 3:
                notes_view(p_ns, p_ds, p_vs);
                break;
            }
        }
        else if (arrow_str == "quit")
        {
            break;
        }
        clear_screen();
    }
    return;
}
void change_password(string username, string new_password)
{
    string username_en, buffer, password_en;
    vector<string> lines;
    ifstream file("pw.txt");
    password_ret password;

    cout << "Confirm New Password\n";
    password = password_reg();

    if (password.proper == false)
    {
        cout << "Unable to change password\n";
        enter_to_continue();
        return;
    }

    if (password.password != new_password)
    {
        cout << "\nPasswords does not match\n";
        enter_to_continue();
        return;
    }

    while (getline(file, username_en, ';'))
    {
        if (username_en == encrypt(username))
        {
            getline(file, password_en);
            buffer = username_en + ";" + encrypt(new_password);
        }
        else
        {
            getline(file, password_en);
            buffer = username_en + ";" + password_en;
        }
        lines.push_back(buffer);
    }
    file.close();
    ofstream file_out;
    file_out.open("pw.txt");

    for (int x = 0; x < lines.size(); x++)
    {
        file_out << lines[x] << "\n";
    }
    file_out.close();

    cout << "\nChanged Password\n";
    enter_to_continue();
}
void change_username(string old, string new_username)
{
    string username_en, buffer, password_en;
    vector<string> lines;
    ifstream file("pw.txt");
    fs::path p = fs::current_path() / "files" / old;
    fs::path p_2 = fs::current_path() / "files" / new_username;
    while (getline(file, username_en, ';'))
    {
        if (username_en == encrypt(old))
        {
            getline(file, password_en);
            buffer = encrypt(new_username) + ";" + password_en;
        }
        else
        {
            getline(file, password_en);
            buffer = username_en + ";" + password_en;
        }
        lines.push_back(buffer);
    }
    file.close();
    ofstream file_out;
    file_out.open("pw.txt");

    for (int x = 0; x < lines.size(); x++)
    {
        file_out << lines[x] << "\n";
    }
    file_out.close();
    fs::rename(p, p_2);

    cout << "\nChanged Username\n";
    enter_to_continue();
}
void remove_account(string username)
{
    string username_en, buffer, password_en;
    vector<string> lines;
    ifstream file("pw.txt");
    fs::path p = fs::current_path() / "files" / username;
    while (getline(file, username_en, ';'))
    {
        if (username_en == encrypt(username))
        {
            getline(file, password_en);
            continue;
        }
        else
        {
            getline(file, password_en);
            buffer = username_en + ";" + password_en;
        }
        lines.push_back(buffer);
    }
    file.close();
    ofstream file_out;
    file_out.open("pw.txt");

    for (int x = 0; x < lines.size(); x++)
    {
        file_out << lines[x] << "\n";
    }
    file_out.close();
    fs::remove_all(p);

    cout << "Account Deleted\nExiting...\n";
    enter_to_continue();
    abort();
}
void account_settings(string username)
{
    string settings[] = {"Change Username", "Change Password", "Delete Account"};
    vector<string> users = scan_users();
    int loop_reader = 0;
    string loop_reader_str;

    while (true)
    {
        cout << "\t\t == Account Settings ==\n";
        for (int x = 0; x < 3; x++)
        {
            if (loop_reader == x)
            {
                cout << "\t\t>";
            }
            else
            {
                cout << "\t\t ";
            }
            cout << settings[x] << endl;
        }
        loop_reader_str = menu_loop_reader();
        if (loop_reader_str == "UP")
        {
            loop_reader--;
            if (loop_reader < 0)
            {
                loop_reader = 0;
            }
        }
        else if (loop_reader_str == "DOWN")
        {
            loop_reader++;
            if (loop_reader == 3)
            {
                loop_reader = 2;
            }
        }
        else if (loop_reader_str == "ENTER")
        {
            if (loop_reader == 1)
            {
                cout << "Current Password\n";
            }
            string buffer;
            password_ret password;

            password = password_reg();

            if (password.proper == false)
            {
                continue;
            }

            if (encrypt(password.password) == get_password(username))
            {
                if (loop_reader == 0)
                {
                    cout << "Enter new username: ";
                    getline(cin, buffer);
                    for (int x = 0; x < buffer.length(); x++)
                    {
                        if (buffer[x] == ' ')
                        {
                            cout << "Don't Include Whitespaces!" << endl;
                            continue;
                        }
                    }
                    for (int x = 0; x < buffer.size(); x++)
                    {
                        if (buffer == users[x])
                        {
                            cout << "Username is already used! Please use a different username..."
                                 << endl;
                            continue;
                        }
                    }
                    change_username(username, buffer);
                }
                else if (loop_reader == 1)
                {
                    cout << "\nNew Password\n";
                    password = password_reg();
                    change_password(username, password.password);
                }
                else if (loop_reader == 2)
                {
                    char ch;
                    cout << "\nAre you sure you want to delete your account(y/n)?\n";
                    ch = getch();

                    if (ch == 'y')
                    {
                        remove_account(username);
                    }
                }
            }
        }
        else if (loop_reader_str == "quit")
        {
            break;
        }
        clear_screen();
    }
}
void menu_file_sel(string username, string username_out)
{
    vector<string> filenames;

    filenames = scan_files(username);

    vector<vector<string>> dir_files = get_dir_files_names(filenames);
    vector<string> dir = dir_files[0];
    vector<string> file = dir_files[1];
    int loop_reader_num = 0;
    string loop_read, add_file, marked, mkdir_name;
    char y_n;

    while (true)
    {
        int y = 0;

        cout << "/" << username_out << endl;
        if (empty(dir) && empty(file))
        {
            cout << "No Directory or Files (press 'a' to add a file or 'm' to create a directory)" << endl;
        }

        // printing the folder and file names
        for (int x = 0; x < dir.size(); x++)
        {
            if (loop_reader_num == y)
            {
                cout << ">";
                marked = dir[x];
            }
            else
            {
                cout << " ";
            }
            cout << "/" << dir[x].substr(2) << endl;
            y++;
        }

        for (int x = 0; x < file.size(); x++)
        {
            if (loop_reader_num == y)
            {
                cout << ">";
                marked = file[x];
            }
            else
            {
                cout << " ";
            }
            cout << file[x].substr(2) << endl;
            y++;
        }

        cout << "\n - UP and DOWN arrow keys to navigate\n - ENTER -> enter file or directory\n - 'a' -> add file \n - 'd' -> delete file\n - 'm' -> make directory\n - 'u' -> update name\n - 'q' -> quit or escape\n";

        loop_read = menu_loop_reader();

        if (loop_read == "UP")
        {
            loop_reader_num--;
        }
        else if (loop_read == "DOWN")
        {
            loop_reader_num++;
        }
        else if (loop_read == "ENTER")
        {
            clear_screen();
            if (loop_reader_num < dir.size())
            {
                menu_file_sel(username + "/" + dir[loop_reader_num], username + "/" + dir[loop_reader_num].substr(2));
            }
            else
            {
                open_file(username, file[loop_reader_num - dir.size()]);
            }
        }
        else if (loop_read == "add")
        {
            cout << endl
                 << "Enter File Name: ";
            getline(cin, add_file);

            if (fs::exists("files/" + username + "/f_" + add_file))
            {
                cout << endl
                     << "File Already Exists";
                enter_to_continue();
            }
            else
            {
                fs::create_directory("files/" + username + "/f_" + add_file);
                cout << endl
                     << "Created " + add_file;
                enter_to_continue();
            }

            filenames = scan_files(username);
            dir_files = get_dir_files_names(filenames);
            dir = dir_files[0];
            file = dir_files[1];
        }
        else if (loop_read == "mkdir")
        {
            cout << endl
                 << "Enter Directory Name: ";
            getline(cin, mkdir_name);

            if (fs::exists("files/" + username + "/d_" + mkdir_name))
            {
                cout << endl
                     << "Directory Already Exists";
                enter_to_continue();
            }
            else
            {
                fs::create_directory("files/" + username + "/d_" + mkdir_name);
                cout << endl
                     << "Created " + mkdir_name;
                enter_to_continue();
            }

            filenames = scan_files(username);

            dir_files = get_dir_files_names(filenames);
            dir = dir_files[0];
            file = dir_files[1];
        }
        else if (loop_read == "delete")
        {
            y_n = 'a';
            while (y_n != 'y' && y_n != 'n')
            {
                cout << "Are you sure you want to delete(y/n) " << marked.substr(2) << ": ";
                cin >> y_n;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            if (y_n == 'y')
            {
                fs::remove_all("files/" + username + "/" + marked);
                filenames = scan_files(username);

                dir_files = get_dir_files_names(filenames);
                dir = dir_files[0];
                file = dir_files[1];
            }
        }
        else if (loop_read == "update")
        {
            string buffer;

            cout << "New name for " << marked.substr(2) << ": ";
            getline(cin, buffer);

            if (loop_reader_num < dir.size())
            {
                fs::rename("files/" + username + "/" + marked, "files/" + username + "/d_" + buffer);
            }
            else
            {
                fs::rename("files/" + username + "/" + marked, "files/" + username + "/f_" + buffer);
            }
            filenames = scan_files(username);

            dir_files = get_dir_files_names(filenames);
            dir = dir_files[0];
            file = dir_files[1];
        }
        else if (loop_read == "quit")
        {
            return;
        }
        if (loop_reader_num == dir.size() + file.size())
        {
            loop_reader_num = 0;
        }
        if (loop_reader_num < 0)
        {
            loop_reader_num = dir.size() + file.size() - 1;
        }
        clear_screen();
    }
}
void after_login(string username)
{
    int index_loop_read = 0;
    string loop_read;

    while (true)
    {
        quiks_header();
        if (index_loop_read == 0)
        {
            cout << "\t\t> Program\n";
            cout << "\t\t  Account\n";
        }
        else
        {
            cout << "\t\t  Program\n";
            cout << "\t\t> Account\n";
        }
        cout << "\nUse the UP and DOWN arrow keys to navigate, ENTER to continue and the 'q' character to quit\n";
        loop_read = menu_loop_reader();
        if (loop_read == "UP")
        {
            index_loop_read = 0;
        }
        else if (loop_read == "DOWN")
        {
            index_loop_read = 1;
        }
        else if (loop_read == "ENTER")
        {
            if (index_loop_read == 0)
            {
                clear_screen();
                menu_file_sel(username, username);
            }
            else if (index_loop_read == 1)
            {
                clear_screen();
                account_settings(username);
            }
        }
        else if (loop_read == "quit")
        {
            break;
        }
        clear_screen();
    }
}
int main()
{
    string loop_read;
    int index_loop_read = 0;
    login_struct is_user_logged;

    while (true)
    {
        quiks_header();
        if (index_loop_read == 0)
        {
            cout << login_ascii_arrow;
            cout << sign_up_ascii;
        }
        else
        {
            cout << login_ascii;
            cout << sign_up_ascii_arrow;
        }
        cout << "\nUse the UP and DOWN arrow keys to navigate, ENTER to continue and the 'q' character to quit\n";
        loop_read = menu_loop_reader();
        if (loop_read == "UP")
        {
            index_loop_read = 0;
        }
        else if (loop_read == "DOWN")
        {
            index_loop_read = 1;
        }
        else if (loop_read == "ENTER")
        {
            if (index_loop_read == 0)
            {
                clear_screen();
                is_user_logged = loginform();
            }
            else if (index_loop_read == 1)
            {
                clear_screen();
                regform();
            }
        }
        else if (loop_read == "quit")
        {
            break;
        }

        if (is_user_logged.loggedin == true)
        {
            after_login(is_user_logged.name);
            is_user_logged.loggedin = false;
        }
        clear_screen();
    }
}
