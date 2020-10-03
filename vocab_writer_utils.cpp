#include <stdio.h>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <chrono>
#include <algorithm>
#include <ctime>
#include "unicode/utypes.h"
#include "unicode/uchar.h"
#include "unicode/uclean.h"
#include "unicode/unistr.h"

using namespace std; 

unordered_map<string, int> patterns = {
    {"e>", 233},
    {"a>", 225},
    {"A>", 193},
    {"E>", 201},
    {"i>", 237},
    {"I>", 205},
    {"o>", 243},
    {"O>", 211},
    {"u>", 250},
    {"U>", 218},
    {"n~", 241},
    {"N~", 209},
    {"?>", 191},
    {"!>", 161}
};

string get_unicode_as_utf8(int unicode) {
    icu::UnicodeString s = icu::UnicodeString(unicode);
    std:: string str;
    s.toUTF8String(str);
    return str;
}

// reads a sentence and replaces patterns with unicode 
string read_sentence(string prompt, bool quit) {
    if (quit) return "";
    cout << prompt;
    string s;
    getline(cin, s);
    for (int i=0; s.length() > 0 && i<s.length()-1; i++) {
        string sub = s.substr(i,2);
        if (patterns.find(sub) != patterns.end()) {
            s.replace(i, 2, get_unicode_as_utf8(patterns[sub]));
        }
    }
    return s;
}

// reads a sentence and replaces patterns with unicode 
string read_sentence() {
    string s;
    getline(cin, s);
    for (int i=0; s.length() > 0 && i<s.length()-1; i++) {
        string sub = s.substr(i,2);
        if (patterns.find(sub) != patterns.end()) {
            s.replace(i, 2, get_unicode_as_utf8(patterns[sub]));
        }
    }
    return s;
}

// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

string get_file_name() {
    time_t date = std::chrono::system_clock::to_time_t(chrono::system_clock::now());
    string temp = ctime(&date);
    replace(temp.begin(), temp.end(), ' ', '_');
    return trim(temp);
}

bool verify_add(std::string& spanisch, std::string& deutsch) {
    cout << "Add " << spanisch << " <-> " << deutsch << " to vocabulary? y/n\n";
    char key[1];
    cin.getline(key, 2);
    return strcmp(key, "y") == 0;
}

bool write_vocab(std::string& spanisch, std::string& deutsch, std::ofstream& file, bool quit) {
    if (quit) return false;
    if (!file.is_open()) 
        file.open(get_file_name());
    if (verify_add(spanisch, deutsch))
        file << deutsch << " <-> " << spanisch << "\n";
    return true;
}
