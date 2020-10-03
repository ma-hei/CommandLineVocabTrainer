#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/algorithm/remove_if.hpp>
#include <boost/algorithm/string.hpp>
#include <stdlib.h> 
#include "vocab_reader_utils.h"
#include "vocab_writer_utils.h"

using namespace std;
using namespace boost::filesystem;

int main(int argc, char *argv[]) {

    path p(argc>1? argv[1] : ".");
    vector<string> all_files = get_all_files_in_path(p);
    vector<Vocab> all_vocab = read_all_vocab_of_files(all_files); 
    
    std::srand (time(NULL));
    while (true) {
        int q = rand() % all_vocab.size();
        Vocab v = all_vocab[q];
        cout << v.deutsch << " > ";
        std::string eingabe = read_sentence();
        if (std::strcmp(eingabe.c_str(), v.spanisch.c_str()) == 0)
            std::cout<<"Richtig\n";
        else
            std::cout<<"Falsch.. "<<v.spanisch<<"\n";
    } 
}
