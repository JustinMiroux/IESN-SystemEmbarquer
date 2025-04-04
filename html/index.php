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
				$convertedCmd = escapeshellcmd("python ./change_mode.py auto"); //Converti une commande sous le bon format
				$answer = shell_exec($convertedCmd); //execute + renvoi reponse
				echo $answer; //ecrit la reponse sur la page web

				try {
					$mydb = new PDO("sqlite:sqlite.db");
					
					$sql = 'SELECT * FROM distance';
					foreach ($mydb->query($sql) as $row) {
						print_r($row);
					}
				}

				catch (Exception $e) {
					echo 'Caught exception: ', $e->getMessage(), "\n";
				}

				
			}

			if(isset($_POST["manual"])){
				$convertedCmd = escapeshellcmd("python ./change_mode.py manual"); //Converti une commande sous le bon format
				$answer = shell_exec($convertedCmd); //execute + renvoi reponse
				echo $answer; //ecrit la reponse sur la page web

				try {
					$mydb = new PDO("sqlite:sqlite.db");
					
					$sql = 'SELECT * FROM distance';
					foreach ($mydb->query($sql) as $row) {
						print_r($row);
					}
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