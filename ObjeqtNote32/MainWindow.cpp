// ヘッダのインクルード
// 独自のヘッダ
#include "MainWindow.h"	// CMainWindow
#include "FileDialog.h"	// CFileDialog
#include "resource.h"		// リソース

// コンストラクタCMainWindow()
CMainWindow::CMainWindow() : CMenuWindow(){

	// メンバの初期化.
	m_pMultiView = NULL;	// m_pMultiViewをNULLで初期化.
	m_pTextFile = NULL;	// m_pTextFileをNULLで初期化.

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

	// テキストファイルの破棄.
	if (m_pTextFile != NULL){	// m_pTextFileがNULLでなければ.
		delete m_pTextFile;	// deleteでm_pTextFileを解放.
		m_pTextFile = NULL;	// m_pTextFileにNULLをセット.
	}

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

// テキストファイルの初期化.
void CMainWindow::InitTextFile(){

	// m_pTextFileがあるかどうかで処理が変わる.
	if (m_pTextFile != NULL){	// m_pTextFileがNULLでない時.

		// いったん閉じる.
		m_pTextFile->Clear();	// m_pTextFile->Clearでバッファのクリア.
		m_pTextFile->Close();	// m_pTextFile->Closeでファイルを閉じる.

	}
	else{	// NULLの時.

		// CTextFileオブジェクトの作成.
		m_pTextFile = new CTextFile();	// newでCTextFileオブジェクトを作成し, m_pTextFileにポインタを格納.

	}

}

// マルチビューの初期化.
void CMainWindow::InitMultiView(){

	// m_pMultiViewがあるかどうかで処理が変わる.
	if (m_pMultiView != NULL){	// m_pMultiViewがNULLでない時.

		// いったん載せているビューたちを削除.
		m_pMultiView->RemoveAll();	// m_pMultiView->RemoveAllで全て削除.

	}
	else{	// NULLの時.

		// CMultiViewオブジェクトの作成.
		m_pMultiView = new CMultiView();	// CMultiViewオブジェクトの作成.
		m_pMultiView->Create(_T(""), 0 /*WS_HSCROLL | WS_VSCROLL*/, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight, m_hWnd, (HMENU)(WM_APP + 1), m_hInstance);	// m_pMultiView->Createで作成.
		
	}

}

// テキストファイルの表示.
void CMainWindow::ShowTextFile(LPCTSTR lpctszText){

	// マルチビューアイテムの追加.
	m_pMultiView->Add(_T("Item0"), 0, 0, m_iClientAreaWidth, 25, m_hInstance);	// m_pMultiView->Addで"Item0"を追加.
	m_pMultiView->Add(_T("Item1"), 0, 25, m_iClientAreaWidth, m_iClientAreaHeight - 25, m_hInstance);	// m_pMultiView->Addで"Item1"を追加.

	// マルチビューアイテムの取得.
	CMultiViewItem *pItem0 = m_pMultiView->Get(0);	// 0番目を取得.
	CMultiViewItem *pItem1 = m_pMultiView->Get(1);	// 1番目を取得.

	// コンボボックスオブジェクトの生成.
	CComboBox *pComboBox0 = new CComboBox();	// CComboBoxオブジェクトポインタpComboBox0.

	// コンボボックスのウィンドウ生成.
	pComboBox0->Create(_T(""), CBS_SORT | CBS_DROPDOWNLIST, 0, 0, m_iClientAreaWidth, 300, pItem0->m_hWnd, (HMENU)WM_APP + 200, m_hInstance);	// pComboBox0->CreateでpItem0->m_hWndを親としてウィンドウ作成.

	// アイテムの追加.
	pComboBox0->AddString(_T("Shift_JIS"));	// pComboBox0->AddStringで"Shift_JIS"を追加.
	pComboBox0->AddString(_T("Unicode"));	// pComboBox0->AddStringで"Unicode"を追加.

	// エディットボックスオブジェクトの生成.
	CEdit *pEdit1 = new CEdit();	// CEditオブジェクトポインタpEdit1.
	
	// エディットボックスのウィンドウ作成.
	pEdit1->Create(_T(""), WS_BORDER | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight - 25, pItem1->m_hWnd, (HMENU)WM_APP + 201, m_hInstance);	// pEdit1->CreateでpItem1->m_hWndを親としてウィンドウ作成.
	
	// テキストのセット.
	pEdit1->SetText(lpctszText);	// pEdit1->SetTextでテキストをセット.

	// チャイルドマップへの追加.
	pItem0->m_mapChildMap.insert(std::make_pair(_T("ComboBox0"), pComboBox0));	// "ComboBox0"をキー, pComboBox0を値として, pItem0->m_mapChildMapに登録.
	pItem1->m_mapChildMap.insert(std::make_pair(_T("Edit1"), pEdit1));	// "Edit1"をキー, pEdit1を値として, pItem1->m_mapChildMapに登録.

	// 初回更新タイマーをセット.
	SetTimer(m_hWnd, 2, 100, NULL);	// SetTimerで更新タイマーをセット.(100ミリ秒==0.1秒)

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
	AddCommandHandler(ID_FILE_NEW_TXT, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileNewTxt);	// AddCommandHandlerでID_FILE_NEW_TXTに対するハンドラCMainWindow::OnFileNewTxtを登録.
	AddCommandHandler(ID_FILE_OPEN, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileOpen);	// AddCommandHandlerでID_FILE_OPENに対するハンドラCMainWindow::OnFileOpenを登録.
	AddCommandHandler(ID_FILE_SAVE_AS, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileSaveAs);	// AddCommandHandlerでID_FILE_SAVE_ASに対するハンドラCMainWindow::OnFileSaveAsを登録.

	// 親のOnCreateを呼ぶ.
	return CMenuWindow::OnCreate(hwnd, lpCreateStruct);	// CMenuWindow::OnCreateを返す.

}

// ウィンドウが破棄された時.
void CMainWindow::OnDestroy(){

	// メニューハンドラの削除.
	DeleteCommandHandler(ID_FILE_OPEN, 0);	// DeleteCommandHandlerでID_FILE_OPENのハンドラを削除.
	DeleteCommandHandler(ID_FILE_SAVE_AS, 0);	// DeleteCommandHandlerでID_FILE_SAVE_ASのハンドラを削除.
	DeleteCommandHandler(ID_FILE_NEW_TXT, 0);	// DeleteCommandHandlerでID_FILE_NEW_TXTのハンドラを削除.

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
		CMultiViewItem *pItem0 = m_pMultiView->Get(0);	// 0番目を取得.
		CMultiViewItem *pItem1 = m_pMultiView->Get(1);	// 1番目を取得.
		MoveWindow(pItem0->m_mapChildMap[_T("ComboBox0")]->m_hWnd, 0, 0, cx, 300, TRUE);	// MoveWindowで"ComboBox0"をリサイズ.
		MoveWindow(pItem1->m_mapChildMap[_T("Edit1")]->m_hWnd, 0, 0, cx, cy - 25, TRUE);	// MoveWindowで"Edit1"をリサイズ.
	}

	// 画面更新.
	//InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRectで更新.

}

