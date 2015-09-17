<?php
require("../includes/config.php");

$rows = query("SELECT transaction, dateTime, symbol, shares, price FROM history WHERE id = ?", $_SESSION["id"]);

render("history_form.php", ["rows" => $rows, "title" => "History"]);
?>
