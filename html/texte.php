<!DOCTYPE html>
<title >webserv's super html page</title>

<body id =\"all\" style="font-family:'Roboto',sans-serif;margin: 0em; padding: 0em;">
<div class="header" style="display:block; background-color: orange; text-align: center; padding: 15px; "><h1 style="
font-weight: bold;
font-size: 30px;
margin-top: 0px;
margin-bottom: 10px;font-family:'Roboto',sans-serif;  "><a href="home.html" style="text-decoration: none; color: white;">webserv index</a></h1>
</div>

<div class="menu" >
<ul style=" margin: 0em; padding: 0em; list-style-type: none; overflow: hidden; background-color: #333;">
    <li style="float:left;"><a href="home.html" style="display: block; color: white; text-align: center; padding: 14px 16px; text-decoration: none;">accueil</a></li>
    <li style="float:left;"><a href="galerie.html" style="display: block; color: white; text-align: center; padding: 14px 16px; text-decoration: none;">galerie</a></li>
    <li style="float:left;"><a href="texte.php" style="display: block; color: white; text-align: center; padding: 14px 16px; text-decoration: none;">upload text</a></li>
</ul>
</div>

<h2 style="font-family:'Roboto',sans-serif; text-align: center;"> PAGE EXEMPLE TEXTE</h2>
<p style="font-family:'Roboto',sans-serif; text-align: center;"> utilise le menu pour tester des trucs, ca marche super bien</p>

<hr>

<h2 style ="text-align: center;" > TEST DE NOM ET PRENOM</h2>
<p style ="text-align: center;" > dis nous t ki stp</p>

<form style ="text-align: center;" id="nom_form" action="/action_page.php" method="POST">
    <label for="fname">donnes ton prenom</label><br>
    <input style ="text-align: center;" type="text" id="fname" name="fname" value="mon prenom"><br>
    <label for="lname">donnes ton nom</label><br>
    <input  style ="text-align:  center;" type="text" id="lname" name="lname" value="mon nom"><br><br>
    <input type="submit" value="Submit">
  </form> 
  
<hr>





<form style ="text-align: center;"  id="form" action="/uploads/upload_txt.php" method="POST">
    Type text to upload to the server:<br><br>
    <input style ="text-align: center;"  id="form_text" type="text" name="textToUpload"><br><br>
    <input style ="text-align: center;"  type="submit" value="Send text" name="submit">
</form>

</div>

<div id="upload">
<h2 style ="text-align: center;" >Read the text uploaded to the server</h2>

<?php
$file = './tmp_txt.txt';
if (isset($_POST["textToUpload"])) {
    $txt = htmlspecialchars($_POST['textToUpload']);
    file_put_contents($file, $txt);
}
$file = file_get_contents($file, true);
echo "<input id=\"read_box\" type=\"text\" value=\"$file\" readonly>";
?>

</div>









<hr>
<footer style="background-color: orange;
position: absolute;
left: 0;
bottom: 0;
height: 20%;
width: 100%;
overflow: hidden;">
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
