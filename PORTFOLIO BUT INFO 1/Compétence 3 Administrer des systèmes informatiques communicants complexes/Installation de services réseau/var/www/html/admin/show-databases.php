<?php 
    $sql="SHOW DATABASES"; 
    $link = mysqli_connect('127.0.0.1', 'root', 'lannion') or die ('Error connecting to mysql: ' . mysqli_error($link).'\r\n'); 
    
    if (!($result=mysqli_query($link,$sql))) { 
            printf("Error: %s\n", mysqli_error($link)); 
    } 
    
    while( $row = mysqli_fetch_row( $result ) ){ 
            if (($row[0]!="information_schema") && ($row[0]!="mysql")) { 
                echo $row[0]."<br/>\r\n"; 
            } 
    } 
?>