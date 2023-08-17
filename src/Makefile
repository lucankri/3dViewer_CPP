GCC = g++ -Wall -Werror -Wextra -std=c++17
TESTFLAGS=-lgtest -lgtest_main
FILES = 3DViewer_v2/model/*.cc
TESTS = tests.cc


.PHONY: clean tests

all: install check gcov_report

clean:
	rm -rf *.a && rm -rf *.o *.exe test
	rm -rf *.info && rm -rf *.gcda && rm -rf *.gcno &&  rm -rf *.gcov *.html *.css *.cfg
	rm -rf report/ && rm -rf *.out
	rm -rf .clang-format 3DViewer_v2/.clang-format manual

tests: clean
	$(GCC) --coverage $(TESTS) $(FILES) $(TESTFLAGS) -o test
	./test

gcov_report: tests
	lcov --no-external -t "test" -o report.info -c -d .
	genhtml -o report.html report.info
	rm *.gcda *.gcno
	open report.html/index.html 2>/dev/null


install:
	rm -rf ../build
	cd 3DViewer_v2 && cmake .
	cd 3DViewer_v2 && make
	mkdir ../build
	mv 3DViewer_v2/3DViewer_v2.app ../build
	open ../build/3DViewer_v2.app/Contents/MacOS/3DViewer_v2

uninstall:
	cd 3DViewer_v2 && make clean
	rm -rf 3DViewer_v2/CMakeFiles 3DViewer_v2/CMakeCache.txt 3DViewer_v2/Makefile
	rm -rf 3DViewer_v2/library/CMakeFiles 3DViewer_v2/cmake_install.cmake 3DViewer_v2/library/CMakeCache.txt
	rm -rf 3DViewer_v2/library/Makefile
	rm -rf 3DViewer_v2/library/QCustomPlot-library/*.cmake 3DViewer_v2/library/QCustomPlot-library/CMakeFiles
	rm -rf 3DViewer_v2/library/QCustomPlot-library/Makefile
	rm -rf ../build

dist_clean:
	cd ../ && rm -rf 3DViewer_v2.tgz

dist:
	cd ../ && tar -czf 3DViewer_v2.tgz src

dvi_clean:
	rm -rf manual


dvi: dvi_clean
	rm -rf manual
	makeinfo manual.texi --html
	open manual/index.html

leaks: tests
	leaks -atExit -- ./test

check:
	cp ../materials/linters/.clang-format .clang-format
	cp ../materials/linters/.clang-format 3DViewer_v2/.clang-format
	clang-format -n 3DViewer_v2/*.cc
	clang-format -n 3DViewer_v2/controller/*.cc 3DViewer_v2/controller/*.h
	clang-format -n 3DViewer_v2/model/*.cc 3DViewer_v2/model/*.h
	clang-format -n 3DViewer_v2/view/*.cc 3DViewer_v2/view/*.h
	clang-format -n *.cc
	cppcheck --language=c++ *.cc
	cppcheck --language=c++ 3DViewer_v2/*.cc
	cppcheck --language=c++ 3DViewer_v2/model/*.cc
	cppcheck --language=c++ 3DViewer_v2/model/*.h
	cppcheck --language=c++ 3DViewer_v2/controller/*.cc
	cppcheck --language=c++ 3DViewer_v2/controller/*.h
	cppcheck --language=c++ 3DViewer_v2/view/*.cc
	cppcheck --language=c++ 3DViewer_v2/view/*.h
	rm -rf .clang-format
	rm -rf 3DViewer_v2/.clang-format
