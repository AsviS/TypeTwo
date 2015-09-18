How to install and configure for WAMP
=============

## WAMP
1. Install WAMP.
2. Put the contents of this directory into the "www" directory located in the WAMP installation directory, **OR** see [derpderpderp](derpderpderp). 
3. Try starting it WAMP. If the tray icon does not turn green (meaning the server is online), try opening the port 80.

## Configuration 
For the website to function properly, some changes needs to be made to the server's configuration file. Edit the file _wamp\bin\apache\apache2.4.9\conf\httpd.conf_ in a text editor and make the following changes:

### mod_rewrite ###
To enable the mod_rewrite module, uncomment the line that says **"#LoadModule rewrite_module modules/mod_rewrite.so"**. To uncomment it, remove the hash sign at the start of the line.

Go to the _<Directory>_ tag. It should look something like **<Directory "C:/wamp/www/">**, depending on where WAMP was installed. After the line that says "AllowOverride all", insert the following lines:

    RewriteEngine On
    RewriteCond %{REQUEST_FILENAME} !-f
    RewriteCond %{REQUEST_FILENAME} !-d
    RewriteRule .* main.php

### PHP ini values ###
After inserting the Rewrite lines in the previous section. Insert the following right after those lines:

    php_value mysqli.default_host		"THE HOST OF THE DATABASE"
    php_value mysqli.default_user		"USER TO CONNECT TO THE DATABASE WITH"
    php_value mysqli.default_pw 		"USER'S PASSWORD TO THE DATABASE"

The content in the strings are of course supposed to be replaced by the actual host, user and password used to connect to the database.

### Set the Document Root directory to the repository's "Webb" directory (Optional) ###
This has nothing to do with the functionality of the server. Doing this will just make it a lot more easier, since all files will be located in the repository and the files will not have to be copied over to the repository everytime a change is to be commited.

Find the line that says something like **DocumentRoot "C:/wamp/www/"**, depending on where WAMP was installed. Change the path to the "Webb" directory in the local repository.

Do the same for the path in the _<Directory>_ tag covered in the [mod_rewrite](derpderpderp) section.
