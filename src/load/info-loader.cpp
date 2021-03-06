#include "load/info-loader.h"
#include "game-option/runtime-arguments.h"
#include "load/angband-version-comparer.h"
#include "load/load-util.h"
#include "load/option-loader.h"
#include "system/angband-version.h"
#include "system/angband.h"
#include "view/display-messages.h"
#include "world/world.h"

/*!
 * @brief セーブファイルからバージョン情報及びセーブ情報を取得する
 * @details
 * バージョン0.x.x時代のバージョン情報である場合、サポート対象外
 * (FAKE_VERもH_VERも10台の数字のはず)
 */
void rd_version_info(void)
{

    load_xor_byte = 0;
    w_ptr->h_ver_extra = rd_byte();
    load_xor_byte = 0;
    w_ptr->h_ver_patch = rd_byte();
    load_xor_byte = 0;
    w_ptr->h_ver_minor = rd_byte();
    load_xor_byte = 0;
    w_ptr->h_ver_major = rd_byte();

    strip_bytes(1);

    load_xor_byte = w_ptr->sf_extra;
    v_check = 0L;
    x_check = 0L;

    w_ptr->sf_system = rd_u32b();
    w_ptr->sf_when = rd_u32b();
    w_ptr->sf_lives = rd_u16b();
    w_ptr->sf_saves = rd_u16b();

    loading_savefile_version = rd_u32b();

    load_note(format(_("バージョン %d.%d.%d のセーブデータ(SAVE%lu形式)をロード中...", "Loading a Verison %d.%d.%d savefile (SAVE%lu format)..."),
        w_ptr->h_ver_major, w_ptr->h_ver_minor, w_ptr->h_ver_patch,
        loading_savefile_version));
}

/*!
 * @brief 乱数状態を読み込む / Read RNG state (added in 2.8.0)
 */
void rd_randomizer(void)
{
    strip_bytes(4);

    Xoshiro128StarStar::state_type state;
    for (auto &s : state) {
        s = rd_u32b();
    }
    w_ptr->rng.set_state(state);

    strip_bytes(4 * (RAND_DEG - state.size()));
}

/*!
 * @brief メッセージログを読み込む / Read the saved messages
 */
void rd_messages(void)
{
    auto num = rd_u32b();
    int message_max = (int)num;
    for (int i = 0; i < message_max; i++) {
        char buf[128];
        rd_string(buf, sizeof(buf));
        message_add(buf);
    }
}

void rd_system_info(void)
{
    kanji_code = rd_byte();
    rd_randomizer();
    load_note(_("乱数情報をロードしました", "Loaded Randomizer Info"));
    rd_options();
    load_note(_("オプションをロードしました", "Loaded Option Flags"));
    rd_messages();
    load_note(_("メッセージをロードしました", "Loaded Messages"));
}
