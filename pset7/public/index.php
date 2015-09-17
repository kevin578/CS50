<?php

    // configuration
    require("../includes/config.php"); 


$rows = query("SELECT symbol, shares FROM stocks WHERE id = ?", $_SESSION["id"]);

$positions = [];
foreach ($rows as $row)
{
    $stock = lookup($row["symbol"]);
    if ($stock !== false)
    {
        $positions[] = [
            "price" => $stock["price"],
            "shares" => $row["shares"],
            "symbol" => $row["symbol"]
        ];
    }
}


    // render portfolio
    render("portfolio.php", ["positions" => $positions, "title" => "Portfolio"]);

?>
