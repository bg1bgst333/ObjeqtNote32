// ヘッダのインクルード
// 独自のヘッダ
#include "MainWindow.h"	// CMainWindow
#include "FileDialog.h"	// CFileDialog
#include "resource.h"		// リソース

// コンストラクタCMainWindow()
CMainWindow::CMainWindow() : CMenuWindow(){

	// メンバの初期化.
	m_pMultiView = NULL;	// m_pMultiViewをNULLで初期化.

}

// デストラクタ~CMainWindow()
CMainWindow::~CMainWindow(){

	// メンバの終了処理
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance){

	// ウィンドウプロシージャにはCWindow::StaticWndowProc, メニューはなし(NULL)とする.((LPCTSTR)でキャストしないとオーバーロードが曖昧になる.)
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"), (LPCTSTR)NULL);	// CWindow::RegisterClassで登録.

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpszMenuName){

	// ウィンドウプロシージャにはCWindow::StaticWndowProc, メニューはlpszMenuNameとする.((LPCTSTR)でキャストしないとオーバーロードが曖昧になる.)
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"), (LPCTSTR)lpszMenuName);	// CWindow::RegisterClassで登録.

}

// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)

	// ウィンドウクラス名は"CMainWindow".
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createにウィンドウクラス名"CMainWindow"を指定.

}

// ウィンドウの破棄と終了処理関数Destroy.
void CMainWindow::Destroy(){

	// マルチビューの削除.
	if (m_pMultiView != NULL){	// m_pMultiViewがNULLでなければ.
		m_pMultiView->Destroy();	// m_pMultiView->Destroyでm_pMultiViewの終了処理を実行.
		delete m_pMultiView;	// deleteでm_pMultiViewを解放.
		m_pMultiView = NULL;	// m_pMultiViewにNULLをセット.
	}

	// 親ウィンドウのDestroyを呼ぶ.
	CMenuWindow::Destroy();	// CMenuWindow::Destroyを呼ぶ.

}

// ウィンドウの作成が開始された時.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// メニューバーの作成.
	m_pMenuBar = new CMenuBar(hwnd);	// CMenuBarオブジェクトm_pMenuBarを作成.

	// メニューのロード.
	m_pMenuBar->LoadMenu(lpCreateStruct->hInstance, IDR_MENU1);	// LoadMenuでIDR_MENU1をロード.

	// メニューのセット.
	m_pMenuBar->SetMenu(hwnd);	// SetMenuでhwndにメニューをセット.

	// マルチビューコントロールオブジェクトの作成.
	m_pMultiView = new CMultiView();	// CMultiViewオブジェクトの作成.

	// マルチビューコントロールのウィンドウ作成.
	m_pMultiView->Create(_T(""), WS_BORDER, 0, 0, 640, 480, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// m_pMultiView->Createで作成.

	// メニューハンドラの追加.
	AddCommandHandler(ID_FILE_OPEN, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileOpen);	// AddCommandHandlerでID_FILE_OPENに対するハンドラCMainWindow::OnFileOpenを登録.
	AddCommandHandler(ID_FILE_SAVE_AS, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileSaveAs);	// AddCommandHandlerでID_FILE_SAVE_ASに対するハンドラCMainWindow::OnFileSaveAsを登録.

	// 常にウィンドウ作成に成功するものとする.
	return 0;	// 0を返すと, ウィンドウ作成に成功したということになる.

}

// ウィンドウが破棄された時.
void CMainWindow::OnDestroy(){

	// メニューハンドラの削除.
	DeleteCommandHandler(ID_FILE_OPEN, 0);	// DeleteCommandHandlerでID_FILE_OPENのハンドラを削除.
	DeleteCommandHandler(ID_FILE_SAVE_AS, 0);	// DeleteCommandHandlerでID_FILE_SAVE_ASのハンドラを削除.

	// メンバの終了処理
	//Destroy();	// Destroyでこのウィンドウの終了処理をする.

	// 親ウィンドウのOnDestroyを呼ぶ.
	CMenuWindow::OnDestroy();	// CMenuWindow::OnDestroyを呼ぶ.

	// 終了メッセージの送信.
	PostQuitMessage(0);	// PostQuitMessageで終了コードを0としてWM_QUITメッセージを送信.

}

// ウィンドウを閉じた時.
int CMainWindow::OnClose(){

	// ウィンドウの終了処理.
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

	// 0を返す.
	return 0;	// 0を返してウィンドウを閉じる.

}

// "開く"を選択された時のハンドラ.
int CMainWindow::OnFileOpen(WPARAM wParam, LPARAM lParam){

	// "開く"ファイルの選択.
	CFileDialog selDlg(NULL, _T("*"), _T("テキスト文書(*.txt)|*.txt|すべてのファイル(*.*)|*.*||"), OFN_FILEMUSTEXIST);	// CFileDialogオブジェクトselDlgを定義.
	if (selDlg.ShowOpenFileDialog(m_hWnd)){	// selDlg.ShowOpenFileDialogで"開く"ファイルダイアログを表示.

		// 選択されたファイルパスを表示.
		MessageBox(m_hWnd, selDlg.m_tstrPath.c_str(), _T("ObjeqtNote"), MB_OK | MB_ICONASTERISK);	// MessageBoxでselDlg.m_tstrPathを表示.

	}

	// 処理したので0.
	return 0;	// returnで0を返す.

}

// "名前を付けて保存"を選択された時のハンドラ.
int CMainWindow::OnFileSaveAs(WPARAM wParam, LPARAM lParam){

	// "名前を付けて保存"ファイルの選択.
	CFileDialog selDlg(NULL, _T("*"), _T("テキスト文書(*.txt)|*.txt|すべてのファイル(*.*)|*.*||"), OFN_OVERWRITEPROMPT);	// CFileDialogオブジェクトselDlgを定義.
	if (selDlg.ShowSaveFileDialog(m_hWnd)){	// selDlg.ShowSaveFileDialogで"名前を付けて保存"ファイルダイアログを表示.

		// 選択されたファイルパスを表示.
		MessageBox(m_hWnd, selDlg.m_tstrPath.c_str(), _T("ObjeqtNote"), MB_OK | MB_ICONASTERISK);	// MessageBoxでselDlg.m_tstrPathを表示.

	}
	
	// 処理したので0.
	return 0;	// returnで0を返す.

}