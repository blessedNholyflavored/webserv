<!DOCTYPE html>
<title >webserv's galerie super page</title>

<body id =\"all\" style="font-family:'Roboto',sans-serif;margin: 0em; padding: 0em;">
<div class="header" style="display:block; background-color: orange; text-align: center; padding: 15px; "><h1 style="
font-weight: bold;
font-size: 30px;
margin-top: 0px;
margin-bottom: 10px;font-family:'Roboto',sans-serif;  "><a href="/html/home.html" style="text-decoration: none; color: white;">webserv index</a></h1>
</div>

<div class="menu" >
    <ul style=" margin: 0em; padding: 0em; list-style-type: none; overflow: hidden; background-color: #333;">
        <li style="float:left;"><a href="/html/home.html" style="display: block; color: white; text-align: center; padding: 14px 16px; text-decoration: none;">accueil</a></li>
        <li style="float:left;"><a href="/html/galerie.php" style="display: block; color: white; text-align: center; padding: 14px 16px; text-decoration: none;">galerie</a></li>
        <li style="float:left;"><a href="/html/text.php" style="display: block; color: white; text-align: center; padding: 14px 16px; text-decoration: none;">upload text</a></li>
        <li style="float:left;"><a href="/html/cookies.php" style="display: block; color: white; text-align: center; padding: 14px 16px; text-decoration: none;">Cookies</a></li>
    </ul>
    </div>

<h2 style="font-family:'Roboto',sans-serif; text-align: center;"> Page qui gere les images upload et delete mec</h2>
<p style="font-family:'Roboto',sans-serif;text-align: center;"> utilise le menu pour tester des trucs, ca marche super bien</p>

<div class="column" style="text-align: center ;">
    
    <img style="width:10%; display: block; margin: auto;" src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/8d/42_Logo.svg/2048px-42_Logo.svg.png" id="blah" alt="Img"><br><br>
    <input style="width:10%; display: block; margin: auto; display: inline-block; 
    border:0.16em solid #696969;
    text-decoration:none;
    font-weight:400;
    color:#696969;
    text-align:center;" type="file" id="inputFile" onchange="readUrl(this)">
    <button style="width:10%; display: block; margin: auto; display: inline-block; 
    border:0.16em solid #696969;
    text-decoration:none;
    font-weight:400;
    color:#696969;
    text-align:center;" type="button" onclick="removeImg()">Remove</button>
</div>
	<hr>

	<?php
	$files = scandir('../images');
        foreach ($files as $file) {
        	if ($file !== "." && $file !== "..") {
		echo "<div>";
                $image = "../images/$file";
			
		echo "<img src='$image' style='width:20%';>\n";
		echo "<button type=\"button\" onclick=\"deleteSomething('$image')\">";
                echo "Delete</button>";
                echo "</div>";
		echo "<hr>";
                }
        }
        ?>



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
<script>
        async function deleteSomething(path) {
		await doDelete(path);
                window.location.reload();
	}

        async function doDelete(path) {
                return fetch(path, {
                        method: 'DELETE'
                })
        }
</script>
