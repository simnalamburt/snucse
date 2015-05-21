all: filter semaphore

%: %.rs
	rustc $< -C opt-level=3
