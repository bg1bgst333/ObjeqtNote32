// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MainWindow.h"	// CMainWindow
#include "FileDialog.h"	// CFileDialog
#include "resource.h"		// ���\�[�X

// �R���X�g���N�^CMainWindow()
CMainWindow::CMainWindow() : CMenuWindow(){

	// �����o�̏�����.
	m_pMultiView = NULL;	// m_pMultiView��NULL�ŏ�����.

}

// �f�X�g���N�^~CMainWindow()
CMainWindow::~CMainWindow(){

	// �����o�̏I������
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance){

	// ���j���[����, LTGRAY_BRUSH.
	return RegisterClass(hInstance, NULL);	// RegisterClass�œo�^.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpszMenuName){

	// �E�B���h�E�v���V�[�W���ɂ�CWindow::StaticWndowProc, ���j���[��lpszMenuName�Ƃ���.((LPCTSTR)�ŃL���X�g���Ȃ��ƃI�[�o�[���[�h���B���ɂȂ�.)
	return RegisterClass(hInstance, (LPCTSTR)lpszMenuName, (HBRUSH)GetStockObject(LTGRAY_BRUSH));	// CWindow::RegisterClass�œo�^.(�w�i��LTGRAY_BRUSH.)

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(���j���[���w��, �w�i�u���V�w��o�[�W����.)
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpszMenuName, HBRUSH hbrBackground){

	// �E�B���h�E�v���V�[�W���ɂ�CWindow::StaticWndowProc, ���j���[��lpszMenuName�Ƃ���.((LPCTSTR)�ŃL���X�g���Ȃ��ƃI�[�o�[���[�h���B���ɂȂ�.�w�i��hbrBackground.)
	return CMenuWindow::RegisterClass(hInstance, _T("CMainWindow"), (LPCTSTR)lpszMenuName, hbrBackground);	// CMenuWindow::RegisterClass�œo�^.

}

// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)

	// �E�B���h�E�N���X����"CMainWindow".
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Create�ɃE�B���h�E�N���X��"CMainWindow"���w��.

}

// �E�B���h�E�̔j���ƏI�������֐�Destroy.
void CMainWindow::Destroy(){

	// �}���`�r���[�̍폜.
	if (m_pMultiView != NULL){	// m_pMultiView��NULL�łȂ����.

		// �}���`�r���[�A�C�e���̍폜.
		m_pMultiView->RemoveAll();	// m_pMultiView->RemoveAll�ŃA�C�e����S�č폜.
		
		// �}���`�r���[�̔j��.
		m_pMultiView->Destroy();	// m_pMultiView->Destroy��m_pMultiView�̏I�����������s.
		delete m_pMultiView;	// delete��m_pMultiView�����.
		m_pMultiView = NULL;	// m_pMultiView��NULL���Z�b�g.

	}

	// �e�E�B���h�E��Destroy���Ă�.
	CMenuWindow::Destroy();	// CMenuWindow::Destroy���Ă�.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// ���j���[�o�[�̍쐬.
	m_pMenuBar = new CMenuBar(hwnd);	// CMenuBar�I�u�W�F�N�gm_pMenuBar���쐬.

	// ���j���[�̃��[�h.
	m_pMenuBar->LoadMenu(lpCreateStruct->hInstance, IDR_MENU1);	// LoadMenu��IDR_MENU1�����[�h.

	// ���j���[�̃Z�b�g.
	m_pMenuBar->SetMenu(hwnd);	// SetMenu��hwnd�Ƀ��j���[���Z�b�g.

#if 0
	// �}���`�r���[�R���g���[���I�u�W�F�N�g�̍쐬.
	m_pMultiView = new CMultiView();	// CMultiView�I�u�W�F�N�g�̍쐬.

	// �}���`�r���[�R���g���[���̃E�B���h�E�쐬.
	m_pMultiView->Create(_T(""), 0, 0, 0, 720, 800, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// m_pMultiView->Create�ō쐬.

	// �}���`�r���[�A�C�e���̒ǉ�.
	m_pMultiView->Add(_T("Item0"), 320, 32, 64, 64, lpCreateStruct->hInstance);	// m_pMultiView->Add��"Item0"��ǉ�.
	m_pMultiView->Add(_T("Item1"), 32, 320, 64, 64, lpCreateStruct->hInstance);	// m_pMultiView->Add��"Item1"��ǉ�.

	// �}���`�r���[�A�C�e���̎擾.
	CMultiViewItem *pItem0 = m_pMultiView->Get(0);	// 0�Ԗڂ��擾.
	CMultiViewItem *pItem1 = m_pMultiView->Get(1);	// 1�Ԗڂ��擾.
#endif

#if 0
	// �G�f�B�b�g�R���g���[���̐���.
	// �G�f�B�b�g0.
	CEdit *pEdit0 = new CEdit();	// CEdit�I�u�W�F�N�g�𐶐�.
	pEdit0->Create(_T("Edit0"), WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 480, 100, pItem0->m_hWnd, (HMENU)WM_APP + 200, lpCreateStruct->hInstance);	// m_pEdit0->Create��pItem0->m_hWnd��e�Ƃ��ăE�B���h�E�쐬.
	pItem0->m_mapChildMap.insert(std::make_pair(_T("Edit0"), pEdit0));	// "Edit0"���L�[, pEdit0��l�Ƃ���, pItem0->m_mapChildMap�ɓo�^.

	// �G�f�B�b�g1.
	CEdit *pEdit1 = new CEdit();	//CEdit�I�u�W�F�N�g�𐶐�.
	pEdit1->Create(_T("Edit1"), WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 100, 480, pItem1->m_hWnd, (HMENU)WM_APP + 201, lpCreateStruct->hInstance);	// m_pEdit1->Create��pItem1->m_hWnd��e�Ƃ��ăE�B���h�E�쐬.
	pItem1->m_mapChildMap.insert(std::make_pair(_T("Edit1"), pEdit1));	// "Edit1"���L�[, pEdit1��l�Ƃ���, pItem1->m_mapChildMap�ɓo�^.
#endif

	// ���j���[�n���h���̒ǉ�.
	AddCommandHandler(ID_FILE_OPEN, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileOpen);	// AddCommandHandler��ID_FILE_OPEN�ɑ΂���n���h��CMainWindow::OnFileOpen��o�^.
	AddCommandHandler(ID_FILE_SAVE_AS, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileSaveAs);	// AddCommandHandler��ID_FILE_SAVE_AS�ɑ΂���n���h��CMainWindow::OnFileSaveAs��o�^.

	// ��ɃE�B���h�E�쐬�ɐ���������̂Ƃ���.
	return 0;	// 0��Ԃ���, �E�B���h�E�쐬�ɐ��������Ƃ������ƂɂȂ�.

}

// �E�B���h�E���j�����ꂽ��.
void CMainWindow::OnDestroy(){

	// ���j���[�n���h���̍폜.
	DeleteCommandHandler(ID_FILE_OPEN, 0);	// DeleteCommandHandler��ID_FILE_OPEN�̃n���h�����폜.
	DeleteCommandHandler(ID_FILE_SAVE_AS, 0);	// DeleteCommandHandler��ID_FILE_SAVE_AS�̃n���h�����폜.

	// �����o�̏I������
	//Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

	// �e�E�B���h�E��OnDestroy���Ă�.
	CMenuWindow::OnDestroy();	// CMenuWindow::OnDestroy���Ă�.

	// �I�����b�Z�[�W�̑��M.
	PostQuitMessage(0);	// PostQuitMessage�ŏI���R�[�h��0�Ƃ���WM_QUIT���b�Z�[�W�𑗐M.

}
// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CMainWindow::OnSize(UINT nType, int cx, int cy){

	// �e�E�B���h�E��OnSize.
	CMenuWindow::OnSize(nType, cx, cy);	// CWindow��OnSize.

	// �}���`�r���[�̃T�C�Y�̓E�B���h�E�ɂ҂����荇�킹��.
	if (m_pMultiView != NULL){	// NULL�łȂ����.
		MoveWindow(m_pMultiView->m_hWnd, m_pMultiView->m_x, m_pMultiView->m_y, cx, cy, TRUE);	// MoveWindow��m_pMultiView->m_hWnd�̃T�C�Y��ύX.
	}

	// ��ʍX�V.
	InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRect�ōX�V.

}

// �E�B���h�E�̕`���v�����ꂽ���̃n���h��OnPaint.
void CMainWindow::OnPaint(){

	// �ϐ��̏�����.
	HDC hDC = NULL;	// hDC��NULL�ŏ�����.
	PAINTSTRUCT ps = {0};	// ps��{0}�ŏ�����.
	HPEN hPen = NULL;	// hPen��NULL�ŏ�����.
	HBRUSH hBrush = NULL;	// hBrush��NULL�ŏ�����.

	// �`��J�n.
	hDC = BeginPaint(m_hWnd, &ps);	// BeginPaint�ŕ`��J�n.

	// �y���ƃu���V�̐���.
	hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0xff, 0));	// CreatePen�ŗ�(�W)�̃y�����쐬.
	hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0x7f, 0));		// CreateSolidBrush�ŗ�(�Z)�̃u���V���쐬.

	// �y���ƃu���V�̑I��.
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);		// �΂̃y����I��.
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);	// �΂̃u���V��I��.

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

