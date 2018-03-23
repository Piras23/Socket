<!DOCTYPE html> 
	<?php
   		include('header.php');
      include('conn.php');     
      $errore=""; 
      if($_SERVER["REQUEST_METHOD"] == "POST") {
        $username=$_SESSION["login_user"];
        $titolo=$_POST["txtTitolo"];
        $autore=$_POST["txtAutore"];
        $isbn=$_POST["txtISBN"];
        $pag=$_POST["txtNumeroPagine"];
        $target_dir = "imgUpload/";
        $target_file = $target_dir . basename($_FILES["fileToUpload"]["name"]);
        $uploadOk = 1;
        $imageFileType = strtolower(pathinfo($target_file,PATHINFO_EXTENSION));
        // Check if image file is a actual image or fake image
        if(isset($_POST["submit"])) {
            $check = getimagesize($_FILES["fileToUpload"]["tmp_name"]);
            if($check !== false) {
                $errore = "File is an image - " . $check["mime"] . ".";
                $uploadOk = 1;
            } else {
                $errore = "File is not an image.";
                $uploadOk = 0;
            }
        }
        // Check if file already exists
        if (file_exists($target_file)) {
            $errore = "Sorry, file already exists.";
            $uploadOk = 0;
        }
        // Check file size
        if ($_FILES["fileToUpload"]["size"] > 500000) {
            $errore = "Sorry, your file is too large.";
            $uploadOk = 0;
        }
        // Allow certain file formats
        if($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg"
        && $imageFileType != "gif" ) {
            $errore = "Sorry, only JPG, JPEG, PNG & GIF files are allowed.";
            $uploadOk = 0;
        }
        // Check if $uploadOk is set to 0 by an error
        if ($uploadOk == 0) {
           // $errore = "Sorry, your file was not uploaded.";
        // if everything is ok, try to upload file
        } else {
            if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
                $errore = "The file ". basename( $_FILES["fileToUpload"]["name"]). " has been uploaded.";
            } else {
                $errore="Sorry, there was an error uploading your file.";+
                $uploadOk = 0;
            }
        }
        




        $percorso = $target_file;
        if ($uploadOk == 1) {
          try{
              $stmSql = $conn->prepare("INSERT INTO book (ISBN, Titolo, Autore, NumPagine, Immagine, Username) VALUES(?,?,?,?,?,?)");
              $stmSql->bindParam(1, $isbn);
              $stmSql->bindParam(2, $titolo);
              $stmSql->bindParam(3, $autore);
              $stmSql->bindParam(4, $pag);
              $stmSql->bindParam(5, $percorso);
              $stmSql->bindParam(6, $username);
              $risultato = $stmSql->execute();
          }catch(PDOException $ex){
              $errore="*Errore catch2";
          }
            if($risultato){
              header("Location: profilo.php");
            }else{
              $errore = "Errore nell'aggiornamento dell'immagine del profilo";
            }
        }
      }
   	?> 
   <!--	<style>
    	#img{
        	width: 100%;
            background-color: grey;
            
        }
   		
   	<div id= "img" class= "">
   
   	</div>-->
    <div class="col-sm-offset-5 col-sm-3"> 
      <h1>Carica libro</h1> 
	  </div>
    <form action="" class="form-horizontal" role="form" method="post" enctype="multipart/form-data"> 
   <div> 
      <label for="txtTitolo" class="col-sm-5 control-label">Titolo*</label> 
      <div class="col-sm-3"> 
         <input type="text" class="form-control" name="txtTitolo"> 
         <p></p>
      </div> 
   </div> 
   <div> 
      <label for="txtAutore" class="col-sm-5 control-label">Autore*</label> 
      <div class="col-sm-3"> 
         <input type="text" class="form-control" name="txtAutore"> 
         <p></p>
      </div> 
   </div> 
   <div> 
      <label for="txtISBN" class="col-sm-5 control-label">ISBN*</label> 
      <div class="col-sm-3"> 
         <input type="text" maxlength="13" class="form-control" name="txtISBN"> 
         <p></p>
      </div> 
   </div> 
   <div> 
      <label for="txtNumeroPagine" class="col-sm-5 control-label">Numero pagine</label> 
      <div class="col-sm-3"> 
         <input type="number" class="form-control" name="txtNumeroPagine"> 
         <p></p>
      </div> 
   </div> 
    Select image to upload:
    <input type="file" name="fileToUpload" id="fileToUpload">
   <br>
   <?php
    echo $errore;
    ?>
   <div class="col-sm-offset-5 col-sm-7">
    		<button type="submit" values="fileToUpload" class="btn btn-primary">Conferma</button> 
			<button type="button" class="btn btn-danger" data-dismiss="modal">Annulla</button>
   		</div>
	<?php	
		include('footer.php');
	?>
</html>
