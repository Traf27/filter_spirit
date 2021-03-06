#pragma once
#include <fs/lang/generation.hpp>

/*
 * some of these constants would seem to be very trivial but:
 * - code duplication still allows to make typos in strings
 * - having centralized place of language constants makes:
 *   - searching for usage of code in the IDE easier
 *   - refactoring code easier
 *   - changing filter language easier
 *   - finding differences between Filter Spirit and the real
 *     filter accepted by game client easier - some keywords are
 *     different for more consistent filter templates
 */
namespace fs::lang::keywords
{

constexpr auto level        = "Level";
constexpr auto font_size    = "FontSize";
constexpr auto sound_id     = "SoundId";
constexpr auto volume       = "Volume";
constexpr auto group        = "Group";
constexpr auto minimap_icon = "MinimapIcon";
constexpr auto beam_effect  = "Beam";
constexpr auto path         = "Path";
constexpr auto alert_sound  = "AlertSound";

constexpr auto show = generation::show;
constexpr auto hide = generation::hide;

// ---- whitespace ----

// (obviously no keywords for whitespace)

// ---- fundamental tokens ----

// (tokens only, no keywords here)

// ---- literal types ----

constexpr auto true_       = generation::true_;
constexpr auto false_      = generation::false_;

constexpr auto normal      = generation::normal;
constexpr auto magic       = generation::magic;
constexpr auto rare        = generation::rare;
constexpr auto unique      = generation::unique;

constexpr auto circle      = generation::circle;
constexpr auto diamond     = generation::diamond;
constexpr auto hexagon     = generation::hexagon;
constexpr auto square      = generation::square;
constexpr auto star        = generation::star;
constexpr auto triangle    = generation::triangle;

constexpr auto red         = generation::red;
constexpr auto green       = generation::green;
constexpr auto blue        = generation::blue;
constexpr auto white       = generation::white;
constexpr auto brown       = generation::brown;
constexpr auto yellow      = generation::yellow;

constexpr auto shaper      = generation::shaper;
constexpr auto elder       = generation::elder;
constexpr auto crusader    = generation::crusader;
constexpr auto redeemer    = generation::redeemer;
constexpr auto hunter      = generation::hunter;
constexpr auto warlord     = generation::warlord;

// ---- expressions ----

// (nothing)

// ---- definitions ----

// (nothing)

// ---- rules ----

constexpr auto item_level       = generation::item_level;
constexpr auto drop_level       = generation::drop_level;
constexpr auto quality          = generation::quality;
constexpr auto rarity           = generation::rarity;
constexpr auto class_           = generation::class_;
constexpr auto base_type        = generation::base_type;
constexpr auto sockets          = generation::sockets;
constexpr auto linked_sockets   = generation::linked_sockets;
constexpr auto socket_group     = generation::socket_group;
constexpr auto height           = generation::height;
constexpr auto width            = generation::width;
constexpr auto has_explicit_mod = generation::has_explicit_mod;
constexpr auto has_enchantment  = generation::has_enchantment;
constexpr auto prophecy         = generation::prophecy;
constexpr auto has_influence    = generation::has_influence;
constexpr auto stack_size       = generation::stack_size;
constexpr auto gem_level        = generation::gem_level;
constexpr auto identified       = generation::identified;
constexpr auto corrupted        = generation::corrupted;
constexpr auto elder_item       = generation::elder_item;
constexpr auto shaper_item      = generation::shaper_item;
constexpr auto fractured_item   = generation::fractured_item;
constexpr auto synthesised_item = generation::synthesised_item;
constexpr auto any_enchantment  = generation::any_enchantment;
constexpr auto shaped_map       = generation::shaped_map;
constexpr auto elder_map        = generation::elder_map;
constexpr auto blighted_map     = generation::blighted_map;
constexpr auto map_tier         = generation::map_tier;

constexpr auto set_border_color           = generation::set_border_color;
constexpr auto set_text_color             = generation::set_text_color;
constexpr auto set_background_color       = generation::set_background_color;
constexpr auto set_font_size              = generation::set_font_size;
constexpr auto set_alert_sound            = "SetAlertSound";
constexpr auto play_default_drop_sound    = "PlayDefaultDropSound";
constexpr auto set_minimap_icon           = "SetMinimapIcon";
constexpr auto set_beam                   = "SetBeam";

}
