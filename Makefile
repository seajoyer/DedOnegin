##
# Onegin - text parser
#

CXX=clang++
CXXFLAGS=-c -D _DEBUG -ggdb3 -std=c++20 -Wall -Wextra -Weffc++ -Wcast-align -Wcast-qual -Wchar-subscripts -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2 -Winline -Wnon-virtual-dtor -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wsign-promo -Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -fPIE -O0 -Ilib -Isrc
RM=rm -rfv

SRC_DIR=src
LIB_DIR=lib
DOC_DIR=doc
BUILD_DIR=build
TESTS_DIR=tests

SRCS=$(wildcard $(SRC_DIR)/*.cpp)
LIBS=$(wildcard $(LIB_DIR)/*.cpp)
OBJS=$(addprefix $(BUILD_DIR)/,$(patsubst %.cpp,%.o,$(notdir $(LIBS)) $(notdir $(SRCS))))
# TEST_OBJS=$(addprefix $(BUILD_DIR)/,tests.o compare_floats.o solve_equation.o)
GENERATED_FILES=$(wildcard $(BUILD_DIR)/*.o) $(addprefix $(BUILD_DIR)/,check bin) $(DOC_DIR)/html
TESTS=$(BUILD_DIR)/check
TARGET=$(BUILD_DIR)/bin

all: $(TARGET) $(TESTS) doc

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
# $(TESTS): $(TEST_OBJS)
# 	$(CXX) $(TEST_OBJS) -o $@

# $(BUILD_DIR)/%.o: $(TESTS_DIR)/%.cpp
# 	$(CXX) $(CXXFLAGS) $< -o $@

run:
	$(TARGET)

doc: $(DOC_DIR)/html/index.html

check:
	$(TESTS)

clean:
	$(RM) $(GENERATED_FILES)

# end
