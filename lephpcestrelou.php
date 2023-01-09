<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>PHP File Upload</title>
</head>
<body>
    <form action="./upload.php" method="post" enctype="multipart/form-data">
        Upload a File:
        <input type="file" name="the_file" id="fileToUpload">
        <input type="submit" name="submit" value="Start Upload">
    </form>

    <?php
    $uploadDirectory = '../images';

    $errors = []; // Store errors here

    $fileExtensionsAllowed = ['jpeg','jpg','png']; // These will be the only file extensions allowed 

    $fileName = $_FILES['the_file']['name'];
    $fileTmpName  = $_FILES['the_file']['tmp_name'];
    $fileType = $_FILES['the_file']['type'];
    $fileExtension = strtolower(end(explode('.',$fileName)));
    echo full_path($fileName);
    echo $_FILES['the_file']['name'];
    $uploadPath = $uploadDirectory . basename($fileName); 
    $test = fopen(".test", "w+");
    fwrite($test, $_FILES['the_file']['name']);

    if (isset($_POST['submit'])) {

      if (! in_array($fileExtension,$fileExtensionsAllowed)) {
        $errors[] = "This file extension is not allowed. Please upload a JPEG or PNG file";
      }

      if (empty($errors)) {
        $didUpload = move_uploaded_file($fileTmpName, $uploadPath);

        if ($didUpload) {
          echo "The file " . basename($fileName) . " has been uploaded";
        } else {
          echo "An error occurred. Please contact the administrator.";
        }
      } else {
        foreach ($errors as $error) {
          echo $error . "These are the errors" . "\n";
        }
      }

    }
?>

</body>
</html>
