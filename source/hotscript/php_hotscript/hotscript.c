/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_hotscript.h"
#include "main/php_output.h"

#ifdef ZTS
#include "TSRM.h"
#endif

#include "ext/standard/php_smart_str.h"

/* If you declare any globals in php_hotscript.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(hotscript)
*/

/* True global resources - no need for thread safety here */
static int le_hotscript;

/* {{{ hotscript_functions[]
 *
 * Every user visible function must have an entry in hotscript_functions[].
 */
const zend_function_entry hotscript_functions[] = {
	PHP_FE(confirm_hotscript_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(myhello,	NULL)
	PHP_FE_END	/* Must be the last line in hotscript_functions[] */
};
/* }}} */

/* {{{ hotscript_module_entry
 */
zend_module_entry hotscript_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"hotscript",
	hotscript_functions,
	PHP_MINIT(hotscript),
	PHP_MSHUTDOWN(hotscript),
	PHP_RINIT(hotscript),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(hotscript),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(hotscript),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_HOTSCRIPT
ZEND_GET_MODULE(hotscript)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("hotscript.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_hotscript_globals, hotscript_globals)
    STD_PHP_INI_ENTRY("hotscript.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_hotscript_globals, hotscript_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_hotscript_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_hotscript_init_globals(zend_hotscript_globals *hotscript_globals)
{
	hotscript_globals->global_value = 0;
	hotscript_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(hotscript)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(hotscript)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(hotscript)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(hotscript)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(hotscript)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "hotscript support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_hotscript_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_hotscript_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "hotscript", arg);
	RETURN_STRINGL(strg, len, 0);
}

void echo(smart_str *buf, zval *val TSRMLS_DC)
{
	HashTable *myht;

	if (Z_TYPE_P(val) == IS_ARRAY) {
		myht = HASH_OF(val);
	} else {
		myht = Z_OBJPROP_P(val);
	}

	switch (Z_TYPE_P(val))
	{
	case IS_NULL:
		smart_str_appendl(buf, "null", 4);
		break;

	case IS_BOOL:
		if (Z_BVAL_P(val)) {
			smart_str_appendl(buf, "true", 4);
		} else {
			smart_str_appendl(buf, "false", 5);
		}
		break;

	case IS_LONG:
		smart_str_append_long(buf, Z_LVAL_P(val));
		break;

	case IS_DOUBLE:
		{
			char *d = NULL;
			int len;
			double dbl = Z_DVAL_P(val);

			if (!zend_isinf(dbl) && !zend_isnan(dbl)) {
				len = spprintf(&d, 0, "%.*k", (int) EG(precision), dbl);
				smart_str_appendl(buf, d, len);
				efree(d);
			} else {
//				JSON_G(error_code) = PHP_JSON_ERROR_INF_OR_NAN;
				smart_str_appendc(buf, '0');
			}
		}
		break;

	case IS_STRING:
		//json_escape_string(buf, Z_STRVAL_P(val), Z_STRLEN_P(val), options TSRMLS_CC);
		break;

	case IS_OBJECT:
		/*
		if (instanceof_function(Z_OBJCE_P(val), php_json_serializable_ce TSRMLS_CC)) {
			json_encode_serializable_object(buf, val, options TSRMLS_CC);
			break;
		}
		/* fallthrough -- Non-serializable object */
	case IS_ARRAY:
//		json_encode_array(buf, &val, options TSRMLS_CC);
		break;

	default:
//		JSON_G(error_code) = PHP_JSON_ERROR_UNSUPPORTED_TYPE;
		smart_str_appendl(buf, "null", 4);
		break;
	}

	return;
}

PHP_FUNCTION(myhello)
{
	zval *parameter;
	smart_str buf = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|ll", &parameter) == FAILURE)
	{
		return;
	}

	echo(&buf, parameter TSRMLS_CC);

	ZVAL_STRINGL(return_value, buf.c, buf.len, 1);

	smart_str_free(&buf);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
