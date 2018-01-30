ALLEG=allegro5
MAIN=src/main
CXXFLAGS+=-I$(ALLEG)/include

LINK_ALLEG=-L$(ALLEG)/lib -lallegro_main
app: src/main/main.o
	$(CXX) $(LINK_ALLEG) -o $@ $^

.PHONY: clean
clean:
	$(RM) app $(MAIN)/main.o

.PHONY: run
run: app
	./app
