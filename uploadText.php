<?php
    $name = $_POST['textUpload'];
    if (empty($name)) {
        echo "Name is empty";
    } else {
        echo $name;
    }
?>
