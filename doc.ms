.ns VS 15p
.ds FAM LinLibertine
.nr PS 15p
.TL
Library App
.AU
Александър Хаджиев № 3
.br
Михаил Димитров № 15
.AL
ТУЕС
.AS
11 \*{A\*}
.SH
Описание:
.PP
Приложение за библиотека в терминала подобно на Calibre с UI написан на
.I ncurses .
То ще позволява добавяне на книги в колекции определени от потребителя, като всяка колекция ще се намира в определена папка. Потребителя ще може да зададе заглавие, автор, издател, година на издаване, и колекция, за всяка книга, като тази информация ще бъде използване за да се преименува файла
.I "(това ще позволи универсалност на наименованията на файловете)" .
Във всяка колекция списъкът с книги ще може да бъде сортиран по категориите изброени преди малко.
.PP
Тъй като приложението е в терминала ползването не мишката ще бъде ненужно и затова всяка функционалност ще бъде направена да бъде различен
.I shortcut .
.SH
Technologies:
.RS
.IP \[bu] 2
C
.IP \[bu] 2
MySQL / MariaDB
.IP \[bu] 2
ncurses Library
.IP \[bu] 2
Shell script [ + awk]
.I "(If needed)" .
.IP \[bu] 2
CMake
.RE
.SH
Management:
.RS
.IP \[bu] 2
Git Flow - Github / GitLab ?
.IP \[bu] 2
Kanban / Scrum ?
.IP \[bu] 2
Mandatory code reviews
.RE
.bp
.SH
First Milestone:
.nr step 1 1
.RS
.IP \n[step]. 3
Create MySQL database and functionalities:
.RS
.IP \[bu] 2
Init function.
.IP \[bu] 2
Create
.I (Insert)
function.
.IP \[bu] 2
Update function.
.IP \[bu] 2
Delete function.
.IP \[bu] 2
Select functions.
.RE
.IP \n+[step]. 3
Function to get the pagecount of a PDF.
.IP \n+[step]. 3
Time to reasearch the ncurses library.
.IP \n+[step]. 3
Time to research CMake.
.RE
.SH
Second Milestone:
.nr step 1 1
.RS
.IP \n[step]. 3
Add the ability to sort books by author, title, publisher, and year published.
.IP \n+[step]. 3
Create the UI for collections and books + keybinds:
.RS
.IP \[bu] 2
UI for the collections and the list of books.
.IP \[bu] 2
Keybinds for sorting by category (author, title, publisher, year published).
.RE
.IP \n+[step]. 3
Make it so that each file is renamed with their respective author, title and publisher
.I "(The pattern will be the same for every collection and/file file)" .
.RE
.SH
Third Milestone:
.nr step 1 1
.RS
.IP \n[step]. 3
The ability to add books from the UI.
.IP \n+[step]. 3
The ability to edit and delete books from the UI.
.IP \n+[step]. 3
Cleaning up the UI.
.IP \n+[step]. 3
Bug fixes.
.IP \n+[step]. 3
Unit tests.
.RE
.bp
.SH
Additional Tasks:
.nr step 1 1
.RS
.IP \n[step]. 3
Man page.
.IP \n+[step]. 3
Config.h\*{[1]\*}
.I "(Simular to how you configure the suckless programs)" .
.IP \n+[step]. 3
Reading and redacting the metadata of a PDF.
.IP \n+[step]. 3
The ability to search a directory added by the user and add all books from this folder to the database and default collection.
.IP \n+[step]. 3
The ability to search books in the current collection or in all collections together.
.RE
.br
.PP
\*{[1]\*}  -  includes colours, default settings, default directories, etc.