// �E�B���h�E�������.
int CMainWindow::OnClose(){

	// �E�B���h�E�̏I������.
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

	// 0��Ԃ�.
	return 0;	// 0��Ԃ��ăE�B���h�E�����.

}

// "�J��"��I�����ꂽ���̃n���h��.
int CMainWindow::OnFileOpen(WPARAM wParam, LPARAM lParam){

	// "�J��"�t�@�C���̑I��.
	CFileDialog selDlg(NULL, _T("*"), _T("�e�L�X�g����(*.txt)|*.txt|���ׂẴt�@�C��(*.*)|*.*||"), OFN_FILEMUSTEXIST);	// CFileDialog�I�u�W�F�N�gselDlg���`.
	if (selDlg.ShowOpenFileDialog(m_hWnd)){	// selDlg.ShowOpenFileDialog��"�J��"�t�@�C���_�C�A���O��\��.

		// �I�����ꂽ�t�@�C���p�X��\��.
		MessageBox(m_hWnd, selDlg.m_tstrPath.c_str(), _T("ObjeqtNote"), MB_OK | MB_ICONASTERISK);	// MessageBox��selDlg.m_tstrPath��\��.

	}

	// ���������̂�0.
	return 0;	// return��0��Ԃ�.

}

// "���O��t���ĕۑ�"��I�����ꂽ���̃n���h��.
int CMainWindow::OnFileSaveAs(WPARAM wParam, LPARAM lParam){

	// "���O��t���ĕۑ�"�t�@�C���̑I��.
	CFileDialog selDlg(NULL, _T("*"), _T("�e�L�X�g����(*.txt)|*.txt|���ׂẴt�@�C��(*.*)|*.*||"), OFN_OVERWRITEPROMPT);	// CFileDialog�I�u�W�F�N�gselDlg���`.
	if (selDlg.ShowSaveFileDialog(m_hWnd)){	// selDlg.ShowSaveFileDialog��"���O��t���ĕۑ�"�t�@�C���_�C�A���O��\��.

		// �I�����ꂽ�t�@�C���p�X��\��.
		MessageBox(m_hWnd, selDlg.m_tstrPath.c_str(), _T("ObjeqtNote"), MB_OK | MB_ICONASTERISK);	// MessageBox��selDlg.m_tstrPath��\��.

	}
	
	// ���������̂�0.
	return 0;	// return��0��Ԃ�.

}