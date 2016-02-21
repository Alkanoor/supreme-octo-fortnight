Projet C++


R�ponses aux questions:


4e Etape : photos et videos


?Cependant, contrairement � la fonction d'affichage, son impl�mentation ne fait pas sens au niveau de la classe de base. Comment appelle-t'on ce type de m�thode et comment faut-il les d�clarer ?

*On appelle ce type de m�thode une m�thode virtuelle abstraite, qu'on d�clare avec son prototype classique pr�c�d�e d'un virtual pour le polymorphisme et suivie d'un =0 pour le caract�re abstrait de la m�thode. En faisant ainsi, on ne peut plus instancier la classe m�re (celle qui contient la m�thode abstraite) directement (sans instancier une de ses classes filles).


?Modifier le Makefile si n�cessaire (on rappelle qu'il ne faut pas mettre les .h dans SOURCES). Compiler, corriger les �ventuelles erreurs et tester le programme. Si vous avez fait correctement ce qui pr�c�de, il ne sera plus possible d'instancer des objets de la classe de base. Pourquoi ?

*Le makefile a �t� l�g�rement modifi� pour une utilisation personnelle (projet effectu� avec codeblocks, donc pour garder uniquement l'essentiel, des fonctions ont �t� ajout�es dans le makefile, elles seront normalement inutilisables dans le projet rendu). On a �videmment ajout� les nouveaux fichiers .cpp dans la variable SOURCES. Pour la r�ponse � la deuxi�me partie de la question, cela a d�j� �t� dit dans la r�ponse pr�cdente.



5e Etape : traitement g�n�rique


?Quelle est la propri�t� caract�ristique de l'orient� objet qui permet de faire cela ? Qu'est-il sp�cifiquement n�cessaire de faire dans le cas du C++ ? Quel est le type des �l�ments du tableau : est-ce que ce tableau contient les objets ou des pointeurs vers ces objets ? Pourquoi ? Comparer � Java.

*C'est le polymorphisme qui permet de faire cela, dans le cas du C++ on est oblig� d'utiliser des pointeurs ou des r�f�rences pour que le polymorphisme s'applique (vtables en C++). Le tableau contient donc des pointeurs vers les objets. Celui-ci est pr�sent dans le main en commantaire (dans le fichier main.cpp) qui a servi � faire des tests de fuite de m�moire avec valgrind. En java, on manipule constamment des r�f�rences vers des objets sans sans apercevoir : � part les types primitifs, tout n'est que r�f�rence. C'est pourquoi, les principes internes �tant globalement identiques, le polymorphisme s'applique sans effort suppl�mentaire.



6e Etape : films et tableaux


?Que faut-il faire dans ce cas pour que l'objet puisse avoir plein contr�le sur ses donn�es (ici, le tableau de dur�es du Film) ?

*La solution retenue (et l'une des seules r�alistes) est la copie des donn�es de dur�es dans le constructeur de copie et dans l'op�rateur d'affectation. De plus, concernant l'accesseur, on est oblig�, pour garantir l'int�grit� des donn�es, de retourner un pointeur sur des int constants. Le pointeur peut �ventuellement �tre constant (il l'est ici). Malheureusement, je crois qu'il est toujours possible de forcer le cast de const vers non const, rendant ce m�canisme non s�r � 100%, mais cela rel�ve plus de la responsabilit� du programmeur utilisant la classe Film.
De nombreux tests ont �t� effectu�s et v�rifi�s avec Valgrind (voir le main comment� en dessous du "vrai" main).



7e Etape :


?Parmi les classes pr�c�demment �crites quelles sont celles qu'il faut modifier et comment afin qu'il n'y ait pas de fuite m�moire quand on d�truit leurs instances ? De m�me, la copie d'objets peut poser probl�me dans certains cas. Quelle(s) classe(s) sont concern�es parmi celles d�j� �crites et que faut-il faire ?

*La classe Film est la seule concern�e par des fuites m�moires �ventuelles vu qu'on copie les donn�es allou�es dynamiquement de mani�re dynamique dans certaines m�thodes de la classe. Il faut donc delete ces donn�es dans le destructeur. Le probl�me de la copie d'objets a �t� �voqu� pr�c�demment vu qu'un constructeur de copie et que l'op�rateur d'affectation ont �t� red�finis. Le main testait cela tr�s bien.



8e Etape :


?Le groupe ne doit pas d�truire les objets quand il est d�truit car un objet peut appartenir � plusieurs groupes. Consid�rant ce fait, la classe groupe doit-elle forc�ment avoir un destructeur ou �a d�pend des cas ? Expliquez.

*La classe groupe n'a pas besoin de disposer d'un destructeur. En effet, si un objet appartient � plusieurs groupes (ce qui est tout � fait possible), mettre en place un m�canisme de destruction intelligent est complexe et inutile si le programmeur fait attention � d�truire les objets concern�s apr�s les derni�res op�rations engendr�es depuis des instances de groupe (sinon on prend le risque de d�truire un objet utilis� dans le groupe). Rien n'emp�che toutefois de d�clarer un destructeur quasiment vide pour le groupe.


?On rappelle que la liste d'objets doit en fait �tre une liste de pointeurs d'objets. Pourquoi ? Comparer � Java.

*La liste d'objets doit �tre une liste de pointeurs d'objets pour conserver le polymorphisme � l'int�rieur de m�thodes de la classe groupe. En java, comme il a d�j� �t� �voqu� pr�c�demment, ce m�canisme est automatique vu que tout objet est une r�f�rence : il n'y a pas besoin de d�clarer de surplus.



11e Etape :


?Si les noms des objets multim�dia (par exemple le nom d'une vid�o) contiennent des espaces il faut utiliser une des formes de la fonction getline() au lieu de l'operateur >> (car cet op�rateur s'arr�te d�s qu'il trouve un espace) et s�parer les mots avec un caract�re appropri� (mais pas \n qui sert � s�parer les messages !).

*Done


?Vous pouvez rajouter toute commande utile pour une t�l�commande (et servira pour l'interface graphique Java Swing du TP suivant). Par exemple il peut �tre int�ressant d'obtenir la liste des objets d'un certain type ou appartenant � un certain groupe pour afficher cette liste sur la t�l�commande.

*On peut d�j� afficher des groupes, l'utilisateur pourra ainsi acc�der aux groupes "images" ou "videos". Une commande ajout�e est la suppression d'un item (�a n'est pas tr�s utile puisque si on supprime tous les items, on ne peut plus rien faire d'int�ressant).


?On peut utiliser une map avec des pointeurs de m�thodes pour effectuer le lien entre le nom des commandes et les m�thodes correspondantes afin d'avoir une plus grande flexibilit� (on peut ainsi rajouter des commandes sans modifier la partie serveur) et une meilleure efficacit� (la recherche de la commande est plus rapide s'il y en a beaucoup).

*Vu le nombre de commandes (4) je n'ai pas pris la peine de d�clarer une std::map<std::string,std::function<void(const std::string&)> > qui aurait pu �tre utilis�e pour proc�der chaque type de message.



12e Etape : s�rialisation/d�s�rialisation


Je n'ai pas fait de s�rialisation "sp�ciale". A la base j'avais d�j� pris en compte cet aspect pour afficher les objets facilement, du coup on peut utiliser un ofstream quelconque ofs et utiliser ofs<<(objet). C'est ce que je fais ici pour g�rer la commande print. Je n'ai pas le temps d'impl�menter une s�rialisation � proprement parler et je n'en vois pas l'int�r�t vu qu'il n'est d'aucune utilit� ici de reconstruire les classes en bout de transmission (on veut juste afficher les donn�es importantes).



13e Etape : traitement des erreurs


La couche de traitement d'erreurs ajout�e est superficielle, il s'agit juste de renvoyer des exceptions dans le cas o� on cr�e plusieurs groupes ou objets avec le m�me nom ou dans le cas o� on nomme un �l�ment multim�dia avec des caract�res invalides (ASCII<32 ou ASCII>127). Voici pourquoi : la suppression d'un objet n'existant pas renvoie false (donc code d'erreur simple), et cela est �galement renvoy� sur le r�seau. Concernant la taille du tableau de dur�es d'un Film, c'est difficile � g�rer ici puisque le programmeur est sens� fournir le tableau des chapitres et la taille de ce tableau (un entier positif). Si le programmeur donne une taille improbable (plus grande que la taille du tableau des chapitres), le programme plantera, mais cela ne peut pas se pr�dire. Le programmeur fera donc attention. C'est le cas parce que je n'ai d�lib�r�ment pas chang� la classe Film avec un vector d'entiers pour les chapitres. En effet, il �tait demand� dans le TP de ne pas le faire au d�but, et ce n'est pas maintenant que je vais effacer ce qui a �t� fait pr�c�demment et qui m'a cout� un certain temps de v�rification par rapport aux fuites de m�moires �ventuelles.
