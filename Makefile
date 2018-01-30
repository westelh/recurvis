app: src/main/main.o
	$(CXX) src/main/main.o -o app

.PHONY: clean
clean:
	$(MAKE) -C src/main clean
	$(RM) app
