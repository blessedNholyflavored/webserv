nom=val_1&age=val_2;
<!DOCTYPE html>
<html>
	
<body>

 <?php if(isset($_POST['age'])){
			
	echo "TAMER";
} else {
	echo "LAPUTE";
}	

?>
	Bonjour, <?php echo htmlspecialchars($_POST['nom']); ?>.
	Tu as <?php echo $_POST['age']; ?> ans.
	<?php print_r($_POST); ?>

	<table>
<?php 


    foreach ($_POST as $key => $value) {
        echo "<tr>";
        echo "<td>";
        echo $key;
        echo "</td>";
        echo "<td>";
        echo $value;
        echo "</td>";
        echo "</tr>";
    }


?>
</table>

</body>
</html>
