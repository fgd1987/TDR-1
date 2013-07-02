#ifndef _H_DDEKIT_JSON_ENCODING_READER
#define _H_DDEKIT_JSON_ENCODING_READER

#include "hotpot/hp_platform.h"
#include "hotpot/hp_reader.h"

typedef struct tagDDEKIT_JSON_ENCODING_READER
{
	HPAbstractReader dpr;


}DDEKIT_JSON_ENCODING_READER;


HP_API hpint32 ddekit_json_encoding_reader_init(DDEKIT_JSON_ENCODING_READER *self, const void *addr, hpuint32 size);

HP_API hpint32 ddekit_json_encoding_reader_fini(DDEKIT_JSON_ENCODING_READER *self);

//virtual public functions

HP_API hpint32 ddekit_json_encoding_read_struct_begin(HPAbstractReader *self, const char *struct_name);

HP_API hpint32 ddekit_json_encoding_read_struct_end(HPAbstractReader *self, const char *struct_name);

HP_API hpint32 ddekit_json_encoding_read_vector_begin(HPAbstractReader *self, const char *var_name, hpint32 var_type, hpint32 end_with_zero);

HP_API hpint32 ddekit_json_encoding_read_vector_end(HPAbstractReader *self, const char *var_name, hpint32 var_type, hpint32 end_with_zero);

HP_API hpint32 ddekit_json_encoding_read_field_begin(HPAbstractReader *self, const char *var_name, hpint32 var_type);

HP_API hpint32 ddekit_json_encoding_read_field_end(HPAbstractReader *self, const char *var_name, hpint32 var_type);

HP_API hpint32 ddekit_json_encoding_read_enum(HPAbstractReader *super, hpint32 *val);

HP_API hpint32 ddekit_json_encoding_read_enum_name(HPAbstractReader *super, hpchar *enum_name, hpuint32 *enum_name_length);

HP_API hpint32 ddekit_json_encoding_read_hpchar(HPAbstractReader *super, char *val);

HP_API hpint32 ddekit_json_encoding_read_hpdouble(HPAbstractReader *super, double *val);

HP_API hpint32 ddekit_json_encoding_read_hpint8(HPAbstractReader *super, hpint8 *val);

HP_API hpint32 ddekit_json_encoding_read_hpint16(HPAbstractReader *super, hpint16 *val);

HP_API hpint32 ddekit_json_encoding_read_hpint32(HPAbstractReader *super, hpint32 *val);

HP_API hpint32 ddekit_json_encoding_read_hpint64(HPAbstractReader *super, hpint64 *val);

HP_API hpint32 ddekit_json_encoding_read_hpuint8(HPAbstractReader *super, hpuint8 *val);

HP_API hpint32 ddekit_json_encoding_read_hpuint16(HPAbstractReader *super, hpuint16 *val);

HP_API hpint32 ddekit_json_encoding_read_hpuint32(HPAbstractReader *super, hpuint32 *val);

HP_API hpint32 ddekit_json_encoding_read_hpuint64(HPAbstractReader *super, hpuint64 *val);

#endif//_H_DDEKIT_JSON_ENCODING_READER