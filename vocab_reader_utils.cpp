#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/algorithm/remove_if.hpp>
#include <boost/algorithm/string.hpp>
#include <math.h>
#include <iostream>
#include <algorithm>
#include "vocab_writer_utils.h"

using namespace boost::filesystem;
using namespace std;

std::vector<std::string> get_all_files_in_path(boost::filesystem::path p) {
    std::vector<std::string> all_files;
    if(is_directory(p)) {
        int count = 0; 
        for(auto& entry : boost::make_iterator_range(directory_iterator(p), {})) {
            std::ostringstream oss;
            oss << entry;
            std::string path = oss.str();
	    path.erase(std::remove(path.begin(), path.end(), '"'), path.end());
            all_files.push_back(path);
        } 
    }
    return all_files;
}

struct Vocab {
    std::string spanisch;
    std::string deutsch;
    Vocab(std::string s) {
        deutsch = s.substr(0, s.find('<')-1);
        spanisch = s.substr(s.find('>')+2, s.size());
    } 
};

std::vector<Vocab> read_all_vocab_of_files(std::vector<std::string> all_files) {
    std::vector<Vocab> all_vocab;
    for (int i=0;i<all_files.size();i++) {
        std::fstream file(all_files[i]);
        std::string line;
        while( getline( file, line ) ) {
            Vocab v(line);
            all_vocab.push_back(v);
        }
    } 
    return all_vocab;
}

std::vector<std::vector<Vocab> > batch_vocab(std::vector<Vocab> all_vocab, int batch_size) {
    std::srand (time(NULL));
    std::vector<std::vector<Vocab> > result;
    for (int i=0; i<all_vocab.size(); i++) {
        int q = rand() % all_vocab.size();
        Vocab temp = all_vocab[q];
        all_vocab[q] = all_vocab[i];
        all_vocab[i] = temp;
    }
    for (int i=0; i<all_vocab.size(); i++) {
        if (i == 0 || result[result.size()-1].size() == batch_size) {
            result.push_back(std::vector<Vocab>());
        }
        result[result.size()-1].push_back(all_vocab[i]); 
    }
    return result;
}

void train_batch(std::vector<Vocab> batch) {
    bool all_correct;
    while(!all_correct) {
       all_correct = true;
       for (int i=0; i<batch.size(); i++) {
           Vocab v = batch[i];
           cout << v.deutsch << " <-> ";
           std::string eingabe = read_sentence();
           if (std::strcmp(eingabe.c_str(), v.spanisch.c_str()) == 0)
               std::cout<<"Richtig\n";
           else {
               std::cout<<"Falsch.. "<<v.spanisch<<"\n";
               all_correct = false;
           }
       }
    }
}
