ALLEG=allegro5/build
MAIN=src/main
ALLEGW=src/allegw
ALLEGWSRC=$(wildcard $(ALLEGW)/*.cpp)
ALLEGWOBJ=$(ALLEGWSRC:.cpp=.o)
RV=src/rv
RVSRC=$(wildcard $(RV)/*.cpp)
RVOBJ=$(RVSRC:.cpp=.o)
LIB=-L$(ALLEG)/lib -lallegro -lallegro_main -lallegro_primitives
CXXFLAGS+=-std=c++1z -Wall -Wextra -Werror -I$(ALLEG)/include

app: $(MAIN)/main.o $(ALLEGWOBJ) $(RVOBJ)
	$(CXX) $(CXXFLAGS) $^ -o$@ $(LIB)

.PHONY: clean
clean:
	$(RM) app
	$(RM) $(MAIN)/main.o
	$(RM) $(ALLEGWOBJ)
	$(RM) $(RVOBJ)

.PHONY: run
run: app
	
