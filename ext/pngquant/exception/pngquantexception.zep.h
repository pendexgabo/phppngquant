
extern zend_class_entry *pngquant_exception_pngquantexception_ce;

ZEPHIR_INIT_CLASS(Pngquant_Exception_PngquantException);

PHP_METHOD(Pngquant_Exception_PngquantException, __construct);
PHP_METHOD(Pngquant_Exception_PngquantException, __toString);

ZEND_BEGIN_ARG_INFO_EX(arginfo_pngquant_exception_pngquantexception___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, message)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(pngquant_exception_pngquantexception_method_entry) {
	PHP_ME(Pngquant_Exception_PngquantException, __construct, arginfo_pngquant_exception_pngquantexception___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Pngquant_Exception_PngquantException, __toString, NULL, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
