// ヘッダのインクルード
// 独自のヘッダ
#include "resource.h"	// リソース
#include "MainWindow.h"	// CMainWindow
#include "FileDialog.h"	// CFileDialog

// ウィンドウクラス登録関数RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance) {

	// ウィンドウクラス名は"CMainWindow".
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"));	// CWindow::RegisterClassでウィンドウクラス名"CMainWindow"を登録.

}

// コンストラクタCMainWindow()
CMainWindow::CMainWindow() {

	// メンバの初期化.
	m_hInstance = NULL;	// m_hInstanceをNULLで初期化.
	m_pMainMenu = NULL;	// m_pMainMenuをNULLで初期化.

}

// デストラクタ~CMainWindow()
CMainWindow::~CMainWindow() {

	// メンバの終了処理.
	Destroy();	// Destroyで子ウィンドウの破棄.

}

// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance) {

	// ウィンドウクラス名は"CMainWindow".
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createにウィンドウクラス名"CMainWindow"を指定.

}

// ウィンドウ破棄関数Destroy
BOOL CMainWindow::Destroy() {

	// 変数の初期化.
	BOOL bRet = FALSE;	// bRetをFALSEで初期化.

	// DestroyChildrenを分けたので, 自身のウィンドウ破棄は問題ない.
	// まず子ウィンドウの破棄.
	DestroyChildren();

	// 自身のウィンドウ破棄.
	bRet = CWindow::Destroy();	// 戻り値をbRetに格納.

	// bRetを返す.
	return bRet;

}

// 子ウィンドウ破棄関数DestroyChildren
BOOL CMainWindow::DestroyChildren() {

	// 変数の初期化.
	BOOL bRet = FALSE;	// bRetをFALSEで初期化.

	// 破棄したらTRUEを返す.
	if (bRet) {	// TRUEなら.
		return TRUE;	// TRUEを返す.
	}

	// 破棄しなければ, CWindowのDestroyChildrenを返す.
	return CWindow::DestroyChildren();	// CWindow::DestroyChildrenを返す.

}

// ウィンドウの作成が開始された時.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {

	// 親クラスのOnCreateを呼ぶ.
	m_hInstance = lpCreateStruct->hInstance;
	int iRet = CWindow::OnCreate(hwnd, lpCreateStruct);	// CWindow::OnCreateを呼び, 戻り値を返す.
	m_pMainMenu = CWindow::GetMenu();	// CWindow::GetMenuでm_pMainMenu取得.
	if (m_pMainMenu == NULL) {	// メニューハンドルが無い場合は, m_pMainMenuがNULLになる.
		m_pMainMenu = new CMenu();
		BOOL bRet = m_pMainMenu->LoadMenu(lpCreateStruct->hInstance, IDM_MAINMENU);	// IDM_MAINMENUをロード.
		if (bRet) {
			SetMenu(m_pMainMenu);	// CWindow::SetMenuでm_pMainMenuをセット.
			// メニューハンドラの追加.
			AddCommandHandler(ID_ITEM_FILE_OPEN, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnFileOpen);	// AddCommandHandlerでID_ITEM_FILE_OPENに対するハンドラCMainWindow::OnFileOpenを登録.
		}
	}

	return iRet;

}

// ウィンドウが破棄された時.
void CMainWindow::OnDestroy() {

	// メニューハンドラの削除.
	DeleteCommandHandler(ID_ITEM_FILE_OPEN, 0);	// DeleteCommandHandlerでID_ITEM_FILE_OPENのハンドラを削除.

	// メニューの終了処理.
	CMenu::DeleteMenuHandleMap();
	m_pMainMenu = NULL;

	// CWindowのOnDestroyを呼ぶ.
	CWindow::OnDestroy();	// CWindow::OnDestroyを呼ぶ.

}

// ウィンドウが閉じられる時.
int CMainWindow::OnClose() {

	// メッセージボックスで"Close CMainWindow OK?"と表示.
	int iRet = MessageBox(m_hWnd, _T("Close CMainWindow OK?"), _T("ObjeqtNote32"), MB_OKCANCEL);	// MessageBoxで"Close CMainWindow OK?"と表示し, 戻り値をiRetに格納.
	if (iRet != IDOK) {	// OK以外.(Cancelなど.)
		return -1;	// -1を返す.
	}

	// このウィンドウの破棄.(OnCloseの後, ウィンドウの破棄処理が勝手に行われるので, Destroyは不要なのでコメントアウト.)
	//Destroy();	// Destroyでこのウィンドウの破棄処理.

	// OKなので閉じる.
	return CWindow::OnClose();	// 親クラスのOnCloseを呼ぶ.(親クラスのOnCloseは常に閉じる処理になっている.)

}

// "開く"が選択された時.
int CMainWindow::OnFileOpen(WPARAM wParam, LPARAM lParam) {

	// "開く"ダイアログ
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("テキストファイル(*.txt)|*.txt|すべてのファイル(*.*)|*.*||"));
	INT_PTR ret = dlg.DoModal();
	if (ret == IDOK) {
		MessageBox(m_hWnd, dlg.GetOFN().lpstrFile, _T("ObjeqtNote32"), MB_OK);	// 選択したファイルのファイルパスを表示.
	}

	// 0を返す.
	return 0;	// 処理したので0.

}
