<?php
require("../includes/config.php");
if ($_SERVER["REQUEST_METHOD"] == "GET"){
    render("sell_form.php");
  }
else if ($_SERVER["REQUEST_METHOD"] == "POST"){
    
    if (empty($_POST["symbol"])){
    apologize("You need to put a stock in.");
    }
    
    
    $rows = query("SELECT shares FROM stocks WHERE id = ? and symbol = ?", $_SESSION["id"], $_POST["symbol"]);
   
       
    if((count($rows) == 0)){
    apologize("You don't have this stock");
    }
    
    $shares = $rows[0]["shares"];
    
    $stock = lookup($_POST["symbol"]);
    $stock_price = ($stock["price"]);
    $total_price = $shares * $stock_price;
    
    $query = query("DELETE FROM `stocks` WHERE `id` = ? AND `symbol` = ?",$_SESSION["id"], ($_POST["symbol"]));
    
    if ($query === false){
        apologize("There was an error while selling your stocks");
    }
    
    $rows = query("SELECT cash FROM users WHERE id = ?",$_SESSION["id"]);
    $old_cash = $rows[0]["cash"];
    $new_cash = $old_cash + $total_price;
    
    $query = query("UPDATE users SET cash = ? WHERE id = ?", $new_cash, $_SESSION["id"]);
  
    if ($query === false){
        apologize("There was an error while getting your money back.");
    }
    
    $dateTime = date('Y-m-d'); 
    $symbol = strtoupper($_POST["symbol"]);
    $query = query("INSERT INTO `pset7`.`history` (`id`,`transaction`, `dateTime`, `symbol`, `shares`, `price`) 
    VALUES (?,'Sell',?,?,?,?)",$_SESSION["id"], $dateTime, $symbol, $shares, $stock_price);
    render("sell_info.php", ["shares" => $shares,"price" => $total_price, "cash" => "$new_cash", "title" => "Sell"]);
  }
?>
