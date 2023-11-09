#include <conio.h>
#include <direct.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <vector>
#include <map>
#include <cmath>

using namespace std;
namespace fs = filesystem;

vector<string> users_sort(vector<string> filenames)
{
    vector<string> users;
    vector<string> users_vec_buffer;
    string users_buffer, prev_buffer;

    for (int x = 0; x < filenames.size(); x++)
    {
        users_buffer = "";
        for (int y = 0; y < filenames[x].length(); y++)
        {
            if (filenames[x][y] == ' ' || filenames[x][y] == '\\' ||
                filenames[x][y] == 0)
            {
                break;
            }
            users_buffer += filenames[x][y];
        }
        if (string(users_buffer) != string(prev_buffer))
        {
            users.push_back(users_buffer);
        }
        prev_buffer = users_buffer;
    }

    int y = 0;

    return users;
}
int main()
{
    vector<string> filenames, users;
    string buffer;
    fs::path p = fs::current_path() / "files";
    for (const auto &entry : fs::directory_iterator(p))
    {
        buffer = entry.path().string();
        filenames.push_back(buffer.substr(p.string().length() + 1));
    }
    users = users_sort(filenames);

    return users;
}
/* Old Version

vector<string> users_sort(vector<string> filenames)
{
  vector<string> users;
  vector<string> users_vec_buffer;
  string users_buffer, prev_buffer;

  for (int x = 0; x < filenames.size(); x++)
  {
    if (filenames[x].length() > 5)
    {
      users_buffer = "";
      for (int y = 0; y < filenames[x].length() - 5; y++)
      {
        char z = filenames[x][y + 6];
        if (filenames[x][y + 6] == ' ' || filenames[x][y + 6] == '\\' ||
            filenames[x][y + 6] == 0)
        {
          break;
        }
        users_buffer += filenames[x][y + 6];
      }
      if (string(users_buffer) != string(prev_buffer))
      {
        users.push_back(users_buffer);
      }
      prev_buffer = users_buffer;
    }
  }

  int y = 0;

  return users;
}
vector<string> scan_users()
{
  fs::path p = fs::current_path();
  vector<string> filenames, filenames_files, users;
  string buffer, files_lit_str = "files";

  for (const auto &entry : fs::recursive_directory_iterator(p))
  {
    buffer = entry.path().string();
    filenames.push_back(buffer.substr(p.string().length() + 1));
  }

  for (int x = 0; x < filenames.size(); x++)
  {
    if (filenames[x].substr(0, 5) != "files")
    {
      filenames.erase(filenames.begin() + x);
      x--;
    }
  }

  users = users_sort(filenames);

  return users;
}

*/