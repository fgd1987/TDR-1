#include "xml_parser.h"
#include "xml_y.h"
#include "xml_l.h"
#include "hotpot/hp_error.h"

#include "hotscript/hotscript_trie.h"


HOTSCRIPT_TRIE hs_t;

void debug_print_tab(hpuint32 n)
{
	hpuint32 i;
	for(i = 0;i < n;++i)
	{
		printf("\t");
	}
}
void debug_print(const XML_TREE *tree, hpint32 index, hpuint32 level)
{
	hpuint32 i;
	debug_print_tab(level);
	printf("%s\n", tree->element_list[index].name);
	if(tree->element_list[index].first_child_index != -1)
	{
		debug_print_tab(level);
		printf("{\n");

		for(i = tree->element_list[index].first_child_index; i != -1; i = tree->element_list[i].next_sibling_index)
		{
			debug_print(tree, i, level + 1);
		}
		debug_print_tab(level);
		printf("}\n");
	}
}

void dfs(const XML_TREE *tree, hpint32 index)
{
	hpuint32 i;
	hotscript_trie_write_struct_begin(&hs_t, tree->element_list[index].name);
	if(tree->element_list[index].first_child_index != -1)
	{
		for(i = tree->element_list[index].first_child_index; i != -1; i = tree->element_list[i].next_sibling_index)
			if(tree->element_list[i].first_child_index == HOTSCRIPT_TRIE_INVALID_INDEX)
			{
				hotscript_trie_write_var_begin(&hs_t, tree->element_list[i].name, 0);
				hotscript_trie_write_string(&hs_t, tree->element_list[i].name, tree->element_list[i].text);
				hotscript_trie_write_var_end(&hs_t, tree->element_list[i].name, 0);
			}
			else
			{
				hotscript_trie_write_var_begin(&hs_t, tree->element_list[i].name, 0);
				dfs(tree, i);
				hotscript_trie_write_var_end(&hs_t, tree->element_list[i].name, 0);
			}
	}
	hotscript_trie_write_struct_end(&hs_t, tree->element_list[index].name);
}

hpint32 xml_parser(XML_PARSER *self, const char* file_name)
{
	hpint32 ret;
	hpint64 data;

	
	self->result = HP_INVALID_ERROR_CODE;
	self->tree.element_list_num = 0;
	self->xml_stack_num = 0;
	self->xml_stack[0].first_element_index = -1;
	self->xml_stack[0].last_element_index = -1;
	
	yyxmllex_init_extra(&self->scanner, &self->scanner);

	xml_open_file(&self->scanner, file_name);

	ret = yyxmlparse(&self->scanner);
	if(ret == 0)
	{
		self->result = E_HP_NOERROR;
	}

	hotscript_trie_init(&hs_t, HP_OFFSET_OF(HOTSCRIPT_TRIE, xml_tree), "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789[].");
	debug_print(&self->tree, self->tree.element_list_num - 1, 0);

	return self->result;
	dfs(&self->tree, self->tree.element_list_num - 1);

	debug_print(&hs_t.xml_tree, 0, 0);

	ret = hotscript_trie_search(&hs_t, "level3[0].next_package[1].B[0]", &data);
	printf("%lld : %s = %s\n", data, hs_t.xml_tree.element_list[data].name, hs_t.xml_tree.element_list[data].text);

	
	return self->result;
}

hpint32 xml_open_file(yyscan_t *super, const char *file_name)
{
	XML_PARSER *self = HP_CONTAINER_OF(super, XML_PARSER, scanner);

	self->stack[self->stack_num].f = fopen(file_name, "r");
	if(self->stack[self->stack_num].f == NULL)
	{
		goto ERROR_RET;
	}
	self->stack[self->stack_num].bs = yyxml_create_buffer(self->stack[self->stack_num].f, YY_BUF_SIZE, self->scanner);
	if(self->stack[self->stack_num].bs == NULL)
	{
		goto ERROR_RET;
	}
	self->stack[self->stack_num].bs->yy_bs_column = 1;
	++self->stack_num;
	yyxml_switch_to_buffer(self->stack[self->stack_num - 1].bs, self->scanner);

	return E_HP_NOERROR;
ERROR_RET:
	return E_HP_ERROR;
}

hpint32 xml_close_file(yyscan_t *super)
{
	XML_PARSER *self = HP_CONTAINER_OF(super, XML_PARSER, scanner);

	fclose(self->stack[self->stack_num - 1].f);
	yyxml_delete_buffer(self->stack[self->stack_num - 1].bs, self->scanner);

	--self->stack_num;
	if(self->stack_num <= 0)
	{
		goto ERROR_RET;
	}
	yyxml_switch_to_buffer(self->stack[self->stack_num - 1].bs, self->scanner);
	return E_HP_NOERROR;
ERROR_RET:
	return E_HP_ERROR;
}