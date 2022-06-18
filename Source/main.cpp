#include "Initialize.hpp"
#include "Game.hpp"

int main(int argc, char* argv[]) {
	std::unique_ptr<Initialize> initialize(new Initialize(800, 600, "Game"));
	return 0;
}