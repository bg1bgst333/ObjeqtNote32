// ヘッダのインクルード
// 独自のヘッダ
#include "ComboBox.h"	// CComboBox

// コンストラクタCComboBox
CComboBox::CComboBox() : CCustomControl(){

}

// デストラクタ~CComboBox
CComboBox::~CComboBox(){

	// メンバの終了処理
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
BOOL CComboBox::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)

	// ウィンドウクラス名が"ComboBox"なカスタムコントロールを作成.
	return CCustomControl::Create(_T("ComboBox"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, (HMENU)hMenu, hInstance);	// CCustomControl::Createでコンボボックスコントロールを作成.

}

// コンボボックスに文字列を追加する関数AddString.
void CComboBox::AddString(LPCTSTR lpctszStr){

	// 指定の文字列を追加.
	SendMessage(m_hWnd, CB_ADDSTRING, 0, (LPARAM)lpctszStr);	// SendMessageでCB_ADDSTRINGを送ることで指定の文字列を追加.

}

// コンボボックスの指定のインデックス要素を選択SetCurSel.
void CComboBox::SetCurSel(int iIndex){

	// 指定の要素をセット.
	SendMessage(m_hWnd, CB_SETCURSEL, (WPARAM)iIndex, 0);	// SendMessageでCB_SETCURSELを送ることで指定の要素を選択.

}

// ウィンドウの作成が開始された時.
int CComboBox::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// UM_SIZECHILDで子ウィンドウのサイズに合わせる.
	WPARAM wParam;	// WPARAM型wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAMでwParamをセット.
	SendMessage(GetParent(hwnd), UM_SIZECHILD, wParam, (LPARAM)hwnd);	// SendMessageでUM_SIZECHILDを送信.

	// 親のOnCreateを呼ぶ.
	return CCustomControl::OnCreate(hwnd, lpCreateStruct);	// CCustomControl::OnCreateを返す.

}

// ウィンドウのサイズが変更された時.
void CComboBox::OnSize(UINT nType, int cx, int cy){

	// 親クラスのOnSize.
	CCustomControl::OnSize(nType, cx, cy);	// CCustomControl::OnSizeを呼ぶ.

	// UM_SIZECHILDで子ウィンドウのサイズに合わせる.
	WPARAM wParam;	// WPARAM型wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAMでwParamをセット.
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);	// SendMessageでUM_SIZECHILDを送信.

}