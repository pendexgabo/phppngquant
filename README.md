phppngquant
===========

A pngquant utility wrapper PHP extension using the Zephir language

Requiremets
-----------
1. the [pngquant](http://pngquant.org/) command-line utility


How to build (install)
----------------------

Install [zephir](http://zephir-lang.com/install.html)

Compile phppngquant:

    cd phppngquant
    zephir generate
    zephir compile

Add extension to your php.ini

    extension=pngquant.so

Finally restart/reload php

