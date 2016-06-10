all: Subway.class

%.class: %.java
	javac $<

run: all
	java Subway data

clean:
	rm -f *.class

.PHONY: run clean
