<?php
session_start();
$isbnErr=$cNumErr = $sAreaErr =$nCopiesErr="";
$isbn=isset($_SESSION["isbn"])?$_SESSION["isbn"]:"";
$cNum=isset($_SESSION["cNum"])?$_SESSION["cNum"]:"";
$nCopies=isset($_SESSION["nCopies"])?$_SESSION["nCopies"]:"";
$sArea=isset($_SESSION["sArea"])?$_SESSION["sArea"]:"";
$login=isset($_SESSION["login"])?$_SESSION["login"]:"none";
$nLogin=isset($_SESSION["nLogin"])?$_SESSION["nLogin"]:"initial";

if ($_SERVER["REQUEST_METHOD"] == "POST") {

    if (empty($_POST["isbn"])) {
       $isbnErr = "ISBN is required";
    }else 
    {      
        if(!is_isbn($_POST["isbn"])){
            $isbnErr = "Invalid ISBN";
        }
        else{
            $_SESSION["isbn"]=$isbn = test_input($_POST["isbn"]);
        }
    }
    if (empty($_POST["cNum"])) {
        $cNumErr = "Call Number is required";
     }else {
        $_SESSION["cNum"]=$cNum = test_input($_POST["cNum"]);
     }
      if (empty($_POST["nCopies"])) {
        $nCopiesErr = "Number of Copies is required";
     }else {
        $_SESSION["nCopies"]=$nCopies = test_input($_POST["nCopies"]);
     }
     if (empty($_POST["sArea"])) {
        $sAreaErr = "Subject Area is required";
     }else {
        $_SESSION["sArea"]=$sArea = test_input($_POST["sArea"]);
     }
     if(isset($_SESSION["sArea"])&&isset($_SESSION["nCopies"])&&isset($_SESSION["cNum"])&&isset($_SESSION["isbn"])){
         header("Location: HSresults.php", TRUE, 301);
     }
 }

    function test_input($data) {
       $data = trim($data);
       $data = stripslashes($data);
       $data = htmlspecialchars($data);
       return $data;
    }
     
function isbn_sum($isbn, $len) 
{ 
    $sum = 0; 
    if ($len == 10) { 
        for ($i = 0; $i < $len-1; $i++) { 
            $sum = $sum + (int)$isbn[$i] * ($len - $i); 
        } 
    } 
    elseif ($len == 13) { 
        for ($i = 0; $i < $len-1; $i++) { 
            if ($i % 2 == 0) {
                $sum = $sum + (int)$isbn[$i]; 
            }
            else {
                $sum = $sum + (int)$isbn[$i] * 3; 
            }
        } 
    } 
    return $sum; 
} 
function isbn_compute($isbn, $len) 
{ 
    if ($len == 10){ 
        $digit = 11 - isbn_sum($isbn, $len) % 11; 
        if ($digit == 10){ 
            $rc = 'X'; 
        }
        else if ($digit == 11){ 
            $rc = '0'; 
        }
        else{ 
            $rc = (string)$digit;
        }
    } 
    else if($len == 13){ 
        $digit = 10 - isbn_sum($isbn, $len) % 10; 
        if ($digit == 10){ 
            $rc = '0'; 
        }
        else{ 
            $rc = (string)$digit;
        }
    } 
    return $rc; 
} 
function is_isbn($isbn) 
{ 
    $len = strlen($isbn); 
    if ($len!=10 && $len!=13){ 
        return 0; 
    }
    $rc = isbn_compute($isbn, $len); 
    if ($isbn[$len-1] != $rc){  
        return 0; 
    }
    else{ 
        return 1;
    }
} 

?>
