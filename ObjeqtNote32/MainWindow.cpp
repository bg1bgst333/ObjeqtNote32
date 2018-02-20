// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MainWindow.h"	// CMainWindow
#include "FileDialog.h"	// CFileDialog
#include "resource.h"		// ���\�[�X

// �R���X�g���N�^CMainWindow()
CMainWindow::CMainWindow() : CMenuWindow(){

	// �����o�̏�����.
	m_pMultiView = NULL;	// m_pMultiView��NULL�ŏ�����.
	m_pTextFile = NULL;	// m_pTextFile��NULL�ŏ�����.

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

	// �e�L�X�g�t�@�C���̔j��.
	if (m_pTextFile != NULL){	// m_pTextFile��NULL�łȂ����.
		delete m_pTextFile;	// delete��m_pTextFile�����.
		m_pTextFile = NULL;	// m_pTextFile��NULL���Z�b�g.
	}

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

// �e�L�X�g�t�@�C���̏�����.
void CMainWindow::InitTextFile(){

	// m_pTextFile�����邩�ǂ����ŏ������ς��.
	if (m_pTextFile != NULL){	// m_pTextFile��NULL�łȂ���.

		// �����������.
		m_pTextFile->Clear();	// m_pTextFile->Clear�Ńo�b�t�@�̃N���A.
		m_pTextFile->Close();	// m_pTextFile->Close�Ńt�@�C�������.

	}
	else{	// NULL�̎�.

		// CTextFile�I�u�W�F�N�g�̍쐬.
		m_pTextFile = new CTextFile();	// new��CTextFile�I�u�W�F�N�g���쐬��, m_pTextFile�Ƀ|�C���^���i�[.

	}

}

// �}���`�r���[�̏�����.
void CMainWindow::InitMultiView(){

	// m_pMultiView�����邩�ǂ����ŏ������ς��.
	if (m_pMultiView != NULL){	// m_pMultiView��NULL�łȂ���.

		// ��������ڂ��Ă���r���[�������폜.
		m_pMultiView->RemoveAll();	// m_pMultiView->RemoveAll�őS�č폜.

	}
	else{	// NULL�̎�.

		// CMultiView�I�u�W�F�N�g�̍쐬.
		m_pMultiView = new CMultiView();	// CMultiView�I�u�W�F�N�g�̍쐬.
		m_pMultiView->Create(_T(""), 0 /*WS_HSCROLL | WS_VSCROLL*/, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight, m_hWnd, (HMENU)(WM_APP + 1), m_hInstance);	// m_pMultiView->Create�ō쐬.
		
	}

}

// �e�L�X�g�t�@�C���̕\��.
void CMainWindow::ShowTextFile(LPCTSTR lpctszText){

	// �}���`�r���[�A�C�e���̒ǉ�.
	m_pMultiView->Add(_T("Item0"), 0, 0, m_iClientAreaWidth, 25, m_hInstance);	// m_pMultiView->Add��"Item0"��ǉ�.
	m_pMultiView->Add(_T("Item1"), 0, 25, m_iClientAreaWidth, m_iClientAreaHeight - 25, m_hInstance);	// m_pMultiView->Add��"Item1"��ǉ�.

	// �}���`�r���[�A�C�e���̎擾.
	CMultiViewItem *pItem0 = m_pMultiView->Get(0);	// 0�Ԗڂ��擾.
	CMultiViewItem *pItem1 = m_pMultiView->Get(1);	// 1�Ԗڂ��擾.

	// �R���{�{�b�N�X�I�u�W�F�N�g�̐���.
	CComboBox *pComboBox0 = new CComboBox();	// CComboBox�I�u�W�F�N�g�|�C���^pComboBox0.

	// �R���{�{�b�N�X�̃E�B���h�E����.
	pComboBox0->Create(_T(""), CBS_SORT | CBS_DROPDOWNLIST, 0, 0, m_iClientAreaWidth, 300, pItem0->m_hWnd, (HMENU)WM_APP + 200, m_hInstance);	// pComboBox0->Create��pItem0->m_hWnd��e�Ƃ��ăE�B���h�E�쐬.

	// �A�C�e���̒ǉ�.
	pComboBox0->AddString(_T("Shift_JIS"));	// pComboBox0->AddString��"Shift_JIS"��ǉ�.
	pComboBox0->AddString(_T("Unicode"));	// pComboBox0->AddString��"Unicode"��ǉ�.

	// �G�f�B�b�g�{�b�N�X�I�u�W�F�N�g�̐���.
	CEdit *pEdit1 = new CEdit();	// CEdit�I�u�W�F�N�g�|�C���^pEdit1.
	
	// �G�f�B�b�g�{�b�N�X�̃E�B���h�E�쐬.
	pEdit1->Create(_T(""), WS_BORDER | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight - 25, pItem1->m_hWnd, (HMENU)WM_APP + 201, m_hInstance);	// pEdit1->Create��pItem1->m_hWnd��e�Ƃ��ăE�B���h�E�쐬.
	
	// �e�L�X�g�̃Z�b�g.
	pEdit1->SetText(lpctszText);	// pEdit1->SetText�Ńe�L�X�g���Z�b�g.

	// �`���C���h�}�b�v�ւ̒ǉ�.
	pItem0->m_mapChildMap.insert(std::make_pair(_T("ComboBox0"), pComboBox0));	// "ComboBox0"���L�[, pComboBox0��l�Ƃ���, pItem0->m_mapChildMap�ɓo�^.
	pItem1->m_mapChildMap.insert(std::make_pair(_T("Edit1"), pEdit1));	// "Edit1"���L�[, pEdit1��l�Ƃ���, pItem1->m_mapChildMap�ɓo�^.

	// ����X�V�^�C�}�[���Z�b�g.
	SetTimer(m_hWnd, 2, 100, NULL);	// SetTimer�ōX�V�^�C�}�[���Z�b�g.(100�~���b==0.1�b)

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
	AddCommandHandler(ID_FILE_NEW_TXT, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileNewTxt);	// AddCommandHandler��ID_FILE_NEW_TXT�ɑ΂���n���h��CMainWindow::OnFileNewTxt��o�^.
	AddCommandHandler(ID_FILE_OPEN, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileOpen);	// AddCommandHandler��ID_FILE_OPEN�ɑ΂���n���h��CMainWindow::OnFileOpen��o�^.
	AddCommandHandler(ID_FILE_SAVE_AS, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileSaveAs);	// AddCommandHandler��ID_FILE_SAVE_AS�ɑ΂���n���h��CMainWindow::OnFileSaveAs��o�^.

	// �e��OnCreate���Ă�.
	return CMenuWindow::OnCreate(hwnd, lpCreateStruct);	// CMenuWindow::OnCreate��Ԃ�.

}

// �E�B���h�E���j�����ꂽ��.
void CMainWindow::OnDestroy(){

	// ���j���[�n���h���̍폜.
	DeleteCommandHandler(ID_FILE_OPEN, 0);	// DeleteCommandHandler��ID_FILE_OPEN�̃n���h�����폜.
	DeleteCommandHandler(ID_FILE_SAVE_AS, 0);	// DeleteCommandHandler��ID_FILE_SAVE_AS�̃n���h�����폜.
	DeleteCommandHandler(ID_FILE_NEW_TXT, 0);	// DeleteCommandHandler��ID_FILE_NEW_TXT�̃n���h�����폜.

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
		CMultiViewItem *pItem0 = m_pMultiView->Get(0);	// 0�Ԗڂ��擾.
		CMultiViewItem *pItem1 = m_pMultiView->Get(1);	// 1�Ԗڂ��擾.
		MoveWindow(pItem0->m_mapChildMap[_T("ComboBox0")]->m_hWnd, 0, 0, cx, 300, TRUE);	// MoveWindow��"ComboBox0"�����T�C�Y.
		MoveWindow(pItem1->m_mapChildMap[_T("Edit1")]->m_hWnd, 0, 0, cx, cy - 25, TRUE);	// MoveWindow��"Edit1"�����T�C�Y.
	}

	// ��ʍX�V.
	//InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRect�ōX�V.

}

