Library App
===========

[Описание:](#Описание:)  
[Technologies:](#Technologies:)  
[Management:](#Management:)  
[First Milestone:](#First Milestone:)  
[Second Milestone:](#Second Milestone:)  
[Third Milestone:](#Third Milestone:)  
[Additional Tasks:](#Additional Tasks:)  

* * *

_Александър Хаджиев № 3  
Михаил Димитров № 15  
ТУЕС  
11 A_

Описание:
---------

Приложение за библиотека в терминала подобно на Calibre с UI написан на _ncurses_. То ще позволява добавяне на книги в колекции определени от потребителя, като всяка колекция ще се намира в определена папка. Потребителя ще може да зададе заглавие, автор, издател, година на издаване, и колекция, за всяка книга, като тази информация ще бъде използване за да се преименува файла _(това ще позволи универсалност на наименованията на файловете)_. Във всяка колекция списъкът с книги ще може да бъде сортиран по категориите изброени преди малко.

Тъй като приложението е в терминала ползването не мишката ще бъде ненужно и затова всяка функционалност ще бъде направена да бъде различен _shortcut_.

Technologies:
-------------

•

C

•

MySQL / MariaDB

•

ncurses Library

•

Shell script \[ + awk\] _(If needed)_.

•

CMake

Management:
-----------

•

Git Flow

•

Kanban (Azure DevOps)

•

Mandatory code reviews

First Milestone:
----------------

1.

Create MySQL database and functionalities:

•

Init function.

•

Create _(Insert)_ function.

•

Update function.

•

Delete function.

•

Select functions.

2.

Function to get the pagecount of a PDF.

3.

Time to reasearch the ncurses library.

4.

Time to research CMake.

Second Milestone:
-----------------

1.

Add the ability to sort books by author, title, publisher, and year published.

2.

Create the UI for collections and books + keybinds:

•

UI for the collections and the list of books.

•

Keybinds for sorting by category (author, title, publisher, year published).

3.

Make it so that each file is renamed with their respective author, title and publisher _(The pattern will be the same for every collection and/file file)_.

Third Milestone:
----------------

1.

The ability to add books from the UI.

2.

The ability to edit and delete books from the UI.

3.

Cleaning up the UI.

4.

Bug fixes.

5.

Unit tests.

Additional Tasks:
-----------------

1.

Man page.

2.

Config.h \[1\] _(Simular to how you configure the suckless programs)_.

3.

Reading and redacting the metadata of a PDF.

4.

The ability to search a directory added by the user and add all books from this folder to the database and default collection.

5.

The ability to search books in the current collection or in all collections together.

\[1\] - includes colours, default settings, default directories, etc.

* * *
