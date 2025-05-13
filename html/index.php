<DOCTYPE! html>
<html>
	<head>
		<title>JRPI Steve controler page</title>
		<meta charset="UTF-8">
		<link rel="stylesheet" href="stylesheet.css">
	</head>
	<body>
		<?php

			if(isset($_POST["auto"])){

				try {
					$db = new SQLite3('sqlite.db');
					$blow = [];
					$results = $db->query('SELECT * FROM distance');
					while ($row = $results->fetchArray(SQLITE3_ASSOC)) {
						$debug = var_export($row, true);
						}
						$final = explode("'", $debug);
						echo "distance: ";
						echo $final[3];
						echo "cm";	
					
					$convertedCmd = escapeshellcmd("python ./buttons_to_db.py auto"); //Converti une commande sous le bon format
					shell_exec($convertedCmd); //execute + renvoi reponse

				}

				catch (Exception $e) {
					echo 'Caught exception: ', $e->getMessage(), "\n";
				}
			}

			if(isset($_POST["manual"])){
				
				try {
					$db = new SQLite3('sqlite.db');
					$blow = [];
					$results = $db->query('SELECT * FROM distance');
					while ($row = $results->fetchArray(SQLITE3_ASSOC)) {
						$debug = var_export($row, true);
						}
						$final = explode("'", $debug);
						echo $final[3];
						
					$convertedCmd = escapeshellcmd("python ./buttons_to_db.py manual"); //Converti une commande sous le bon format
					shell_exec($convertedCmd); //execute + renvoi reponse

				}

				catch (Exception $e) {
					echo 'Caught exception: ', $e->getMessage(), "\n";
				}
			}

		?>

		<form name="SteveControler" method="post" action="index.php">
			<table>
				<tr>
					<td><button type="submit" name="auto" value="Pressed">Mode Auto</button></td>
					<td><button type="submit" name="manual" value="Pressed">Mode Manuel</button></td>
				</tr>
			</table>
		</form>
	</body>
</html>