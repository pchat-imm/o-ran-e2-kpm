<?php

require "tests.php";

check::classes(array('Foo_int','Foo_short'));
$foo_int=new foo_int(3);
check::is_a($foo_int,"foo_int","Made a foo_int");

check::done();
