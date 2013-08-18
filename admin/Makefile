target := dump_core
sources := dump_core.cpp
CXXFLAGS := -g -Wall
CXX := g++
OBJDIR := build

all: build_dir $(target)

$(target) : $(addprefix $(OBJDIR)/,$(sources:.cpp=.o))
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@


-include $(addprefix $(OBJDIR)/,$(sources:.cpp=.d))

$(OBJDIR)/%.d: %.cpp
	@ set -e; rm -f $@; \
	$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

build_dir:
	if [ ! -d "$(OBJDIR)" ]; then	mkdir -p "$(OBJDIR)"; fi
   

clean:
	rm -rf $(OBJDIR)/*.o $(OBJDIR)/*.d
