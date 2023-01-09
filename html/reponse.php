<!DOCTYPE html>
<title >webserv's super html page</title>

<style>
  body {
    min-height: 100vh;
    background: #eceffd;
}




.menu1 a:hover{
    background-color:#C8FFD4;
}


.container { 
    position: relative;
  }
  
  .center {
    margin: 0;
    position: absolute;
    top: 50%;
    left: 50%;
    -ms-transform: translate(-50%, -50%);
    transform: translate(-50%, -50%);
  }
/* hightligh */

.container {
    line-height: 1;
    text-align: center;
    padding: 20px;
    color: #333;
  }
  
  h1 {
    font-size: 30px;
  }
  
  p {
    font-size: 13px;
  }
  p small {
    font-size: 80%;
    color: #666;
  }
  
  .highlight-container, .highlight {
    position: relative;
  }
  
  .highlight-container {
    display: inline-block;
  }
  .highlight-container:before {
    content: " ";
    display: block;
    height: 90%;
    width: 100%;
    margin-left: -3px;
    margin-right: -3px;
    position: absolute;
    background: #FDFDBD;
    transform: rotate(2deg);
    top: -1px;
    left: -1px;
    border-radius: 20% 25% 20% 24%;
    padding: 10px 3px 3px 10px;
  }



 .container { 
  height: 100px;
  position: relative;
}


</style>

<body id =\"all\" style="font-family: 'Courier New', Courier, monospace, serif;margin: 0em; padding: 0em; ">

<div class="header" style="display:block; background-color: #B1AFFF; text-align: center; padding: 15px; "><h1 style="
  font-weight: bold;
  font-size: 30px;
  margin-top: 0px;
  margin-bottom: 10px;font-family: 'Courier New', Courier, monospace, serif;  ">
<h1 style="font-weight: bold; font-size: 30px; 
margin-top: 0px; 
margin-bottom: 10px;  "><a style="text-decoration: none;" href="/html/home.html"><span class="highlight-container"><span class="highlight">WEBSERV</span></span></a>
</div>


<div class="menu" style="padding: 0; margin: 0; background-color: #B8E8FC;
text-align: center;" >
    <ul class="menu1" style=" margin: 0em; padding: 0em; list-style-type: none; overflow: hidden; justify-content:center ;">
        <li style="display: inline; list-style: none;"><a href="/html/home.html" style=" display:inline-block; margin: 0 30px; color: #B1AFFF; font-weight: 800; text-align: center; padding: 14px 16px; text-decoration: none;">accueil</a></li>
        <li style="display: inline; list-style: none;"><a href="/html/galerie.php" style=" display:inline-block; margin: 0 30px; color: #B1AFFF; font-weight: 800; text-align: center; padding: 14px 16px; text-decoration: none;">Delete img</a></li>
        <li style="display: inline; list-style: none;"><a href="/html/text.php" style=" display:inline-block; margin: 0 30px; color: #B1AFFF; font-weight: 800; text-align: center; padding: 14px 16px; text-decoration: none;">text</a></li>
        <li style="display: inline; list-style: none;"><a href="/html/cookies.html" style=" display:inline-block; margin: 0 30px; color: #B1AFFF; font-weight: 800; text-align: center; padding: 14px 16px; text-decoration: none;">Cookies</a></li>
        <li style="display: inline; list-style: none;"><a href="/html/upload.php" style=" display:inline-block; margin: 0 30px; color: #B1AFFF; font-weight: 800; text-align: center; padding: 14px 16px; text-decoration: none;">upload img</a></li>
    </ul>
    </div>

<hr>



<p style="font-family: 'Courier New', Courier, monospace, serif; text-align: center; font-size: x-large; font-weight: bold;"> Page qui gere le DELETE mec</p>

<hr>
	

Bonjour, <?php if (isset($_GET['fname'])){echo htmlspecialchars($_GET['fname']);} ?>.
Tu as <?php if (isset($_GET['lname'])){echo $_GET['lname'];} ?> ans.


<hr>
<footer style="  
  right: 0;
  bottom: 0;
  left: 0;
  padding: 1rem;
  background-color: #FFD495;
  text-align: center;">
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
