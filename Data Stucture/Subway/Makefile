all: Subway.class

%.class: %.java
	javac $<

test: all
	java -ea Subway tests/data < tests/stdin > tests/stdout
score: all
	@./test

clean:
	rm -f *.class

.PHONY: run clean
