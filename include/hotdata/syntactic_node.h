/**
 * Autogenerated by HotScript (0.0.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */

#ifndef _H_hotdata_syntactic_node_hd_TYPES
#define _H_hotdata_syntactic_node_hd_TYPES
#include "hotpot/hp_platform.h"
#define	MAX_IDENTIFIER_LENGTH 128
#define	MAX_COMMENT_LENGTH 1024
typedef struct _ST_UNIX_COMMENT
{
	hpbool empty;
	hpchar text[MAX_COMMENT_LENGTH];
}ST_UNIX_COMMENT;
typedef enum _SN_VALUE_TYPE
{
	E_SNVT_IDENTIFIER = 0,
	E_SNVT_CHAR = 1,
	E_SNVT_DOUBLE = 2,
	E_SNVT_STRING = 3,
	E_SNVT_BOOL = 4,
	E_SNVT_INT64 = 5,
	E_SNVT_UINT64 = 6,
	E_SNVT_HEX_INT64 = 7,
	E_SNVT_HEX_UINT64 = 8,
}SN_VALUE_TYPE;
#define SN_VALUE_TYPE_NUM 9
typedef union _UN_VALUE
{
	hpint64 i64;
	hpint64 hex_i64;
	hpuint64 ui64;
	hpuint64 hex_ui64;
	hpchar str[MAX_IDENTIFIER_LENGTH];
	hpbool b;
	hpdouble d;
	hpchar c;
	hpchar identifier[MAX_IDENTIFIER_LENGTH];
}UN_VALUE;
typedef struct _ST_VALUE
{
	SN_VALUE_TYPE type;
	UN_VALUE val;
}ST_VALUE;
typedef enum _SN_SIMPLE_TYPE
{
	E_ST_INT8 = 0,
	E_ST_INT16 = 1,
	E_ST_INT32 = 2,
	E_ST_INT64 = 3,
	E_ST_UINT8 = 4,
	E_ST_UINT16 = 5,
	E_ST_UINT32 = 6,
	E_ST_UINT64 = 7,
	E_ST_BOOL = 8,
	E_ST_CHAR = 9,
	E_ST_DOUBLE = 10,
}SN_SIMPLE_TYPE;
#define SN_SIMPLE_TYPE_NUM 11
typedef enum _SN_CONTAINER_TYPE
{
	E_CT_VECTOR = 0,
	E_CT_STRING = 1,
}SN_CONTAINER_TYPE;
#define SN_CONTAINER_TYPE_NUM 2
typedef enum _SN_TYPE
{
	E_SNT_SIMPLE = 0,
	E_SNT_CONTAINER = 1,
	E_SNT_REFER = 2,
}SN_TYPE;
#define SN_TYPE_NUM 3
typedef struct _ST_TYPE
{
	SN_TYPE type;
	SN_SIMPLE_TYPE st;
	SN_CONTAINER_TYPE ct;
	hpchar ot[MAX_IDENTIFIER_LENGTH];
}ST_TYPE;
typedef struct _ST_Parameter
{
	ST_TYPE type;
	hpchar identifier[MAX_IDENTIFIER_LENGTH];
}ST_Parameter;
#define	MAX_PARAMETER_NUM 16
typedef struct _ST_Parameters
{
	hpuint32 par_list_num;
	ST_Parameter par_list[MAX_PARAMETER_NUM];
}ST_Parameters;
#define	MAX_ARGUMENT_NUM 16
typedef struct _ST_ARGUMENTS
{
	hpuint32 arg_list_num;
	ST_TYPE arg_list[MAX_ARGUMENT_NUM];
}ST_ARGUMENTS;
typedef enum _ST_EXPRESSION_OPER
{
	E_EO_AND = 0,
	E_EO_EQUAL = 1,
}ST_EXPRESSION_OPER;
#define ST_EXPRESSION_OPER_NUM 2
typedef struct _ST_Expression
{
	hpbool neg;
	ST_VALUE op0;
	ST_EXPRESSION_OPER oper;
	ST_VALUE op1;
}ST_Expression;
typedef struct _ST_CONDITION
{
	hpbool empty;
	ST_Expression exp;
}ST_CONDITION;
typedef struct _ST_FIELD
{
	ST_CONDITION condition;
	ST_TYPE type;
	ST_ARGUMENTS args;
	hpchar identifier[MAX_IDENTIFIER_LENGTH];
	ST_UNIX_COMMENT comment;
}ST_FIELD;
#define	MAX_TA_LIST_NUM 4
typedef enum _TA_TYPE
{
	E_TA_SWITCH = 0,
	E_TA_UNIQUE = 1,
	E_TA_LOWER_BOUND = 2,
	E_TA_UPPER_BOUND = 3,
	E_TA_COUNTER = 4,
}TA_TYPE;
#define TA_TYPE_NUM 5
typedef struct _ST_TypeAnnotation
{
	TA_TYPE type;
	ST_VALUE val;
}ST_TypeAnnotation;
typedef struct _ST_TypeAnnotations
{
	hpuint32 ta_list_num;
	ST_TypeAnnotation ta_list[MAX_TA_LIST_NUM];
}ST_TypeAnnotations;
#define	MAX_PACKAGE_NAME_LENGTH 1024
typedef struct _ST_Import
{
	hpchar package_name[MAX_PACKAGE_NAME_LENGTH];
}ST_Import;
typedef struct _ST_Const
{
	ST_TYPE type;
	hpchar identifier[MAX_IDENTIFIER_LENGTH];
	ST_VALUE val;
}ST_Const;
typedef struct _ST_ENUM_DEF
{
	hpchar identifier[MAX_IDENTIFIER_LENGTH];
	ST_VALUE val;
	ST_UNIX_COMMENT comment;
}ST_ENUM_DEF;
#define	MAX_ENUM_DEF_LIST_NUM 65536
typedef struct _ST_ENUM
{
	hpchar name[MAX_IDENTIFIER_LENGTH];
	ST_TypeAnnotations type_annotations;
	hpuint32 enum_def_list_num;
	ST_ENUM_DEF enum_def_list[MAX_ENUM_DEF_LIST_NUM];
}ST_ENUM;
#define	MAX_FIELD_LIST_NUM 65536
typedef struct _ST_FIELD_LIST
{
	hpuint32 field_list_num;
	ST_FIELD field_list[MAX_FIELD_LIST_NUM];
}ST_FIELD_LIST;
typedef struct _ST_STRUCT
{
	ST_TypeAnnotations ta;
	hpchar name[MAX_IDENTIFIER_LENGTH];
	ST_Parameters parameters;
	ST_FIELD_LIST field_list;
}ST_STRUCT;
typedef struct _ST_UNION
{
	ST_TypeAnnotations ta;
	hpchar name[MAX_IDENTIFIER_LENGTH];
	ST_Parameters parameters;
	ST_FIELD_LIST field_list;
}ST_UNION;
typedef struct _ST_TYPEDEF
{
	ST_TYPE type;
	hpchar name[MAX_IDENTIFIER_LENGTH];
}ST_TYPEDEF;
typedef enum _EN_DEFINITION_TYPE
{
	E_DT_IMPORT = 0,
	E_DT_CONST = 1,
	E_DT_ENUM = 2,
	E_DT_STRUCT = 3,
	E_DT_UNION = 4,
	E_DT_TYPEDEF = 5,
	E_DT_UNIX_COMMENT = 6,
}EN_DEFINITION_TYPE;
#define EN_DEFINITION_TYPE_NUM 7
typedef union _UN_DEFINITION
{
	ST_Import de_import;
	ST_Const de_const;
	ST_UNIX_COMMENT de_unix_comment;
	ST_ENUM de_enum;
	ST_STRUCT de_struct;
	ST_UNION de_union;
	ST_TYPEDEF de_typedef;
}UN_DEFINITION;
typedef struct _ST_DEFINITION
{
	EN_DEFINITION_TYPE type;
	UN_DEFINITION definition;
}ST_DEFINITION;
#endif//_H_hotdata_syntactic_node_hd_TYPES
