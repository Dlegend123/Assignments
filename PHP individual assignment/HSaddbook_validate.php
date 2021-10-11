<?php

session_start();
$titleErr=$authorErr =$bCoverErr= $yearErr ="";
$title=isset($_SESSION["title"])?$_SESSION["title"]:"";
$author=isset($_SESSION["author"])?$_SESSION["author"]:"";
$bCover=isset($_SESSION["bCover"])?$_SESSION["bCover"]:null;
$year  =isset($_SESSION["year"])  ?$_SESSION["year"]:"";
$login=isset($_SESSION["login"])?$_SESSION["login"]:"none";
$nLogin=isset($_SESSION["nLogin"])?$_SESSION["nLogin"]:"initial";


         if ($_SERVER["REQUEST_METHOD"] == "POST") {
            
            
            
            if (empty($_POST["title"])) {
               $titleErr = "Title is required";
            }else {
                $_SESSION["title"]=$title= test_input($_POST["title"]);
            }
            if (empty($_POST["author"])) {
                $authorErr = "Author is required";
             }else {
                $_SESSION["author"]=$author=test_input($_POST["author"]);
             }
            if (empty($_POST["year"])) {
                $yearErr = "Year Published is required";
             }else {
                $_SESSION["year"]=$year=test_input($_POST["year"]);
             }
             if ($_FILES["bCover"]["size"]==0) {
                $bCoverErr = "Book cover image is required";
             }
             else{
             if(isset($_FILES["bCover"]["name"])){
                  
                    $target_dir = "CoverImages/";
                    $filepath = "CoverImages/".$_FILES["bCover"]["name"];
                    $filepath1 = "CoverImages/".$_FILES["bCover"]["tmp_name"];
         $target_file = $target_dir. basename($_FILES["bCover"]["name"]);
         $filename = $_FILES["bCover"]["name"];
        $folder = "CoverImages/".$filename;
        
        $imageFileType = strtolower(pathinfo($target_file,PATHINFO_EXTENSION));
            $check = getimagesize($_FILES["bCover"]["tmp_name"]);
            
                if($check !== false) {
                    move_uploaded_file($_FILES["bCover"]["tmp_name"], $folder);
                    $uploadOk = 1;
                    $_SESSION["bCover"]=$bCover=$filepath;
                }
                else{
                    if($check == false) {
                    $bCoverErr = "File is not an image.";
                    }
                }
                if (file_exists($target_file)&&$_SESSION["bCover"]!=$filepath) {
                    $bCoverErr = "Sorry, file already exists.";
                  }
              $uploadOk = 0;
             }
             }
             
             if(isset($_SESSION["title"])&&isset($_SESSION["author"])&&isset($_SESSION["bCover"])&&isset($_SESSION["year"])&&isset($_SESSION["bCover"])){
                 header("Location: HSaddbook2.php");
             }
             
                 
        }
            
         function test_input($data) {
            $data = trim($data);
            $data = stripslashes($data);
            $data = htmlspecialchars($data);
            return $data;
         }
?>


