all: test start

game: clean
	@mkdir -p build
	@cd build && cmake -DPC_PLATFORM=True .. && make --no-print-directory && cd ..

test: clean
	@mkdir -p build
	@cd build && cmake -DTEST_PLATFORM=True .. && make --no-print-directory && cd ..
	@./scripts/run_tests.sh

start: game
	@./scripts/run_game.sh

clean:
	@rm -rf build
	@rm -rf *.dSYM

.PHONY: clean game start