// �^�C�}�[�C�x���g������������.
void  CMainWindow::OnTimer(UINT_PTR nIDEvent){

#if 1
	// ����X�V�^�C�}�[�̎�.
	if (nIDEvent == 2){	// 2�̎�.

		// �����̈���쐬���ĉ�ʂ̍X�V.
		InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRect�Ŗ����̈�쐬.

		// �^�C�}�[���I��.
		KillTimer(m_hWnd, 2);	// ����X�V�^�C�}�[���I��.

	}
#endif

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

// "�e�L�X�g����"��I�����ꂽ���̃n���h��.
int CMainWindow::OnFileNewTxt(WPARAM wParam, LPARAM lParam){

	// �e�L�X�g�t�@�C���̏�����.
	InitTextFile();	// InitTextFile�ŏ�����.

	// �}���`�r���[�̏�����.
	InitMultiView();	// InitMultiView�ŏ�����.
	
	// �e�L�X�g�t�@�C���̕\��.
	ShowTextFile(_T(""));	// ShowTextFile��""���Z�b�g.

	// ���������̂�0.
	return 0;	// 0��Ԃ�.

}

// "�J��"��I�����ꂽ���̃n���h��.
int CMainWindow::OnFileOpen(WPARAM wParam, LPARAM lParam){

	// "�J��"�t�@�C���̑I��.
	CFileDialog selDlg(NULL, _T("*"), _T("�e�L�X�g����(*.txt)|*.txt|���ׂẴt�@�C��(*.*)|*.*||"), OFN_FILEMUSTEXIST);	// CFileDialog�I�u�W�F�N�gselDlg���`.
	if (selDlg.ShowOpenFileDialog(m_hWnd)){	// selDlg.ShowOpenFileDialog��"�J��"�t�@�C���_�C�A���O��\��.

		// �܂�, �g���q�Ńt�@�C�����������.
		if (selDlg.m_tstrExt.compare(_T(".txt")) == 0){	// selDlg.m_tstrExt.compare��".txt"�Ȃ�.

			// �e�L�X�g�t�@�C���̏�����.
			InitTextFile();	// InitTextFile�ŏ�����.

			// �e�L�X�g�t�@�C���̓ǂݍ���.
			if (m_pTextFile->Read(selDlg.m_tstrPath.c_str())){	// m_pTextFile->Read�œǂݍ���.

				// ShiftJIS�Ȃ�J��.
				if (m_pTextFile->m_Encoding == CTextFile::ENCODING_SHIFT_JIS){	// ShiftJIS.

					// �}���`�r���[�̏�����.
					InitMultiView();	// InitMultiView�ŏ�����.
					
					// �e�L�X�g�t�@�C���̕\��.
					ShowTextFile(m_pTextFile->m_tstrText.c_str());	// ShowTextFile��m_pTextFile�̓��e��\��.
				
				}

			}
			
		}

	}

	// ���������̂�0.
	return 0;	// return��0��Ԃ�.

}

// "���O��t���ĕۑ�"��I�����ꂽ���̃n���h��.
int CMainWindow::OnFileSaveAs(WPARAM wParam, LPARAM lParam){

	// "���O��t���ĕۑ�"�t�@�C���̑I��.
	CFileDialog selDlg(NULL, _T("*"), _T("�e�L�X�g����(*.txt)|*.txt|���ׂẴt�@�C��(*.*)|*.*||"), OFN_OVERWRITEPROMPT);	// CFileDialog�I�u�W�F�N�gselDlg���`.
	if (selDlg.ShowSaveFileDialog(m_hWnd)){	// selDlg.ShowSaveFileDialog��"���O��t���ĕۑ�"�t�@�C���_�C�A���O��\��.

		// �e�L�X�g�t�@�C���̏�������.
		if (m_pTextFile != NULL){	// m_pTextFile��NULL�łȂ��Ȃ�.

			// �e�A�C�e�����擾.
			CMultiViewItem *pItem0 = m_pMultiView->Get(0);	// 0�Ԗڂ��擾.
			CComboBox *pComboBox0 = (CComboBox *)(pItem0->m_mapChildMap[_T("ComboBox0")]);	// pComboBox0���擾.
			CMultiViewItem *pItem1 = m_pMultiView->Get(1);	// 1�Ԗڂ��擾.
			CEdit *pEdit1 = (CEdit *)(pItem1->m_mapChildMap[_T("Edit1")]);	// pEdit1���擾.
			m_pTextFile->SetText(pEdit1->GetText());	// "Edit1"�̃e�L�X�g���Z�b�g.
			m_pTextFile->Write(selDlg.m_tstrPath.c_str());	// m_tstrPath�ɏ�������.

		}

	}
	
	// ���������̂�0.
	return 0;	// return��0��Ԃ�.

}