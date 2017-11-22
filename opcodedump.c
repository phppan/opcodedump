/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
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
#include "php_opcodedump.h"

void dasm_zend_op_array(zval *dst, const zend_op_array *src );

/* If you declare any globals in php_opcodedump.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(opcodedump)
*/

/* True global resources - no need for thread safety here */
static int le_opcodedump;



/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("opcodedump.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_opcodedump_globals, opcodedump_globals)
    STD_PHP_INI_ENTRY("opcodedump.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_opcodedump_globals, opcodedump_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */


void dasm_zend_arg_info(zval * dst, const zend_arg_info *src )
{


	if (src->name == NULL) {
		add_assoc_null(dst, "name");
		add_assoc_long(dst, "name_len", 0);
	} else {
		add_assoc_string(dst, "name", ZSTR_VAL(src->name));
		add_assoc_long(dst, "name_len", ZSTR_LEN(src->name));
	}


	if (src->class_name == NULL) {
		add_assoc_null(dst, ("class_name"));
		add_assoc_long(dst, ("class_name_len"), 0);
	} else {
		add_assoc_string(dst, ("class_name"), ZSTR_VAL(src->class_name));
		add_assoc_long(dst, ("class_name_len"), ZSTR_LEN(src->class_name));
	}

	add_assoc_long_ex(dst, ("type_hint"), (sizeof("type_hint")), src->type_hint);
	add_assoc_bool_ex(dst, ("pass_by_reference"), (sizeof("pass_by_reference")), src->pass_by_reference ? 1 : 0);
	add_assoc_bool_ex(dst, ("allow_null"), (sizeof("allow_null")), src->allow_null ? 1 : 0);
	add_assoc_bool_ex(dst, ("is_variadic"), (sizeof("is_variadic")), src->is_variadic ? 1 : 0);
}

void dasm_zend_uint_array(zval *dst, const uint32_t *src ) 	
{
	int len = sizeof(src)/sizeof(uint32_t);

	if (len > 0) {
		int i;

		for (i = 0; i < len; i++ ) {
			add_next_index_long(dst, src[i]);
		}
	}

}

	
static void inline dasm_zend_op(zval *dst, const zend_op  *src ) 	
{
	add_assoc_long_ex(dst, ("opcode"), (sizeof("opcode")), src->opcode);
	add_assoc_long_ex(dst, ("op1_type"), (sizeof("op1_type")), src->op1_type);
	add_assoc_long_ex(dst, ("op2_type"), (sizeof("op2_type")), src->op2_type);
	add_assoc_long_ex(dst, ("result_type"), (sizeof("result_type")), src->result_type);
	add_assoc_long_ex(dst, ("extended_value"), (sizeof("extended_value")), src->extended_value);
	add_assoc_long_ex(dst, ("lineno"), (sizeof("lineno")), src->lineno);
		

	add_assoc_long_ex(dst, ("result.constant"), (sizeof("result.constant")), src->result.constant);
	add_assoc_long_ex(dst, ("result.var"), (sizeof("result.var")), src->result.var);
	add_assoc_long_ex(dst, ("result.num"), (sizeof("result.num")), src->result.num);
	add_assoc_long_ex(dst, ("result.opline_num"), (sizeof("result.opline_num")), src->result.opline_num);


	add_assoc_long_ex(dst, ("op1.constant"), (sizeof("op1.constant")), src->op1.constant);
	add_assoc_long_ex(dst, ("op1.var"), (sizeof("op1.var")), src->op1.var);
	add_assoc_long_ex(dst, ("op1.num"), (sizeof("op1.num")), src->op1.num);
	add_assoc_long_ex(dst, ("op1.opline_num"), (sizeof("op1.opline_num")), src->op1.opline_num);



	add_assoc_long_ex(dst, ("op2.constant"), (sizeof("op2.constant")), src->op2.constant);
	add_assoc_long_ex(dst, ("op2.var"), (sizeof("op2.var")), src->op2.var);
	add_assoc_long_ex(dst, ("op2.num"), (sizeof("op2.num")), src->op2.num);
	add_assoc_long_ex(dst, ("op2.opline_num"), (sizeof("op2.opline_num")), src->op2.opline_num);

}


#if defined(ZEND_ENGINE_7_0)
static void inline dasm_zend_brk_cont_element(zval *dst, const zend_brk_cont_element * src) 	
{
	add_assoc_long_ex(dst, ("start"), (sizeof("start")), src->start);
	add_assoc_long_ex(dst, ("cont"), (sizeof("cont")), src->cont);
	add_assoc_long_ex(dst, ("brk"), (sizeof("brk")), src->brk);
	add_assoc_long_ex(dst, ("parent"), (sizeof("parent")), src->parent);
}
#endif

#if defined(ZEND_ENGINE_7_1)
static void inline dasm_zend_live_range(zval *dst, const zend_live_range *src )
{
	add_assoc_long_ex(dst, ("var"), (sizeof("var")), src->var);
	add_assoc_long_ex(dst, ("start"), (sizeof("start")), src->start);
	add_assoc_long_ex(dst, ("end"), (sizeof("end")), src->end);
}
#endif

	
static void inline dasm_zend_try_catch_element(zval *dst, const zend_try_catch_element *src) 	
{
	add_assoc_long_ex(dst, ("try_op"), (sizeof("try_op")), src->try_op);
	add_assoc_long_ex(dst, ("catch_op"), (sizeof("catch_op")), src->catch_op);
	add_assoc_long_ex(dst, ("finally_op"), (sizeof("finally_op")), src->finally_op);
	add_assoc_long_ex(dst, ("finally_end"), (sizeof("finally_end")), src->finally_end);
}




static void inline dasm_HashTable(zval *dst, HashTable *src) 	
{
	ulong num_key;
	zend_string *key;
	zval *val;


	ZEND_HASH_FOREACH_KEY_VAL(src, num_key, key, val) {
		zval zv;
		array_init(&zv);
		ZVAL_COPY_VALUE(&zv, val);
		add_next_index_zval(dst, &zv);
	}ZEND_HASH_FOREACH_END();
}
/* }}} */


static void inline dasm_function_table(zval *dst, const HashTable *src) 	
{
	zend_function *zif;

	ZEND_HASH_FOREACH_PTR(src, zif) {
		if (zif->common.type == ZEND_USER_FUNCTION) {
			zval zv;
			zend_op_array *op_array;
			array_init(&zv);
			add_assoc_long(&zv, "type", zif->type);
			op_array = &(zif->op_array);
			dasm_zend_op_array(&zv, op_array);

			zval array;
			array_init(&array);
			add_assoc_zval(&array, "op_array", &zv);
			add_assoc_zval(dst, ZSTR_VAL(zif->common.function_name), &array);
			// add_next_index_zval(dst, &zv);
		}

	} ZEND_HASH_FOREACH_END();

}
/* }}} */


static void inline _dasm_properties_info(zval *dst, const zend_property_info  *src ) 	
{
	if (src->name == NULL) {
		add_assoc_null(dst, "name");
		add_assoc_long(dst, "name_len", 0);
	} else {
		add_assoc_string(dst, "name", ZSTR_VAL(src->name));
		add_assoc_long(dst, "name_len", ZSTR_LEN(src->name));
	}


	if (src->doc_comment == NULL) {
		add_assoc_null(dst, "doc_comment");
		add_assoc_long(dst, "doc_comment_len", 0);
	} else {
		add_assoc_string(dst, "doc_comment", ZSTR_VAL(src->doc_comment));
		add_assoc_long(dst, "doc_comment_len", ZSTR_LEN(src->doc_comment));
	}

	add_assoc_long(dst, "offset", src->offset);
	add_assoc_long(dst, "flags", src->flags);

	if (src->ce->name == NULL) {
		add_assoc_null(dst, "ce");
	} else {
		add_assoc_string(dst, "ce", ZSTR_VAL(src->ce->name));
	}

	/*
	uint32_t offset; 
	uint32_t flags;
	zend_string *name;
	zend_string *doc_comment;
	zend_class_entry *ce;
	*/
}


/* {{{ add_class_vars */
static void inline dasm_properties_info(zval *dst, zend_class_entry *ce, int statics)
{
	zend_property_info *prop_info;
	zval *prop, prop_copy;
	zend_string *key;

	ZEND_HASH_FOREACH_STR_KEY_PTR(&ce->properties_info, key, prop_info) {
		if (((prop_info->flags & ZEND_ACC_SHADOW) &&
		     prop_info->ce != ce) ||
		    ((prop_info->flags & ZEND_ACC_PROTECTED) &&
		     !zend_check_protected(prop_info->ce, ce)) ||
		    ((prop_info->flags & ZEND_ACC_PRIVATE) &&
		     prop_info->ce != ce)) {
			continue;
		}
		prop = NULL;
		if (statics && (prop_info->flags & ZEND_ACC_STATIC) != 0) {
			prop = &ce->default_static_members_table[prop_info->offset];
		} else if (!statics && (prop_info->flags & ZEND_ACC_STATIC) == 0) {
			prop = &ce->default_properties_table[OBJ_PROP_TO_NUM(prop_info->offset)];
		}
		if (!prop) {
			continue;
		}


		zval zv;
		array_init(&zv);
		
		_dasm_properties_info(&zv, prop_info);
		add_assoc_zval(dst, ZSTR_VAL(prop_info->name), &zv);
	} ZEND_HASH_FOREACH_END();
	
}
/* }}} */


static void inline dasm_zend_class_entry(zval *dst,  zend_class_entry *src) 	
{

	add_assoc_long_ex(dst, ("type"), (sizeof("type")), src->type);
	if (src->name == NULL) {
		add_assoc_null(dst, "name");
		add_assoc_long(dst, "name_len", 0);
	} else {
		add_assoc_string(dst, "name", ZSTR_VAL(src->name));
		add_assoc_long(dst, "name_len", ZSTR_LEN(src->name));
	}


	if (src->parent) {
		add_assoc_string(dst, "parent", ZSTR_VAL(src->parent->name));
	} else {
		add_assoc_null_ex(dst, ("parent"), (sizeof("parent")));
		assert(src->parent == NULL);
	}

	add_assoc_long_ex(dst, ("refcount"), (sizeof("refcount")), src->refcount);
	add_assoc_long_ex(dst, ("ce_flags"), (sizeof("ce_flags")), src->ce_flags);
	add_assoc_long_ex(dst, ("default_properties_count"), (sizeof("default_properties_count")), src->default_properties_count);

	add_assoc_long_ex(dst, ("default_static_members_count"), (sizeof("default_static_members_count")), src->default_static_members_count);

	if (src->default_properties_table) {
		zval table;
		array_init(&table);
		for (int i= 0; i < src->default_properties_count; i++) {
			zval zv;
			ZVAL_COPY_VALUE(&zv, src->default_properties_table + i);
			add_next_index_zval(&table, &zv);
		}
		add_assoc_zval(dst, "default_properties_table", &table);
	}else{
		add_assoc_null_ex(dst, ("default_properties_table"), (sizeof("default_properties_table")));
	}

	if (src->default_static_members_table) {
		zval table;
		array_init(&table);
		for (int i= 0; i < src->default_static_members_count; i++) {
			zval zv;
			ZVAL_COPY_VALUE(&zv, src->default_static_members_table + i);
			add_next_index_zval(&table, &zv);
		}
		add_assoc_zval(dst, "default_static_members_table", &table);
	}else{
		add_assoc_null_ex(dst, ("default_static_members_table"), (sizeof("default_static_members_table")));
	}

	do {
		zval zv;
		array_init(&zv);
		dasm_function_table(&zv, &src->function_table);
		add_assoc_zval(dst, "function_table", &zv);
	} while(0);

	do {
		zval zv;
		array_init(&zv);
		dasm_properties_info(&zv, src, 0);
		dasm_properties_info(&zv, src, 1);
		add_assoc_zval(dst, "properties_info", &zv);
	} while(0);

	
	/*

struct _zend_class_entry {
	char type;
	zend_string *name;
	struct _zend_class_entry *parent;
	int refcount;
	uint32_t ce_flags;

	int default_properties_count;
	int default_static_members_count;
	zval *default_properties_table;
	zval *default_static_members_table;
	zval *static_members_table;
	HashTable function_table;
	HashTable properties_info;
	HashTable constants_table;

	union _zend_function *constructor;
	union _zend_function *destructor;
	union _zend_function *clone;
	union _zend_function *__get;
	union _zend_function *__set;
	union _zend_function *__unset;
	union _zend_function *__isset;
	union _zend_function *__call;
	union _zend_function *__callstatic;
	union _zend_function *__tostring;
	union _zend_function *__debugInfo;
	union _zend_function *serialize_func;
	union _zend_function *unserialize_func;

	zend_class_iterator_funcs iterator_funcs;

	zend_object* (*create_object)(zend_class_entry *class_type);
	zend_object_iterator *(*get_iterator)(zend_class_entry *ce, zval *object, int by_ref);
	int (*interface_gets_implemented)(zend_class_entry *iface, zend_class_entry *class_type);
	union _zend_function *(*get_static_method)(zend_class_entry *ce, zend_string* method);

	int (*serialize)(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data);
	int (*unserialize)(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data);

	uint32_t num_interfaces;
	uint32_t num_traits;
	zend_class_entry **interfaces;

	zend_class_entry **traits;
	zend_trait_alias **trait_aliases;
	zend_trait_precedence **trait_precedences;

	union {
		struct {
			zend_string *filename;
			uint32_t line_start;
			uint32_t line_end;
			zend_string *doc_comment;
		} user;
		struct {
			const struct _zend_function_entry *builtin_functions;
			struct _zend_module_entry *module;
		} internal;
	} info;
};
*/

}
/* }}} */

static void inline dasm_class_table(zval *dst, const HashTable *src) 	
{

	zend_class_entry *ce;

	ZEND_HASH_FOREACH_PTR(src, ce) {
		if (ce->type == ZEND_USER_CLASS) {
		    zval zv;
			array_init(&zv);
			dasm_zend_class_entry(&zv, ce);
			add_assoc_zval(dst, ZSTR_VAL(ce->name), &zv);
			// add_next_index_zval(dst, &zv);
		}
	} ZEND_HASH_FOREACH_END();
}
/* }}} */



// static void inline dasm_function_table() 
// {
// 	return TG(internal_function_tail) ? TG(internal_function_tail)->pListNext : TG(function_table).pListHead;
// }


void dasm_zend_op_array(zval *dst, const zend_op_array *src ) 	
{
	

	assert(sizeof(zend_uchar) == sizeof(src->type));
	
	add_assoc_long_ex(dst, ("type"), (sizeof("type")), src->type);
		
	/* PROC_ZSTRING(,function_name) */
 
	/* PROC_ZSTRING_N(,function_name,,strlen) */

	
	if (src->function_name == NULL) {
		add_assoc_null(dst,  "function_name");
	} else {
		add_assoc_string(dst, "function_name", ZSTR_VAL(src->function_name));
	}

	add_assoc_long_ex(dst, ("fn_flags"), (sizeof("fn_flags")), src->fn_flags);

	if (src->arg_info) {
		int i;
		
		zval arr;
		array_init(&arr);

		for (i = 0; i < src->num_args; ++i) {
			zval zv;

			array_init(&zv);
			dasm_zend_arg_info (&zv, &(src->arg_info[i]));
			add_next_index_zval(&arr, &zv);
		}
		add_assoc_zval(dst, "arg_info", &arr);
	}else{
		add_assoc_null(dst, ("arg_info"));
	}

	
	add_assoc_long_ex(dst, ("num_args"), (sizeof("num_args")), src->num_args);
	add_assoc_long_ex(dst, ("required_num_args"), (sizeof("required_num_args")), src->required_num_args);

	if (src->refcount) {	
		do {
			zval zv;
			array_init(&zv);
			dasm_zend_uint_array(&zv, src->refcount);
			add_assoc_zval_ex(dst, ("refcount"), (sizeof("refcount")), &zv);
		} while (0);
	} else {
		add_assoc_null_ex(dst, ("refcount"), (sizeof("refcount")));
		assert(src->refcount == NULL);
	}


	if (src->literals) {
		int i; 
		zval arr;
		array_init(&arr);

		for (i = 0; i < src->last_literal; ++i) {
			zval zv;
			array_init(&zv);
			ZVAL_COPY_VALUE(&zv, &(src->literals[i]));
			add_next_index_zval(&arr, &zv);
		}
		add_assoc_zval_ex(dst, ("literals"), (sizeof("literals")), &arr);
	}else{
		add_assoc_null_ex(dst, ("literals"), (sizeof("literals")));
	}

	add_assoc_long_ex(dst, ("last_literal"), (sizeof("last_literal")), src->last_literal);

	if (src->opcodes) {
		int i; 
		zval arr;
		array_init(&arr);

		for (i = 0; i < src->last; ++i) {
			zval zv;
			array_init(&zv);
			dasm_zend_op (&zv, &(src->opcodes[i]));
			add_next_index_zval(&arr, &zv);
		}
		add_assoc_zval_ex(dst, ("opcodes"), (sizeof("opcodes")), &arr);
	} else {
		add_assoc_null_ex(dst, ("opcodes"), (sizeof("opcodes")));

		assert(src->opcodes == NULL);
	}	


	add_assoc_long_ex(dst, ("last"), (sizeof("last")), src->last);
	add_assoc_long_ex(dst, ("T"), (sizeof("T")), src->T);


#if defined(ZEND_ENGINE_7_0)
	if (src->brk_cont_array) {
		int i; 
		zval arr;
		array_init(&arr);

		for (i = 0; i < src->last_brk_cont; ++i) {
			zval zv;
			array_init(&zv);
			dasm_zend_brk_cont_element(&zv, &(src->brk_cont_array[i]));
			add_next_index_zval(&arr, &zv);
		}
		add_assoc_zval_ex(dst, ("brk_cont_array"), (sizeof("brk_cont_array")), &arr);
	} else {
		add_assoc_null_ex(dst, ("brk_cont_array"), (sizeof("brk_cont_array")));
		assert(src->brk_cont_array == NULL);
	}

	add_assoc_long_ex(dst, ("last_brk_cont"), (sizeof("last_brk_cont")), src->last_brk_cont);

#endif

#if defined(ZEND_ENGINE_7_1)
	if (src->live_range) {
		int i; 
		zval arr;
		array_init(&arr);

		for (i = 0; i < src->last_live_range; ++i) {
			zval zv;
			array_init(&zv);
			dasm_zend_live_range(&zv, &(src->live_range[i]));
			add_next_index_zval(&arr, &zv);
		}
		add_assoc_zval_ex(dst, ("live_range"), (sizeof("live_range")), &arr);
	} else {
		add_assoc_null_ex(dst, ("live_range"), (sizeof("live_range")));
		assert(src->live_range == NULL);
	}

	add_assoc_long_ex(dst, ("last_live_range"), (sizeof("last_live_range")), src->last_live_range);
#endif
	
	if (src->try_catch_array) {
		int i; 
		
		zval arr;
		array_init(&arr);

		for (i = 0; i < src->last_try_catch; ++i) {
			zval zv;
			array_init(&zv);
			dasm_zend_try_catch_element (&zv, &(src->try_catch_array[i]));
			add_next_index_zval(&arr, &zv);
		}
		add_assoc_zval_ex(dst, ("try_catch_array"), (sizeof("try_catch_array")), &arr);
	} else {
		add_assoc_null_ex(dst, ("try_catch_array"), (sizeof("try_catch_array")));
		assert(src->try_catch_array == NULL);
	}

	assert(sizeof(int) == sizeof(src->last_try_catch));
	add_assoc_long_ex(dst, ("last_try_catch"), (sizeof("last_try_catch")), src->last_try_catch);


	if (src->static_variables && sizeof(HashTable) == sizeof(( src->static_variables)[0])) {
		
		do {
			zval zv;
			array_init(&zv);
			dasm_HashTable(&zv, src->static_variables );
			add_assoc_zval_ex(dst, ("static_variables"), (sizeof("static_variables")), &zv);
		} while (0);

	} else {
		add_assoc_null_ex(dst, ("static_variables"), (sizeof("static_variables")));
		assert(src->static_variables == NULL);
	}


#if defined(ZEND_ENGINE_7_0)
	add_assoc_long_ex(dst, ("this_var"), (sizeof("this_var")), src->this_var);
#endif

	if (src->filename == NULL) {
		add_assoc_null(dst,  "filename");
	} else {
		add_assoc_string(dst, "filename", ZSTR_VAL(src->filename));
	}


	if (src->doc_comment == NULL) {
		add_assoc_null(dst,  "doc_comment");
		add_assoc_long(dst, "doc_comment_len", 0);
	} else {
		add_assoc_string(dst, "doc_comment", ZSTR_VAL(src->doc_comment));
		add_assoc_long(dst, "doc_comment_len", ZSTR_LEN(src->doc_comment));
	}
	

	add_assoc_long_ex(dst, ("line_start"), (sizeof("line_start")), src->line_start);
	add_assoc_long_ex(dst, ("line_end"), (sizeof("line_end")), src->line_end);
	add_assoc_long_ex(dst, ("early_binding"), (sizeof("early_binding")), src->early_binding);
	add_assoc_long_ex(dst, ("cache_size"), (sizeof("cache_size")), src->cache_size);

	if (src->vars) {
		int	i;
		zval arr;
		array_init(&arr);

		for (i = 0; i < src->last_var; ++i) {
			add_next_index_string(&arr, ZSTR_VAL(src->vars[i]));
		}
		add_assoc_zval_ex(dst, ("vars"), (sizeof("vars")), &arr);
	}
	else {
		add_assoc_null_ex(dst, ("vars"), (sizeof("vars")));
		assert(src->vars == NULL);
	}

	add_assoc_long_ex(dst, ("last_var"), (sizeof("last_var")), src->last_var);


	if (src->prototype) {
		zval zv;
		zend_op_array *op_array;
		array_init(&zv);
		add_assoc_long(&zv, "type", src->prototype->type);
		op_array = &(src->prototype->op_array);
		dasm_zend_op_array(&zv, op_array);

		add_assoc_zval_ex(dst, ("prototype"), (sizeof("prototype")), &zv);
	} else {
		add_assoc_null_ex(dst, ("prototype"), (sizeof("prototype")));
		assert(src->prototype == NULL);
	}

	if (src->scope) {
		add_assoc_string(dst, "scope", ZSTR_VAL(src->scope->name));
	} else {
		add_assoc_null_ex(dst, ("scope"), (sizeof("scope")));
		assert(src->scope == NULL);
	}



/*
	zend_uchar arg_flags[3];
	zend_string *function_name;
	zend_class_entry *scope;
	zend_function *prototype;
	uint32_t num_args;
	uint32_t required_num_args;
	zend_arg_info *arg_info;

	uint32_t *refcount;

	uint32_t this_var;

	uint32_t last;
	zend_op *opcodes;

	int last_var;
	uint32_t T;
	zend_string **vars;

	int last_brk_cont;
	int last_try_catch;
	zend_brk_cont_element *brk_cont_array;
	zend_try_catch_element *try_catch_array;

	HashTable *static_variables;

	zend_string *filename;
	uint32_t line_start;
	uint32_t line_end;
	zend_string *doc_comment;
	uint32_t early_binding; 

	int last_literal;
	zval *literals;

	int  cache_size;
	void **run_time_cache;
	*/

}


/* {{{ proto array xcache_dasm_file(string filename)
   Disassemble file into opcode array by filename */
#ifdef ZEND_BEGIN_ARG_INFO_EX
ZEND_BEGIN_ARG_INFO_EX(arginfo_dasm_file, 0, 0, 1)
	ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()
#else
static unsigned char arginfo_dasm_file[] = { 1, BYREF_NONE };
#endif

PHP_FUNCTION(dasm_file)
{
	char *filename;
	size_t filename_len;

	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &filename, &filename_len) == FAILURE) {
		return;
	}
	if (!filename_len) RETVAL_FALSE;

	zend_op_array *op_array = NULL;

	zval zfilename;

	ZVAL_STRINGL(&zfilename, filename, filename_len);

	op_array = compile_filename(ZEND_REQUIRE, &zfilename);


	zval zv;
	array_init(&zv);

	dasm_zend_op_array(&zv, op_array);


 	array_init(return_value);
    add_assoc_zval_ex(return_value, ZEND_STRS("op_array"), &zv);

    zval function_table;
    array_init(&function_table);

    if (CG(function_table)) {
		do {
			zval zv;
			array_init(&zv);
			dasm_function_table(&zv, CG(function_table));
			add_assoc_zval_ex(return_value, ("function_table"), (sizeof("function_table")), &zv);
		} while (0);

	} else {
		add_assoc_null_ex(return_value, ("function_table"), (sizeof("function_table")));
	}

	  if (CG(class_table)) {
		do {
			zval zv;
			array_init(&zv);
			dasm_class_table(&zv, CG(class_table));
			add_assoc_zval_ex(return_value, ("class_table"), (sizeof("class_table")), &zv);
		} while (0);

	} else {
		add_assoc_null_ex(return_value, ("class_table"), (sizeof("class_table")));
	}
}


/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_opcodedump_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_opcodedump_init_globals(zend_opcodedump_globals *opcodedump_globals)
{
	opcodedump_globals->global_value = 0;
	opcodedump_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(opcodedump)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(opcodedump)
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
PHP_RINIT_FUNCTION(opcodedump)
{
#if defined(COMPILE_DL_OPCODEDUMP) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(opcodedump)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(opcodedump)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "opcodedump support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* {{{ opcodedump_functions[]
 *
 * Every user visible function must have an entry in opcodedump_functions[].
 */
const zend_function_entry opcodedump_functions[] = {
	PHP_FE(dasm_file,         arginfo_dasm_file)

	PHP_FE_END	/* Must be the last line in opcodedump_functions[] */
};
/* }}} */

/* {{{ opcodedump_module_entry
 */
zend_module_entry opcodedump_module_entry = {
	STANDARD_MODULE_HEADER,
	"opcodedump",
	opcodedump_functions,
	PHP_MINIT(opcodedump),
	PHP_MSHUTDOWN(opcodedump),
	PHP_RINIT(opcodedump),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(opcodedump),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(opcodedump),
	PHP_OPCODEDUMP_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_OPCODEDUMP
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(opcodedump)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
