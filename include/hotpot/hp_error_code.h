/**
 * Autogenerated by HotScript (0.0.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */

#ifndef _H_hotpot_hp_error_code_hd_TYPES
#define _H_hotpot_hp_error_code_hd_TYPES
#include "hotpot/hp_platform.h"
typedef enum _HP_ERROR_CODE
{
	E_HP_NOERROR = 0,
	E_HP_ERROR = -1,
	E_HP_BAD_PARAMETER = -2,
	E_HP_SYNTAX_ERROR = -3,
	E_HP_NOT_ENOUGH_BYTEBUFF_SIZE = -4,
	E_HP_CONSTANT_REDEFINITION = -5,
	E_HP_INTEGER_OVERFLOW = -6,
	E_HP_CAN_NOT_OPEN_FILE = -7,
	E_HP_CAN_NOT_FIND_CONSTANCE = -8,
	E_HP_CONSTANCE_TYPE_TOO_SMALL = -9,
	E_HP_INVALID_CONSTANCE_TYPE = -10,
	E_HP_UNKNOW_CONSTANT_VALUE = -11,
	E_HP_SYMBOL_REDEFINITION = -12,
	E_HP_TYPEDEF_ONLY_SUPPORT_SIMPLEY_TYPE_OR_OBJECCT_TYPE = -13,
}HP_ERROR_CODE;
#define HP_ERROR_CODE_NUM 14
#endif//_H_hotpot_hp_error_code_hd_TYPES
