#pragma once
#include "lang/types.hpp"
#include <memory>
#include <variant>
#include <vector>

namespace fs::lang
{

template <typename T>
struct range_bound
{
	T value;
	bool inclusive;
};

enum class range_relation
{
	identical, superset, subset, intersect, disjoint
};

template <typename T>
class range_condition
{
public:
	range_condition(comparison_type comparison, T value)
	{
		if (comparison == comparison_type::greater)
		{
			lower_bound = {value, false};
		}
		else if (comparison == comparison_type::greater_equal)
		{
			lower_bound = {value, true};
		}
		else if (comparison == comparison_type::less)
		{
			upper_bound = {value, false};
		}
		else if (comparison == comparison_type::less_equal)
		{
			upper_bound = {value, true};
		}
		else
		{
			lower_bound = {value, true};
			upper_bound = {value, true};
		}
	}

	range_relation relation_with(range_condition other) const
	{
		// TODO implement
		return range_relation::identical;
	}

	bool includes(range_condition other) const
	{
		// FIXME implement relation testing
		// return enum: exact/superset/subset/intersect/disjoint
		return true;
	}

private:
	std::optional<range_bound<T>> lower_bound;
	std::optional<range_bound<T>> upper_bound;
};

using numeric_range_condition = range_condition<int>;
using rarity_range_condition = range_condition<rarity>;

struct condition_set
{
	std::optional<numeric_range_condition> item_level;
	std::optional<numeric_range_condition> drop_level;
	std::optional<numeric_range_condition> quality;
	std::optional<rarity_range_condition> rarity;
	std::shared_ptr<std::vector<std::string>> class_;
	std::shared_ptr<std::vector<std::string>> base_type;
	std::optional<numeric_range_condition> sockets;
	std::optional<numeric_range_condition> links;
	std::optional<socket_group> socket_group;
	std::optional<numeric_range_condition> height;
	std::optional<numeric_range_condition> width;
	std::shared_ptr<std::vector<std::string>> has_explicit_mod;
	std::optional<numeric_range_condition> stack_size;
	std::optional<numeric_range_condition> gem_level;
	std::optional<numeric_range_condition> map_tier;
	std::optional<boolean> is_identified;
	std::optional<boolean> is_corrupted;
	std::optional<boolean> is_shaper_item;
	std::optional<boolean> is_elder_item;
	std::optional<boolean> is_shaped_map;
};

}
