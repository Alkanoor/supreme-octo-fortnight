MAKE = make


all: C++-Swing

C++-Swing:
	$(MAKE) -C cpp
	$(MAKE) -C swing

run: all
	$(MAKE) -C cpp run
	@sleep 0.2
	$(MAKE) -C swing run

clean:
	$(MAKE) -C cpp clean
	$(MAKE) -C swing clean