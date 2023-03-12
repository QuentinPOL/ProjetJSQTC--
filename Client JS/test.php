<?php
// Démarrer une session
session_start();

// Récupérer l'ID de session
$sessionId = session_id();

// Stocker l'ID de session dans une variable JavaScript
echo "<script>const sessionId = '{$sessionId}';</script>";

echo $sessionId;
?>

