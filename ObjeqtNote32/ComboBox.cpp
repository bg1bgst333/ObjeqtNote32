// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "ComboBox.h"	// CComboBox

// �R���X�g���N�^CComboBox
CComboBox::CComboBox() : CCustomControl(){

}

// �f�X�g���N�^~CComboBox
CComboBox::~CComboBox(){

	// �����o�̏I������
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

}

// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
BOOL CComboBox::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)

	// �E�B���h�E�N���X����"ComboBox"�ȃJ�X�^���R���g���[�����쐬.
	return CCustomControl::Create(_T("ComboBox"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, (HMENU)hMenu, hInstance);	// CCustomControl::Create�ŃR���{�{�b�N�X�R���g���[�����쐬.

}

// �R���{�{�b�N�X�ɕ������ǉ�����֐�AddString.
void CComboBox::AddString(LPCTSTR lpctszStr){

	// �w��̕������ǉ�.
	SendMessage(m_hWnd, CB_ADDSTRING, 0, (LPARAM)lpctszStr);	// SendMessage��CB_ADDSTRING�𑗂邱�ƂŎw��̕������ǉ�.

}

// �R���{�{�b�N�X�̎w��̃C���f�b�N�X�v�f��I��SetCurSel.
void CComboBox::SetCurSel(int iIndex){

	// �w��̗v�f���Z�b�g.
	SendMessage(m_hWnd, CB_SETCURSEL, (WPARAM)iIndex, 0);	// SendMessage��CB_SETCURSEL�𑗂邱�ƂŎw��̗v�f��I��.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CComboBox::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// UM_SIZECHILD�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.
	WPARAM wParam;	// WPARAM�^wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAM��wParam���Z�b�g.
	SendMessage(GetParent(hwnd), UM_SIZECHILD, wParam, (LPARAM)hwnd);	// SendMessage��UM_SIZECHILD�𑗐M.

	// �e��OnCreate���Ă�.
	return CCustomControl::OnCreate(hwnd, lpCreateStruct);	// CCustomControl::OnCreate��Ԃ�.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CComboBox::OnSize(UINT nType, int cx, int cy){

	// �e�N���X��OnSize.
	CCustomControl::OnSize(nType, cx, cy);	// CCustomControl::OnSize���Ă�.

	// UM_SIZECHILD�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.
	WPARAM wParam;	// WPARAM�^wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAM��wParam���Z�b�g.
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);	// SendMessage��UM_SIZECHILD�𑗐M.

}