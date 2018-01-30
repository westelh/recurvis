ALLEG=allegro5
MAIN=src/main
ALLEGW=src/allegw
LIB=allegro_main
CXXFLAGS+=-std=c++1z -Wall -Wextra -Werror

app: $(MAIN)/main.o $(ALLEGW)/allegw.o
	$(CXX) -L$(ALLEG)/lib -l$(LIB) -o $@ $^

$(MAIN)/main.o: CXXFLAGS+=-I$(ALLEG)/include
$(ALLEGW)/allegw.o: $(wildcard $(ALLEGW)/*.cpp)
	$(CXX) $(CXXFLAGS) -c -o $@ $^

.PHONY: clean
clean:
	$(RM) app $(MAIN)/main.o
	$(RM) $(wildcard $(ALLEGW)/*.o)

.PHONY: run
run: app
	
