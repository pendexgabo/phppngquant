
extern zend_class_entry *pngquant_pngquant_ce;

ZEPHIR_INIT_CLASS(Pngquant_Pngquant);

PHP_METHOD(Pngquant_Pngquant, _doChecks);
PHP_METHOD(Pngquant_Pngquant, _processArgs);
PHP_METHOD(Pngquant_Pngquant, _readSourceFile);
PHP_METHOD(Pngquant_Pngquant, _processFile);
PHP_METHOD(Pngquant_Pngquant, __construct);
PHP_METHOD(Pngquant_Pngquant, setImage);
PHP_METHOD(Pngquant_Pngquant, pngquantBin);
PHP_METHOD(Pngquant_Pngquant, compress);
PHP_METHOD(Pngquant_Pngquant, getBlob);
PHP_METHOD(Pngquant_Pngquant, quality);

ZEND_BEGIN_ARG_INFO_EX(arginfo_pngquant_pngquant___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_pngquant_pngquant_setimage, 0, 0, 1)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_pngquant_pngquant_compress, 0, 0, 0)
	ZEND_ARG_INFO(0, new_path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_pngquant_pngquant_quality, 0, 0, 2)
	ZEND_ARG_INFO(0, min)
	ZEND_ARG_INFO(0, max)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(pngquant_pngquant_method_entry) {
	PHP_ME(Pngquant_Pngquant, _doChecks, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Pngquant_Pngquant, _processArgs, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Pngquant_Pngquant, _readSourceFile, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Pngquant_Pngquant, _processFile, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Pngquant_Pngquant, __construct, arginfo_pngquant_pngquant___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Pngquant_Pngquant, setImage, arginfo_pngquant_pngquant_setimage, ZEND_ACC_PUBLIC)
	PHP_ME(Pngquant_Pngquant, pngquantBin, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Pngquant_Pngquant, compress, arginfo_pngquant_pngquant_compress, ZEND_ACC_PUBLIC)
	PHP_ME(Pngquant_Pngquant, getBlob, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Pngquant_Pngquant, quality, arginfo_pngquant_pngquant_quality, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
