// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MultiView.h"	// CMultiView

// �R���X�g���N�^CMultiView
CMultiView::CMultiView() : CUserControl(){

	// �����o�ϐ��̏�����.
	m_pMultiViewItemsPanel = NULL;	// m_pMultiViewItemsPanel��NULL�ŏ�����.

}

// �f�X�g���N�^~CMultiView
CMultiView::~CMultiView(){

	// �����o�̏I������
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CMultiView::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�N���X�̓o�^.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(LTGRAY_BRUSH));	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
BOOL CMultiView::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackground���w��.
	return CUserControl::RegisterClass(hInstance, _T("CMultiView"), hbrBackground);	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�쐬�֐�Create.
BOOL CMultiView::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�̍쐬.
	return CUserControl::Create(_T("CMultiView"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Create�ō쐬.

}

// �E�B���h�E�̔j���ƏI�������֐�Destroy.
void CMultiView::Destroy(){

	// �}���`�r���[�A�C�e���Y�p�l���̔j��.
	if (m_pMultiViewItemsPanel != NULL){	// m_pMultiViewItemsPanel��NULL�łȂ���.
		m_pMultiViewItemsPanel->Destroy();	// m_pMultiViewItemsPanel->Destroy�Ŕj��.
		delete m_pMultiViewItemsPanel;	// delete��m_pMultiViewItemsPanel�����.
		m_pMultiViewItemsPanel = NULL;	// m_pMultiViewItemsPanel��NULL���Z�b�g.
	}

	// �e�E�B���h�E��Destroy���Ă�.
	CUserControl::Destroy();	// CUserControl::Destroy���Ă�.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CMultiView::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// �}���`�r���[�A�C�e���Y�p�l���̐���.
	m_pMultiViewItemsPanel = new CMultiViewItemsPanel();	// CMultiViewItemsPanel�̍쐬.

	// �}���`�r���[�A�C�e���Y�p�l���̃E�B���h�E����.
	m_pMultiViewItemsPanel->Create(_T(""), 0, 0, 0, 320, 240, hwnd, (HMENU)(WM_APP + 2), lpCreateStruct->hInstance);	// m_pMultiViewItemsPanel->Create�ŃE�B���h�E����.

	// ��ɃE�B���h�E�쐬�ɐ���������̂Ƃ���.
	return 0;	// 0��Ԃ���, �E�B���h�E�쐬�ɐ��������Ƃ������ƂɂȂ�.

}

// �E�B���h�E���j�����ꂽ��.
void CMultiView::OnDestroy(){

	// �����o�̏I������
	//Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

	// �e�N���X��OnDestroy���Ă�.
	CUserControl::OnDestroy();	// CUserControl::OnDestroy���Ă�.

}

// �E�B���h�E�̕`���v�����ꂽ���̃n���h��OnPaint.
void CMultiView::OnPaint(){

	// �ϐ��̏�����.
	HDC hDC = NULL;	// hDC��NULL�ŏ�����.
	PAINTSTRUCT ps = {0};	// ps��{0}�ŏ�����.
	HPEN hPen = NULL;	// hPen��NULL�ŏ�����.
	HBRUSH hBrush = NULL;	// hBrush��NULL�ŏ�����.

	// �`��J�n.
	hDC = BeginPaint(m_hWnd, &ps);	// BeginPaint�ŕ`��J�n.

	// �y���ƃu���V�̐���.
	hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 0xff));	// CreatePen�Ő�(�W)�̃y�����쐬.
	hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0x7f));		// CreateSolidBrush�Ő�(�Z)�̃u���V���쐬.

	// �y���ƃu���V�̑I��.
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);		// �̃y����I��.
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);	// �̃u���V��I��.

	// ��`�`��.
	Rectangle(hDC, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight);	// Rectangle�ŋ�`��`��.
	
	// �y���ƃu���V�̕���
	SelectObject(hDC, hOldBrush);		// �Â��u���V��I��.
	SelectObject(hDC, hOldPen);		// �Â��y����I��.

	// �y���ƃu���V�̔j��.
	DeleteObject(hBrush);	// �u���V�̔j��.
	DeleteObject(hPen);	// �y���̔j��.

	// �`��I��.
	EndPaint(m_hWnd, &ps);	// EndPaint�ŕ`��I��.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CMultiView::OnSize(UINT nType, int cx, int cy){

	// �e�E�B���h�E�̊��菈��.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSize���Ă�.

}