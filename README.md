php7的opcode dump

函数列表：
## dasm_file 函数
### 定义和用法
Disassemble file into opcode array by filename 

### 语法
dasm_file(string filename)

## dasm_string 函数
### 定义和用法
Disassemble php code into opcode array 

### 语法
dasm_file(string code)



## 编译

1.  $ cd ext/opcodedump
2.  $ [phpize-cmd-path]
1.  $ ./configure --with-php-config=[php-config-cmd-path] --[with|enable]-opcodedump
2.  $ make && make install
3.  $ [php7-cmd-path] -f ext/opcodedump/opcodedump.php

