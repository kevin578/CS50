<table border="1" align = "center" style = "width:50%; margin-bottom: 15px; margin-top: 15px;">   
    <tr>
        <td><b>Transaction</b></td>
        <td><b>Date/Time</b></td>
        <td><b>Symbol</b></td>
        <td><b>Shares</b></td>
        <td><b>Price</b></td>
        
    </tr>
 <?php foreach ($rows as $rows): ?>
    <?$price = $rows["price"]?>
    <tr>
        <td><?= $rows["transaction"] ?></td>
        <td><?= $rows["dateTime"] ?></td>
        <td><?= $rows["symbol"] ?></td>
        <td><?= $rows["shares"] ?></td>
        <td><?= number_format($price, 2)?></td>
    </tr>  
<?php endforeach ?>
 </table> 

