<?php
require("../includes/config.php");
if ($_SERVER["REQUEST_METHOD"] == "GET"){
    render("buy_form.php");
  }
else if ($_SERVER["REQUEST_METHOD"] == "POST"){
    
    if (empty($_POST["symbol"])){
    apologize("You need to put a stock in.");
   }
    if (!preg_match("/^\d+$/", $_POST["shares"])){
    apologize("You can't by factions of a stock, dummy.");   
   }
       
    $stock = lookup($_POST["symbol"]);
    
    if($stock === false){
    apologize("Could not find stock");
    }
    else if ($stock["name"] == "N/A"){
    apologize("Could not find stock");
    }
    /*Calculate total cost of shares*/
    $buy_price = $stock["price"] * $_POST["shares"];
    
    /*Do they have enough money?*/
    $rows = query("SELECT cash FROM users WHERE id = ?",$_SESSION["id"]);
    
    $old_cash = $rows[0]["cash"];
    if ($old_cash < $buy_price){
    apologize("You're too broke to buy this many shares.");
    }
    
    /*Calculate how much money they have now and change database.*/
    $new_cash = $old_cash - $buy_price;
    
    $query = query("UPDATE users SET cash = ? WHERE id = ?", $new_cash, $_SESSION["id"]);
    
    $symbol = strtoupper($_POST["symbol"]);
    
    /*Figure out if they have the stock already. Either update or insert.*/
    $rows = query("SELECT symbol, shares FROM stocks WHERE id = ? AND symbol = ?", $_SESSION["id"], $symbol);
    
    if (count($rows) == 1){
    $new_shares = $rows[0]["shares"] + $_POST["shares"];
    $query = query("UPDATE stocks SET shares = ? WHERE id = ? AND symbol = ?", $new_shares, $_SESSION["id"], 
    $symbol);
    }
    else{
    $query = query("INSERT INTO `pset7`.`stocks` (`id`, `symbol`, `shares`) VALUES (?,?,?)",$_SESSION["id"],
    $symbol,$_POST["shares"]);
    }
    /*Insert into history*/
    $dateTime = date('Y-m-d-g-i-s'); 
    $query = query("INSERT INTO `pset7`.`history` (`id`,`transaction`, `dateTime`, `symbol`, `shares`, `price`) 
    VALUES (?,'Buy',?,?,?,?)",$_SESSION["id"], $dateTime, $symbol, $_POST["shares"], $stock["price"]);
    
    /*Render buy page*/
    render("buy_info.php", ["symbol" => $symbol,"cash" => $new_cash,"price" => $buy_price, "shares" => $_POST["shares"], "title" => "Congrats on your purchase!"]);
}
?>
