all: create_folder bin/ut_all

bin/ut_all: test/ut_all.cpp test/files_test.h src/node.h src/folder.h src/file.h src/null_iterator.h iterator.o dfs_iterator.o
	g++ -std=c++11 test/ut_all.cpp obj/iterator.o obj/dfs_iterator.o -o bin/ut_all -lgtest -lpthread

iterator.o: src/iterator.cpp src/iterator.h
	g++ -std=c++11 -c src/iterator.cpp -o obj/iterator.o

dfs_iterator.o: src/dfs_iterator.cpp src/dfs_iterator.h
	g++ -std=c++11 -c src/dfs_iterator.cpp -o obj/dfs_iterator.o

create_folder:
	mkdir -p bin obj test_folder test_folder/test_search
	touch test_folder/test1 test_folder/test2 test_folder/test3 test_folder/test_search/test4

clean:
	rm -rf bin obj test_folder

.PHONY: clean