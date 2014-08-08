
extern zend_class_entry *pngquant_exception_binarynotfoundexception_ce;

ZEPHIR_INIT_CLASS(Pngquant_Exception_BinaryNotFoundException);

PHP_METHOD(Pngquant_Exception_BinaryNotFoundException, __toString);

ZEPHIR_INIT_FUNCS(pngquant_exception_binarynotfoundexception_method_entry) {
	PHP_ME(Pngquant_Exception_BinaryNotFoundException, __toString, NULL, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
