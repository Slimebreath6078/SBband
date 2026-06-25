#include "main-win/main-win-exception.h"
#include "locale/character-encoding.h"
#include "main-win/main-win-utils.h"
#include "util/angband-files.h"
#include <sstream>

/*!
 * @brief 予期しない例外を処理する
 *
 * 予期しない例外が発生した場合、確認を取り例外のエラー情報を開発チームに送信する。
 * その後、バグ報告ページを開くかどうか尋ね、開く場合はWebブラウザで開く。
 *
 * @param e 例外オブジェクト
 */
void handle_unexpected_exception(const std::exception &e)
{
    std::string msg = e.what();
#ifdef JP
    // 例外メッセージがUTF-8の場合一旦SJISに変換する(SJISの場合はそのまま)
    const auto msg_len = guess_convert_to_system_encoding(msg.data(), msg.size());
    msg.erase(msg_len);
#endif

    const auto first_line = msg.substr(0, msg.find('\n'));

    std::wstringstream issue_page_open_msg_ss;
    issue_page_open_msg_ss
        << to_wchar(first_line).wc_str();
};
