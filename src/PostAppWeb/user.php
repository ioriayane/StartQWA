<?php
  header("Content-type: text/html; charset=utf-8");
  header("Access-Control-Allow-Origin: *");

  $id = $_GET["id"];
  $name = "ハヤテ";
  $image = "https://qwa.relog.tech/sns/123456789.jpg";

  $array = ['id'=>$id, 'name'=>$name, 'image'=>$image];
  $json = json_encode($array, JSON_UNESCAPED_UNICODE | JSON_UNESCAPED_SLASHES);

  echo $json;
?>