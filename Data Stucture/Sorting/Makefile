all: SortingTest.class

%.class: %.java
	javac $<

.PHONY: clean run
clean:
	rm -f *.class

run: SortingTest.class
	java SortingTest
