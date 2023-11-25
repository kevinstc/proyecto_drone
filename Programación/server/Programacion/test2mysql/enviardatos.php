<?php
#echo "inicia pagina";
$conexion = mysql_connect("localhost", "root", "root");
mysql_select_db("data_sensors_and_esc", $conexion);
mysql_query("SET NAMES 'utf8'");
#echo "Conectada base de datos";
$ESC01 = $_POST ['ESC01'];
$ESC02 = $_POST ['ESC02'];
$ESC03 = $_POST ['ESC03'];
$ESC04 = $_POST ['ESC04'];

mysql_query("INSERT INTO `data_sensors_and_esc`.`ESCs` (`ID`, `ESC01`, `ESC02`, `ESC03`, `ESC04`) VALUES (NULL, '$ESC01', '$ESC02','$ESC03','$ESC04');");

mysql_close();

echo "Datos ingresados correctamente.";
?>