ALLEG=allegro5
MAIN=src/main
LIB=allegro_main

app: $(MAIN)/main.o
	$(CXX) -L$(ALLEG)/lib -l$(LIB) -o $@ $^

$(MAIN)/main.o: CXXFLAGS+=-I$(ALLEG)/include

.PHONY: clean
clean:
	$(RM) app $(MAIN)/main.o

.PHONY: run
run: app
	./app
