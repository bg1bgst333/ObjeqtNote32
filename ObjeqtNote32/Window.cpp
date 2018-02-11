// ヘッダのインクルード
// 独自のヘッダ
#include "Window.h"	// CWindow

// staticメンバ変数の定義.
std::map<HWND, CWindow *> CWindow::m_mapWindowMap;	// ウィンドウマップm_mapWindowMap.
std::map<DWORD, HandlerConditions *> CWindow::m_mapHandlerMap;	// ハンドラマップm_mapHandlerMap.

// コンストラクタCWindow()
CWindow::CWindow(){

	// メンバの初期化.
	m_hWnd = NULL;	// m_hWndをNULLで初期化.
	m_x = 0;	// m_xを0で初期化.
	m_y = 0;	// m_yを0で初期化.
	m_iWidth = 0;	// m_iWidthを0で初期化.
	m_iHeight = 0;	// m_iHeightを0で初期化.
	m_iClientAreaWidth = 0;	// m_iClientAreaWidthを0で初期化.
	m_iClientAreaHeight = 0;	// m_iClientAreaHeightを0で初期化.

}

// デストラクタ~CWindow()
CWindow::~CWindow(){

	// メンバの終了処理.
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ウィンドウクラス登録関数RegisterClass.(ウィンドウクラス名省略バージョン.)
BOOL CWindow::RegisterClass(HINSTANCE hInstance){

	// ウィンドウクラス名は"CWindow".
	return RegisterClass(hInstance, _T("CWindow"));	// ウィンドウクラス名に"CWindow"を指定する.

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpctszClassName){

	// ウィンドウプロシージャには"CWindow"のモノを指定する.
	return RegisterClass(hInstance, lpctszClassName, StaticWindowProc);	// ウィンドウプロシージャバージョンにStaticWindowProcを指定.
	
}

// ウィンドウクラス登録関数RegisterClass.(ウィンドウプロシージャ指定バージョン.)
BOOL CWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpctszClassName, WNDPROC lpfnWndProc){

	// lpfnWndProcを指定.
	return RegisterClass(hInstance, lpctszClassName, lpfnWndProc, NULL, (HBRUSH)GetStockObject(WHITE_BRUSH));	// ウィンドウプロシージャバージョンにlpfnWndProcを指定.

}

// ウィンドウクラス登録関数RegisterClass.(ウィンドウプロシージャ省略, メニュー名指定バージョン.)
BOOL CWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpctszClassName, LPCTSTR lpszMenuName){

	// StaticWindowProc, lpszMenuNameを指定.
	return RegisterClass(hInstance, lpctszClassName, StaticWindowProc, lpszMenuName, (HBRUSH)GetStockObject(WHITE_BRUSH));	// メニュー名指定バージョンでStaticWindowProcとlpszMenuNameを指定.(hbrBackgroundはWHITE_BRUSH.)

}

// ウィンドウクラス登録関数RegisterClass.(ウィンドウプロシージャ省略, メニュー名指定バージョン, 背景ブラシ指定バージョン.)
BOOL CWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpctszClassName, LPCTSTR lpszMenuName, HBRUSH hbrBackground){

	// StaticWindowProc, lpszMenuName, hbrBackgroundを指定.
	return RegisterClass(hInstance, lpctszClassName, StaticWindowProc, lpszMenuName, hbrBackground);	// hbrBackgroundを指定.

}

