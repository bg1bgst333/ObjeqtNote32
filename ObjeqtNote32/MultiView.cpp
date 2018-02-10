// ヘッダのインクルード
// 独自のヘッダ
#include "MultiView.h"	// CMultiView

// コンストラクタCMultiView
CMultiView::CMultiView() : CUserControl(){

	// メンバ変数の初期化.
	m_pMultiViewItemsPanel = NULL;	// m_pMultiViewItemsPanelをNULLで初期化.
	m_iHScrollPos = 0;	// m_iHScrollPosを0で初期化.
	m_iVScrollPos = 0;	// m_iVScrollPosを0で初期化.

}

// デストラクタ~CMultiView
CMultiView::~CMultiView(){

	// メンバの終了処理
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CMultiView::RegisterClass(HINSTANCE hInstance){

	// ウィンドウクラスの登録.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(LTGRAY_BRUSH));	// CUserControl::RegisterClassで登録.

}

// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
BOOL CMultiView::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackgroundを指定.
	return CUserControl::RegisterClass(hInstance, _T("CMultiView"), hbrBackground);	// CUserControl::RegisterClassで登録.

}

// ウィンドウ作成関数Create.
BOOL CMultiView::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウの作成.
	return CUserControl::Create(_T("CMultiView"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createで作成.

}

// ウィンドウの破棄と終了処理関数Destroy.
void CMultiView::Destroy(){

	// マルチビューアイテムズパネルの破棄.
	if (m_pMultiViewItemsPanel != NULL){	// m_pMultiViewItemsPanelがNULLでない時.
		m_pMultiViewItemsPanel->Destroy();	// m_pMultiViewItemsPanel->Destroyで破棄.
		delete m_pMultiViewItemsPanel;	// deleteでm_pMultiViewItemsPanelを解放.
		m_pMultiViewItemsPanel = NULL;	// m_pMultiViewItemsPanelにNULLをセット.
	}

	// 親ウィンドウのDestroyを呼ぶ.
	CUserControl::Destroy();	// CUserControl::Destroyを呼ぶ.

}

// アイテムを末尾から追加する関数Add.
void CMultiView::Add(LPCTSTR lpctszWindowName, int x, int y, int iWidth, int iHeight, HINSTANCE hInstance){

	// アイテムズパネルに追加.
	if (m_pMultiViewItemsPanel != NULL){	// m_pMultiViewItemsPanelがNULLでなければ.
		m_pMultiViewItemsPanel->Add(lpctszWindowName, x, y, iWidth, iHeight, hInstance);	// Addで末尾に追加.
	}

}

// アイテムを末尾から削除する関数Remove.
void CMultiView::Remove(){

	// アイテムズパネルから削除.
	if (m_pMultiViewItemsPanel != NULL){	// m_pMultiViewItemsPanelがNULLでなければ.
		m_pMultiViewItemsPanel->Remove();	// Removeで末尾から削除.
	}

}

// アイテムを取得する関数Get.
CMultiViewItem * CMultiView::Get(int iIndex){

	// アイテムズパネルから取得.
	if (m_pMultiViewItemsPanel != NULL){	// m_pMultiViewItemsPanelがNULLでなければ.
		return m_pMultiViewItemsPanel->Get(iIndex);	// 
	}

	// なければNULL.
	return NULL;	// NULLを返す.

}

// 全てのアイテムを削除する関数RemoveAll.
void CMultiView::RemoveAll(){

	// アイテムズパネルから全て削除.
	if (m_pMultiViewItemsPanel != NULL){	// m_pMultiViewItemsPanelがNULLでなければ.
		m_pMultiViewItemsPanel->RemoveAll();
	}

}

// ウィンドウの作成が開始された時.
int CMultiView::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// マルチビューアイテムズパネルの生成.
	m_pMultiViewItemsPanel = new CMultiViewItemsPanel();	// CMultiViewItemsPanelの作成.

	// マルチビューアイテムズパネルのウィンドウ生成.
	m_pMultiViewItemsPanel->Create(_T(""), 0, 0, 0, 320 + 300, 240 + 200, hwnd, (HMENU)(WM_APP + 2), lpCreateStruct->hInstance);	// m_pMultiViewItemsPanel->Createでウィンドウ生成.

	// 初回更新タイマーをセット.
	SetTimer(hwnd, 1, 100, NULL);	// SetTimerで更新タイマーをセット.(100ミリ秒==0.1秒)

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

// ウィンドウの描画を要求された時のハンドラOnPaint.
void CMultiView::OnPaint(){

	// 変数の初期化.
	HDC hDC = NULL;	// hDCをNULLで初期化.
	PAINTSTRUCT ps = {0};	// psを{0}で初期化.
	HPEN hPen = NULL;	// hPenをNULLで初期化.
	HBRUSH hBrush = NULL;	// hBrushをNULLで初期化.

	// 描画開始.
	hDC = BeginPaint(m_hWnd, &ps);	// BeginPaintで描画開始.

	// ペンとブラシの生成.
	hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 0xff));	// CreatePenで青(淡)のペンを作成.
	hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0x7f));		// CreateSolidBrushで青(濃)のブラシを作成.

	// ペンとブラシの選択.
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);		// 青のペンを選択.
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);	// 青のブラシを選択.

	// 矩形描画.
	Rectangle(hDC, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight);	// Rectangleで矩形を描画.
	
	// ペンとブラシの復元
	SelectObject(hDC, hOldBrush);		// 古いブラシを選択.
	SelectObject(hDC, hOldPen);		// 古いペンを選択.

	// ペンとブラシの破棄.
	DeleteObject(hBrush);	// ブラシの破棄.
	DeleteObject(hPen);	// ペンの破棄.

	// スクロールバー設定.
	// 水平方向.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemoryでm_ScrollInfoをクリア.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// サイズ
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// フラグ
	m_ScrollInfo.nPage = m_iClientAreaWidth;	// ページ幅
	m_ScrollInfo.nMin = 0;	// 最小値
	m_ScrollInfo.nMax = m_pMultiViewItemsPanel->m_iWidth;	//最大値
	SetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo, TRUE);	// SetScrollInfoでセット.(SetImageのInvalidateRectと第4引数のTRUEがないとスクロールバーつまみが即座に更新されない.)
	// 垂直方向.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemoryでm_ScrollInfoをクリア.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// サイズ
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// フラグ
	m_ScrollInfo.nPage = m_iClientAreaHeight;	// ページ高さ
	m_ScrollInfo.nMin = 0;	// 最小値
	m_ScrollInfo.nMax = m_pMultiViewItemsPanel->m_iHeight;	//最大値
	SetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo, TRUE);	// SetScrollInfoでセット.(SetImageのInvalidateRectと第4引数のTRUEがないとスクロールバーつまみが即座に更新されない.)

	// 描画終了.
	EndPaint(m_hWnd, &ps);	// EndPaintで描画終了.

}

