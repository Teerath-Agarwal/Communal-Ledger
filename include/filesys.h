#ifndef FS_H
#define FS_H

#include "CL.h"
#include "ES.h"

#ifdef _WIN32
#define pc _pclose
#define po _popen
#else
#define pc pclose
#define po popen
#endif

string exec(const char* cmd);

string remove_ext(string s);

vector<string> file_list();

#endif