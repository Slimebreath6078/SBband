#pragma once

#include <stdint.h>

#define VERSION_NAME "SBband" /*!< バリアント名称 / Name of the version/variant */

/*!
 * @brief セーブファイル上のバージョン定義(メジャー番号) / "Savefile Version Number" for SBband 1.1.1 and later
 * @details
 * 当面FAKE_VER_*を参照しておく。
 * <pre>
 * Program Version of SBband version is
 *   "(H_VER_MAJOR).(H_VER_MINOR).(H_VER_PATCH).(H_VER_EXTRA)".
 * Upper compatibility is always guaranteed when it is more than 1.0.0 .
 * </pre>
 */
#define H_VER_MAJOR 0 //!< ゲームのバージョン定義(メジャー番号)
#define H_VER_MINOR 0 //!< ゲームのバージョン定義(マイナー番号)
#define H_VER_PATCH 1 //!< ゲームのバージョン定義(パッチ番号)
#define H_VER_EXTRA 1 //!< ゲームのバージョン定義(エクストラ番号)

/*!
 * @brief セーブファイルのバージョン(3.0.0から導入)
 */
constexpr uint32_t SAVEFILE_VERSION = 1;

/*!
 * @brief バージョンが開発版が安定版かを返す(廃止予定)
 */
#define IS_STABLE_VERSION (H_VER_MINOR % 2 == 0 && H_VER_EXTRA == 0)

/*!
 * @brief 状態がアルファ版かどうかを返す
 * @note アルファ版はエクストラ番号一定値までをアルファとし、一定まで進めて安定次第ベータ版、さらにそれも解除して無印版とする。
 */
#define IS_ALPHA_VERSION 1

void put_version(char *buf);
