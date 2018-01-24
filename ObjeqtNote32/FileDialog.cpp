// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "FileDialog.h"	// CFileDialog
#include "c_string_utility.h"	// class_c_string_utility

// �R���X�g���N�^�ɂ�, �f�t�H���g�t�@�C����, �g���q, �t�B���^, �t���O���w�肷��.
CFileDialog::CFileDialog(LPCTSTR lpctszDefFileName, LPCTSTR lpctszExt, LPCTSTR lpctszFilter, DWORD dwFlags){

	// �����o�̃Z�b�g.
	// �f�t�H���g�t�@�C����.
	if (lpctszDefFileName == NULL || _tcscmp(lpctszDefFileName, _T("")) == 0){	// NULL�܂��͋󕶎���̏ꍇ.
		m_tstrDefFileName = _T("*.");	// "*."���Z�b�g.
		m_tstrDefFileName = m_tstrDefFileName + lpctszExt;	// lpctszExt��A��. 
	}
	else{	// �����łȂ��ꍇ.
		m_tstrDefFileName = lpctszDefFileName;	// �f�t�H���g�t�@�C����lpctszDefFileName���Z�b�g.
	}
	// �f�t�H���g�g���q.
	if (lpctszExt == NULL){	// NULL�Ȃ�.
		m_tstrExt = _T("");	// m_tstrExt��""���Z�b�g.
	}
	else{	// �����łȂ��ꍇ.
		m_tstrExt = lpctszExt;	// �f�t�H���g�g���qlpctszExt���Z�b�g.
	}
	// �t�B���^.
	m_ptszFilter = NULL;	// m_ptszFilter��m_ptszFilter���Z�b�g.
	SetFilter(lpctszFilter);	// SetFilter�Ńt�B���^���Z�b�g.
	// �t���O.
	m_dwFlags = dwFlags;	// m_dwFlags��dwFlags���Z�b�g.

}

// �f�X�g���N�^.
CFileDialog::~CFileDialog(){

	// �t�B���^�z��̉��.
	delete[] m_ptszFilter;	// delete[]��m_ptszFilter�����.
	m_ptszFilter = NULL;	// m_ptszFilter��NULL�ɃZ�b�g.

}

// �t�B���^�̃Z�b�g.
void CFileDialog::SetFilter(LPCTSTR lpctszFilter){	// �t�B���^�̃Z�b�g.

	// �������擾.
	size_t len = _tcslen(lpctszFilter);	// �t�B���^�̒������擾.
	m_ptszFilter = new TCHAR[len + 1];	// �t�B���^�z��̊m��.
	wmemset(m_ptszFilter, _T('\0'), len + 1);	// '\0'�Ŗ��߂�.
	_tcscpy(m_ptszFilter, lpctszFilter);	// �t�B���^�̃R�s�[.
	class_c_string_utility::wmemreplace(m_ptszFilter, len, _T('|'), _T('\0'));	// class_c_string_utility::wmemreplace��'|'��'\0'�ɒu��.

}

