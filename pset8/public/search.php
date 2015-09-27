<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];
    
    $get =  $_GET["geo"];
    $get = preg_replace('~[+,US]~', ' ',$_GET["geo"]);
    $get = explode (' ', $get);
    for ($i = 0; $i < count($get); $i++){
        $get[$i] = strtoupper($get[$i]);
        if (strlen($get[$i]) == 2){
        
        $get[$i] = state_abrv($get[$i]);
        }
    }
    $get = implode (' ',$get);
    
    
    $places = query("SELECT * FROM places WHERE MATCH(place_name, admin_name1, admin_code1, postal_code, 
    country_code) AGAINST(?)", $get);   
    

       
    //output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
