#include <iostream>
#include <fstream>
#include "vocab_writer_utils.h"

using namespace std;

int main() {
    ofstream file;
    bool quit = false;
    while (!quit) {
        string spanisch = read_sentence("spanish: ", false);
        string deutsch = read_sentence("deutsch: ", spanisch.length() == 0);
        quit = deutsch == "";
        write_vocab(spanisch, deutsch, file, quit);     
    }
}
