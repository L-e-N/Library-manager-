# Library-manager-
Conception d'un moteur de persistance object/relationnel en C++/qt

Inspiration from https://doc.qt.io/archives/qt-4.8/tutorials-addressbook-fr.html
Equivalents : 
AddressBook <-> Library
name <-> author
text <-> title

library.h le fichier de définition (header) pour la classe MainWindow
ex: contient les widgets QLineEdit

library.cpp le fichier source, qui comprend l'implémentation de la classe MainWindow
ex: contient les Qlabel, i.e. les noms de lignes ; contient le layout

main.cpp le fichier qui contient la méthode main() , et une instance de la classe MainWindow
