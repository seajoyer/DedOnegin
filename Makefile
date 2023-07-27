##
# Onegin - text parser
#

CXX      = clang++
CXXFLAGS = -c -D _DEBUG -ggdb3 -std=c++20 -Wall -Wextra -Weffc++ -Wcast-align -Wcast-qual -Wchar-subscripts -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2 -Winline -Wnon-virtual-dtor -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wsign-promo -Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -fPIE -O0 -Ilib -Isrc

RM = rm -rfv

SRC_DIR = src
LIB_DIR = lib
DOC_DIR = doc

BUILD_DIR = build
TESTS_DIR = tests

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
LIBS = $(wildcard $(LIB_DIR)/*.cpp)
OBJS = $(addprefix $(BUILD_DIR)/,$(patsubst %.cpp,%.o,$(notdir $(LIBS)) $(notdir $(SRCS))))

GENERATED = $(wildcard $(addprefix $(BUILD_DIR)/,bin *.o) $(addprefix $(BUILD_DIR)/$(TESTS_DIR)/,check *.o) $(addprefix $(DOC_DIR)/,html))

TO_TEST = $(addprefix $(BUILD_DIR)/,file_parser.o lexicographic_sort.o quick_sort.o $(TESTS_DIR)/tests.o)

TARGET = $(BUILD_DIR)/bin
TESTS  = $(BUILD_DIR)/$(TESTS_DIR)/check

all: $(TARGET) $(TESTS) # doc

#
# Building the target
##
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

$(BUILD_DIR)/%.o: $(LIB_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -o $@

#
# Building docs
##
$(DOC_DIR)/html/index.html: $(TARGET)
	@echo \nBuilding docs...
	cd doc ; doxygen doxygen.conf

#
# Building tests
##
$(TESTS): $(TO_TEST)
	mkdir -p $(@D)
	$(CXX) $(TO_TEST) -lgtest -o $@

$(BUILD_DIR)/$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -o $@

#
# Commands
##
run: $(TARGET)
	$(TARGET)

doc: $(DOC_DIR)/html/index.html

check: $(TESTS)
	$(TESTS)

clean:
	$(RM) $(GENERATED)

# end
