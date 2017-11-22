<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('opcodedump')) {
	dl('opcodedump.' . PHP_SHLIB_SUFFIX);
}
$module = 'opcodedump';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";

$path = dirname(__FILE__) . "/";
echo __FILE__, "\r\n";
if (extension_loaded($module)) {
	$rs = dasm_file($path . "demo.php");
} else {
	$rs = "Module $module is not compiled into PHP";
}
echo 1;
print_r($rs);
echo 2;
