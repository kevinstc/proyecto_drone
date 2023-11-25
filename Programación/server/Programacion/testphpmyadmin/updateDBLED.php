<?php     
  require 'database.php';
  
  if (!empty($_POST)) {
    $Stat = $_POST['ESC01'];
      
    // insert data
    $pdo = Database::connect();
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    $sql = "UPDATE ESCs SET ESC01 = ? WHERE ID = 1";
    $q = $pdo->prepare($sql);
    $q->execute(array($ESC01));
    Database::disconnect();
    header("Location: Main.php");
  }
?>