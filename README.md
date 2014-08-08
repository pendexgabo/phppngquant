phppngquant
===========

A pngquant utility wrapper PHP extension using the Zephir language

Requiremets
-----------
1. the [pngquant](http://pngquant.org/) command-line utility


How to build
-------------------------

Compile phppngquant:

    cd phppngquant/ext
    phpize .
    ./configure
    ./make
    ./make install

Add extension to your php.ini

    extension=pngquant.so


Finally restart/reload php

How to build using zephir
-------------------------

Install [zephir](http://zephir-lang.com/install.html)

Compile phppngquant:

    cd phppngquant
    zephir generate
    zephir compile

Add extension to your php.ini

    extension=pngquant.so

Finally restart/reload php

