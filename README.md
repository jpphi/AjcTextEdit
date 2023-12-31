# TP Editeur de texte, Septembre 2023
## 1 Objet du développement
Il est demandé de développper un éditeur de texte en C++ à l’aide de la librairie Qt5.  
  
## 2 Listes des fonctionalités demandées
Pour chaque fonctionnalité demandée, une indication sur les classe Qt5 facilitant la mise en oeuvre est fournie dans les paragraphes suivants.  
Il est demandé de commenter le code à l’aide des commentaires Doxygen  
Le projet sera hébergé sur un serveur git.  
Le projet pourra être géré par qmake ou par cmake  
L’IDE QtCreator sera utilisé  
  
## 3 Critères d’évaluation
Le logiciel devra être testé au fur et à mesure de son évolution  
Les fonctionnalités présentées dans le logiciels mais non développées ne sont pas admises. Aussi il est demandé de n’ajouter une fonctionalité que lorsque la précédente est fonctionnelle et testée  
  
## 4 Listes des fonctionalités demandées
Lecture de fichiers texte  
Écriture de fichiers texte  
Affichage de la ligne et de la colonne du curseur  
Recherche d’un texte dans un fichier ouvert  
Remplacement d’un texte dans un fichier  
Mémorisation des derniers fichiers ouverts  
  
## Ressources  
Excellent tuto QT en français: https://www.youtube.com/playlist?list=PL8ThI0DA8FbUBpEihprYsoQJSbcLm40nZ  
  
## Bug  
A l'exécution on a les avertissements suivants:  
QSocketNotifier: Can only be used with threads started with QThread  
qt.qpa.wayland: Wayland does not support QWindow::requestActivate()  
  
La recherche un parent de QPlainTextEdit échou et renvoie -1:  
qDebug()<< "tabwidget->indexOf(lqpte[i]->parentWidget()): " << tabwidget->indexOf(lqpte[i]->parentWidget());  
  
**La sauvegarde peut fonctionner** à condition de **déplacer l'onglet** à sauvegarder en **dernière position**.  

