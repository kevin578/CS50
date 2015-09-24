<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];
    
    $places = preg_replace('~[+,US]~', ' ',$_GET["geo"]);
    $places = explode (' ', $places);

    
    
    for ($i = 0; $i < count($places); $i++){
    if( (is_numeric($places[$i])) && (strlen($places[$i]) == 5)){  
        $places = query("SELECT * FROM places WHERE postal_code = ?", $places[$i]);
        break;
        }
    else {
        if (count($places = 1)){
        $places = query("SELECT * FROM places WHERE place_name = ?", $places[0]);
        echo $places[0];
        }

        else if (count($places > 1)){
            $places = query("SELECT * FROM places WHERE place_name = ? AND admin_name1 = ?", $places[0], $places[1]);
        }
    }
    }    
    

       
    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
