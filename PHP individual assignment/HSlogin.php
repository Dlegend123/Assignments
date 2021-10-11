
<?php
session_start();
$username=isset($_SESSION["remember"])?$_SESSION["username"]:null;
$password=isset($_SESSION["remember"])?$_SESSION["password"]:null;
$usernameErr=$passwordErr=$rememberErr="";
$remember=isset($_SESSION["remember"])?$_SESSION["remember"]:null;
$login=isset($_SESSION["login"])?$_SESSION["login"]:"none";
$nLogin=isset($_SESSION["nLogin"])?$_SESSION["nLogin"]:"initial";
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    if (empty($_POST["username"])) {
     $usernameErr = "UserName is required";
  }
  if (empty($_POST["password"])) {
      $passwordErr = "Password is required";
   }
    if(!empty($_POST["remember"])) {
        $_SESSION["remember"]="checked";
        $_SESSION["username"]=$username=$_POST["username"];
        $_SESSION["password"]=$password=$_POST["password"];
    }
if (!empty($_POST["username"])&&!empty($_POST["password"])){
if($_POST["username"]!="HSadmin" || $_POST["password"]!="HSpages123"){
    $passwordErr="Invalid Username and or Password";
}
else{
    $_SESSION["login"]="initial";
    $_SESSION["nLogin"]="none";
    header("Location: HSindex.php", TRUE, 301);
}
}
}


?>
<html>
    <head>
        <link href="Images/Logox.png" rel="shortcut icon" type="image/x-icon" class="img-fluid" />
        <title>HSlogin</title>
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
                    <form class="form-horizontal" method="POST" action = "<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
                        <table  class="table table-dark table-striped table-bordered container-fluid" style="max-width: fit-content;">
                            <tr>
                                
                                <td>
                            <label for="username" style="color:whitesmoke">UserName</label>
                                <input id="username" type="text" class="form-control" name="username" value="<?php echo $username;?>" autofocus>
                                <!-- comment -->
                                <span class="error">
                                        <strong>
                                        <?php echo $usernameErr;?>
                                      <!--{{ $errors->first('username') }}-->
                                      </strong>
                                    </span>
                                </td>
                                </tr>
                        <tr>
                                
                                <td>
                            <label for="password" style="color:whitesmoke">Password</label>

                            <input id="password" type="password" class="form-control" name="password" value="<?php echo $password;?>">

                                <!--@if ($errors->has('password'))-->
                                    <span class="error">
                                        <strong>
                                          <!--{{ $errors->first('password') }}-->
                                        <?php echo "<br>", $passwordErr;?>
                                      </strong>
                                    </span>
                               
                            </td>
                        </tr><!-- comment -->
                        <tr>
                                
                                <td>
                        
                                <div class="checkbox">
                                    <label>
                                        <input type="checkbox" name="remember" <?php echo $remember;?>> Remember Me
                                    </label>
                                </div>
                            </td>
                        </tr><!-- comment -->
<tr>
                                
    <td style="text-align:right">
                        <div class="form-group">
                            <div>
                                <button type="submit" class="btn btn-outline-warning">
                                    Login
                                </button>

                            </div>
                        </div>
                                    </td>
                        </tr><!-- comment -->
                    </form>
<br><!-- comment -->
<br><!-- comment -->
</div>
        <footer class="fixed-bottom border-top border-light bg-dark container-fluid" style="text-align:right;" >
                <p style="margin-bottom: auto;margin-right:20px;color:whitesmoke;font-family:fantasy">&copy;&nbsp;<?php echo date("Y"); ?> - Legacy Institute</p>
            </footer>
    </body>
</html>


      

