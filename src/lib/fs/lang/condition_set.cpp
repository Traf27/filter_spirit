#include <fs/lang/condition_set.hpp>
#include <fs/lang/generation.hpp>

#include <cassert>

namespace
{

using namespace fs;

std::ostream& operator<<(std::ostream& os, lang::rarity r)
{
	namespace lg = lang::generation;

	switch (r)
	{
		case lang::rarity::normal:
			os << lg::normal;
			break;
		case lang::rarity::magic:
			os << lg::magic;
			break;
		case lang::rarity::rare:
			os << lg::rare;
			break;
		case lang::rarity::unique:
			os << lg::unique;
			break;
		default:
			break;
	}

	return os;
}

template <typename T>
void output_range_condition(
	lang::range_condition<T> range,
	const char* name,
	std::ostream& output_stream)
{
	if (!range.has_anything())
		return;

	if (range.is_exact())
	{
		output_stream << '\t' << name << " = " << (*range.lower_bound).value << '\n';
		return;
	}

	if (range.lower_bound.has_value())
	{
		output_stream << '\t' << name << ' ';
		const lang::range_bound<T>& bound = *range.lower_bound;

		if (bound.inclusive)
			output_stream << ">= " << bound.value;
		else
			output_stream << "> " << bound.value;

		output_stream << '\n';
	}

	if (range.upper_bound.has_value())
	{
		output_stream << '\t' << name << ' ';
		const lang::range_bound<T>& bound = *range.upper_bound;

		if (bound.inclusive)
			output_stream << "<= " << bound.value;
		else
			output_stream << "< " << bound.value;

		output_stream << '\n';
	}
}

void output_socket_group_condition(
	std::optional<lang::socket_group_condition> cond,
	std::ostream& output_stream)
{
	if (!cond.has_value())
		return;

	const auto output_letter = [&](char letter, int times)
	{
		for (int i = 0; i < times; ++i)
			output_stream << letter;
	};

	namespace lg = lang::generation;
	const lang::socket_group& sg = (*cond).group;
	assert(sg.is_valid());

	output_stream << '\t' << lg::socket_group << ' ';
	output_letter(lg::r, sg.r);
	output_letter(lg::g, sg.g);
	output_letter(lg::b, sg.b);
	output_letter(lg::w, sg.w);
	output_stream << '\n';
}

void output_strings_condition(
	const lang::strings_condition& cond,
	const char* name,
	std::ostream& output_stream)
{
	if (cond.strings == nullptr)
		return;

	output_stream << '\t' << name;

	if (cond.exact_match_required)
		output_stream << " ==";

	for (const std::string& str : *cond.strings)
		output_stream << " \"" << str << '"';

	output_stream << '\n';
}

void output_influences_condition(
	const lang::influences_condition& cond,
	const char* name,
	std::ostream& output_stream)
{
	if (cond.influences == nullptr)
		return;

	output_stream << '\t' << name;

	if (cond.exact_match_required)
		output_stream << " ==";

	for (lang::influence infl : *cond.influences) {
		output_stream << ' ';

		namespace lg = lang::generation;

		switch (infl) {
			case lang::influence::shaper:
				output_stream << lg::shaper;
				break;
			case lang::influence::elder:
				output_stream << lg::elder;
				break;
			case lang::influence::crusader:
				output_stream << lg::crusader;
				break;
			case lang::influence::redeemer:
				output_stream << lg::redeemer;
				break;
			case lang::influence::hunter:
				output_stream << lg::hunter;
				break;
			case lang::influence::warlord:
				output_stream << lg::warlord;
				break;
			default:
				break;
		}
	}

	output_stream << '\n';
}

void output_boolean_condition(
	std::optional<lang::boolean_condition> cond,
	const char* name,
	std::ostream& output_stream)
{
	if (!cond.has_value())
		return;

	output_stream << '\t' << name << ' ';

	const lang::boolean_condition& bc = *cond;
	if (bc.value.value)
		output_stream << lang::generation::true_;
	else
		output_stream << lang::generation::false_;

	output_stream << '\n';
}

} // namespace

namespace fs::lang
{

void condition_set::generate(std::ostream& output_stream) const
{
	namespace lg = lang::generation;
	output_range_condition(item_level, lg::item_level,     output_stream);
	output_range_condition(drop_level, lg::drop_level,     output_stream);
	output_range_condition(quality,    lg::quality,        output_stream);
	output_range_condition(rarity,     lg::rarity,         output_stream);
	output_range_condition(sockets,    lg::sockets,        output_stream);
	output_range_condition(links,      lg::linked_sockets, output_stream);
	output_range_condition(height,     lg::height,         output_stream);
	output_range_condition(width,      lg::width,          output_stream);
	output_range_condition(stack_size, lg::stack_size,     output_stream);
	output_range_condition(gem_level,  lg::gem_level,      output_stream);
	output_range_condition(map_tier,   lg::map_tier,       output_stream);

	output_socket_group_condition(socket_group, output_stream);

	output_boolean_condition(is_identified,       lg::identified,       output_stream);
	output_boolean_condition(is_corrupted,        lg::corrupted,        output_stream);
	output_boolean_condition(is_elder_item,       lg::elder_item,       output_stream);
	output_boolean_condition(is_shaper_item,      lg::shaper_item,      output_stream);
	output_boolean_condition(is_fractured_item,   lg::fractured_item,   output_stream);
	output_boolean_condition(is_synthesised_item, lg::synthesised_item, output_stream);
	output_boolean_condition(is_enchanted,        lg::any_enchantment,  output_stream);
	output_boolean_condition(is_shaped_map,       lg::shaped_map,       output_stream);
	output_boolean_condition(is_elder_map,        lg::elder_map,        output_stream);
	output_boolean_condition(is_blighted_map,     lg::blighted_map,     output_stream);

	output_strings_condition(class_,           lg::class_,           output_stream);
	output_strings_condition(base_type,        lg::base_type,        output_stream);
	output_strings_condition(has_explicit_mod, lg::has_explicit_mod, output_stream);
	output_strings_condition(has_enchantment,  lg::has_enchantment,  output_stream);
	output_strings_condition(prophecy,         lg::prophecy,         output_stream);

	output_influences_condition(has_influence, lg::has_influence, output_stream);
}

bool condition_set::is_valid() const
{
	const auto is_valid_array_condition = [](const auto& shared_ptr_array)
	{
		// no condition: ok, we just don't require item to have this property
		if (shared_ptr_array == nullptr)
			return true;

		// empty list of allowed values: there are no items that can match this block
		// game client will not accept an empty list so return that the block is invalid
		if ((*shared_ptr_array).empty())
			return false;

		return true;
	};

	return is_valid_array_condition(class_.strings)
		&& is_valid_array_condition(base_type.strings)
		&& is_valid_array_condition(has_explicit_mod.strings)
		&& is_valid_array_condition(has_enchantment.strings)
		&& is_valid_array_condition(prophecy.strings)
		&& is_valid_array_condition(has_influence.influences);
}

}
