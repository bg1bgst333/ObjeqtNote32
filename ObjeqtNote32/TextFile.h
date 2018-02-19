// ��d�C���N���[�h�h�~
#ifndef __TEXT_FILE_H__
#define __TEXT_FILE_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "BinaryFile.h"	// CBinaryFile

// �e�L�X�g�t�@�C���N���XCTextFile
class CTextFile : public CBinaryFile{

	// public�����o
	public:

		// �񋓌^�̒�`
		// �����R�[�h
		typedef enum TAG_ENCODING{
			ENCODING_NONE,
			ENCODING_SHIFT_JIS,
			ENCODING_UNICODE
		} ENCODING;
		// BOM
		typedef enum TAG_BOM{
			BOM_NONE,
			BOM_UTF16LE
		} BOM;

		// public�����o�ϐ�
		tstring m_tstrText;		// �e�L�X�g���e.
		ENCODING m_Encoding;	// �����R�[�h.
		BOM m_Bom;	// BOM.
		
		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CTextFile();	// �R���X�g���N�^CTextFile
		virtual ~CTextFile();	// �f�X�g���N�^~CTextFile
		// �����o�֐�
		BOM CheckBom();	// BOM�̃`�F�b�N.
		void DecodeUtf16LE();	// UTF16LE�̃o�C�g�f�[�^���e�L�X�g�Ƀf�R�[�h.
		void DecodeShiftJis();	// Shift_JIS�̃o�C�g�f�[�^���e�L�X�g�Ƀf�R�[�h.
		virtual BOOL Read(LPCTSTR lpctszFileName);	// �w��̃e�L�X�g�t�@�C����S����ēǂݍ���.
		void SetText(tstring tstrText);	// �e�L�X�g�̃Z�b�g.
		void EncodeUtf16LEWithBom(tstring tstrText);	// �w��̃e�L�X�g��UTF-16LE�ɕϊ�.
		void EncodeShiftJis(tstring tstrText);	// �w��̃e�L�X�g��Shift_JIS�ɕϊ�.
		virtual BOOL Write(LPCTSTR lpctszFileName);	// �w��̃e�L�X�g�t�@�C���ɑS����ď�������.
		virtual void Clear();	// �o�b�t�@�̃N���A.

};

#endif