// ��d�C���N���[�h�h�~
#ifndef __FILE_DIALOG_H__
#define __FILE_DIALOG_H__

// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <tchar.h>		// TCHAR�^
#include <windows.h>	// �W��WindowsAPI
#include <string>	// std::string

// �}�N���̒�`
// UNICODE�؂�ւ�
#ifdef UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

// �t�@�C���_�C�A���O�N���XCFileDialog
class CFileDialog{

	// private�����o
	private:

		// private�����o�֐�
		void SetFilter(LPCTSTR lpctszFilter);	// �t�B���^�̃Z�b�g.

	// public�����o
	public:

		// public�����o�ϐ�
		tstring m_tstrPath;	// �t�@�C���p�Xm_tstrPath.
		tstring m_tstrDefFileName;	// �f�t�H���g�t�@�C����m_tstrDefFileName.
		tstring m_tstrExt;	// �g���qm_tstrExt.
		TCHAR *m_ptszFilter;	// �t�B���^������ւ̃|�C���^m_ptszFilter.
		DWORD m_dwFlags;	// �t���Om_dwFlags.

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CFileDialog(LPCTSTR lpctszDefFileName, LPCTSTR lpctszExt, LPCTSTR lpctszFilter, DWORD dwFlags);	// �R���X�g���N�^�ɂ�, �f�t�H���g�t�@�C����, �g���q, �t�B���^, �t���O���w�肷��.
		virtual ~CFileDialog();	// �f�X�g���N�^.
		// �����o�֐�
		BOOL ShowOpenFileDialog(HWND hWnd);	// "�J��"�t�@�C���_�C�A���O�̕\��ShowOpenFileDialog.
		BOOL ShowSaveFileDialog(HWND hWnd);	// "���O��t���ĕۑ�"�t�@�C���_�C�A���O�̕\��ShowSaveFileDialog.
		
};

#endif