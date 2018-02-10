// ヘッダのインクルード
// 独自のヘッダ
#include "MultiViewItemsPanel.h"	// CMultiViewItemsPanel

// コンストラクタCMultiViewItemsPanel
CMultiViewItemsPanel::CMultiViewItemsPanel() : CUserControl(){

	// メンバの初期化.
	m_vecMultiViewItemList.clear();	// m_vecMultiViewItemList.clearでクリア.
	m_nNextId = 0;	// m_nNextIdを0で初期化.

}

// デストラクタ~CMultiViewItemsPanel
CMultiViewItemsPanel::~CMultiViewItemsPanel(){

	// メンバの終了処理
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CMultiViewItemsPanel::RegisterClass(HINSTANCE hInstance){

	// ウィンドウクラスの登録.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(LTGRAY_BRUSH));	// CUserControl::RegisterClassで登録.

}

// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
BOOL CMultiViewItemsPanel::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackgroundを指定.
	return CUserControl::RegisterClass(hInstance, _T("CMultiViewItemsPanel"), hbrBackground);	// CUserControl::RegisterClassで登録.

}

// ウィンドウ作成関数Create.
BOOL CMultiViewItemsPanel::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウの作成.
	return CUserControl::Create(_T("CMultiViewItemsPanel"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createで作成.

}

// ウィンドウの破棄と終了処理関数Destroy.
void CMultiViewItemsPanel::Destroy(){

	// マルチビューアイテムリストの終了処理.
	m_vecMultiViewItemList.clear();	// m_vecMultiViewItemList.clearでクリア.
	m_nNextId = 0;	// m_nNextIdに0をセット.

	// 親ウィンドウのDestroyを呼ぶ.
	CUserControl::Destroy();	// CUserControl::Destroyを呼ぶ.

}

// アイテムを末尾から追加する関数Add.
void CMultiViewItemsPanel::Add(LPCTSTR lpctszWindowName, int x, int y, int iWidth, int iHeight, HINSTANCE hInstance){

	// マルチビューアイテムの追加.
	CMultiViewItem *pMultiViewItem = new CMultiViewItem();	// CMultiViewItemオブジェクトを生成し, ポインタをpMultiViewItemに格納.
	pMultiViewItem->Create(lpctszWindowName, WS_CHILD | WS_VISIBLE, x, y, iWidth, iHeight, m_hWnd, (HMENU)(MULTI_VIEW_ITEM_ID_START + m_nNextId), hInstance);	// pMultiViewItem->Createでアイテム作成.
	m_vecMultiViewItemList.push_back(pMultiViewItem);	// m_vecMultiViewItemList.push_backで末尾に追加.
	m_nNextId++;	// m_nNextIdをインクリメント.
	
}

// アイテムを末尾から削除する関数Remove.
void CMultiViewItemsPanel::Remove(){

	// マルチビューアイテムの削除.
	CMultiViewItem *pMultiViewItem = m_vecMultiViewItemList[m_vecMultiViewItemList.size() - 1];	// 末尾要素を取得.
	delete pMultiViewItem;	// deleteでpMultiViewItemの削除.
	m_vecMultiViewItemList.pop_back();	// m_vecMultiViewItemList.pop_backでリストを1つ減らす.
	m_nNextId--;

}

// 全てのアイテムを削除する関数RemoveAll.
void CMultiViewItemsPanel::RemoveAll(){

	// アイテムの数だけ繰り返す.
	size_t n = GetSize();	// GetSizeでサイズを取得し, nに格納.
	for (size_t i = 0; i < n; i++){	// nの数だけ繰り返す.
		Remove();	// Removeで末尾を削除.
	}

}

// アイテムの数を返す関数GetSize.
size_t CMultiViewItemsPanel::GetSize(){

	// アイテムの要素数を返す.
	return m_vecMultiViewItemList.size();	// m_vecMultiViewItemList.sizeで要素数を返す.

}

// ウィンドウの作成が開始された時.
int CMultiViewItemsPanel::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// 常にウィンドウ作成に成功するものとする.
	return 0;	// 0を返すと, ウィンドウ作成に成功したということになる.

}

// ウィンドウが破棄された時.
void CMultiViewItemsPanel::OnDestroy(){

	// メンバの終了処理
	//Destroy();	// Destroyでこのウィンドウの終了処理をする.

	// 親クラスのOnDestroyを呼ぶ.
	CUserControl::OnDestroy();	// CUserControl::OnDestroyを呼ぶ.

}

// ウィンドウの描画を要求された時のハンドラOnPaint.
void CMultiViewItemsPanel::OnPaint(){

	// 変数の初期化.
	HDC hDC = NULL;	// hDCをNULLで初期化.
	PAINTSTRUCT ps = {0};	// psを{0}で初期化.
	HPEN hPen = NULL;	// hPenをNULLで初期化.
	HBRUSH hBrush = NULL;	// hBrushをNULLで初期化.

	// 描画開始.
	hDC = BeginPaint(m_hWnd, &ps);	// BeginPaintで描画開始.

	// ペンとブラシの生成.
	hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0xff, 0, 0));	// CreatePenで赤(淡)のペンを作成.
	hBrush = (HBRUSH)CreateSolidBrush(RGB(0x7f, 0, 0));		// CreateSolidBrushで赤(濃)のブラシを作成.

	// ペンとブラシの選択.
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);		// 赤のペンを選択.
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);	// 赤のブラシを選択.

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

// ウィンドウのサイズが変更された時.
void CMultiViewItemsPanel::OnSize(UINT nType, int cx, int cy){

	// 親ウィンドウの既定処理.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSizeを呼ぶ.

}