<!DOCTYPE HTML>
<html lang="fr">
  <head>
  <meta charset="utf-8">
  <title>Page d'accueil de connexion PHP</title>
  <link href='/sessions/style.css' type="text/css" rel="stylesheet">
  </head>
  <body>
    <h1 class="center">Accueil</h1>
    <p class="center">Merci de vous connecter avec votre identifiant (<i>test</i>) et votre 
    mot de passe (<i>pass</i>).</p>

    <form accept="text/html" method="POST" accept-charset="utf-8" action="http://localhost/test.php"
      name="formulaire">
    <table class="center">
     <tr>
      <td>Identifiant :</td>
      <td><input name="identifiant" type="text"></td>
     </tr>
     <tr>
      <td>Mot de passe :</td>
      <td><input name="motdepasse" type="password"></td>
     </tr>
     <tr>
      <td colspan="2" style="padding-top:20px;text-align:center;"><input name="connexion" type="submit" value="Se
        connecter"> </td>
     </tr>
    </table>
    </form>
<?php 
  if ( ! empty($message_erreur) ) { echo $message_erreur; }
?>
  </body>
  
<?php
// Lieu de la création de la session 
session_save_path('C:\TEMP');
// Nom de la session 
session_name('SessionPHP');
// Création de la session 
session_start();

// Vérification de la session
if ( isset($_SESSION["identifiant"]) and ($_SESSION["identifiant"] == "test") )  {
  // OK
}
else {
  header('Location: http://localhost/test.php');
  exit;
}

?>

  <head>
  <meta charset="utf-8">
  <title>PHP : &Eacute;tape 1</title>
  <link href='/sessions/style.css' type="text/css" rel="stylesheet">
  </head>
  <body>
    <h1 class="center">Accueil - &eacute;tape 1</h1>
    <div class="deconnexion"><a href="/sessions/deconnexion.php">Se d&eacute;connecter</a></div>
    <p>
    Bonjour <b><?php echo $_SESSION["identifiant"]; ?></b><br>
    Demandons &agrave; Perl la date du jour : <a href="http://localhost/date.pl">ici</a>.

    <hr>
    Variable session : <?php print_r($_SESSION); ?>

  </body>
</html>
