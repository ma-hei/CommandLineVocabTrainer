struct Vocab {
    std::string spanisch;
    std::string deutsch;
    Vocab(std::string s) {
        spanisch = s.substr(0, s.find('<')-1);
        deutsch = s.substr(s.find('>')+2, s.size());
    } 
};

std::vector<std::string> get_all_files_in_path(boost::filesystem::path path);
std::vector<Vocab> read_all_vocab_of_files(std::vector<std::string> files);
std::vector<std::vector<Vocab> > batch_vocab(std::vector<Vocab> all_vocab, int batch_size);
void train_batch(std::vector<Vocab> batch);

