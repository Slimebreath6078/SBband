#include "main-win/main-win-exception.h"
#include "io/files-util.h"
#include "main-win/main-win-utils.h"
#include "util/angband-files.h"
#include <sstream>

static void write_error_message(const wchar_t *caption, const std::string &msg)
{

    const auto path = path_build(ANGBAND_DIR_USER, "error.txt");
    auto *fp = angband_fopen(path, FileOpenMode::WRITE);
    if (!fp) {
        const auto &path_str = path.string();
#ifdef JP
        std::wstringstream file_error_msg_ss;
        file_error_msg_ss
            << path_str.data() << L" を開くことができませんでした。";
#else
        std::wstringstream report_confirm_msg_ss;
        report_confirm_msg_ss
            << L"Failed to open " << path_str.data() << ".";
#endif
        MessageBoxW(NULL, file_error_msg_ss.str().data(), caption, MB_ICONEXCLAMATION | MB_OK | MB_ICONSTOP);
        return;
    }

    // 現在時刻を取得
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss = std::stringstream() << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");

    // フォーマットされた日付と時間を出力
    fputs((std::string("-----") + ss.str() + "-----\n\n").data(), fp);

    fputs((msg + "\n\n").data(), fp);
    angband_fclose(fp);
}

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
    constexpr auto caption = _(L"予期しないエラー！", L"Unexpected error!");

    const std::string msg = e.what();
    const auto first_line = msg.substr(0, msg.find('\n'));

#if !defined(DISABLE_NET)
    std::wstringstream report_confirm_msg_ss;
    report_confirm_msg_ss
        << to_wchar(first_line.data()).wc_str() << L"\n\n"
        << _(L"エラー内容をファイルに書き出しますか？\n", L"Are you sure you want to write the error information file?\n");

    if (auto choice = MessageBoxW(NULL, report_confirm_msg_ss.str().data(), caption, MB_ICONEXCLAMATION | MB_YESNO | MB_ICONSTOP);
        choice == IDYES) {
        write_error_message(caption, e.what());
    }
#endif

    std::wstringstream issue_page_open_msg_ss;
    issue_page_open_msg_ss
        << _(L"エラー発生の詳しい状況を報告してくださると助かります。\n",
               L"It would be helpful if you could report the detailed circumstances of the error.\n")
        << _(L"バグ報告ページを開きますか？\n", L"Open bug report page?\n");

    if (auto choice = MessageBoxW(NULL, issue_page_open_msg_ss.str().data(), caption, MB_ICONEXCLAMATION | MB_YESNO | MB_ICONSTOP);
        choice == IDYES) {
        constexpr auto url = "https://github.com/slimebreath6078/SBband/issues/new/choose";
        ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
    }
};
