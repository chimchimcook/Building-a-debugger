#include <catch2/catch_test_macros.hpp>
#include <libsdb/error.hpp>
#include <libsdb/process.hpp>
#include <signal.h>
#include <sys/types.h>

using namespace sdb;

namespace {
bool process_exists(pid_t pid) {
	/* If you call kill with a signal of 0, it doesn’t send a sig-
	nal to the process but still carries out the existence and permission checks
	it would make when actually sending a signal */
	return kill(pid, 0) != -1 && errno != ESRCH;
}
} // namespace

TEST_CASE("process::launch success", "[process]") {
	auto proc = process::launch("yes");
	REQUIRE(process_exists(proc->pid()));
}

TEST_CASE("process::launch no such program", "[process]") {
	REQUIRE_THROWS_AS(process::launch("you_do_not_have_to_be_good"), error);
}
