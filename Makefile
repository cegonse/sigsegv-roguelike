UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
NODE := nodejs
endif
ifeq ($(UNAME_S),Darwin)
NODE := node
endif

all: test start

game: clean resources
	@mkdir -p build
	@cd build && cmake -G Ninja -DPC_PLATFORM=True .. && cmake --build . -j8 && cd ..

resources:
	@mkdir -p build/resources
	@cd ./resource_packer && npm install && cd ..
	@$(NODE) ./resource_packer/main.js resources/default default
	@mv default.pack ./build/resources

test: clean
	@mkdir -p build
	@cd build && cmake -G Ninja -DTEST_PLATFORM=True .. && cmake --build . -j8 && cd ..
	@./scripts/run_tests.sh

test-resource-packer:
	@cd resource_packer && npm test && cd ..

start: game
	@./scripts/run_game.sh

clean:
	@rm -rf build
	@rm -rf *.dSYM

.PHONY: clean game start test-resource-packer resources test
