<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
    $username = $_POST['username'];
    $password = $_POST['password'];
    $confirmation = $_POST['confirmation'];
        if (!$username || !$password || !$confirmation){
            apologize("You did not fill in all the info.");            
            }
        else if ($password != $confirmation){
            apologize("Your passwords do not match");
            }
        $rows = query ("SELECT * FROM users WHERE username = ?", $username);
        if ($rows == 1){
            apologize("Username already exists");
            }
        else {
            query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $username, 
            crypt($password));
            $rows = query("SELECT LAST_INSERT_ID() AS id");
            $id = $rows[0]["id"];
            $_SESSION["id"] = $id;
            redirect("index.php");
            
        }
    }

?>
