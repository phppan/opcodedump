<?php
class AAB{
static $a = 22;
}
const AA=1;
$apple = 1;
$b = [1, 2, 3];

if (-1) {
    $apple = 2;
}

echo $apple;

function aa($a) {
echo $a;
}


class StaticClass {

  public static  $stStateArr = NULL;

  public function __construct() {
    if (!isset(self::$stStateArr)) {
      self::initializeStStateArr();
    }
  }

  public static function initializeStStateArr() {
    if (!isset(self::$stStateArr)) {
      self::$stStateArr = array('CA' => 'California', 'CO' => 'Colorado',);
      echo "In " . __FUNCTION__. "\n";
    }
  }

}
