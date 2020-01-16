<?php
$DATABASE_HOST = 'localhost';
$DATABASE_USER = 'root';
$DATABASE_PASS = 'root';
$DATABASE_NAME = 'tema';
// Try and connect using the info above.
$con = mysqli_connect($DATABASE_HOST, $DATABASE_USER, $DATABASE_PASS, $DATABASE_NAME);
if ( mysqli_connect_errno() ) {
	// If there is an error with the connection, stop the script and display the error.
	die ('Failed to connect to MySQL: ' . mysqli_connect_error());
}
if ( !isset($_POST['comment']) ) {
	// Could not get the data that should have been sent.
	die ('Please fill the comment field!');
}

if ($stmt = $con->prepare('INSERT INTO comments (content) VALUES (?)')) {
	$stmt->bind_param('s', $_POST['comment']);
    $stmt->execute();
}

$stmt->close();
header('Location: home.php');

?>