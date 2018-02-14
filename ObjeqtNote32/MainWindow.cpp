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

	// メニュー無し, LTGRAY_BRUSH.
	return RegisterClass(hInstance, NULL);	// RegisterClassで登録.

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpszMenuName){

	// ウィンドウプロシージャにはCWindow::StaticWndowProc, メニューはlpszMenuNameとする.((LPCTSTR)でキャストしないとオーバーロードが曖昧になる.)
	return RegisterClass(hInstance, (LPCTSTR)lpszMenuName, (HBRUSH)GetStockObject(LTGRAY_BRUSH));	// CWindow::RegisterClassで登録.(背景はLTGRAY_BRUSH.)

}

// ウィンドウクラス登録関数RegisterClass.(メニュー名指定, 背景ブラシ指定バージョン.)
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpszMenuName, HBRUSH hbrBackground){

	// ウィンドウプロシージャにはCWindow::StaticWndowProc, メニューはlpszMenuNameとする.((LPCTSTR)でキャストしないとオーバーロードが曖昧になる.背景はhbrBackground.)
	return CMenuWindow::RegisterClass(hInstance, _T("CMainWindow"), (LPCTSTR)lpszMenuName, hbrBackground);	// CMenuWindow::RegisterClassで登録.

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

		// マルチビューアイテムの削除.
		m_pMultiView->RemoveAll();	// m_pMultiView->RemoveAllでアイテムを全て削除.
		
		// マルチビューの破棄.
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

#if 0
	// マルチビューコントロールオブジェクトの作成.
	m_pMultiView = new CMultiView();	// CMultiViewオブジェクトの作成.

	// マルチビューコントロールのウィンドウ作成.
	m_pMultiView->Create(_T(""), 0, 0, 0, 720, 800, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// m_pMultiView->Createで作成.

	// マルチビューアイテムの追加.
	m_pMultiView->Add(_T("Item0"), 320, 32, 64, 64, lpCreateStruct->hInstance);	// m_pMultiView->Addで"Item0"を追加.
	m_pMultiView->Add(_T("Item1"), 32, 320, 64, 64, lpCreateStruct->hInstance);	// m_pMultiView->Addで"Item1"を追加.

	// マルチビューアイテムの取得.
	CMultiViewItem *pItem0 = m_pMultiView->Get(0);	// 0番目を取得.
	CMultiViewItem *pItem1 = m_pMultiView->Get(1);	// 1番目を取得.
#endif

#if 0
	// エディットコントロールの生成.
	// エディット0.
	CEdit *pEdit0 = new CEdit();	// CEditオブジェクトを生成.
	pEdit0->Create(_T("Edit0"), WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 480, 100, pItem0->m_hWnd, (HMENU)WM_APP + 200, lpCreateStruct->hInstance);	// m_pEdit0->CreateでpItem0->m_hWndを親としてウィンドウ作成.
	pItem0->m_mapChildMap.insert(std::make_pair(_T("Edit0"), pEdit0));	// "Edit0"をキー, pEdit0を値として, pItem0->m_mapChildMapに登録.

	// エディット1.
	CEdit *pEdit1 = new CEdit();	//CEditオブジェクトを生成.
	pEdit1->Create(_T("Edit1"), WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 100, 480, pItem1->m_hWnd, (HMENU)WM_APP + 201, lpCreateStruct->hInstance);	// m_pEdit1->CreateでpItem1->m_hWndを親としてウィンドウ作成.
	pItem1->m_mapChildMap.insert(std::make_pair(_T("Edit1"), pEdit1));	// "Edit1"をキー, pEdit1を値として, pItem1->m_mapChildMapに登録.
#endif

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
// ウィンドウのサイズが変更された時.
void CMainWindow::OnSize(UINT nType, int cx, int cy){

	// 親ウィンドウのOnSize.
	CMenuWindow::OnSize(nType, cx, cy);	// CWindowのOnSize.

	// マルチビューのサイズはウィンドウにぴったり合わせる.
	if (m_pMultiView != NULL){	// NULLでなければ.
		MoveWindow(m_pMultiView->m_hWnd, m_pMultiView->m_x, m_pMultiView->m_y, cx, cy, TRUE);	// MoveWindowでm_pMultiView->m_hWndのサイズを変更.
	}

	// 画面更新.
	InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRectで更新.

}

// ウィンドウの描画を要求された時のハンドラOnPaint.
void CMainWindow::OnPaint(){

	// 変数の初期化.
	HDC hDC = NULL;	// hDCをNULLで初期化.
	PAINTSTRUCT ps = {0};	// psを{0}で初期化.
	HPEN hPen = NULL;	// hPenをNULLで初期化.
	HBRUSH hBrush = NULL;	// hBrushをNULLで初期化.

	// 描画開始.
	hDC = BeginPaint(m_hWnd, &ps);	// BeginPaintで描画開始.

	// ペンとブラシの生成.
	hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0xff, 0));	// CreatePenで緑(淡)のペンを作成.
	hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0x7f, 0));		// CreateSolidBrushで緑(濃)のブラシを作成.

	// ペンとブラシの選択.
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);		// 緑のペンを選択.
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);	// 緑のブラシを選択.

	// 矩形描画.
	Rectangle(hDC, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight);	// Rectangleで矩形を描画.
	
	// ペンとブラシの復元
	SelectObject(hDC, hOldBrush);		// 古いブラシを選択.
	SelectObject(hDC, hOldPen);		// 古いペンを選択.

	// ペンとブラシの破棄.
	DeleteObject(hBrush);	// ブラシの破棄.
	DeleteObject(hPen);	// ペンの破棄.

	// 描画終了.
	EndPaint(m_hWnd, &ps);	// EndPaintで描画終了.

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