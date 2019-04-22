#include "fs/compiler/compiler.hpp"
#include "fs/compiler/evaluate.hpp"
#include "fs/compiler/error.hpp"
#include "fs/parser/ast.hpp"
#include "fs/lang/constants_map.hpp"

#include <cassert>
#include <string_view>
#include <utility>
#include <sstream>

namespace
{

using namespace fs;
namespace ast = parser::ast;

/*
 * core entry point into adding constants
 *
 * task:
 * Add object only if valid, error with appropriate information otherwise; in any case
 * after either successful addition or any error return immediately.
 *
 * flow:
 * - check that name is not already taken and error if so
 *   (it's impossible to have multiple objects with the same name)
 *   (as of now, filter's language has no scoping/name shadowing)
 * - convert expression to language object and proceed
 */
[[nodiscard]]
std::optional<compiler::error::error_variant> add_constant_from_definition(
	const ast::constant_definition& def,
	lang::constants_map& map,
	const itemdata::item_price_data& item_price_data)
{
	const ast::identifier& wanted_name = def.name;
	const ast::value_expression& value_expression = def.value;

	const auto it = map.find(wanted_name.value); // C++17: use if (expr; cond)
	if (it != map.end())
	{
		const lang::position_tag place_of_original_name = parser::get_position_info(it->second.name_origin);
		const lang::position_tag place_of_duplicated_name = parser::get_position_info(wanted_name);
		return compiler::error::name_already_exists{place_of_duplicated_name, place_of_original_name};
	}

	std::variant<lang::object, compiler::error::error_variant> expr_result =
		compiler::evaluate_value_expression(value_expression, map, item_price_data);

	if (std::holds_alternative<compiler::error::error_variant>(expr_result))
		return std::get<compiler::error::error_variant>(expr_result);

	const auto pair = map.emplace(
		wanted_name.value,
		lang::named_object{
			std::get<lang::object>(std::move(expr_result)),
			parser::get_position_info(wanted_name)});
	assert(pair.second); // C++20: use [[assert]]
	(void) pair; // ignore insertion result in release builds
	return std::nullopt;
}

} // namespace

namespace fs::compiler
{

[[nodiscard]]
std::variant<lang::constants_map, compiler::error::error_variant> resolve_constants(
	const std::vector<parser::ast::constant_definition>& constant_definitions,
	const itemdata::item_price_data& item_price_data)
{
	lang::constants_map map;

	for (const ast::constant_definition& def : constant_definitions)
	{
		const std::optional<compiler::error::error_variant> error =
			add_constant_from_definition(def, map, item_price_data);

		if (error)
			return *error;
	}

	return map;
}

[[nodiscard]]
std::string generate_filter(const std::vector<lang::filter_block>& blocks)
{
	std::stringstream ss;

	for (const lang::filter_block& block : blocks)
		block.generate(ss);

	return ss.str();
}

} // namespace