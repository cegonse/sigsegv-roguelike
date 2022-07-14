all: test start

game: clean resources
	@mkdir -p build
	@cd build && cmake -DPC_PLATFORM=True .. && make --no-print-directory && cd ..

resources:
	@mkdir -p build/resources
	@node ./resource_packer/main.js ./resources/default
	@mv resources/default.pack ./build/resources
	@cp resources/default/*.png ./build/resources

test: clean
	@mkdir -p build
	@cd build && cmake -DTEST_PLATFORM=True .. && make --no-print-directory && cd ..
	@./scripts/run_tests.sh

test-resource-packer:
	@cd resource_packer && npm test && cd ..

start: game
	@./scripts/run_game.sh

clean:
	@rm -rf build
	@rm -rf *.dSYM

.PHONY: clean game start test-resource-packer resources
