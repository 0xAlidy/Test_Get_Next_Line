# INSTALLATION

- Git clone mon dossier
- Transferez le fichier main.c et la bible (texte de test tres long) dans votre dossier get_next_line
- N'oubliez pas de mettre en commentaire le main que vous ne voulez pas tester 

# INFORMATIONS
- Je ne suis pas un expert des leaks et du cassage de code, il peut y avoir des erreurs !
- Je ne sais pas comment est testé le multi fd par la moulinette.
- Je pense qu'elle verifie juste s'il marche (Test A et B du multi-fd)
- Dans le cas où elle ne verifie pas les leaks je vous conseille quand meme de faire mes tests 
	et de modifier votre fonction qui free votre liste a la fin si jamais il y a des problemes (voir #aide)
	
# TEST-GNL

**A) Test si le programme fonctionne correctement :**

- GCC -Wall -Wextra -Werror -D BUFFER_SIZE=30 *.c 	// Compilation avec les flags 
- ./a.out bible > res         // Permet de mettre la lecture de la bible grace a notre programme dans un fichier
- diff bible res .           // Permet de verifier les differences entre les deux fichiers (rien ne doit s'afficher)
- tester avec un buffer_size de 1 et un grand buffer_size (+ de 1000)

**B) Test des adresses :**

- GCC -g3 -fsanitize=address -Wall -Wextra -Werror -D BUFFER_SIZE=30 *.c
- ./a.out bible 	// Le programme doit s'afficher correctement

**C) Test des leaks :**

- GCC -Wall -Wextra -Werror -D BUFFER_SIZE=30 *.c
- valgrind ./a.out bible										

**!! Ne pas compiler avec les flags de -fsanitize et utiliser valgrind apres !!**

**RESULTAT :**

==40221== LEAK SUMMARY:
==40221==    definitely lost: 0 bytes in 0 blocks		// Il doit y avoir 0 pertes
==40221==    indirectly lost: 0 bytes in 0 blocks		// Ici aussi
==40221==      possibly lost: 72 bytes in 3 blocks
==40221==    still reachable: 200 bytes in 6 blocks

**D) Divers tests**

- Teste avec un fichier vide 		// Rien ne doit s'afficher 
- un BUFFER_SIZE <= 0 			// Retourne (null)
- Passer 0 en parametre de la function get_next_line(fd, 0) 	// Test si le pointeur est null => return (null)
- Passer 0 en parametre de la function get_next_line(0, &line)  // Test si le fd est null ou negatif => return (null)

# TEST-MULTI-FD

Si le premier test est bon et que vous voulez tester les bonus :

**A) Check qu'il n'y a bien qu'une static**

- static t_gnl	*list;

**B) Savoir si la gestion du multi-fd est bonne**

- Laisser la deuxieme boucle while (res > 0) en commentaire	// Cette boucle servira pour le test des leaks
- GCC -Wall -Wextra -Werror -D BUFFER_SIZE=30 *.c
- ./a.out bible test

**RESULAT :**

1:1 In the beginning God created the heaven and the earth.
Demain, dès l'aube, à l'heure où blanchit la campagne,

Je partirai. Vois-tu, je sais que tu m'attends.
1:2 And the earth was without form, and void; and darkness was upon
J'irai par la forêt, j'irai par la montagne.
the face of the deep. And the Spirit of God moved upon the face of the
Je ne puis demeurer loin de toi plus longtemps.
waters.


Je marcherai les yeux fixés sur mes pensées,
1:3 And God said, Let there be light: and there was light.
Sans rien voir au dehors, sans entendre aucun bruit,

Seul, inconnu, le dos courbé, les mains croisées,
1:4 And God saw the light, that it was good: and God divided the light
Triste, et le jour pour moi sera comme la nuit.
from the darkness.
'\n'

**C) Test des adresses**

- Enlever les commentaires de la deuxieme boucle while
- GCC -g3 -fsanitize=address -Wall -Wextra -Werror -D BUFFER_SIZE=30 *.c
- ./a.out bible test // Le programme doit s'afficher correctement

**D) Test des leaks**

 Ceci est la partie de test la plus importante, 
 On va tester si notre liste est correcte apres avoir free le maillon de la liste
 une fois arrive a la fin de la lecture d'un fd
 La liste doit etre correctement free une fois tous les fd lus 	

- Enlever les commentaires de la deuxieme boucle while
- GCC -Wall -Wextra -Werror -D BUFFER_SIZE=30 *.c
- valgrind ./a.out bible test	

**!! Ne pas compiler avec les flags de -fsanitize et utiliser valgrind apres !!**

**RESULTAT :**
```
==40221== LEAK SUMMARY:
==40221==    definitely lost: 0 bytes in 0 blocks 	// Il doit y avoir 0 pertes
==40221==    indirectly lost: 0 bytes in 0 blocks	// Ici aussi
==40221==    possibly lost: 72 bytes in 3 blocks
==40221==    still reachable: 200 bytes in 6 blocks ```

Refaire la meme chose mais en echangeant le fd de la bible et du test :

// Il est important d'echanger les deux , c'est pour voir si votre fonction qui free fonctionne correctement

- Dans la deuxieme boucle while du main il faut remplacer fd par fd2 dans la fonction get_next_line 
- GCC -Wall -Wextra -Werror -D BUFFER_SIZE=30 *.c
- valgrind ./a.out test bible
- Le resultat doit etre le meme que precedement !

# AIDE

Si vous avez des leaks dans votre gnl qui gere plusieurs fd :

- Cela doit venir de votre fonction qui doit free le maillon de la liste une fois la lecture finie.
- Il faut penser à rattacher le maillon d'avant avec le suivant avant de free pour eviter de casser la liste;
- Il ne faut pas oublier de free la chaine de caractere qui a été malloc avant de free le maillon;

# AUTEUR

	ALIDY student 42 LYON , Get_Next_Line 2019
