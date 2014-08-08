
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


ZEPHIR_INIT_CLASS(Pngquant_Exception_BinaryNotFoundException) {

	ZEPHIR_REGISTER_CLASS_EX(Pngquant\\Exception, BinaryNotFoundException, pngquant, exception_binarynotfoundexception, pngquant_exception_pngquantexception_ce, pngquant_exception_binarynotfoundexception_method_entry, 0);

	return SUCCESS;

}

PHP_METHOD(Pngquant_Exception_BinaryNotFoundException, __toString) {


	RETURN_STRING("pngquant binary not found", 1);

}

