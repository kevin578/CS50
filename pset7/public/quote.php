<?php
require("../includes/config.php");
if ($_SERVER["REQUEST_METHOD"] == "GET"){
    render("quote_form.php");
  }
else if ($_SERVER["REQUEST_METHOD"] == "POST"){
    if (empty($_POST["symbol"])){
    apologize("You need to put a stock in.");
    }
    
    $stock = lookup($_POST["symbol"]);
    
    if($stock === false){
    apologize("Could not find stock");
    }
    else if ($stock["name"] == "N/A"){
    apologize("Could not find stock");
    }
    else{
    render("price_form.php", ["stock" => $stock, "title" => "Quote"]);
    }
  }
?>
