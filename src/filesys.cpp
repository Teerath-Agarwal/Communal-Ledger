#include "filesys.h"

string exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pc)> pipe(po(cmd, "r"), pc);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

string remove_ext(string s){
    if (s.empty()) return s;
    int n = s.size();
    n--;
    while (n && s[n]!='.') n--;
    return s.substr(0,n);
}

vector<string> file_list(){
    stringstream s(exec(to_char("ls .data")));
    vector<string> files;
    while(!s.eof()){
        string t;
        // s >> t;
        getline(s,t);
        files.push_back(remove_ext(t));
    }
    files.pop_back();
    return files;
}