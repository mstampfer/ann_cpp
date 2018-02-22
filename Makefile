CXX = g++
DEBUG_LEVEL = -g
EXTRA_FLAGS = -std=c++17 -Wall -MMD -Werror=vla 
CPPFLAGS = -I /usr/include/python3.6dm/ -I /usr/lib/python3/dist-packages/numpy/core/include/ -I /usr/lib/python3/dist-packages/matplotlib/ -I /home/marcel/workspace
LDFLAGS = -L /usr/lib/python3.6/config-3.6dm-x86_64-linux-gnu/ -L /usr/lib/python3/dist-packages/matplotlib/
LDLIBS = -lpython3.6dm 
CXXFLAGS = $(DEBUG_LEVEL) $(EXTRA_FLAGS) 
LFLAGS = $(LDFLAGS) $(LDLIBS)
O_FILES = $(SRC_FILES:%.cpp=%.o)
DEPS = ann.h
DEPENDS = $(OBJECTS:.o=.d)
OBJECTS = main.o 

EXEC = ann
$(EXEC) : $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LFLAGS) -o $(EXEC) 
-include $(DEPENDS) 

.PHONY: clean
clean:
	rm -f *.o *.d $(EXEC)