// "�J��"�t�@�C���_�C�A���O�̕\��ShowOpenFileDialog.
BOOL CFileDialog::ShowOpenFileDialog(HWND hWnd){

	// �ϐ��̐錾�E������.
	OPENFILENAME ofn = {0};	// OPENFILENAME�\����ofn��{0}�ŏ�����.
	TCHAR *ptszPath = new TCHAR[_MAX_PATH];	// TCHAR���I�z����쐬��, ptszPath�Ɋi�[.
	
	// �f�t�H���g�t�@�C�������Z�b�g.
	wmemset(ptszPath, _T('\0'), _MAX_PATH);	// wmemset��0�Ŗ��߂�.
	_tcscpy(ptszPath, m_tstrDefFileName.c_str());	// �f�t�H���g�t�@�C������ptszPath�ɃZ�b�g.

	// ofn�ɒl���Z�b�g.
	ofn.lStructSize = sizeof(OPENFILENAME);	// �\���̂̃T�C�Y.
	ofn.hwndOwner = hWnd;	// �I�[�o�[�E�B���h�E.
	ofn.lpstrFile = ptszPath;	// �f�t�H���g�p�X.
	ofn.nMaxFile = _MAX_PATH;	// MAX��_MAX_PATH(260).
	ofn.lpstrDefExt = m_tstrExt.c_str();	// �f�t�H���g�g���q.
	ofn.lpstrFilter = m_ptszFilter;	// �t�B���^.
	ofn.Flags = m_dwFlags;	// �t���O.

	// �t�@�C���I��.
	if (!GetOpenFileName(&ofn)){	// GetOpenFileName�Ńt�@�C����I��.

		// �I�����Ȃ������ꍇ.(�L�����Z��)
		delete[] ptszPath;	// delete[]��ptszPath�����.
		m_tstrPath = _T("");	// m_tstrPath��""���Z�b�g.
		return FALSE;	// �������ĂȂ��̂�FALSE��Ԃ�.

	}

	// �p�X���i�[.
	m_tstrPath = ptszPath;	// ptszPath��m_tstrPath�ɑ��.

	// �o�b�t�@�����.
	delete[] ptszPath;	// delete[]��ptszPath�����.

	// ���������̂�TRUE��Ԃ�.
	return TRUE;	// ���������̂Ŗ߂�l�Ƃ���TRUE��Ԃ�.

}

// "���O��t���ĕۑ�"�t�@�C���_�C�A���O�̕\��ShowSaveFileDialog.
BOOL CFileDialog::ShowSaveFileDialog(HWND hWnd){

	// �ϐ��̐錾�E������.
	OPENFILENAME ofn = {0};	// OPENFILENAME�\����ofn��{0}�ŏ�����.
	TCHAR *ptszPath = new TCHAR[_MAX_PATH];	// TCHAR���I�z����쐬��, ptszPath�Ɋi�[.
	
	// �f�t�H���g�t�@�C�������Z�b�g.
	wmemset(ptszPath, _T('\0'), _MAX_PATH);	// wmemset��0�Ŗ��߂�.
	_tcscpy(ptszPath, m_tstrDefFileName.c_str());	// �f�t�H���g�t�@�C������ptszPath�ɃZ�b�g.

	// ofn�ɒl���Z�b�g.
	ofn.lStructSize = sizeof(OPENFILENAME);	// �\���̂̃T�C�Y.
	ofn.hwndOwner = hWnd;	// �I�[�o�[�E�B���h�E.
	ofn.lpstrFile = ptszPath;	// �f�t�H���g�p�X.
	ofn.nMaxFile = _MAX_PATH;	// MAX��_MAX_PATH(260).
	ofn.lpstrDefExt = m_tstrExt.c_str();	// �f�t�H���g�g���q.
	ofn.lpstrFilter = m_ptszFilter;	// �t�B���^.
	ofn.Flags = m_dwFlags;	// �t���O.

	// �t�@�C���I��.
	if (!GetSaveFileName(&ofn)){	// GetSaveFileName�Ńt�@�C����I��.

		// �I�����Ȃ������ꍇ.(�L�����Z��)
		delete[] ptszPath;	// delete[]��ptszPath�����.
		m_tstrPath = _T("");	// m_tstrPath��""���Z�b�g.
		return FALSE;	// �������ĂȂ��̂�FALSE��Ԃ�.

	}

	// �p�X���i�[.
	m_tstrPath = ptszPath;	// ptszPath��m_tstrPath�ɑ��.

	// �o�b�t�@�����.
	delete[] ptszPath;	// delete[]��ptszPath�����.

	// ���������̂�TRUE��Ԃ�.
	return TRUE;	// ���������̂Ŗ߂�l�Ƃ���TRUE��Ԃ�.

}