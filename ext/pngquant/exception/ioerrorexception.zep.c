
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
#include "kernel/operators.h"
#include "kernel/memory.h"


ZEPHIR_INIT_CLASS(Pngquant_Exception_IOErrorException) {

	ZEPHIR_REGISTER_CLASS_EX(Pngquant\\Exception, IOErrorException, pngquant, exception_ioerrorexception, pngquant_exception_pngquantexception_ce, pngquant_exception_ioerrorexception_method_entry, 0);

	return SUCCESS;

}

PHP_METHOD(Pngquant_Exception_IOErrorException, __construct) {

	zval *message_param = NULL;
	zval *message = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &message_param);

	zephir_get_strval(message, message_param);


	zephir_update_property_this(this_ptr, SL("message"), message TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Pngquant_Exception_IOErrorException, __toString) {


	RETURN_MEMBER(this_ptr, "message");

}