// ウィンドウのサイズが変更された時.
void CMultiView::OnSize(UINT nType, int cx, int cy){

	// 親ウィンドウの既定処理.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSizeを呼ぶ.

	// スクロールバー設定.
	// 水平方向.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemoryでm_ScrollInfoをクリア.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// サイズ
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// フラグ
	m_ScrollInfo.nPage = m_iClientAreaWidth;	// ページ幅
	m_ScrollInfo.nMin = 0;	// 最小値
	m_ScrollInfo.nMax = m_pMultiViewItemsPanel->m_iWidth;	//最大値
	SetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo, TRUE);	// SetScrollInfoでセット.(SetImageのInvalidateRectと第4引数のTRUEがないとスクロールバーつまみが即座に更新されない.)
	// 垂直方向.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemoryでm_ScrollInfoをクリア.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// サイズ
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// フラグ
	m_ScrollInfo.nPage = m_iClientAreaHeight;	// ページ高さ
	m_ScrollInfo.nMin = 0;	// 最小値
	m_ScrollInfo.nMax = m_pMultiViewItemsPanel->m_iHeight;	//最大値
	SetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo, TRUE);	// SetScrollInfoでセット.(SetImageのInvalidateRectと第4引数のTRUEがないとスクロールバーつまみが即座に更新されない.)

}

// タイマーイベントが発生した時.
void  CMultiView::OnTimer(UINT_PTR nIDEvent){

	// 初回更新タイマーの時.
	if (nIDEvent == 1){	// 1の時.

		// 無効領域を作成して画面の更新.
		InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRectで無効領域作成.

		// タイマーを終了.
		KillTimer(m_hWnd, 1);	// 初回更新タイマーを終了.

	}

}

