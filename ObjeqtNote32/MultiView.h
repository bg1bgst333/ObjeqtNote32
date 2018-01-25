// 二重インクルード防止
#ifndef __MULTI_VIEW_H__
#define __MULTI_VIEW_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "UserControl.h"	// CUserControl

// マルチビューコントロールクラスCMultiView
class CMultiView : public CUserControl{

	// publicメンバ
	public:

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CMultiView();	// コンストラクタCMultiView
		virtual ~CMultiView();	// デストラクタ~CMultiView
		// staticメンバ関数
		static BOOL RegisterClass(HINSTANCE hInstance);	// ウィンドウクラス登録関数RegisterClass.
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.
		virtual void Destroy();	// ウィンドウの破棄と終了処理関数Destroy.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウの作成が開始された時.
		virtual void OnDestroy();	// ウィンドウが破棄された時.
		virtual void OnSize(UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.

};

#endif