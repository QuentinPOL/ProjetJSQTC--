<?php
session_start();
?>

<!DOCTYPE html>
<html lang="fr">
	<head>
		<title>Connexion</title>
		<meta charset="UTF-8">
		<meta name="viewport" content="width=device-width, initial-scale=1">
	<!--===============================================================================================-->	
		<link rel="icon" type="image/png" href="images/icons/favicon.ico"/>
	<!--===============================================================================================-->
		<link rel="stylesheet" type="text/css" href="vendor/bootstrap/css/bootstrap.min.css">
	<!--===============================================================================================-->
		<link rel="stylesheet" type="text/css" href="fonts/font-awesome-4.7.0/css/font-awesome.min.css">
	<!--===============================================================================================-->
		<link rel="stylesheet" type="text/css" href="fonts/iconic/css/material-design-iconic-font.min.css">
	<!--===============================================================================================-->
		<link rel="stylesheet" type="text/css" href="vendor/animate/animate.css">
	<!--===============================================================================================-->	
		<link rel="stylesheet" type="text/css" href="vendor/css-hamburgers/hamburgers.min.css">
	<!--===============================================================================================-->
		<link rel="stylesheet" type="text/css" href="vendor/animsition/css/animsition.min.css">
	<!--===============================================================================================-->
		<link rel="stylesheet" type="text/css" href="vendor/select2/select2.min.css">
	<!--===============================================================================================-->	
		<link rel="stylesheet" type="text/css" href="vendor/daterangepicker/daterangepicker.css">
	<!--===============================================================================================-->
		<link rel="stylesheet" type="text/css" href="css/util.css">
		<link rel="stylesheet" type="text/css" href="css/main.css">
	<!--===============================================================================================-->
	</head>

	<body>
		<div class="limiter">
			<div class="container-login100" style="background-image: url('images/bg-01.jpg');">
				<div class="wrap-login100 p-l-55 p-r-55 p-t-65 p-b-54">
					<form class="login100-form validate-form" id="formConnect">
						<span class="login100-form-title p-b-49">
							Connexion Client
						</span>

						<div class="wrap-input100 validate-input m-b-23" data-validate = "Ce champ ne doit pas être vide">
							<span class="label-input100">Nom d'utilisateur</span>
							<input class="input100" type="text" id="username" maxlength="30" placeholder="Entrez votre nom d'utilisateur">
							<span class="focus-input100" data-symbol="&#xf206;"></span>
						</div>

						<div class="wrap-input100 validate-input" data-validate="Ce champ ne doit pas être vide">
							<span class="label-input100">Mot de passe</span>
							<input class="input100" type="password" id="passwd" maxlength="20" placeholder="Entrez votre mot de passe">
							<span class="focus-input100" data-symbol="&#xf190;"></span>
						</div>

						<div class="container-login100-form-btn p-t-8">
							<div class="wrap-login100-form-btn">
								<div class="login100-form-bgbtn"></div>
								<button class="login100-form-btn">
									Se connecter
								</button>
							</div>
						</div>

						<div class="flex-col-c p-t-20">
							<!-- Informations -->
							<p id="status">Status : Aucun</p>
							<p id="reponse">Réponse : Aucune</p>
							<p id="innner">cookie : Aucune</p>
						</div>

						<div class="txt1 text-center p-t-30 p-b-20">
							<span style="color: black;">
								Bienvenue sur le formulaire de connexion !
							</span>
						</div>

						<div class="flex-col-c">
							<a href="inscription.php" class="txt2">
								Pas inscrit ?
							</a>
						</div>
					</form>
				</div>
			</div>
		</div>
		
	<!--===============================================================================================-->
		<script src="vendor/jquery/jquery-3.2.1.min.js"></script>
	<!--===============================================================================================-->
		<script src="vendor/animsition/js/animsition.min.js"></script>
	<!--===============================================================================================-->
		<script src="vendor/bootstrap/js/popper.js"></script>
		<script src="vendor/bootstrap/js/bootstrap.min.js"></script>
	<!--===============================================================================================-->
		<script src="vendor/select2/select2.min.js"></script>
	<!--===============================================================================================-->
		<script src="vendor/daterangepicker/moment.min.js"></script>
		<script src="vendor/daterangepicker/daterangepicker.js"></script>
	<!--===============================================================================================-->
		<script src="vendor/countdowntime/countdowntime.js"></script>
	<!--===============================================================================================-->
		<script src="https://cdnjs.cloudflare.com/ajax/libs/crypto-js/4.0.0/crypto-js.min.js"></script>
	<!--===============================================================================================-->
		<script src="js/main.js"></script>
		<script src="js/client.js"></script>
	</body>
</html>