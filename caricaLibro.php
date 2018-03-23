<!DOCTYPE html> 
	<?php
   		include('header.php');
   	?> 
   
   <style>
    	#img{
        	width: 100%;
            background-color: grey;
            
        }
        
        .custom-file-input{
        display: inline-block;
		overflow: hidden;
        position: relative;
    }
    .custom-file-input input[type="file"]{
        width: 100%;
        height: 100%;
        opacity: 0;
        filter: alpha(opacity=0);
       
        position: absolute;
        top: 0;
        left: 0;
        z-index: 999;
    }
        
      
    </style>
     <script src="https://code.jquery.com/jquery-1.12.4.min.js"></script>
		<script type="text/javascript">
    	$(document).ready(function(){
        $('.custom-file-input input[type="file"]').change(function(e){
            $(this).siblings('input[type="text"]').val(e.target.files[0].name);
        });
    });
	</script>
    
   		
   	<div id= "img" class= "">
   
   	</div>
    <div class="col-sm-offset-5 col-sm-3"> 
      <h1>Carica libro</h1> 
	  </div>
    <form action="" class="form-horizontal" role="form" method="post"> 
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
         <input type="text" class="form-control" name="txtISBN"> 
         <p></p>
      </div> 
   </div> 
   <div> 
      <label for="txtNumeroPagine" class="col-sm-5 control-label">Numero pagine</label> 
      <div class="col-sm-3"> 
         <input type="text" class="form-control" name="txtNumeroPagine"> 
         <p></p>
      </div> 
   	</div> 
    <div>
     <label for="txtSelezionaImmagine" class="col-sm-5 control-label">Seleziona immagine:</label> 
     	<div class="col-sm-3"> 
    	 <div class="custom-file-input">
            <input type="file">
            <input type="text">
            <input type="button" value="Attach">
        </div>
        </div> 
        <p></p>
   </div> 

   <div class="col-sm-offset-5 col-sm-7">
    		<button type="submit" class="btn btn-primary">Conferma</button> 
			<button type="button" class="btn btn-danger" data-dismiss="modal">Annulla</button>
   		</div>
	<?php	
		include('footer.php');
	?>
</html>