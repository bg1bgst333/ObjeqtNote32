// 二重インクルード防止
#ifndef __COMBO_BOX_H__
#define __COMBO_BOX_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "CustomControl.h"	// CCustomControl

// コンボボックスコントロールクラスCComboBox
class CComboBox : public CCustomControl{

	// publicメンバ
	public:

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CComboBox();	// コンストラクタCComboBox
		virtual ~CComboBox();	// デストラクタ~CComboBox
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
		void AddString(LPCTSTR lpctszStr);	// コンボボックスに文字列を追加する関数AddString.
		void SetCurSel(int iIndex);	// コンボボックスの指定のインデックス要素を選択SetCurSel.
		int GetCurSel();	// コンボボックスで選択されている要素のインデックスを返すGetCurSel.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウの作成が開始された時.
		virtual void OnSize(UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.

};

#endif