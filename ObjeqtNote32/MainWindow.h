// 二重インクルード防止
#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

// ヘッダのインクルード
// 既定のヘッダ
#include <string>	// std::string
// 独自のヘッダ
#include "MenuWindow.h"	// CMenuWindow
#include "MultiView.h"	// CMultiView
#include "Edit.h"	// CEdit
#include "TextFile.h"	// CTextFile
#include "resource.h"	// リソース.

// マクロの定義
// UNICODE切り替え
#ifdef UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

// メインウィンドウクラスCMainWindow
class CMainWindow : public CMenuWindow{

	// publicメンバ
	public:

		// publicメンバ変数
		CMultiView *m_pMultiView;	// CMultiViewオブジェクトポインタm_pMultiView.
		CTextFile *m_pTextFile;	// CTextFileオブジェクトポインタm_pTextFile.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CMainWindow();	// コンストラクタCMainWindow()
		virtual ~CMainWindow();	// デストラクタ~CMainWindow()
		// staticメンバ関数
		static BOOL RegisterClass(HINSTANCE hInstance);	// ウィンドウクラス登録関数RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, LPCTSTR lpszMenuName);	// ウィンドウクラス登録関数RegisterClass.(メニュー名指定バージョン.)
		static BOOL RegisterClass(HINSTANCE hInstance, LPCTSTR lpszMenuName, HBRUSH hbrBackground);	// ウィンドウクラス登録関数RegisterClass.(メニュー名指定, 背景ブラシ指定バージョン.)
		// メンバ関数バージョン.
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
		virtual void Destroy();	// ウィンドウの破棄と終了処理関数Destroy.
		void InitTextFile();	// テキストファイルの初期化.
		void InitMultiView();	// マルチビューの初期化.
		void ShowTextFile();	// テキストファイルの表示.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウの作成が開始された時.
		virtual void OnDestroy();	// ウィンドウが破棄された時.
		virtual void OnSize(UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.
		virtual void OnTimer(UINT_PTR nIDEvent);	// タイマーイベントが発生した時.
		virtual void OnPaint();	// ウィンドウの描画を要求された時のハンドラOnPaint.
		virtual int OnClose();	// ウィンドウを閉じた時.
		virtual int OnFileOpen(WPARAM wParam, LPARAM lParam);	// "開く"を選択された時のハンドラ.
		virtual int OnFileSaveAs(WPARAM wParam, LPARAM lParam);	// "名前を付けて保存"を選択された時のハンドラ.

};

#endif