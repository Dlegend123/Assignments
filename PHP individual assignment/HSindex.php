<!doctype html>
<?php 
session_start();
$login=isset($_SESSION["login"])?$_SESSION["login"]:"none";
$nLogin=isset($_SESSION["nLogin"])?$_SESSION["nLogin"]:"initial";

?>
<html >
    <head>
        <link href="Images/Logox.png" rel="shortcut icon" type="image/x-icon" class="img-fluid" />
        <title>HSindex</title>
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
        <div class="container" style="vertical-align:middle">
  <br/>
  <br/>
  <h1 style="color:whitesmoke;text-align:center;font-weight: bold">Welcome</h1>
  <h4 style="color:whitesmoke;text-align:center;font-weight: bold">
      Welcome to Legacy Institute library online 
  </h4>
  <br/>
  <br/>
      </div>
        <footer class="fixed-bottom border-top border-light bg-dark container-fluid" style="text-align:right;" >
                <p style="margin-bottom: auto;margin-right:20px;color:whitesmoke;font-family:fantasy">&copy;&nbsp;<?php echo date("Y"); ?> - Legacy Institute</p>
            </footer>
    </body>
</html>