// ウィンドウクラス登録関数RegisterClass.(メニュー名指定バージョン.)
BOOL CWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpctszClassName, WNDPROC lpfnWndProc, LPCTSTR lpszMenuName, HBRUSH hbrBackground){

	// 構造体の宣言.
	WNDCLASS wc;	// WNDCLASS型ウィンドウクラス構造体wc

	// ウィンドウクラス構造体wcにパラメータをセット.
	wc.lpszClassName = lpctszClassName;	// ウィンドウクラス名にlpctszClassNameを指定する.
	wc.style = CS_HREDRAW | CS_VREDRAW;	// スタイルはとりあえずCS_HREDRAW | CS_VREDRAWにする.
	wc.lpfnWndProc = lpfnWndProc;	// ウィンドウプロシージャには指定されたlpfnWndProc.
	wc.hInstance = hInstance;	// アプリケーションインスタンスハンドルは引数のhInstanceを使う.
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// LoadIconでアプリケーション既定のアイコンをロード.(第1引数はNULL.)
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	// LoadCursorでアプリケーション既定のカーソルをロード.(第1引数はNULL.)
	wc.hbrBackground = hbrBackground;	// hbrBackgroundを背景ブラシとする.
	wc.lpszMenuName = lpszMenuName;	// lpszMenuNameを指定する.
	wc.cbClsExtra = 0;	// とりあえず0を指定.
	wc.cbWndExtra = 0;	// とりあえず0を指定.

	// ウィンドウクラスの登録
	if (!::RegisterClass(&wc)){	// WindowsAPIのRegisterClassでウィンドウクラスを登録する.

		// 戻り値が0なら登録失敗なのでエラー処理.
		return FALSE;	// returnでFALSEを返して異常終了.

	}

	// 登録成功なのでTRUE.
	return TRUE;	// returnでTRUEを返す.

}

// スタティックウィンドウプロシージャStaticWindowProcの定義
LRESULT CALLBACK CWindow::StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	// ポインタの初期化.
	CWindow *pWindow = NULL;	// CWindowオブジェクトポインタpWindowをNULLで初期化.

	// ウィンドウメッセージの処理.
	switch (uMsg){	// uMsgの値ごとに処理を振り分ける.

		
		// ウィンドウの作成が開始された時.
		case WM_CREATE:

			// WM_CREATEブロック
			{

				// ポインタの初期化
				LPCREATESTRUCT lpCreateStruct = NULL;	// CREATESTRUCT構造体へのポインタlpCreateStructをNULL.
				// lParamからlpCreateStructを取り出す.
				lpCreateStruct = (LPCREATESTRUCT)lParam;	// lParamをLPCREATESTRUCT型にキャストしてlpCreateStructに格納.
				if (lpCreateStruct != NULL){	// lpCreateStructがNULLでなければ.
					pWindow = (CWindow *)lpCreateStruct->lpCreateParams;	// lpCreateStruct->lpCreateParamsはCWindowオブジェクトポインタにキャストし, pWindowに格納.
					m_mapWindowMap.insert(std::pair<HWND, CWindow *>(hwnd, pWindow));	// m_mapWindowMapにhwndとpWindowのペアを登録.
				}

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて既定の処理へ向かう.

		// それ以外の時.
		default:

			// defaultブロック
			{

				// hwndでCWindowオブジェクトポインタが引けたら, pWindowに格納.
				if (m_mapWindowMap.find(hwnd) != m_mapWindowMap.end()){	// findでキーをhwndとするCWindowオブジェクトポインタが見つかったら.
					pWindow = m_mapWindowMap[hwnd];	// pWindowにhwndで引けるCWindowオブジェクトポインタを格納.
				}

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて既定の処理へ向かう.

	}

	// CWindowオブジェクトポインタが取得できなかった場合, 取得できた場合で分ける.
	if (pWindow == NULL){	// pWindowがNULL

		// DefWindowProcに任せる.
		return DefWindowProc(hwnd, uMsg, wParam, lParam);	// DefWindowProcに引数をそのまま渡して, DefWindowProcの戻り値をそのまま返す.

	}
	else{	// pWindowがNULLでない時.

		// そのCWindowオブジェクトのDynamicWindowProcに渡す.
		return pWindow->DynamicWindowProc(hwnd, uMsg, wParam, lParam);	// pWindow->DynamicWindowProcに引数をそのまま渡して, DynamicWindowProcの戻り値をそのまま返す.

	}

}

// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
BOOL CWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)

	// ウィンドウクラス名は"CWindow".
	return CWindow::Create(_T("CWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createにウィンドウクラス名"CWindow"を指定.

}

// ウィンドウ作成関数Create.
BOOL CWindow::Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// 指定されたサイズをメンバにセット.
	m_x = x;	// m_xにxをセット.
	m_y = y;	// m_yにyをセット.
	m_iWidth = iWidth;	// m_iWidthにiWidthをセット.
	m_iHeight = iHeight;	// m_iHeightにiHeightをセット.

	// ウィンドウの作成.
	m_hWnd = CreateWindow(lpctszClassName, lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance, this);	// CreateWindowでウィンドウを作成し, ハンドルをm_hWndに格納.(最後の引数にはthis(自分自身)を渡す.)
	if (m_hWnd == NULL){	// m_hWndがNULLなら失敗.

		// 失敗ならFALSEを返す.
		MessageBox(NULL, _T("予期せぬエラーが発生しました!"), _T("ObjeqtNote"), MB_OK | MB_ICONHAND);	// MessageBoxで"予期せぬエラーが発生しました!"と表示.
		return FALSE;	// FALSEを返す.

	}

	// 生成されたウィンドウのサイズをメンバにセット.
	RECT rc = {0};	// RECT型rcを{0}で初期化.
	GetWindowRect(m_hWnd, &rc);	// GetWindowRectでm_hWndのサイズを取得.
	m_x = rc.left;	// m_xにrc.leftを代入.
	m_y = rc.top;	// m_yにrc.topを代入.
	m_iWidth = rc.right - rc.left;	// m_iWidthはrc.rightからrc.leftを引く.
	m_iHeight = rc.bottom - rc.top;	// m_iHeightはrc.bottomからrc.topを引く.

	// 成功ならTRUE.
	return TRUE;	// 成功なのでTRUEを返す.

}

