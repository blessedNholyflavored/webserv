<!DOCTYPE html>
<title >webserv's super html page</title>

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
    <li style="float:left;"><a href="/html/cookies.html" style="display: block; color: white; text-align: center; padding: 14px 16px; text-decoration: none;">Cookies</a></li>
    <li style="float:left;"><a href="/html/upload.php" style="display: block; color: white; text-align: center; padding: 14px 16px; text-decoration: none;">Upload image</a></li>
</ul>
</div>

<h2 style="font-family:'Roboto',sans-serif;text-align: center;"> ca fonctionne c tiptoptap</h2>

<hr>
	

Bonjour, <?php if (isset($_GET['fname'])){echo htmlspecialchars($_GET['fname']);} ?>.
Tu as <?php if (isset($_GET['lname'])){echo $_GET['lname'];} ?> ans.


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
  </footer>
</body>
</html>
