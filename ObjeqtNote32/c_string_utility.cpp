// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "c_string_utility.h"	// class_c_string_utility

// �������̈���̕����u��.
const wchar_t *class_c_string_utility::wmemreplace(wchar_t *target, size_t len, wchar_t before, wchar_t after){

	// target��before��after�ɒu��.
	for (unsigned int i = 0; i < len; i++){	// len�̐������J��Ԃ�.
		if (target[i] == before){	// target[i]��before�������ꍇ.
			target[i] = after;	// target[i]��after���Z�b�g.
		}
	}

	// �ϊ���̕������Ԃ�.
	return target;	// target��Ԃ�.

}