// ウィンドウの破棄と終了処理関数Destroy.
void CWindow::Destroy(){

	// このウィンドウの破棄.
	if (m_hWnd != NULL){	// m_hWndがNULLでない時.
		DestroyWindow(m_hWnd);	// DestroyWindowでm_hWndを破棄.
		m_hWnd = NULL;	// m_hWndにNULLをセット.
	}
	// サイズを0にリセット.
	m_x = 0;	// m_xを0で初期化.
	m_y = 0;	// m_yを0で初期化.
	m_iWidth = 0;	// m_iWidthを0で初期化.
	m_iHeight = 0;	// m_iHeightを0で初期化.
	m_iClientAreaWidth = 0;	// m_iClientAreaWidthを0で初期化.
	m_iClientAreaHeight = 0;	// m_iClientAreaHeightを0で初期化.

}

// ウィンドウ表示関数ShowWindow.
BOOL CWindow::ShowWindow(int nCmdShow){

	// ウィンドウの表示.
	return ::ShowWindow(m_hWnd, nCmdShow);	// WindowsAPIのShowWindowでm_hWndを表示.

}

// コマンドハンドラの追加.
void CWindow::AddCommandHandler(UINT nID, UINT nCode, int(CWindow:: * handler)(WPARAM wParam, LPARAM lParam)){

	// HandlerConditionsの生成と追加.
	HandlerConditions *pCond = new HandlerConditions();	// HandlerConditionsオブジェクトを作成し, ポインタをpCondに格納.
	pCond->m_nID = nID;	// pCond->m_nIDにnIDを格納.
	pCond->m_nCode = nCode;	// pCond->m_nCodeにnCodeを格納.
	pCond->m_fpHandler = handler;	// pCond->m_fpHandlerにhandlerを格納.
	m_mapHandlerMap.insert(std::pair<DWORD, HandlerConditions *>((DWORD)MAKEWPARAM(nID, nCode), pCond));	// m_mapHandlerMap.insertでnID, nCodeをMAKEWPARAMしたものをキー, pCondを値として登録.

}

