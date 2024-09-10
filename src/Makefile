CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I. -I./array -I./associative_container -I./container -I./container_adaptor -I./list -I./map -I./multiset -I./pair -I./queue -I./sequence_container -I./set -I./set_container -I./sorted_container -I./stack -I./thing -I./vector

GTEST_FLAGS = -pthread -lgtest -lgtest_main

PROJECT_SRC = $(wildcard container/*.cpp)
TEST_SRC = $(wildcard test/*.cpp)
PROJECT_OBJ = $(PROJECT_SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)
OBJ = $(PROJECT_OBJ) $(TEST_OBJ)
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

TEST_EXEC = test_exec

all: $(TEST_EXEC)

$(TEST_EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(GCOV_FLAGS) $(OBJ) $(GTEST_FLAGS) -o $(TEST_EXEC)

clean:
	rm -f $(PROJECT_OBJ) $(TEST_OBJ) $(TEST_EXEC) **/*.gcda **/*.gcno coverage.info
	rm -rf coverage

container/%.o: container/%.cpp
	$(CXX) $(CXXFLAGS) $(GCOV_FLAGS) -c $< -o $@

test/%.o: test/%.cpp
	$(CXX) $(CXXFLAGS) $(GCOV_FLAGS) -c $< -o $@

gcov_report: $(TEST_EXEC)
	./$(TEST_EXEC)
	lcov --capture --directory . --output-file coverage.info --ignore-errors source --ignore-errors graph
	lcov --remove coverage.info '/usr/*' --output-file coverage.info
	genhtml coverage.info --output-directory coverage
	firefox coverage/index.html

style:
	clang-format -n -style=Google $(wildcard ./**/*.h ./**/*.tpp ./**/*.cpp ./*.h ./*.tpp ./*.cpp)

fix_style:
	clang-format -i -style=Google $(wildcard ./**/*.h ./**/*.tpp ./**/*.cpp ./*.h ./*.tpp ./*.cpp)

valgrind: $(TEST_EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_EXEC)
