<!DOCTYPE html>
<? if (!isset($_SESSION)) { session_start(); } ?>
<html>
	<head>
		<meta charset="utf-8">
		<title>Home Page</title>
		<link href="style.css" rel="stylesheet" type="text/css">
		<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.1/css/all.css">
	</head>
	<body class="loggedin">
	
		<nav class="navtop">
			<div>
				<h1>Home Page</h1>
			</div>
		</nav>
		<div class="content">
			<h2>Home Page</h2>
			<p>User role: <?=$_SESSION['role']?></p>
		</div>
		<h1>Add new comment</h1>
		<form action="comment.php" method="post">
				<label for="Comment">
					<i class="fas fa-user"></i>
				</label>
				<input type="textarea" name="comment" placeholder="Comment" id="comment"  required>
				<input type="submit" value="Save comment">
			</form>

		<h1>Comments:</h1>
			<?php
    			$con=mysqli_connect("localhost","root","root","tema");
    			if (mysqli_connect_errno())
      				{
      					echo "Failed to connect to MySQL: " . mysqli_connect_error();
      				}

    			$result = mysqli_query($con,"SELECT * FROM comments");

   				while($row = mysqli_fetch_array($result))
      			{
				echo "<li>";
     		 	echo htmlspecialchars($row['content'],ENT_QUOTES, 'UTF-8'); 
      			echo "<br />";
      			}
    			mysqli_close($con);
			?>
			
		<h1> Display content of a file: </h1>
		<form method="get">
		<input type="text" name="filename" placeholder="File Name" id="filename" pattern='^(?:[a-z]:)?[\/\\]{0,2}(?:[.\/\\ ](?![.\/\\\n])|[^<>:"|?*.\/\\ \n])+$' required>
		<input type="submit" value="Show file content">
			</form>
		<?php
		$file = file_get_contents('./messages/'. $_GET['filename'] . '.txt', true);
		if( $file === FALSE)
		{
			echo 'The file does not exist!';
		}
		else{
		echo htmlspecialchars($file,ENT_QUOTES, 'UTF-8');
		}
		?>
		<br>
		<h1> Ping a webpage </h1>
		<form method="get">
		<input type="text" name="address" placeholder="Web address" id="address" pattern = '^(http:\/\/www\.|https:\/\/www\.|http:\/\/|https:\/\/)?[a-z0-9]+([\-\.]{1}[a-z0-9]+)*\.[a-z]{2,5}(:[0-9]{1,5})?(\/.*)?$' required>
		<input type="submit" value="Ping">
			</form>
		<?php
		echo exec("ping ". $_GET["address"]);
		?>
	</body>
</html>