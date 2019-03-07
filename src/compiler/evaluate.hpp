#pragma once

#include "parser/ast.hpp"
#include "lang/types.hpp"
#include "lang/constants_map.hpp"
#include "compiler/error.hpp"
#include "itemdata/types.hpp"

#include <variant>

namespace fs::compiler
{

[[nodiscard]]
std::variant<lang::object, error::error_variant> evaluate_value_expression(
	const parser::ast::value_expression& value_expression,
	const lang::constants_map& map,
	const itemdata::item_price_data& item_price_data);

[[nodiscard]]
lang::object evaluate_literal(
	const parser::ast::literal_expression& expression);

[[nodiscard]]
std::variant<lang::object, error::error_variant> evaluate_array(
	const parser::ast::array_expression& expression,
	const lang::constants_map& map);

[[nodiscard]]
std::variant<lang::object, error::error_variant> evaluate_function_call(
	const parser::ast::function_call& function_call,
	const lang::constants_map& map);

[[nodiscard]]
std::variant<lang::object, error::error_variant> evaluate_price_range_query(
	const parser::ast::price_range_query& price_range_query,
	const lang::constants_map& map,
	const itemdata::item_price_data& item_price_data);

[[nodiscard]]
std::variant<lang::object, error::error_variant> evaluate_identifier(
	const parser::ast::identifier& identifier,
	const lang::constants_map& map);

[[nodiscard]]
std::optional<error::non_homogeneous_array> verify_array_homogeneity(
	const lang::array_object& array);

}
