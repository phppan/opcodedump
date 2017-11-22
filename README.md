php7的opcode dump

函数列表：


1.  $ cd ..
2.  $ vi ext/opcodedump/config.m4
3.  $ ./buildconf
4.  $ ./configure --[with|enable]-opcodedump
5.  $ make
6.  $ ./sapi/cli/php -f ext/opcodedump/opcodedump.php
7.  $ vi ext/opcodedump/opcodedump.c
8.  $ make
