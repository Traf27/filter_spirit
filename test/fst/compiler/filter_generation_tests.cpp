#include "fst/compiler/common.hpp"
#include "fst/parser/common.hpp"

#include "fs/compiler/process_input.hpp"
#include "fs/log/buffered_logger.hpp"
#include "fs/itemdata/types.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <string>
#include <string_view>

namespace ut = boost::unit_test;
namespace tt = boost::test_tools;

using range_type = fs::parser::range_type;
using iterator_type = fs::parser::iterator_type;

std::string generate_filter(
	std::string_view input,
	const fs::itemdata::item_price_data& ipd = {})
{
	fs::buffered_logger logger;
	std::optional<std::string> filter = fs::compiler::process_input(input, ipd, false, logger);
	const auto log_data = logger.flush_out();
	BOOST_TEST_REQUIRE(filter.has_value(), "filter generation failed:\n" << log_data);
	return *filter;
}

BOOST_AUTO_TEST_SUITE(compiler_suite)

	BOOST_AUTO_TEST_CASE(minimal_input_generate_filter)
	{
		const std::string filter = generate_filter(fsut::parser::minimal_input());
		BOOST_TEST(filter.empty());
	}

	BOOST_AUTO_TEST_SUITE(compiler_filter_generation_suite, * ut::depends_on("compiler_suite/minimal_input_generate_filter"))

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()