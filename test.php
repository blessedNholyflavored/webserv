<!DOCTYPE html>
<title >webserv's super html page</title>

<body id =\"all\" style="font-family:'Roboto',sans-serif;margin: 0em; padding: 0em;">
<div class="header" style="display:block; background-color: orange; text-align: center; padding: 15px; "><h1 style="
font-weight: bold;
font-size: 30px;
margin-top: 0px;
margin-bottom: 10px;font-family:'Roboto',sans-serif; color: white;">webserv index</h1>
</div>

<div class="menu" >
<ul style=" margin: 0em; padding: 0em; list-style-type: none; overflow: hidden; background-color: #333;">
    <li style="float:left;"><a href="#" style="display: block; color: white; text-align: center; padding: 14px 16px; text-decoration: none;">accueil</a></li>
    <li style="float:left;"><a href="#" style="display: block; color: white; text-align: center; padding: 14px 16px; text-decoration: none;">galerie</a></li>
    <li style="float:left;"><a href="#" style="display: block; color: white; text-align: center; padding: 14px 16px; text-decoration: none;">upload img</a></li>
    <li style="float:left;"><a href="test.php" style="display: block; color: white; text-align: center; padding: 14px 16px; text-decoration: none;">upload text</a></li>
    <li style="float:left;"><a href="#" style="display: block; color: white; text-align: center; padding: 14px 16px; text-decoration: none;">delete img</a></li>
</ul>
</div>

<h2 style="font-family:'Roboto',sans-serif;"> Bienvenue sur notre page exemple de webserv</h2>
<p style="font-family:'Roboto',sans-serif;"> utilise le menu pour tester des trucs, ca marche super bien</p>

<hr>
<div class="img_and_text" style="background-color: grey;">
    <div class="row" style="box-sizing: border-box;">
     <div class="colonne" style="float: left; width: 33.3%; box-sizing: border-box; padding: 5px;">
        <img src="https://www.pcgames.de/screenshots/1000x562/2022/06/KMA_Kirby_pyramid_transparent-pc-games1.jpg" style="width:100%">
    </div>
      <div class="colonne" style="float: left; width: 33.3%; box-sizing: border-box; padding: 5px;">
        <img src="https://www.pcgames.de/screenshots/1000x562/2022/06/KMA_Kirby_pyramid_transparent-pc-games1.jpg" style="width:100%">
    </div>
      <div class="colonne" style="float: left; width: 33.3%; box-sizing: border-box; padding: 5px;">
        <img src="https://www.pcgames.de/screenshots/1000x562/2022/06/KMA_Kirby_pyramid_transparent-pc-games1.jpg" style="width:100%">
    </div>
    </div>
    <div class="row" style="box-sizing: border-box;">
        <div class="lol" style="float: left; width: 33.3%; box-sizing: border-box; padding: 5px; ">
            <button style="display:inline-block;
            padding:0.5em 3em;
            border:0.16em solid #696969;
            margin:0 0.3em 0.3em 0;
            box-sizing: border-box;
            text-decoration:none;
            text-transform:uppercase;
            font-family:'Roboto',sans-serif;
            font-weight:400;
            color:#696969;
            text-align:center;
            transition: all 0.15s;
            width: 100%;">delete</button>
        </div>
        <div class="lol" style="float: left; width: 33.3%; box-sizing: border-box; padding: 5px;">
            <button style="display:inline-block;
            padding:0.5em 3em;
            border:0.16em solid #696969;
            margin:0 0.3em 0.3em 0;
            box-sizing: border-box;
            text-decoration:none;
            text-transform:uppercase;
            font-family:'Roboto',sans-serif;
            font-weight:400;
            color:#696969;
            text-align:center;
            transition: all 0.15s;
            width: 100%;"> delete</button>
        </div>
        <div class="lol" style=" float: left; width: 33.3%; box-sizing: border-box; padding: 5px;">
            <button style="display:inline-block;
            padding:0.5em 3em;
            border:0.16em solid #696969;
            margin:0 0.3em 0.3em 0;
            box-sizing: border-box;
            text-decoration:none;
            text-transform:uppercase;
            font-family:'Roboto',sans-serif;
            font-weight:400;
            color:#696969;
            text-align:center;
            transition: all 0.15s;
            width: 100%;"> delete</button>
        </div>
    </div>
</div>
<hr>



<div class="corps" style =" margin-left: auto; margin-right: auto; padding: 15px; width: 120px;">
<button style="display:inline-block;
padding:0.5em 3em;
border:0.16em solid #696969;
margin:0 0.3em 0.3em 0;
box-sizing: border-box;
text-decoration:none;
text-transform:uppercase;
font-family:'Roboto',sans-serif;
font-weight:400;
color:#696969;
text-align:center;
transition: all 0.15s;"><a>send</a></button>
</div>

<hr>

<h1> Galerie d'images </h1>


<hr>
<h2> TEST DE NOM ET PRENOM</h2>
<p> dis nous t ki stp</p>

<form id="nom_form" action="/action_page.php" method="POST">
    <label for="fname">donnes ton prenom</label><br>
    <input type="text" id="fname" name="fname" value="mon prenom"><br>
    <label for="lname">donnes ton nom</label><br>
    <input type="text" id="lname" name="lname" value="mon nom"><br><br>
    <input type="submit" value="Submit">
  </form> 
  
<hr>

<?php
$file = './tmp_text.txt';
if(isset($_POST["submit"])) {
  $txt= htmlspecialchars($_POST['fileToUpload']);
  file_put_contents($file, $txt);
  }
  $file = file_get_contents($file, true);
    echo "faut voir";
?>

<h2> Test de ecrire des bails pour le send</h2>
<p> ecris des trucs</p>
<form id="form" action="/uploads/test.php" method="POST">
<input id="texte" type="text" name="textToUpload" style="width: 60%; height:8em;">
<input type="submit" value="Send text" name="submit" style="
padding:0.5em 3em;
border:0.16em solid #696969;
margin:0 0.3em 0.3em 0;

text-decoration:none;
text-transform:uppercase;
font-family:'Roboto',sans-serif;
font-weight:400;
color:#696969;
text-align:center;
transition: all 0.15s;">
</form>



<hr>
<footer style="display: block; position: fixed; bottom: 0; width: 100%;
justify-content: center; padding: 5px; background-color: orange; color: #fff;">
    <h2>The team</h2>
    <p>
        <strong>Lucie Khamlach:</strong>
        <a href="https://profile.intra.42.fr/users/lkhamlac"> Intra Profile</a>
    </p>
    <p>
        <strong>Julien Taravella:</strong>
        <a href="https://profile.intra.42.fr/users/jtaravel"> Intra Profile</a>
    </p>
    <p>
        <strong>Mehdi Mhaya:</strong>
        <a href="https://profile.intra.42.fr/users/mmhaya"> Intra Profile</a>
    </p>
  </footer>
</body>
