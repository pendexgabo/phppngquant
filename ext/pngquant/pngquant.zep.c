
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/object.h"
#include "kernel/exception.h"
#include "kernel/file.h"
#include "kernel/array.h"
#include "kernel/concat.h"


/**
 * A wrapper for the pngquant utility
 * @link http://pngquant.org/
 *
 * Currently this call in only compatible with POXIS enviroments,
 * no Mi*soft Windows compatibility is intented at all
 */
ZEPHIR_INIT_CLASS(Pngquant_Pngquant) {

	ZEPHIR_REGISTER_CLASS(Pngquant, Pngquant, pngquant, pngquant, pngquant_pngquant_method_entry, 0);

	zend_declare_property_string(pngquant_pngquant_ce, SL("pngquant"), "/usr/bin/pngquant", ZEND_ACC_STATIC|ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(pngquant_pngquant_ce, SL("min_quality"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(pngquant_pngquant_ce, SL("max_quality"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(pngquant_pngquant_ce, SL("path"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(pngquant_pngquant_ce, SL("new_path"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_bool(pngquant_pngquant_ce, SL("processed"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_bool(pngquant_pngquant_ce, SL("blob"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);

	return SUCCESS;

}

/**
 * Runs the requires checks for the class to work.
 * the method first read the <b>pngquant_path</b> ini setting
 * if the setting is undefined the class will try to <i>guess</i> the
 * path of the command line utility. Otherwise an exception is raised
 * 
 * @return void
 * @throw Exception\BinaryNotFoundException
 */
PHP_METHOD(Pngquant_Pngquant, _doChecks) {

	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL, *_5 = NULL;
	int exitstatus = 0, ZEPHIR_LAST_CALL_STATUS;
	zval *ini_setting = NULL, *output, _0 = zval_used_for_init, *_2, *_3, *_4 = NULL, *_6;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(output);
	array_init(output);
	ZEPHIR_SINIT_VAR(_0);
	ZVAL_STRING(&_0, "pngquant_path", 0);
	ZEPHIR_CALL_FUNCTION(&ini_setting, "ini_get", &_1, &_0);
	zephir_check_call_status();
	if (ZEPHIR_IS_FALSE(ini_setting)) {
		ZEPHIR_INIT_VAR(_2);
		ZVAL_STRING(_2, "command -v pngquant", 0);
		ZEPHIR_INIT_VAR(_3);
		ZVAL_LONG(_3, exitstatus);
		Z_SET_ISREF_P(output);
		ZEPHIR_CALL_FUNCTION(&_4, "exec", &_5, _2, output, _3);
		zephir_check_temp_parameter(_2);
		Z_UNSET_ISREF_P(output);
		zephir_check_call_status();
		zephir_update_static_property_ce(pngquant_pngquant_ce, SL("pngquant"), _4 TSRMLS_CC);
	}
	ZEPHIR_SINIT_NVAR(_0);
	ZVAL_LONG(&_0, exitstatus);
	if (zephir_get_intval(&_0) != 0) {
		ZEPHIR_INIT_VAR(_6);
		object_init_ex(_6, pngquant_exception_binarynotfoundexception_ce);
		ZEPHIR_CALL_METHOD(NULL, _6, "__construct", NULL);
		zephir_check_call_status();
		zephir_throw_exception_debug(_6, "pngquant/pngquant.zep", 47 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Parses and process the arguments before being passed to the command
 * 
 * @return string; $args a string contaning all parameters
 * @throws Exception\OutOfBoundsException
 * @throws Exception\RangeException
 */
PHP_METHOD(Pngquant_Pngquant, _processArgs) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_12 = NULL;
	zend_bool _1;
	zval *args = NULL, *_0, *_2, *_3, *_4, *_5, *_6, *_7, *_8, *_9, *_10, _11;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(args);
	ZVAL_STRING(args, "", 1);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("min_quality"), PH_NOISY_CC);
	_1 = Z_TYPE_P(_0) != IS_NULL;
	if (_1) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("max_quality"), PH_NOISY_CC);
		_1 = Z_TYPE_P(_2) != IS_NULL;
	}
	if (_1) {
		_3 = zephir_fetch_nproperty_this(this_ptr, SL("min_quality"), PH_NOISY_CC);
		if (ZEPHIR_GT_LONG(_3, 100)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_OutOfBoundsException, "min quality should be lower than 100", "pngquant/pngquant.zep", 66);
			return;
		}
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("min_quality"), PH_NOISY_CC);
		if (ZEPHIR_LT_LONG(_4, 0)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_OutOfBoundsException, "min quality should be greater than 0", "pngquant/pngquant.zep", 70);
			return;
		}
		_5 = zephir_fetch_nproperty_this(this_ptr, SL("max_quality"), PH_NOISY_CC);
		if (ZEPHIR_GT_LONG(_5, 100)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_OutOfBoundsException, "max quality should be lower than 100", "pngquant/pngquant.zep", 74);
			return;
		}
		_6 = zephir_fetch_nproperty_this(this_ptr, SL("max_quality"), PH_NOISY_CC);
		if (ZEPHIR_LT_LONG(_6, 0)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_OutOfBoundsException, "max quality should be greater than 0", "pngquant/pngquant.zep", 78);
			return;
		}
		_7 = zephir_fetch_nproperty_this(this_ptr, SL("min_quality"), PH_NOISY_CC);
		_8 = zephir_fetch_nproperty_this(this_ptr, SL("max_quality"), PH_NOISY_CC);
		if (ZEPHIR_GT(_7, _8)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_RangeException, "min quality should be lower than max quality", "pngquant/pngquant.zep", 82);
			return;
		}
		_9 = zephir_fetch_nproperty_this(this_ptr, SL("min_quality"), PH_NOISY_CC);
		_10 = zephir_fetch_nproperty_this(this_ptr, SL("max_quality"), PH_NOISY_CC);
		ZEPHIR_SINIT_VAR(_11);
		ZVAL_STRING(&_11, "--quality=%2d-%2d", 0);
		ZEPHIR_CALL_FUNCTION(&args, "sprintf", &_12, &_11, _9, _10);
		zephir_check_call_status();
	}
	RETURN_CCTOR(args);

}

/**
 * Opens and reads the file
 * 
 * @return string; the content of the file
 * @throws Exception\IOErrorException if the source file can't be readed
 */
PHP_METHOD(Pngquant_Pngquant, _readSourceFile) {

	zephir_fcall_cache_entry *_16 = NULL;
	zend_bool _3, _7;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL, *_6 = NULL, *_10 = NULL, *_15 = NULL;
	zval *blob, *_0, *_1 = NULL, *_4, *_5 = NULL, *_8, *_9 = NULL, *_11 = NULL, *_12, _13 = zval_used_for_init, *_14 = NULL, *_17;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("path"), PH_NOISY_CC);
	ZEPHIR_CALL_FUNCTION(&_1, "stream_is_local", &_2, _0);
	zephir_check_call_status();
	_3 = zephir_is_true(_1);
	if (_3) {
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("path"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(&_5, "is_file", &_6, _4);
		zephir_check_call_status();
		_7 = !zephir_is_true(_5);
		if (!(_7)) {
			_8 = zephir_fetch_nproperty_this(this_ptr, SL("path"), PH_NOISY_CC);
			ZEPHIR_CALL_FUNCTION(&_9, "is_readable", &_10, _8);
			zephir_check_call_status();
			_7 = !zephir_is_true(_9);
		}
		_3 = _7;
	}
	if (_3) {
		ZEPHIR_INIT_VAR(_11);
		object_init_ex(_11, pngquant_exception_ioerrorexception_ce);
		_12 = zephir_fetch_nproperty_this(this_ptr, SL("path"), PH_NOISY_CC);
		ZEPHIR_SINIT_VAR(_13);
		ZVAL_STRING(&_13, "unable to open '%s' file", 0);
		ZEPHIR_CALL_FUNCTION(&_14, "sprintf", &_15, &_13, _12);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, _11, "__construct", &_16, _14);
		zephir_check_call_status();
		zephir_throw_exception_debug(_11, "pngquant/pngquant.zep", 103 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(blob);
	_12 = zephir_fetch_nproperty_this(this_ptr, SL("path"), PH_NOISY_CC);
	zephir_file_get_contents(blob, _12 TSRMLS_CC);
	if (ZEPHIR_IS_FALSE(blob)) {
		ZEPHIR_INIT_LNVAR(_11);
		object_init_ex(_11, pngquant_exception_ioerrorexception_ce);
		_17 = zephir_fetch_nproperty_this(this_ptr, SL("path"), PH_NOISY_CC);
		ZEPHIR_SINIT_NVAR(_13);
		ZVAL_STRING(&_13, "unable to read '%s' file", 0);
		ZEPHIR_CALL_FUNCTION(&_14, "sprintf", &_15, &_13, _17);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, _11, "__construct", &_16, _14);
		zephir_check_call_status();
		zephir_throw_exception_debug(_11, "pngquant/pngquant.zep", 109 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_CCTOR(blob);

}

/**
 * Run the pngquant binary. This method takes care of checking if the file
 * is readable and spawning a a pngquant process in order to compress the image
 * 
 * @return void
 * @throws Exception\IOErrorException if the source file can't be readed
 * @throws Exception\PngquantException if the compress process didn't succeed
 */
PHP_METHOD(Pngquant_Pngquant, _processFile) {

	zephir_nts_static zephir_fcall_cache_entry *_5 = NULL, *_9 = NULL, *_13 = NULL, *_14 = NULL, *_20 = NULL;
	zval *_1 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0, *args = NULL, *descriptorspec, *pipes, *status = NULL, *fd = NULL, *source = NULL, *_2 = NULL, *_3, *_4, *_6, *_7, *_8 = NULL, *_10, *_11, *_12, *_15, *_16, *_17, _18, *_19 = NULL;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("processed"), PH_NOISY_CC);
	if (ZEPHIR_IS_FALSE(_0)) {
		ZEPHIR_CALL_METHOD(&args, this_ptr, "_processargs",  NULL);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(pipes);
		array_init(pipes);
		ZEPHIR_INIT_VAR(descriptorspec);
		array_init_size(descriptorspec, 5);
		ZEPHIR_INIT_VAR(_1);
		array_init_size(_1, 3);
		ZEPHIR_INIT_VAR(_2);
		ZVAL_STRING(_2, "pipe", 1);
		zephir_array_fast_append(_1, _2);
		ZEPHIR_INIT_NVAR(_2);
		ZVAL_STRING(_2, "r", 1);
		zephir_array_fast_append(_1, _2);
		zephir_array_update_long(&descriptorspec, 0, &_1, PH_COPY, "pngquant/pngquant.zep", 138);
		ZEPHIR_INIT_NVAR(_1);
		array_init_size(_1, 3);
		ZEPHIR_INIT_NVAR(_2);
		ZVAL_STRING(_2, "pipe", 1);
		zephir_array_fast_append(_1, _2);
		ZEPHIR_INIT_NVAR(_2);
		ZVAL_STRING(_2, "w", 1);
		zephir_array_fast_append(_1, _2);
		zephir_array_update_long(&descriptorspec, 1, &_1, PH_COPY, "pngquant/pngquant.zep", 138);
		ZEPHIR_INIT_NVAR(_1);
		array_init_size(_1, 3);
		ZEPHIR_INIT_NVAR(_2);
		ZVAL_STRING(_2, "pipe", 1);
		zephir_array_fast_append(_1, _2);
		ZEPHIR_INIT_NVAR(_2);
		ZVAL_STRING(_2, "w", 1);
		zephir_array_fast_append(_1, _2);
		zephir_array_update_long(&descriptorspec, 2, &_1, PH_COPY, "pngquant/pngquant.zep", 138);
		ZEPHIR_CALL_METHOD(&source, this_ptr, "_readsourcefile",  NULL);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_3, pngquant_pngquant_ce, SL("pngquant") TSRMLS_CC);
		ZEPHIR_INIT_VAR(_4);
		ZEPHIR_CONCAT_VSVS(_4, _3, " ", args, " -");
		Z_SET_ISREF_P(pipes);
		ZEPHIR_CALL_FUNCTION(&fd, "proc_open", &_5, _4, descriptorspec, pipes);
		Z_UNSET_ISREF_P(pipes);
		zephir_check_call_status();
		zephir_array_fetch_long(&_6, pipes, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
		zephir_fwrite(NULL, _6, source TSRMLS_CC);
		ZEPHIR_INIT_NVAR(source);
		ZVAL_NULL(source);
		zephir_array_fetch_long(&_7, pipes, 1, PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_FUNCTION(&_8, "stream_get_contents", &_9, _7);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("blob"), _8 TSRMLS_CC);
		zephir_array_fetch_long(&_10, pipes, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
		zephir_fclose(_10 TSRMLS_CC);
		zephir_array_fetch_long(&_11, pipes, 1, PH_NOISY | PH_READONLY TSRMLS_CC);
		zephir_fclose(_11 TSRMLS_CC);
		zephir_array_fetch_long(&_12, pipes, 2, PH_NOISY | PH_READONLY TSRMLS_CC);
		zephir_fclose(_12 TSRMLS_CC);
		ZEPHIR_CALL_FUNCTION(&status, "proc_get_status", &_13, fd);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(NULL, "proc_close", &_14, fd);
		zephir_check_call_status();
		zephir_array_fetch_string(&_15, status, SL("exitcode"), PH_NOISY | PH_READONLY TSRMLS_CC);
		if (zephir_get_intval(_15) != 0) {
			ZEPHIR_INIT_VAR(_16);
			object_init_ex(_16, pngquant_exception_pngquantexception_ce);
			zephir_array_fetch_string(&_17, status, SL("exitcode"), PH_NOISY | PH_READONLY TSRMLS_CC);
			ZEPHIR_SINIT_VAR(_18);
			ZVAL_STRING(&_18, "non-zero exit status code returned: %d ", 0);
			ZEPHIR_CALL_FUNCTION(&_19, "sprintf", &_20, &_18, _17);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, _16, "__construct", NULL, _19);
			zephir_check_call_status();
			zephir_throw_exception_debug(_16, "pngquant/pngquant.zep", 160 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_update_property_this(this_ptr, SL("processed"), (1) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * The constructor method
 */
PHP_METHOD(Pngquant_Pngquant, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *path_param = NULL;
	zval *path = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &path_param);

	if (!path_param) {
		ZEPHIR_INIT_VAR(path);
		ZVAL_EMPTY_STRING(path);
	} else {
		zephir_get_strval(path, path_param);
	}


	if (!ZEPHIR_IS_STRING(path, "")) {
		zephir_update_property_this(this_ptr, SL("path"), path TSRMLS_CC);
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "_dochecks", NULL);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Sets the path of the image to compress
 * 
 * @param $path the path of the image to compress
 * @return void
 */
PHP_METHOD(Pngquant_Pngquant, setImage) {

	zval *path_param = NULL;
	zval *path = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &path_param);

	zephir_get_strval(path, path_param);


	zephir_update_property_this(this_ptr, SL("processed"), (0) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("path"), path TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Sets the path of the image to compress
 * 
 * @return string the path to the pngquant binary
 */
PHP_METHOD(Pngquant_Pngquant, pngquantBin) {

	zval *_0;


	_0 = zephir_fetch_static_property_ce(pngquant_pngquant_ce, SL("pngquant") TSRMLS_CC);
	RETURN_CTORW(_0);

}

/**
 * The public wrapper for the compression process.
 * 
 * @param string|void the new file path where the compressed image should be saved
 * @return void
 * @throws Exception\IOErrorException if the destination file can't be writen
 */
PHP_METHOD(Pngquant_Pngquant, compress) {

	zephir_nts_static zephir_fcall_cache_entry *_5 = NULL;
	zend_bool _1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *new_path_param = NULL, *save = NULL, *retval, *_0, *_2, _3, *_4 = NULL;
	zval *new_path = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &new_path_param);

	if (!new_path_param) {
		ZEPHIR_INIT_VAR(new_path);
		ZVAL_EMPTY_STRING(new_path);
	} else {
		zephir_get_strval(new_path, new_path_param);
	}


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "_processfile", NULL);
	zephir_check_call_status();
	if (!ZEPHIR_IS_STRING(new_path, "")) {
		ZEPHIR_CPY_WRT(save, new_path);
	} else {
		ZEPHIR_OBS_VAR(save);
		zephir_read_property_this(&save, this_ptr, SL("path"), PH_NOISY_CC);
	}
	ZEPHIR_INIT_VAR(retval);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("blob"), PH_NOISY_CC);
	zephir_file_put_contents(retval, save, _0 TSRMLS_CC);
	_1 = ZEPHIR_IS_LONG(retval, 0);
	if (!(_1)) {
		_1 = ZEPHIR_IS_FALSE(retval);
	}
	if (_1) {
		ZEPHIR_INIT_VAR(_2);
		object_init_ex(_2, pngquant_exception_ioerrorexception_ce);
		ZEPHIR_SINIT_VAR(_3);
		ZVAL_STRING(&_3, "unable to write to '%s'", 0);
		ZEPHIR_CALL_FUNCTION(&_4, "sprintf", &_5, &_3, save);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, _2, "__construct", NULL, _4);
		zephir_check_call_status();
		zephir_throw_exception_debug(_2, "pngquant/pngquant.zep", 218 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Return the blob of the image compressed
 * 
 * @return string $blob
 */
PHP_METHOD(Pngquant_Pngquant, getBlob) {

	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(NULL, this_ptr, "_processfile", NULL);
	zephir_check_call_status();
	RETURN_MM_MEMBER(this_ptr, "blob");

}

/**
 * Set the wanted quality for the compression
 * 
 * @param $min the mininal required quality
 * @param $min the maximun required quality
 * @return void
 */
PHP_METHOD(Pngquant_Pngquant, quality) {

	zval *min_param = NULL, *max_param = NULL, *_0;
	int min, max;

	zephir_fetch_params(0, 2, 0, &min_param, &max_param);

	min = zephir_get_intval(min_param);
	max = zephir_get_intval(max_param);


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, min);
	zephir_update_property_this(this_ptr, SL("min_quality"), _0 TSRMLS_CC);
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, max);
	zephir_update_property_this(this_ptr, SL("max_quality"), _0 TSRMLS_CC);

}

