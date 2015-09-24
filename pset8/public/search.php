<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];
    
    $places = preg_replace('~[+,US]~', ' ',$_GET["geo"]);
    $places = explode (' ', $places);
    
    
    for ($i = 0; $i < count($places); $i++){
    if( (is_numeric($places[$i])) && (strlen($places[$i]) == 5)){  
        $places = query("SELECT * FROM places WHERE postal_code = ?", $places[$i]);
        }
    }
    
    else {
        $places = query("SELECT * FROM places WHERE ")
    
    }
       
    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
