all: Subway.class

%.class: %.java
	javac $<

run: all
	java -ea Subway tests/data < tests/stdin > tests/stdout

clean:
	rm -f *.class

.PHONY: run clean
