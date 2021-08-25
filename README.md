# Library-App
A PDF library application for the terminal

### Supported Operating systems
Anything Linux based

### Technologies
* C
* MySQL
* [NCurses Library](https://invisible-island.net/ncurses/)
* [MuPDF](https://mupdf.com/docs/index.html)
* Some [FreeBSD](https://www.freebsd.org/) libraries
* Shell script

### Management
* Branching strategy - [GitHub flow](https://githubflow.github.io/)
* Kanban - [Azure DevOps](https://dev.azure.com)
* Code reviews

## First Milestone
1. Create MySQL database and functionalities:
* Init function.
* Create (Insert) function.
* Update function.
* Delete function.
* Select functions.
2. Function to get the pagecount of a PDF.
3. Time to reasearch the ncurses library.

## Second Milestone
1. Add the ability to sort books by author, title, publisher, pagecount and year published.
2. Create the UI for collections and books + keybinds:
* UI for the collections and the list of books.
* Keybinds for sorting by category (author, title, publisher, pagecount and year published).
3. Make it so that each file is renamed with their respective author, title and publisher (The pattern will be the same for every collection and/file file).

## Third Milestone
1. The ability to add books from the UI.
2. The ability to edit and delete books from the UI.
3. Residual tasks from the previous milestones.
4. Cleaning up the UI.
5. Bug fixes.

## Optional Tasks
1. Man page.
2. Config.h (Simular to how you configure the [suckless](https://suckless.org/) programs).
3. Reading and redacting the metadata of a PDF.
4. The ability to search a directory added by the user and add all books from this folder to the database and default collection.
