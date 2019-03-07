#pragma once

#include "parser/ast.hpp"
#include "lang/constants_map.hpp"
#include "compiler/error.hpp"
#include "itemdata/types.hpp"

#include <algorithm>
#include <variant>
#include <type_traits>

namespace fs::compiler
{

[[nodiscard]]
std::variant<lang::price_range, error::error_variant> construct_price_range(
	const parser::ast::function_arguments& arguments,
	const lang::constants_map& map);

/**
 * @brief run the [mix, max) query against given sequence of sorted items
 *
 * @details the range MUST BE sorted, otherwise the behaviour is undefined
 */
template <typename RandomAccessIterator> [[nodiscard]]
lang::array_object evaluate_price_range_query_on_sorted_range(
	lang::price_range range,
	RandomAccessIterator first,
	RandomAccessIterator last)
{
	static_assert(
		std::is_same_v<itemdata::price_data, decltype(first->price_data)>,
		"iterator must dereference to an object with price_data field");

	const auto compare = [](const auto& lhs, const auto& rhs)
	{
		return lhs.price_data.mean < rhs.price_data.mean;
	};

	const auto lower_bound = std::lower_bound(first, last, range.min, compare);
	const auto upper_bound = std::upper_bound(first, last, range.max, compare);

	lang::array_object array;
	for (auto it = lower_bound; it != upper_bound; ++it)
	{
		array.push_back(
			lang::object{
				lang::single_object{lang::string{it->base_type_name}},

				std::nullopt});
	}
}

}
