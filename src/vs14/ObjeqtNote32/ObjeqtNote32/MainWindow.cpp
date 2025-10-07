// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "resource.h"	// ���\�[�X
#include "MainWindow.h"	// CMainWindow
#include "FileDialog.h"	// CFileDialog

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance) {

	// �E�B���h�E�N���X����"CMainWindow".
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"));	// CWindow::RegisterClass�ŃE�B���h�E�N���X��"CMainWindow"��o�^.

}

// �R���X�g���N�^CMainWindow()
CMainWindow::CMainWindow() {

	// �����o�̏�����.
	m_hInstance = NULL;	// m_hInstance��NULL�ŏ�����.
	m_pMainMenu = NULL;	// m_pMainMenu��NULL�ŏ�����.

}

// �f�X�g���N�^~CMainWindow()
CMainWindow::~CMainWindow() {

	// �����o�̏I������.
	Destroy();	// Destroy�Ŏq�E�B���h�E�̔j��.

}

// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance) {

	// �E�B���h�E�N���X����"CMainWindow".
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Create�ɃE�B���h�E�N���X��"CMainWindow"���w��.

}

// �E�B���h�E�j���֐�Destroy
BOOL CMainWindow::Destroy() {

	// �ϐ��̏�����.
	BOOL bRet = FALSE;	// bRet��FALSE�ŏ�����.

	// DestroyChildren�𕪂����̂�, ���g�̃E�B���h�E�j���͖��Ȃ�.
	// �܂��q�E�B���h�E�̔j��.
	DestroyChildren();

	// ���g�̃E�B���h�E�j��.
	bRet = CWindow::Destroy();	// �߂�l��bRet�Ɋi�[.

	// bRet��Ԃ�.
	return bRet;

}

// �q�E�B���h�E�j���֐�DestroyChildren
BOOL CMainWindow::DestroyChildren() {

	// �ϐ��̏�����.
	BOOL bRet = FALSE;	// bRet��FALSE�ŏ�����.

	// �j��������TRUE��Ԃ�.
	if (bRet) {	// TRUE�Ȃ�.
		return TRUE;	// TRUE��Ԃ�.
	}

	// �j�����Ȃ����, CWindow��DestroyChildren��Ԃ�.
	return CWindow::DestroyChildren();	// CWindow::DestroyChildren��Ԃ�.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {

	// �e�N���X��OnCreate���Ă�.
	m_hInstance = lpCreateStruct->hInstance;
	int iRet = CWindow::OnCreate(hwnd, lpCreateStruct);	// CWindow::OnCreate���Ă�, �߂�l��Ԃ�.
	m_pMainMenu = CWindow::GetMenu();	// CWindow::GetMenu��m_pMainMenu�擾.
	if (m_pMainMenu == NULL) {	// ���j���[�n���h���������ꍇ��, m_pMainMenu��NULL�ɂȂ�.
		m_pMainMenu = new CMenu();
		BOOL bRet = m_pMainMenu->LoadMenu(lpCreateStruct->hInstance, IDM_MAINMENU);	// IDM_MAINMENU�����[�h.
		if (bRet) {
			SetMenu(m_pMainMenu);	// CWindow::SetMenu��m_pMainMenu���Z�b�g.
			// ���j���[�n���h���̒ǉ�.
			AddCommandHandler(ID_ITEM_FILE_OPEN, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnFileOpen);	// AddCommandHandler��ID_ITEM_FILE_OPEN�ɑ΂���n���h��CMainWindow::OnFileOpen��o�^.
		}
	}

	return iRet;

}

// �E�B���h�E���j�����ꂽ��.
void CMainWindow::OnDestroy() {

	// ���j���[�n���h���̍폜.
	DeleteCommandHandler(ID_ITEM_FILE_OPEN, 0);	// DeleteCommandHandler��ID_ITEM_FILE_OPEN�̃n���h�����폜.

	// ���j���[�̏I������.
	CMenu::DeleteMenuHandleMap();
	m_pMainMenu = NULL;

	// CWindow��OnDestroy���Ă�.
	CWindow::OnDestroy();	// CWindow::OnDestroy���Ă�.

}

// �E�B���h�E�������鎞.
int CMainWindow::OnClose() {

	// ���b�Z�[�W�{�b�N�X��"Close CMainWindow OK?"�ƕ\��.
	int iRet = MessageBox(m_hWnd, _T("Close CMainWindow OK?"), _T("ObjeqtNote32"), MB_OKCANCEL);	// MessageBox��"Close CMainWindow OK?"�ƕ\����, �߂�l��iRet�Ɋi�[.
	if (iRet != IDOK) {	// OK�ȊO.(Cancel�Ȃ�.)
		return -1;	// -1��Ԃ�.
	}

	// ���̃E�B���h�E�̔j��.(OnClose�̌�, �E�B���h�E�̔j������������ɍs����̂�, Destroy�͕s�v�Ȃ̂ŃR�����g�A�E�g.)
	//Destroy();	// Destroy�ł��̃E�B���h�E�̔j������.

	// OK�Ȃ̂ŕ���.
	return CWindow::OnClose();	// �e�N���X��OnClose���Ă�.(�e�N���X��OnClose�͏�ɕ��鏈���ɂȂ��Ă���.)

}

// "�J��"���I�����ꂽ��.
int CMainWindow::OnFileOpen(WPARAM wParam, LPARAM lParam) {

	// "�J��"�_�C�A���O
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("�e�L�X�g�t�@�C��(*.txt)|*.txt|���ׂẴt�@�C��(*.*)|*.*||"));
	INT_PTR ret = dlg.DoModal();
	if (ret == IDOK) {
		MessageBox(m_hWnd, dlg.GetOFN().lpstrFile, _T("ObjeqtNote32"), MB_OK);	// �I�������t�@�C���̃t�@�C���p�X��\��.
	}

	// 0��Ԃ�.
	return 0;	// ���������̂�0.

}
