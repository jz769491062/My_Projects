##Author:Zihan Zhu
This is an inheritance/polymorphism, interface and GUI design exercise under the disguise of employees accessing files.<br>
Users' name,type and password are listed in Employee_Access\x64\Debug.<br>
The files they could access are listed in Employee_Access\x64\Debug\words.<br>
When logged in as Admin, you can change,add and delete non-Admin users' profile.<br>
Default Admin Username: d Password: 4 . <br>
Single click selected cell to directly modify user's profile, and double click quickly to modify a user's file accessibility.<br>
When logged in as non-Admin users, you can see certain files based on your type and Admin's permission.<br>
See default user information in Employee_list.txt or Employee_list.db.<br>
See what files each occupation can access in Employee_words.txt or Employee_list.db.<br>
By default, all managers can see workers' and chiefs' files, and all chiefs can see workers' files.<br>
To access information in db config file, change words in TXT_OR_DB.txt to DB. <br>
To access information in txt config files, change words in TXT_OR_DB.txt to TXT. <br>
Notice that the information in db and txt config files are independent. Changes in the db file will not reflect in txt files, and vice versa.<br>