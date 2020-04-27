<?php
$servername = "localhost";
    $dns        = "mysql:host=$servername;";
    $dbuser     = "root";
    $dbpass     = "";
    $dboption   = array(
        PDO::MYSQL_ATTR_INIT_COMMAND => "set NAMES utf8",
    );

    try{// start connection with database useing PDO Object
        $con = new PDO($dns, $dbuser, $dbpass, $dboption);
        $con->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        // create data base
        $sql ="CREATE DATABASE IF NOT EXISTS fishshop CHARACTER SET utf8 COLLATE utf8_general_ci;";
        $con->exec($sql);
       // echo "Database created successfully<br>";
        // create users table 
            $sql = "CREATE TABLE IF NOT EXISTS fishshop.users (
            Id int(11) PRIMARY KEY AUTO_INCREMENT NOT NULL,
            userName VARCHAR(255) CHARACTER SET utf8 COLLATE utf8_general_ci UNIQUE NOT NULL,
            password VARCHAR(255) CHARACTER SET utf8 COLLATE utf8_general_ci,
            email VARCHAR(255) CHARACTER SET utf8 COLLATE utf8_general_ci UNIQUE NOT NULL,
            fullName VARCHAR(255) CHARACTER SET utf8 COLLATE utf8_general_ci,
            img VARCHAR(255) CHARACTER SET utf8 COLLATE utf8_general_ci,
            groupId int(11) DEFAULT 0 NOT NULL,
            trustStatus int(11) DEFAULT 0 NOT NULL,
            regStatus int(11) DEFAULT 0 NOT NULL,
            regDate datetime NOT NULL,
            lastVisit datetime NOT NULL);"; 
        $con->exec($sql);
           // echo "user table created successfully<br>";
            // create Categories table 
        $sql = "CREATE TABLE IF NOT EXISTS fishshop.categories (
            Id int(11) PRIMARY KEY AUTO_INCREMENT NOT NULL,
            catName VARCHAR(255) CHARACTER SET utf8 COLLATE utf8_general_ci UNIQUE NOT NULL,
            description VARCHAR(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
            catorder int(11) UNIQUE  NOT NULL,
            visibility tinyint(11) DEFAULT 0 NOT NULL,
            commallow tinyint(11) DEFAULT 0 NOT NULL,
            regStatus tinyint(11) DEFAULT 0 NOT NULL,
            addDate datetime NOT NULL,
            lastmodified datetime);"; 
        $con->exec($sql);
           // echo "categories table created successfully<br>";
            // create sections table 
        $sql = "CREATE TABLE IF NOT EXISTS fishshop.sections (
            Id int(11) PRIMARY KEY AUTO_INCREMENT NOT NULL,
            secName VARCHAR(255) CHARACTER SET utf8 COLLATE utf8_general_ci UNIQUE NOT NULL,
            visibility tinyint(11) DEFAULT 0 NOT NULL,
            catName VARCHAR(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
            addDate datetime NOT NULL,
            lastmodified datetime,
            FOREIGN KEY (catName) REFERENCES fishshop.categories(catName) ON UPDATE CASCADE ON DELETE CASCADE);"; 
        $con->exec($sql);
           // echo "sections table created successfully<br>";
            // create items table 
            $sql = "CREATE TABLE IF NOT EXISTS fishshop.items (
            Id int(11) PRIMARY KEY AUTO_INCREMENT NOT NULL,
            itemName VARCHAR(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
            description TEXT CHARACTER SET utf8 COLLATE utf8_general_ci,
            price int(11) NOT NULL,
            visibility tinyint(11) DEFAULT 0 NOT NULL,
            commallow tinyint(11) DEFAULT 0 NOT NULL,
            rating tinyint(11) DEFAULT 0 NOT NULL,
            imge VARCHAR(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
            user VARCHAR(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
            cat VARCHAR(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
            sec VARCHAR(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
            addDate datetime NOT NULL,
            lastmodified datetime,
            FOREIGN KEY (user) REFERENCES fishshop.users(userName) ON UPDATE CASCADE ON DELETE CASCADE,
            FOREIGN KEY (cat) REFERENCES fishshop.categories(catName) ON UPDATE CASCADE ON DELETE CASCADE,
            FOREIGN KEY (sec) REFERENCES fishshop.sections(secName) ON UPDATE CASCADE ON DELETE CASCADE);"; 
        $con->exec($sql);
           // echo "items table created successfully<br>";
          //  create admin to access to dashbord
        $stmt = $con->prepare("SELECT userName  FROM fishshop.users WHERE userName = ?  And groupId =1");
        $stmt->execute(array("maged"));
        $count = $stmt->rowCount();
        if ($count == 0) {
            $sql ="INSERT INTO fishshop.users (userName, password, email , fullName, groupId, trustStatus, regStatus, regDate)
                 VALUES ('maged', sha1('0101830204'), 'maged.fawzy09@gmail.com', 'maged fawzy mohamed', '1', '1', '1', CURRENT_TIMESTAMP());";
                   $con->exec($sql);
                  // echo "admin created successfully<br>";
        }else{
            //echo "admin already created successfully<br>";
        }
        

    }catch(PDOException $e){
    echo $sql . "<br>" . $e->getMessage();
    }

$conn = null;
?>
