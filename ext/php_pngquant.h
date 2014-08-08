
/* This file was generated automatically by Zephir do not modify it! */

#ifndef PHP_PNGQUANT_H
#define PHP_PNGQUANT_H 1

#define ZEPHIR_RELEASE 1

#include "kernel/globals.h"

#define PHP_PNGQUANT_NAME        "pngquant"
#define PHP_PNGQUANT_VERSION     "0.0.2"
#define PHP_PNGQUANT_EXTNAME     "pngquant"
#define PHP_PNGQUANT_AUTHOR      "Gabriel Sosa"
#define PHP_PNGQUANT_ZEPVERSION  "0.4.2a"
#define PHP_PNGQUANT_DESCRIPTION "A simple wrapper for the pngquant png compressor"



ZEND_BEGIN_MODULE_GLOBALS(pngquant)

	/* Memory */
	zephir_memory_entry *start_memory; /**< The first preallocated frame */
	zephir_memory_entry *end_memory; /**< The last preallocate frame */
	zephir_memory_entry *active_memory; /**< The current memory frame */

	/* Virtual Symbol Tables */
	zephir_symbol_table *active_symbol_table;

	/** Function cache */
	HashTable *fcache;

	/* Max recursion control */
	unsigned int recursive_lock;

	/* Global constants */
	zval *global_true;
	zval *global_false;
	zval *global_null;
	
ZEND_END_MODULE_GLOBALS(pngquant)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(pngquant)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) TSRMG(pngquant_globals_id, zend_pngquant_globals *, v)
#else
	#define ZEPHIR_GLOBAL(v) (pngquant_globals.v)
#endif

#ifdef ZTS
	#define ZEPHIR_VGLOBAL ((zend_pngquant_globals *) (*((void ***) tsrm_ls))[TSRM_UNSHUFFLE_RSRC_ID(pngquant_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(pngquant_globals)
#endif

#define zephir_globals_def pngquant_globals
#define zend_zephir_globals_def zend_pngquant_globals

extern zend_module_entry pngquant_module_entry;
#define phpext_pngquant_ptr &pngquant_module_entry

#endif
