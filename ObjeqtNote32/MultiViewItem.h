// 二重インクルード防止
#ifndef __MULTI_VIEW_ITEM_H__
#define __MULTI_VIEW_ITEM_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "UserControl.h"	// CUserControl

// マルチビューアイテムCMultiViewItem
class CMultiViewItem : public CUserControl{

	// publicメンバ
	public:

		// publicメンバ変数
		std::map<tstring, CWindow *> m_mapChildMap;	// アイテムの子ウィンドウマップm_mapChildMap.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CMultiViewItem();	// コンストラクタCMultiViewItem
		virtual ~CMultiViewItem();	// デストラクタ~CMultiViewItem
		// staticメンバ関数
		static BOOL RegisterClass(HINSTANCE hInstance);	// ウィンドウクラス登録関数RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground);	// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.
		virtual void Destroy();	// ウィンドウの破棄と終了処理関数Destroy.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウの作成が開始された時.
		virtual void OnDestroy();	// ウィンドウが破棄された時.
		virtual void OnPaint();	// ウィンドウの描画を要求された時のハンドラOnPaint.
		virtual void OnSize(UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.
		virtual void OnSizeChild(WPARAM wParam, LPARAM lParam);	// 子から親へウィンドウサイズ変更の要求が発生した時.

};

#endif