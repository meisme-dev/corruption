#include "Initialize.hpp"
#include "Game.hpp"

int main(int argc, char* argv[]) {
	std::unique_ptr<Initialize> initialize(new Initialize(600, 800, "Game"));
	return 0;
}