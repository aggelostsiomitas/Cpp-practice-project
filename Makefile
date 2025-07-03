#compiler and flags 
CXX = g++
CXXFLAGS = -Iinc -Wall -Wextra -std=c++17   -fPIC #Wall and Wextra are for warnings,-Inc is for includeing files form inc directory , c++17 is
#to point that i use the c++17

#directories of project
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
TEST_DIR = tests
EXAMPLE_DIR = example

SRCS = $(wildcard $(SRC_DIR)/*.cpp) #take all the cpp files that are locates in SRC_DIR
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS)) #take the cpp files make it to object file -0 ,find the files in SRCS
LIB = $(LIB_DIR)/Libmatrix.a  #the library output will be Libmatrix.a
LIB_SHARED = $(LIB_DIR)/libmatrix.so
# Default target
all: $(LIB) $(LIB_SHARED) test demo
  #the make will built the libmatrix,test,demo 

# Object compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir  -p $(OBJ_DIR)
	@echo   "Compiling $< ..."
	$(CXX) $(CXXFLAGS) -c $< -o $@
  # $< is for source file , $@ is for target file , the .cpp files  becomes .o

# Static library
$(LIB): $(OBJS)
	@mkdir -p $(LIB_DIR)
	@echo "Creating static library $@ ..."
	ar rcs $@ $^   
  # ar creates static libraries rcs:r for replacing/inserting files ,c for creating archive if it does not exist 
  # and s for writing the object, $@ for the target file $^ for all dependencies


# Shared library
$(LIB_SHARED): $(OBJS)
	@mkdir -p $(LIB_DIR)
	@echo "Creating shared library $@ ..."
	$(CXX) -shared -o $@ $^

# Build test executable
test: $(TEST_DIR)/test_matrix.cpp $(LIB)
	@echo "Building test executable..."
	$(CXX) $(CXXFLAGS) -L$(LIB_DIR) -Iinc $< -lmatrix -o $(TEST_DIR)/test_matrix

# Build demo executable
demo: $(EXAMPLE_DIR)/demo.cpp $(LIB)
	@echo "Building demo executable..."
	$(CXX) $(CXXFLAGS) -L$(LIB_DIR) -Iinc $< -lmatrix -o $(EXAMPLE_DIR)/demo

# Clean up
clean:
	@echo "Cleaning up..."
	rm -rf $(OBJ_DIR) $(LIB_DIR) $(TEST_DIR)/test_matrix $(EXAMPLE_DIR)/demo

.PHONY: all clean test demo