// タイマーイベントが発生した時.
void  CMainWindow::OnTimer(UINT_PTR nIDEvent){

#if 1
	// 初回更新タイマーの時.
	if (nIDEvent == 2){	// 2の時.

		// 無効領域を作成して画面の更新.
		InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRectで無効領域作成.

		// タイマーを終了.
		KillTimer(m_hWnd, 2);	// 初回更新タイマーを終了.

	}
#endif

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

// "テキスト文書"を選択された時のハンドラ.
int CMainWindow::OnFileNewTxt(WPARAM wParam, LPARAM lParam){

	// テキストファイルの初期化.
	InitTextFile();	// InitTextFileで初期化.

	// マルチビューの初期化.
	InitMultiView();	// InitMultiViewで初期化.
	
	// テキストファイルの表示.
	ShowTextFile(_T(""));	// ShowTextFileで""をセット.

	// 処理したので0.
	return 0;	// 0を返す.

}

// "開く"を選択された時のハンドラ.
int CMainWindow::OnFileOpen(WPARAM wParam, LPARAM lParam){

	// "開く"ファイルの選択.
	CFileDialog selDlg(NULL, _T("*"), _T("テキスト文書(*.txt)|*.txt|すべてのファイル(*.*)|*.*||"), OFN_FILEMUSTEXIST);	// CFileDialogオブジェクトselDlgを定義.
	if (selDlg.ShowOpenFileDialog(m_hWnd)){	// selDlg.ShowOpenFileDialogで"開く"ファイルダイアログを表示.

		// まず, 拡張子でファイル判定をする.
		if (selDlg.m_tstrExt.compare(_T(".txt")) == 0){	// selDlg.m_tstrExt.compareで".txt"なら.

			// テキストファイルの初期化.
			InitTextFile();	// InitTextFileで初期化.

			// テキストファイルの読み込み.
			if (m_pTextFile->Read(selDlg.m_tstrPath.c_str())){	// m_pTextFile->Readで読み込み.

				// ShiftJISなら開く.
				if (m_pTextFile->m_Encoding == CTextFile::ENCODING_SHIFT_JIS){	// ShiftJIS.

					// マルチビューの初期化.
					InitMultiView();	// InitMultiViewで初期化.
					
					// テキストファイルの表示.
					ShowTextFile(m_pTextFile->m_tstrText.c_str());	// ShowTextFileでm_pTextFileの内容を表示.
				
				}

			}
			
		}

	}

	// 処理したので0.
	return 0;	// returnで0を返す.

}

// "名前を付けて保存"を選択された時のハンドラ.
int CMainWindow::OnFileSaveAs(WPARAM wParam, LPARAM lParam){

	// "名前を付けて保存"ファイルの選択.
	CFileDialog selDlg(NULL, _T("*"), _T("テキスト文書(*.txt)|*.txt|すべてのファイル(*.*)|*.*||"), OFN_OVERWRITEPROMPT);	// CFileDialogオブジェクトselDlgを定義.
	if (selDlg.ShowSaveFileDialog(m_hWnd)){	// selDlg.ShowSaveFileDialogで"名前を付けて保存"ファイルダイアログを表示.

		// テキストファイルの書き込み.
		if (m_pTextFile != NULL){	// m_pTextFileがNULLでないなら.

			// 各アイテムを取得.
			CMultiViewItem *pItem0 = m_pMultiView->Get(0);	// 0番目を取得.
			CComboBox *pComboBox0 = (CComboBox *)(pItem0->m_mapChildMap[_T("ComboBox0")]);	// pComboBox0を取得.
			CMultiViewItem *pItem1 = m_pMultiView->Get(1);	// 1番目を取得.
			CEdit *pEdit1 = (CEdit *)(pItem1->m_mapChildMap[_T("Edit1")]);	// pEdit1を取得.
			m_pTextFile->SetText(pEdit1->GetText());	// "Edit1"のテキストをセット.
			m_pTextFile->Write(selDlg.m_tstrPath.c_str());	// m_tstrPathに書き込み.

		}

	}
	
	// 処理したので0.
	return 0;	// returnで0を返す.

}