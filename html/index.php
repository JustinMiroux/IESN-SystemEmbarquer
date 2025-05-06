<DOCTYPE! html>
<html>
	<head>
		<title>JRPI Steve controler page</title>
		<meta charset="UTF-8">
		<link rel="stylesheet" href="stylesheet.css">
	</head>
	<body>
		<?php

			try {
				$pdo = new PDO("sqlite:sqlite.db");
				$pdo->exec('CREATE TABLE IF NOT EXISTS mode (automated)');
			}

			catch (Exception $e) {
				echo 'Caught exception: ', $e->getMessage(), "\n";
			}

			if(isset($_POST["auto"])){

				try {
					$pdo = new PDO("sqlite:sqlite.db");
					$sql = 'SELECT * FROM distance ORDER BY ROWID ASC LIMIT 1';
					echo $sql;

					$sql = 'UPDATE mode SET automated = 1';
					$stmt = pdo->prepare($sql);
					$stmt = $stmt->execute();
				}

				catch (Exception $e) {
					echo 'Caught exception: ', $e->getMessage(), "\n";
				}
			}

			if(isset($_POST["manual"])){
				
				try {
					$pdo = new PDO("sqlite:sqlite.db");
					$sql = 'SELECT * FROM distance ORDER BY ROWID ASC LIMIT 1';
					echo $sql;

					$sql = 'UPDATE mode SET automated = 0';
					$stmt = pdo->prepare($sql);
					$stmt = $stmt->execute();
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