
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/operators.h"


ZEPHIR_INIT_CLASS(Pngquant_Exception_PngquantException) {

	ZEPHIR_REGISTER_CLASS_EX(Pngquant\\Exception, PngquantException, pngquant, exception_pngquantexception, zend_exception_get_default(TSRMLS_C), pngquant_exception_pngquantexception_method_entry, 0);

	return SUCCESS;

}

PHP_METHOD(Pngquant_Exception_PngquantException, __construct) {

	zval *message_param = NULL;
	zval *message = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &message_param);

	if (!message_param) {
		ZEPHIR_INIT_VAR(message);
		ZVAL_EMPTY_STRING(message);
	} else {
		zephir_get_strval(message, message_param);
	}


	zephir_update_property_this(this_ptr, SL("message"), message TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Pngquant_Exception_PngquantException, __toString) {


	RETURN_MEMBER(this_ptr, "message");

}

