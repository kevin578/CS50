<?php
require("../includes/config.php");
if ($_SERVER["REQUEST_METHOD"] == "GET"){
    render("addcash_form.php");
  }
else if ($_SERVER["REQUEST_METHOD"] == "POST"){
    $query = query("UPDATE users SET cash = cash + ? WHERE id = ?", $_POST["cash"], $_SESSION["id"]);
  
    $cash = $_POST["cash"];
    echo "You added $$cash.";
    }
