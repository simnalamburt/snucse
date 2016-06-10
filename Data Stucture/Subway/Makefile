all: Subway.class

%.class: %.java
	javac $<

run: all
	java Subway tests/data < tests/stdin

clean:
	rm -f *.class

.PHONY: run clean
