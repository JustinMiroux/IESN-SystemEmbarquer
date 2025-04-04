<DOCTYPE! html>
<html>
	<head>
		<title>JRPI Steve controler page</title>
		<meta charset="UTF-8">
		<link rel="stylesheet" href="stylesheet.css">
	</head>

	<body>

		<div class="printing">
			<?php

				if(isset($_POST["forward"])){
					$convertedCmd = escapeshellcmd("python ./test.py forward"); //Converti une commande sous le bon format
					$answer = shell_exec($convertedCmd); //execute + renvoi reponse
					echo $answer; //ecrit la reponse sur la page web
				}

				if(isset($_POST["left"])){
					$convertedCmd = escapeshellcmd("python ./test.py left"); //Converti une commande sous le bon format
					$answer = shell_exec($convertedCmd); //execute + renvoi reponse
					echo $answer; //ecrit la reponse sur la page web
				}

				if(isset($_POST["right"])){
					$convertedCmd = escapeshellcmd("python ./test.py right"); //Converti une commande sous le bon format
					$answer = shell_exec($convertedCmd); //execute + renvoi reponse
					echo $answer; //ecrit la reponse sur la page web
				}

				if(isset($_POST["backward"])){
					$convertedCmd = escapeshellcmd("python ./test.py backward"); //Converti une commande sous le bon format
					$answer = shell_exec($convertedCmd); //execute + renvoi reponse
					echo $answer; //ecrit la reponse sur la page web
				}

			?>
		</div>

		<form name="SteveControler" method="post" action="index.php">
			<table>
				<tr>
					<td></td>
					<td><button type="submit" name="forward" value="Pressed">FORWARD</button></td>
					<td></td>
				</tr>
				<tr>
					<td><button type="submit" name="left" value="Pressed">LEFT</button></td>
					<td></td>
					<td><button type="submit" name="right" value="Pressed">RIGHT</button></td>
				</tr>
				<tr>
					<td></td>
					<td><button type="submit" name="backward" value="Pressed">BACKWARD</button></td>
					<td></td>
				</tr>
			</table>
		</form>
	</body>
</html>
