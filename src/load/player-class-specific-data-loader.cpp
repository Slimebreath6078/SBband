#include "load/player-class-specific-data-loader.h"
#include "load/load-util.h"
#include "player-info/bard-data-type.h"
#include "player-info/bluemage-data-type.h"
#include "player-info/force-trainer-data-type.h"
#include "player-info/magic-eater-data-type.h"
#include "player-info/mane-data-type.h"
#include "player-info/monk-data-type.h"
#include "player-info/ninja-data-type.h"
#include "player-info/samurai-data-type.h"
#include "player-info/smith-data-type.h"
#include "player-info/sniper-data-type.h"
#include "player-info/spell-hex-data-type.h"
#include "util/enum-converter.h"

#include <tuple>
#include <vector>

void PlayerClassSpecificDataLoader::operator()(no_class_specific_data &) const
{
}

void PlayerClassSpecificDataLoader::operator()(std::shared_ptr<smith_data_type> &smith_data) const
{
    while (true) {
        auto essence = rd_s16b();
        auto amount = rd_s16b();
        if (essence < 0 && amount < 0) {
            break;
        }
        smith_data->essences[i2enum<SmithEssenceType>(essence)] = amount;
    }
}

void PlayerClassSpecificDataLoader::operator()(std::shared_ptr<force_trainer_data_type> &force_trainer_data) const
{
    force_trainer_data->ki = rd_s32b();
}

void PlayerClassSpecificDataLoader::operator()(std::shared_ptr<bluemage_data_type> &bluemage_data) const
{
    rd_FlagGroup(bluemage_data->learnt_blue_magics, rd_byte);
}

void PlayerClassSpecificDataLoader::operator()(std::shared_ptr<magic_eater_data_type> &magic_eater_data) const
{
    auto load_item_group = [](auto &item_group) {
        auto item_count = rd_u16b();
        for (auto i = 0U; i < item_count; ++i) {
            auto charge = rd_s32b();
            auto count = rd_byte();
            if (i < item_group.size()) {
                item_group[i].charge = charge;
                item_group[i].count = count;
            }
        }
    };
    load_item_group(magic_eater_data->staves);
    load_item_group(magic_eater_data->wands);
    load_item_group(magic_eater_data->rods);
}

void PlayerClassSpecificDataLoader::operator()(std::shared_ptr<bard_data_type> &bird_data) const
{
    bird_data->singing_song = i2enum<realm_song_type>(rd_s32b());
    bird_data->interrputing_song = i2enum<realm_song_type>(rd_s32b());
    bird_data->singing_duration = rd_s32b();
    bird_data->singing_song_spell_idx = rd_byte();
}

void PlayerClassSpecificDataLoader::operator()(std::shared_ptr<mane_data_type> &mane_data) const
{
    auto count = rd_s16b();
    for (; count > 0; --count) {
        auto spell = rd_s16b();
        auto damage = rd_s16b();
        mane_data->mane_list.push_back({ i2enum<MonsterAbilityType>(spell), damage });
    }
}

void PlayerClassSpecificDataLoader::operator()(std::shared_ptr<SniperData> &sniper_data) const
{
    sniper_data->concent = rd_s16b();
}

void PlayerClassSpecificDataLoader::operator()(std::shared_ptr<samurai_data_type> &samurai_data) const
{
    samurai_data->stance = i2enum<SamuraiStanceType>(rd_byte());
}

void PlayerClassSpecificDataLoader::operator()(std::shared_ptr<monk_data_type> &monk_data) const
{
    monk_data->stance = i2enum<MonkStanceType>(rd_byte());
}

void PlayerClassSpecificDataLoader::operator()(std::shared_ptr<ninja_data_type> &ninja_data) const
{
    ninja_data->kawarimi = rd_byte() != 0;
    ninja_data->s_stealth = rd_byte() != 0;
}

void PlayerClassSpecificDataLoader::operator()(std::shared_ptr<spell_hex_data_type> &spell_hex_data) const
{
    rd_FlagGroup(spell_hex_data->casting_spells, rd_byte);
    spell_hex_data->revenge_power = rd_s32b();
    spell_hex_data->revenge_type = i2enum<SpellHexRevengeType>(rd_byte());
    spell_hex_data->revenge_turn = rd_byte();
}
