<?php
session_start();

$title=isset($_SESSION["title"])?$_SESSION["title"]:"";
$author=isset($_SESSION["author"])?$_SESSION["author"]:"";
$bCover=isset($_SESSION["bCover"])?$_SESSION["bCover"]:"";
$year  =isset($_SESSION["year"])  ?$_SESSION["year"]:"";
$isbn=isset($_SESSION["isbn"])?$_SESSION["isbn"]:"";
$cNum=isset($_SESSION["cNum"])?$_SESSION["cNum"]:"";
$nCopies=isset($_SESSION["nCopies"])?$_SESSION["nCopies"]:"0";
$sArea=isset($_SESSION["sArea"])?$_SESSION["sArea"]:"";
$login=isset($_SESSION["login"])?$_SESSION["login"]:"none";
$nLogin=isset($_SESSION["nLogin"])?$_SESSION["nLogin"]:"initial";
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $myfile = fopen("HSbookdata.txt", "a");
    fwrite($myfile, "Title: ".$title.="\n");
    fwrite($myfile, "Author: ".$author.="\n");
    fwrite($myfile, "Year Published: ".$year.="\n");
    fwrite($myfile, "ISBN: ".$isbn.="\n");
    fwrite($myfile, "Book Cover: ".$bCover.="\n");
    fwrite($myfile, "Number of Copies: ".$nCopies.="\n");
    fwrite($myfile, "Subject Area: ".$sArea.="\n");
    fclose($myfile);
}

?>
<html>
    <head>
        <link href="Images/Logox.png" rel="shortcut icon" type="image/x-icon" class="img-fluid" />
        <title>HSresults</title>
        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <script src="jquery/dist/jquery-3.2.1.slim.min.js"></script>
        <link href="bootstrap/css/bootstrap.min.css" rel="stylesheet">
        <script src="bootstrap/js/bootstrap.bundle.min.js"></script>

        <style>
         .error {color: #FF0000;}
         body{
            background-image: url('Images/little.jpg');
            background-size:cover;
            margin:0;
            height:100%;
            width:100%;
         }
      </style>
    </head>
    <body>
        <header >
        <nav class="navbar navbar-expand-lg navbar-dark bg-dark navbar-static-top">
<nav class="navbar navbar-expand-lg navbar-dark bg-dark navbar-static-top">
            <div class="container-fluid">
                
                    <a class="navbar-brand" aria-current="page" href="HSindex.php">
                        <img src="Images/Logox.png" style="padding-right:1em; border-right:1px solid;height:30px;width:45px;" />
                    </a>
            
                    
            <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
                <span class="navbar-toggler-icon"></span>
            </button>
          
                <div class="collapse navbar-collapse" id="navbarNav">
                  <ul class="navbar-nav me-auto mb-2 mb-lg-0">
                    <li class="nav-item" >
                      <a class="nav-link active" aria-current="page" href="HSindex.php" style="font-size:larger" >Home</a>
                    </li>
                      <li class="nav-item" style="display: <?php echo $login; ?>">
                      <a class="nav-link" href="HSaddbook.php" style="font-size:larger" >Add Book</a>
                    </li>
                    <li class="nav-item" style="text-align:right;display: <?php echo $nLogin; ?>">
                      <a class="nav-link" href="HSlogin.php" style="font-size:larger;" >Login</a>
                    </li>

                  </ul>
                    
                </div>
                
            </div>
        </nav>

</header>
        <div class="container">
            <br><!-- comment -->
            <br><!-- comment -->
            <form method = "post" action = "<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>" enctype="multipart/form-data" >
            <table  class="table table-dark table-striped table-bordered container-fluid" style="max-width: fit-content;">
            <tr>
                <td>
                    <h4 style="">Title </h4>
                    <label><?php echo $title;?> </label>
                    
               </td>
               <td rowspan="7" style="vertical-align: text-top">
                   <h4>Book Cover </label><h4>
                   <div style="height: 100%;vertical-align: middle">
                   <img src="<?php echo $bCover ?>" class="img-fluid" style="max-height: inherit;max-width: 40vw"> 
                   </div>
               </td>
            </tr>
            <tr>
               <td>
                   <h4>Author </h4>
                   <label><?php echo $author;?> </label>
               </td>
            </tr>
            <tr>
               <td>
                   <h4>Year Published </h4>
                   <label><?php echo $year;?> </label>
               </td>
            </tr>


            <tr>
                <td>
                    <h4>ISBN </h4>
                    <label><?php echo $isbn;?> </label>
               </td>
            </tr>
            <tr>
               <td>
                   <h4>Call Number </h4>
                   <label><?php echo $cNum;?> </label>
               </td>
            </tr>
            <tr>
               <td>
                   <h4>Subject Area </h4>
                   <label><?php echo $sArea;?> </label>
               </td>
            </tr>

            <tr>
               <td>
                   <h4>Number of Copies </h4>
                   <label><?php echo $nCopies;?> </label>
               </td>
            </tr>
            <tr>
                <td colspan="2" style="text-align:right">
                    <button type="submit" class="btn btn-outline-warning" name="submit">
                                    Save
                                </button>
                </td>
            </tr>
         </table>
            </form>
            <br><!-- comment -->
            <br><!-- comment -->
        </div>
        <footer class="fixed-bottom border-top border-light bg-dark container-fluid" style="text-align:right;" >
                <p style="margin-bottom: auto;margin-right:20px;color:whitesmoke;font-family:fantasy">&copy;&nbsp;<?php echo date("Y"); ?> - Legacy Institute</p>
            </footer>
    </body>
</html>
