// ヘッダのインクルード
// 独自のヘッダ
#include "MultiView.h"	// CMultiView

// コンストラクタCMultiView
CMultiView::CMultiView() : CUserControl(){

}

// デストラクタ~CMultiView
CMultiView::~CMultiView(){

	// メンバの終了処理
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CMultiView::RegisterClass(HINSTANCE hInstance){

	// ウィンドウクラスの登録.
	return CUserControl::RegisterClass(hInstance, _T("CMultiView"));	// CUserControl::RegisterClassで登録.

}

// ウィンドウ作成関数Create.
BOOL CMultiView::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウの作成.
	return CUserControl::Create(_T("CMultiView"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createで作成.

}

// ウィンドウの破棄と終了処理関数Destroy.
void CMultiView::Destroy(){

	// 親ウィンドウのDestroyを呼ぶ.
	CUserControl::Destroy();	// CUserControl::Destroyを呼ぶ.

}

// ウィンドウの作成が開始された時.
int CMultiView::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// 常にウィンドウ作成に成功するものとする.
	return 0;	// 0を返すと, ウィンドウ作成に成功したということになる.

}

// ウィンドウが破棄された時.
void CMultiView::OnDestroy(){

	// メンバの終了処理
	//Destroy();	// Destroyでこのウィンドウの終了処理をする.

	// 親クラスのOnDestroyを呼ぶ.
	CUserControl::OnDestroy();	// CUserControl::OnDestroyを呼ぶ.

}

// ウィンドウのサイズが変更された時.
void CMultiView::OnSize(UINT nType, int cx, int cy){

}