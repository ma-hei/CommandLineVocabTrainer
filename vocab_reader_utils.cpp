#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/algorithm/remove_if.hpp>
#include <boost/algorithm/string.hpp>

using namespace boost::filesystem;

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
