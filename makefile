include Makefile.inc

all: vocab_writer vocab_reader

vocab_writer: vocab_writer.cpp
	$(CXX) vocab_writer.cpp vocab_writer_utils.cpp $(CXXFLAGS) $(LDFLAGS) $(ICULIBS) -o vocab_writer

vocab_reader: vocab_reader.cpp
	$(CXX) vocab_reader.cpp vocab_reader_utils.cpp vocab_writer_utils.cpp $(CXXFLAGS) $(LDFLAGS) $(ICULIBS) -lboost_system -lboost_filesystem -o vocab_reader

clean:
	rm vocab_writer
	rm vocab_reader
