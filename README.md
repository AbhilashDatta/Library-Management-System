# Library-Management-System
C++ code to manage library of books.

A library of books contains many books. Each book is stored in a text file in a given directory,
which contains the library. Each book has a title, an author, a release date, and a Language. These
can be read from the Project Gutenberg file header. 

A book can contain many types of content, e.g. a novel, a play, etc. A novel can contain many chapters.
Each chapter has a title followed by many paragraphs. Each paragraph contains many sentences, and each 
sentence is a sequence of
words. A play has a optional prologue followed by many acts. Each act has many scenes, and each
scene is a sequence of dialogues. Additionally, a play also has a list of characters or personae,
where each dialogue is spoken by a character.

Library management system (LMS) manages all the books in a given
directory. The program will start with a directory as input, and will manage the books in that
directory. The LMS will maintain the type of each book in the library, in a file called “index.txt”.
It automatically detects all files in the directory and be able to detect the newly added
books. It then asks the user for type of each of the newly added books and add them to
“index.txt”.

To run the LMS, on the command line type:
./a.out \<Directory-Name\>

The LMS has the following functionality:
1. List all books along with their filename, title, and author name.
2. Search for a book by its title or author name, and show the matching books as a list.
3. Display a book from any of the above two lists.
4. If the type of the selected book is novel, given an input word, the LMS is able to
   show the top 5 chapters, or top 5 paragraphs, where this word appears most of the times.
5. If the type of the selected book is play, then given an input character, the LMS
   shows a list of all other characters which appear in at least one scene with the input
   character.
