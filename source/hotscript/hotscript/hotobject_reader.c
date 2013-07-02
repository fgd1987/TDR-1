#include "hotscript/hotobject_reader.h"

#include "hotpot/hp_error.h"




static const HotObject *hotobject_get(HotObjectReader *self)
{
	return self->stack[self->stack_num - 1].ho;
}

static hpint32 hotobject_push(HotObjectReader *self, const HotObject *ho)
{
	self->stack[self->stack_num].ho = ho;
	++(self->stack_num);

	return E_HP_NOERROR;
}

hpint32 hotobject_read_struct_begin(HPAbstractReader *super, const char *struct_name)
{
	HotObjectReader* self = HP_CONTAINER_OF(super, HotObjectReader, super);
	const HotObject *ob = hotobject_get(self);

	return E_HP_NOERROR;
}

hpint32 hotobject_read_struct_end(HPAbstractReader *super, const char *struct_name)
{
	return E_HP_NOERROR;
}

hpint32 hotobject_read_field_begin(HPAbstractReader *super, const char *var_name, hpint32 var_type)
{
	HotObjectReader* self = HP_CONTAINER_OF(super, HotObjectReader, super);
	const HotObject *ob = hotobject_get(self);
	const HotObject *new_ob;
	hpint32 ret;


	ret = trie_retrieve(ob->keys, var_name, &new_ob);
	if(!ret)
	{
		goto ERROR_RET;
	}
	hotobject_push(self, new_ob);

	return E_HP_NOERROR;
ERROR_RET:
	return E_HP_ERROR;
}

hpint32 hotobject_read_field_end(HPAbstractReader *super, const char *var_name, hpint32 var_type)
{
	HotObjectReader* self = HP_CONTAINER_OF(super, HotObjectReader, super);
	--(self->stack_num);

	return E_HP_NOERROR;
}


hpint32 hotobject_read_vector_begin(HPAbstractReader *super, const char *var_name, hpint32 var_type, hpint32 end_with_zero)
{
	HotObjectReader* self = HP_CONTAINER_OF(super, HotObjectReader, super);
	const HotObject *ob = hotobject_get(self);
	self->stack[self->stack_num - 1].current_index = 0;

	return E_HP_NOERROR;
}

hpint32 hotobject_read_vector_end(HPAbstractReader *super, const char *var_name, hpint32 var_type, hpint32 end_with_zero)
{
	HotObjectReader* self = HP_CONTAINER_OF(super, HotObjectReader, super);

	return E_HP_NOERROR;
}

static const HotObject* get_current_ob(HotObjectReader *self)
{
	const HotObject *ob = hotobject_get(self);
	//�����±���һ��λ��
	if(ob->type ==  E_ARRAY)
	{
		HotObject *new_ob;
		char str[1024];
		hpuint32 str_len = 0;
		hpint32 count = self->stack[self->stack_num - 1].current_index;
		while(count > 0)
		{
			str[str_len++] = count % 10;
			count/=10;
		}
		str[str_len++] = TRIE_CHAR_TERM;


		if(!trie_retrieve(ob->keys, str, &new_ob))
		{
			//free ob~~
			goto ERROR_RET;
		}
		return new_ob;
	}
	//���������������
	else if(ob->type == E_UNKNOW)
	{
		return ob;
	}

ERROR_RET:
	return NULL;
}
hpint32 read_hpint8(HPAbstractReader *super, hpint8 *val)
{
	HotObjectReader* self = HP_CONTAINER_OF(super, HotObjectReader, super);
	const HotObject *ob = get_current_ob(self);
	*val = ob->var.val.i8;
	++self->stack[self->stack_num - 1].current_index;

	return E_HP_NOERROR;
}


hpint32 hotobject_reader_init(HotObjectReader* self, const HotObject *hotobject)
{
	self->stack_num = 0;
	self->stack[self->stack_num].ho = hotobject;
	++(self->stack_num);

	self->super.read_struct_begin = hotobject_read_struct_begin;
	self->super.read_struct_end = hotobject_read_struct_end;
	self->super.read_vector_begin = hotobject_read_vector_begin;
	self->super.read_vector_end = hotobject_read_vector_end;
	self->super.read_field_begin = hotobject_read_field_begin;
	self->super.read_field_end = hotobject_read_field_end;
	self->super.read_hpint8 = read_hpint8;

	return E_HP_NOERROR;
}