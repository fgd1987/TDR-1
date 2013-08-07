#ifndef _H_syntactic_node_hd_WRITER_HEADER
#define _H_syntactic_node_hd_WRITER_HEADER
#include "hotpot/hp_platform.h"
#include "hotprotocol/hp_abstract_writer.h"
#include "syntactic_node.h"
void write_ST_UNIX_COMMENT(HPAbstractWriter *self, const ST_UNIX_COMMENT *data);
void write_SN_VALUE_TYPE_name(HPAbstractWriter *self, const SN_VALUE_TYPE data);
void write_SN_VALUE_TYPE_number(HPAbstractWriter *self, const SN_VALUE_TYPE data);
void write_SN_VALUE_TYPE(HPAbstractWriter *self, const SN_VALUE_TYPE data);
void write_UN_VALUE(HPAbstractWriter *self, const UN_VALUE *data , const SN_VALUE_TYPE s);
void write_ST_VALUE(HPAbstractWriter *self, const ST_VALUE *data);
void write_SN_SIMPLE_TYPE_name(HPAbstractWriter *self, const SN_SIMPLE_TYPE data);
void write_SN_SIMPLE_TYPE_number(HPAbstractWriter *self, const SN_SIMPLE_TYPE data);
void write_SN_SIMPLE_TYPE(HPAbstractWriter *self, const SN_SIMPLE_TYPE data);
void write_SN_CONTAINER_TYPE_name(HPAbstractWriter *self, const SN_CONTAINER_TYPE data);
void write_SN_CONTAINER_TYPE_number(HPAbstractWriter *self, const SN_CONTAINER_TYPE data);
void write_SN_CONTAINER_TYPE(HPAbstractWriter *self, const SN_CONTAINER_TYPE data);
void write_SN_TYPE_name(HPAbstractWriter *self, const SN_TYPE data);
void write_SN_TYPE_number(HPAbstractWriter *self, const SN_TYPE data);
void write_SN_TYPE(HPAbstractWriter *self, const SN_TYPE data);
void write_ST_TYPE(HPAbstractWriter *self, const ST_TYPE *data);
void write_ST_Parameter(HPAbstractWriter *self, const ST_Parameter *data);
void write_ST_Parameters(HPAbstractWriter *self, const ST_Parameters *data);
void write_ST_ARGUMENTS(HPAbstractWriter *self, const ST_ARGUMENTS *data);
void write_ST_EXPRESSION_OPER_name(HPAbstractWriter *self, const ST_EXPRESSION_OPER data);
void write_ST_EXPRESSION_OPER_number(HPAbstractWriter *self, const ST_EXPRESSION_OPER data);
void write_ST_EXPRESSION_OPER(HPAbstractWriter *self, const ST_EXPRESSION_OPER data);
void write_ST_Expression(HPAbstractWriter *self, const ST_Expression *data);
void write_ST_CONDITION(HPAbstractWriter *self, const ST_CONDITION *data);
void write_ST_FIELD(HPAbstractWriter *self, const ST_FIELD *data);
void write_TA_TYPE_name(HPAbstractWriter *self, const TA_TYPE data);
void write_TA_TYPE_number(HPAbstractWriter *self, const TA_TYPE data);
void write_TA_TYPE(HPAbstractWriter *self, const TA_TYPE data);
void write_ST_TypeAnnotation(HPAbstractWriter *self, const ST_TypeAnnotation *data);
void write_ST_TypeAnnotations(HPAbstractWriter *self, const ST_TypeAnnotations *data);
void write_ST_Import(HPAbstractWriter *self, const ST_Import *data);
void write_ST_Const(HPAbstractWriter *self, const ST_Const *data);
void write_ST_ENUM_DEF(HPAbstractWriter *self, const ST_ENUM_DEF *data);
void write_ST_ENUM(HPAbstractWriter *self, const ST_ENUM *data);
void write_ST_FIELD_LIST(HPAbstractWriter *self, const ST_FIELD_LIST *data);
void write_ST_STRUCT(HPAbstractWriter *self, const ST_STRUCT *data);
void write_ST_UNION(HPAbstractWriter *self, const ST_UNION *data);
void write_ST_TYPEDEF(HPAbstractWriter *self, const ST_TYPEDEF *data);
void write_EN_DEFINITION_TYPE_name(HPAbstractWriter *self, const EN_DEFINITION_TYPE data);
void write_EN_DEFINITION_TYPE_number(HPAbstractWriter *self, const EN_DEFINITION_TYPE data);
void write_EN_DEFINITION_TYPE(HPAbstractWriter *self, const EN_DEFINITION_TYPE data);
void write_UN_DEFINITION(HPAbstractWriter *self, const UN_DEFINITION *data , const EN_DEFINITION_TYPE s);
void write_ST_DEFINITION(HPAbstractWriter *self, const ST_DEFINITION *data);
#endif//_H_syntactic_node_hd_WRITER_HEADER