// コマンドハンドラの削除.
void CWindow::DeleteCommandHandler(UINT nID, UINT nCode){

	// ハンドラマップから指定のハンドラ情報を削除.
	HandlerConditions *pCond = NULL;	// HandlerConditionsオブジェクトポインタpCondをNULLに初期化.
	std::map<DWORD, HandlerConditions *>::iterator itor = m_mapHandlerMap.find((DWORD)(MAKEWPARAM(nID, nCode)));	// findでキーを(DWORD)(MAKEWPARAM(nID, nCode))とするHandlerConditionsオブジェクトポインタのイテレータを取得.
	if (itor != m_mapHandlerMap.end()){	// 見つかったら.
		pCond = m_mapHandlerMap[(DWORD)(MAKEWPARAM(nID, nCode))];	// (DWORD)(MAKEWPARAM(nID, nCode))を使ってハンドラマップからHandlerConditionsオブジェクトポインタを引き出す.
		delete pCond;	// HandlerConditionsオブジェクトを破棄.
		m_mapHandlerMap.erase(itor);	// itorの指す要素を削除.
	}

}

// ダイナミックウィンドウプロシージャDynamicWindowProc.
LRESULT CWindow::DynamicWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	// ウィンドウメッセージの処理.
	switch (uMsg){	// uMsgの値ごとに処理を振り分ける.

		// ウィンドウの作成が開始された時.
		case WM_CREATE:

			// WM_CREATEブロック
			{

				// OnCreateに任せる.
				return OnCreate(hwnd, (LPCREATESTRUCT)lParam);	// hwndとlParamをOnCreateに渡し, あとは任せる.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// ウィンドウが破棄された時.
		case WM_DESTROY:

			// WM_DESTROYブロック
			{

				// OnDestroyに任せる.
				OnDestroy();	// OnDestroyを呼ぶ.
				
			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// ウィンドウのサイズが変更された時.
		case WM_SIZE:

			// WM_SIZEブロック
			{

				// 変数の初期化
				UINT nType = (UINT)wParam;	// UINT型nTypeにwParamをセット.
				int cx = LOWORD(lParam);	// int型cxにLOWORD(lParam)をセット.
				int cy = HIWORD(lParam);	// int型cyにHIWORD(lParam)をセット.

				// OnSizeに任せる.
				OnSize(nType, cx, cy);	// OnSizeにhwnd, nType, cx, cyを渡す.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// 画面の描画を要求された時.
		case WM_PAINT:

			// WM_PAINTブロック
			{

				// OnPaintに任せる.
				OnPaint();	// OnPaintを呼ぶ.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// ウィンドウを閉じた時.
		case WM_CLOSE:

			// WM_CLOSEブロック
			{

				// OnCloseに任せる.
				if (OnClose() != 0) {	// 0以外なら
					return 0;	// 0を返す.
				}

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// コマンドが発生した時.
		case WM_COMMAND:

			// WM_COMMANDブロック
			{

				// OnCommandに任せる.
				return OnCommand(wParam, lParam) ? 0 : 1;

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// タイマーイベントが発生した時.
		case WM_TIMER:

			// WM_TIMERブロック
			{

				// OnTimerに任せる.
				OnTimer((UINT_PTR)wParam);	// OnTimerに任せる.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// 水平方向スクロールバーイベント時.
		case WM_HSCROLL:

			// WM_HSCROLLブロック
			{
				
				// OnHScrollに任せる.
				OnHScroll(LOWORD(wParam), HIWORD(wParam));	// OnHScrollに任せる.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// 垂直方向スクロールバーイベント時.
		case WM_VSCROLL:

			// WM_VSCROLLブロック
			{

				// OnVScrollに任せる.
				OnVScroll(LOWORD(wParam), HIWORD(wParam));	// OnVScrollに任せる.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// 上記以外の時.
		default:

			// defaultブロック
			{

				// OnUserMessageに任せる.
				OnUserMessage(uMsg, wParam, lParam);	// OnUserMessageに任せる.

			}

				// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

	}

	// あとは既定の処理に任せる.
	return DefWindowProc(hwnd, uMsg, wParam, lParam);	// 戻り値も含めてDefWindowProcに既定の処理を任せる.

}

// ウィンドウの作成が開始された時.
int CWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// 常にウィンドウ作成に成功するものとする.
	return 0;	// 0を返すと, ウィンドウ作成に成功したということになる.

}

// ウィンドウが破棄された時.
void CWindow::OnDestroy(){

	// ウィンドウの終了処理.
	//Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ウィンドウのサイズが変更された時.
void CWindow::OnSize(UINT nType, int cx, int cy){

	// 生成されたウィンドウのサイズをメンバにセット.
	RECT rc = {0};	// RECT型rcを{0}で初期化.
	GetWindowRect(m_hWnd, &rc);	// GetWindowRectでm_hWndのサイズを取得.
	m_x = rc.left;	// m_xにrc.leftを代入.
	m_y = rc.top;	// m_yにrc.topを代入.
	m_iWidth = rc.right - rc.left;	// m_iWidthはrc.rightからrc.leftを引く.
	m_iHeight = rc.bottom - rc.top;	// m_iHeightはrc.bottomからrc.topを引く.

	// クライアント領域のサイズをメンバ変数にセット.
	m_iClientAreaWidth = cx;	// m_iClientAreaWidthにcxを代入.
	m_iClientAreaHeight = cy;	// m_iClientAreaHeightにcyを代入.

}

// ウィンドウの描画を要求された時のハンドラOnPaint.
void CWindow::OnPaint(){

}

// ウィンドウを閉じた時.
int CWindow::OnClose(){

	// ウィンドウの終了処理.
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

	// 0を返す.
	return 0;	// 0を返してウィンドウを閉じる.

}

// コマンドが発生した時.
BOOL CWindow::OnCommand(WPARAM wParam, LPARAM lParam){

	// wParamからハンドラ情報を引き出す.
	HandlerConditions *pCond = NULL;	// HandlerConditionsオブジェクトポインタpCondをNULLに初期化.
	if (m_mapHandlerMap.find((const unsigned long)wParam) != m_mapHandlerMap.end()){	// findでキーをwParamとするHandlerConditionsオブジェクトポインタが見つかったら.
		pCond = m_mapHandlerMap[(const unsigned long)wParam];	// wParamでキーが取得できるので, それを使ってハンドラマップからHandlerConditionsオブジェクトポインタを引き出す.
	}
	if (pCond != NULL){	// pCondがNULLでないなら, ハンドラ登録されている.
		int iRet = (this->*pCond->m_fpHandler)(wParam, lParam);	// 登録したハンドラpCond->m_fpHandlerを呼び出し, 戻り値はiRetに格納.
		if (iRet == 0){	// 0なら処理をした.
			return TRUE;	// 処理をしたのでTRUE.
		}
	}

	// 処理していないのでFALSE.
	return FALSE;	// returnでFALSEを返す.

}

// タイマーイベントが発生した時.
void  CWindow::OnTimer(UINT_PTR nIDEvent){

}

// 水平方向スクロールバーイベント時.
void CWindow::OnHScroll(UINT nSBCode, UINT nPos){

}

// 垂直方向スクロールバーイベント時.
void CWindow::OnVScroll(UINT nSBCode, UINT nPos){

}

// ユーザ定義メッセージが発生した時.
void CWindow::OnUserMessage(UINT uMsg, WPARAM wParam, LPARAM lParam){

	// switch-case文で振り分ける.
	switch (uMsg) {

		// 子から親へウィンドウサイズ変更の要求が発生した時.
		case UM_SIZECHILD:

			// UM_SIZECHILDブロック
			{

				// OnSizeChildに任せる.
				OnSizeChild(wParam, lParam);	// OnSizeChildに任せる.

			}

			// 既定の処理へ向かう.
			break;	// 抜けてDefWindowProcに向かう.

		// それ以外.
		default:

			// 既定の処理へ向かう.
			break;	// 抜けてDefWindowProcに向かう.

	}

}

// 子から親へウィンドウサイズ変更の要求が発生した時.
void CWindow::OnSizeChild(WPARAM wParam, LPARAM lParam){

}