all: Matching.class

%.class: %.java
	javac $<

.PHONY: clean run
clean:
	rm -f *.class

run: Matching.class
	@java Matching
