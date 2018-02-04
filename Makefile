ALLEG=allegro5
MAIN=src/main
ALLEGW=src/allegw
ALLEGWSRC=$(wildcard $(ALLEGW)/*.cpp)
ALLEGWOBJ=$(ALLEGWSRC:.cpp=.o)
LIB= -lallegro -lallegro_main
CXXFLAGS+=-std=c++1z -Wall -Wextra -Werror -I$(ALLEG)/include

app: $(MAIN)/main.o $(ALLEGWOBJ)
	$(CXX) $(CXXFLAGS) -L$(ALLEG)/lib $(LIB) -o $@ $^

.PHONY: clean
clean:
	$(RM) app
	$(RM) $(MAIN)/main.o
	$(RM) $(ALLEGWOBJ)

.PHONY: run
run: app
	
