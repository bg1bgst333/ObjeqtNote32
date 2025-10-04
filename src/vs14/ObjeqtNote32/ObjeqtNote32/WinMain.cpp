// ヘッダのインクルード
// 既定のヘッダ
#include <windows.h>	// 標準WindowsAPI
#include <tchar.h>		// TCHAR型

// _tWinMain関数の定義
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd) {

	// メッセージボックスで"ObjeqtNote32"と表示.
	MessageBox(NULL, _T("ObjeqtNote32"), _T("ObjeqtNote32"), MB_OK);	// MessageBoxで"ObjeqtNote32"と表示.

	// プログラムの正常終了
	return 0;	// 0を返して正常終了.

}