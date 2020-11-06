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
    vector<vector<Vocab>> batches = batch_vocab(all_vocab, 5);
    while (true) {
        for (int i = 0; i < batches.size(); i++) {
            train_batch(batches[i]); 
        }
    }
}
