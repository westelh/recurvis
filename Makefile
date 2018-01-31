ALLEG=allegro5
MAIN=src/main
ALLEGW=src/allegw
LIB= -lallegro -lallegro_main
CXXFLAGS+=-std=c++1z -Wall -Wextra -Werror -I$(ALLEG)/include

app: $(MAIN)/main.o $(wildcard $(ALLEGW)/*.cpp)
	$(CXX) $(CXXFLAGS) -L$(ALLEG)/lib $(LIB) -o $@ $^

.PHONY: clean
clean:
	$(RM) app $(MAIN)/main.o
	$(RM) $(wildcard $(ALLEGW)/*.o)

.PHONY: run
run: app
	