// 水平方向スクロールバーイベント時.
void CMultiView::OnHScroll(UINT nSBCode, UINT nPos){

	// スクロール情報取得.
	m_ScrollInfo.fMask = SIF_POS;	// 位置だけ変更モード(これがないと, スクロールバーが元の位置に戻ってしまうので注意!こっちが前!)
	GetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo);	// マスクを設定してからGetScrollInfo.(こっちが後!)

	// スクロールバー処理.
	switch (nSBCode) {	// nSBCodeごとに振り分け.

		// 一番左
		case SB_LEFT:

			// 位置を最小値に.
			m_ScrollInfo.nPos = m_ScrollInfo.nMin;
			break;

		// 一番右
		case SB_RIGHT:

			// 位置を最大値に.
			m_ScrollInfo.nPos = m_ScrollInfo.nMax;
			break;

		// 1列左
		case SB_LINELEFT:

			// nPosが0でなければデクリメント.
			if (m_ScrollInfo.nPos > 0) {
				m_ScrollInfo.nPos--;
			}
			break;

		// 1列右
		case SB_LINERIGHT:

			// nPosが最大値-1でなければインクリメント.
			if (m_ScrollInfo.nPos < m_ScrollInfo.nMax - 1) {
				m_ScrollInfo.nPos++;
			}
			break;

		// 1ページ左
		case SB_PAGELEFT:

			// nPage分減らす.
			m_ScrollInfo.nPos -= m_ScrollInfo.nPage;
			break;

		// 1ページ右
		case SB_PAGERIGHT:

			// nPage分増やす.
			m_ScrollInfo.nPos += m_ScrollInfo.nPage;
			break;

		// つまみをドラッグ中.
		case SB_THUMBTRACK:

			// 引数のnPosをセット
			m_ScrollInfo.nPos = nPos;
			break;

		// つまみをドラッグ後.
		case SB_THUMBPOSITION:

			// 引数のnPosをセット
			m_ScrollInfo.nPos = nPos;
			break;

		// それ以外.
		default:

			break;

	}

	// スクロール情報設定.
	SetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo, TRUE);
	// メンバにもセット.
	m_iHScrollPos = m_ScrollInfo.nPos;
	// アイテムズパネルの移動.
	MoveWindow(m_pMultiViewItemsPanel->m_hWnd, 0 - m_iHScrollPos, 0 - m_iVScrollPos, m_pMultiViewItemsPanel->m_iWidth, m_pMultiViewItemsPanel->m_iHeight, TRUE);	// MoveWindowで移動.
	// 無効領域を作成して画面の更新.
	InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRectで無効領域作成.

}

// 垂直方向スクロールバーイベント時.
void CMultiView::OnVScroll(UINT nSBCode, UINT nPos){

	// スクロール情報取得.
	m_ScrollInfo.fMask = SIF_POS;	// 位置だけ変更モード(これがないと, スクロールバーが元の位置に戻ってしまうので注意!こっちが前!)
	GetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo);	// マスクを設定してからGetScrollInfo.(こっちが後!)

	// スクロールバー処理.
	switch (nSBCode) {	// nSBCodeごとに振り分け.

		// 一番上
		case SB_TOP:

			// 位置を最小値に.
			m_ScrollInfo.nPos = m_ScrollInfo.nMin;
			break;

		// 一番下
		case SB_BOTTOM:

			// 位置を最大値に.
			m_ScrollInfo.nPos = m_ScrollInfo.nMax;
			break;

		// 1行上
		case SB_LINEUP:

			// nPosが0でなければデクリメント.
			if (m_ScrollInfo.nPos > 0) {
				m_ScrollInfo.nPos--;
			}
			break;

		// 1行下
		case SB_LINEDOWN:

			// nPosが最大値-1でなければインクリメント.
			if (m_ScrollInfo.nPos < m_ScrollInfo.nMax - 1) {
				m_ScrollInfo.nPos++;
			}
			break;

		// 1ページ上
		case SB_PAGEUP:

			// nPage分減らす.
			m_ScrollInfo.nPos -= m_ScrollInfo.nPage;
			break;

		// 1ページ下
		case SB_PAGEDOWN:

			// nPage分増やす.
			m_ScrollInfo.nPos += m_ScrollInfo.nPage;
			break;

		// つまみをドラッグ中.
		case SB_THUMBTRACK:
	
			// 引数のnPosをセット
			m_ScrollInfo.nPos = nPos;
			break;

		// つまみをドラッグ後.
		case SB_THUMBPOSITION:

			// 引数のnPosをセット
			m_ScrollInfo.nPos = nPos;
			break;

		// それ以外.
		default:

			break;

	}

	// スクロール情報設定.
	SetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo, TRUE);
	// メンバにもセット.
	m_iVScrollPos = m_ScrollInfo.nPos;
	// アイテムズパネルの移動.
	MoveWindow(m_pMultiViewItemsPanel->m_hWnd, 0 - m_iHScrollPos, 0 - m_iVScrollPos, m_pMultiViewItemsPanel->m_iWidth, m_pMultiViewItemsPanel->m_iHeight, TRUE);	// MoveWindowで移動.
	// 無効領域を作成して画面の更新.
	InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRectで無効領域作成.

}