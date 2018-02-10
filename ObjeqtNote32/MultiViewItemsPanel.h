// 二重インクルード防止
#ifndef __MULTI_VIEW_ITEMS_PANEL_H__
#define __MULTI_VIEW_ITEMS_PANEL_H__

// ヘッダのインクルード
// 既定のヘッダ
#include <vector>	// std::vector
// 独自のヘッダ
#include "UserControl.h"	// CUserControl
#include "MultiViewItem.h"	// CMultiViewItem

// マクロ定義
#define MULTI_VIEW_ITEM_ID_START (WM_APP + 100)	// マルチビューアイテムのIDの開始はWM_APP + 100とする.

// マルチビューアイテムズパネルCMultiViewItemsPanel
class CMultiViewItemsPanel : public CUserControl{

	// publicメンバ
	public:

		// publicメンバ変数
		std::vector<CMultiViewItem *> m_vecMultiViewItemList;	// マルチビューアイテムリストm_vecMultiViewItemList.
		int m_nNextId;	// マルチビューアイテムの次期払い出しリソースID m_nNextId.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CMultiViewItemsPanel();	// コンストラクタCMultiViewItemsPanel
		virtual ~CMultiViewItemsPanel();	// デストラクタ~CMultiViewItemsPanel
		// staticメンバ関数
		static BOOL RegisterClass(HINSTANCE hInstance);	// ウィンドウクラス登録関数RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground);	// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.
		virtual void Destroy();	// ウィンドウの破棄と終了処理関数Destroy.
		virtual void Add(LPCTSTR lpctszWindowName, int x, int y, int iWidth, int iHeight, HINSTANCE hInstance);	// アイテムを末尾から追加する関数Add.
		virtual void Remove();	// アイテムを末尾から削除する関数Remove.
		virtual CMultiViewItem * Get(int iIndex);	// アイテムを取得する関数Get.
		virtual void RemoveAll();	// 全てのアイテムを削除する関数RemoveAll.
		virtual size_t GetSize();	// アイテムの数を返す関数GetSize.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウの作成が開始された時.
		virtual void OnDestroy();	// ウィンドウが破棄された時.
		virtual void OnPaint();	// ウィンドウの描画を要求された時のハンドラOnPaint.
		virtual void OnSize(UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.

};

#endif