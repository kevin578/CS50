<a href="quote.php">Quote</a>
<a href="sell.php">Sell</a>
<a href="buy.php">Buy</a>
<a href="history.php">History</a>
<a href="addcash.php">Add Cash!</a>


<div>
<table border="1" align = "center" style = "width:50%; margin-bottom: 15px; margin-top: 15px;">   
    <tr>
        <td><b>Symbol</b></td>
        <td><b>Shares</b></td>
        <td><b>Price</b></td>
        
    </tr>
 <?php foreach ($positions as $position): ?>

    <tr>
        <td><?= $position["symbol"] ?></td>
        <td><?= $position["shares"] ?></td>
        <td><?= $position["price"] ?></td>
    </tr>  
<?php endforeach ?>
 </table> 
</div>
<div>
    <a href="logout.php">Log Out</a>
</div>
