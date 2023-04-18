# philosophers_42
multithreading project in c to solve the dining philosophers problem.

description du projet : 
le diner des philosophes est un bon example pour illustrer le concept de **sychronisation** en informatique systemes.
qu'est ce qu'on entend par sychronisation , dans le cadre de notre projet (mandatory part) on va se focaliser sur les threads. 
un thread est le plus petit sequence d'instructions programme par le **scheduler** (process reponsable d'attribuer les ressources necessaires pour effectuer une tache)
d coup la sychronisaiton entre threads est un mecanisme qui assure que deux threads concurents ou plus n'executent pas un segment particulier du programme en meme temps.
ce segment s'appelle **critical section**(une partie de code accede par plus plusieurs threads en meme temps) , en d'autres termes la sychronisation garantit une execution concurrente et non simultanee entre les threads. 
quel est l'interet de cette methode ? ca sert a eviter les "data races" : l'acces a une ressource partage par plusieurs acteurs en meme instant. 
cette sychronoisation est faite par le biais d'un algorithme concurrent , conccurent algorithme ou mulitiple taches peuvent etre execute dans une periode temps qui se chevauche (sans qu'ils rentrent en conflit).
[Et s'te-plait, parle cash, n*gro, parle-moi concrètement](https://genius.com/Freeze-corleone-fentanyl-lyrics).

d'accord revenons au sujet du projet , les threads sont presentes par des philosophes et les ressources partages sont les fourchettes
chaque philosophe a besoin de deux fourchettes pour manger or ils peuvent pas y acceder en meme temps. il y a une fourchette entre chaque paire de philosophes , autrement dit chaque phlosophe a une fourchette a gauche a une autre
a droite ce qui  signifie que deux philosophes adjacents ne peuvent pas acceder a deux fourchette en meme temps . alors le projet consiste a trouver une
solution pour que tous les philosophes puissent manger , dormir , et reflechir avant que la duree donnee **time_to_die** dans le projet ne s'ecoule.
pour resoudre ce probleme on doit eviter les **data-races** , on doit faire en sorte que deux ou plus philosophes/threads ne modifient pas une ressource partagee en meme instant.
je vais utiliser une simple analogie avant de parler de l'aspect technique de la solution . imaginons une queue de personnes qui attendent qu'un cabinet d'essayage se libere pour l'utiliser, a chaque fois une personne rentre 
elle verouille la porte avec un cle , la personne suivant verifie si la porte est verouillee ou pas pour rentrer et ainsi de suite pour le reste de la queue. dans l'informatique on a une abstraction des cles de la porte dans la vrai vie
ce sont les **mutexes** . ce sont des verrou qu'on utiliser pour verouiller une ressource partage pour un seul thread et la liberer apres. dans notre projets
les ressources partages sont les fourchettes et les printfs (chaque thread utilise la meme printf pour afficher un message son etat actuel)
chaque philosophe se comportetera de cette maniere :  
- reflichir tant que la fourchette a sa droite n'est pas disponible , si c'est le cas la prendre.
- si le temps d'attente depasse la duree demandee dans le sujet , le philosophe meurt de faim et notre experimentation s'acheve ici
-reflichir tant que la fourchette a sa gauche n'est pas disponible , si c'est le cas la prendre.
-si le temps d'attente depasse la duree demandee dans le sujet, le philosophe meurt de faim et notre experimentation s'acheve ici
- manger pour une duree determinee
- poser la fourchette a droite 
-  poser la fourchette a gauche
-  repeter depuis le debut

attention une utilisaion erronee des mutex peut entrainer un **dead-lock** , un exemple pour ce cas de figure : 
```

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutexA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexB = PTHREAD_MUTEX_INITIALIZER;

void *threadA(void *arg) {
  pthread_mutex_lock(&mutexA);
  printf("Thread A locked mutexA\n");
  sleep(1);
  pthread_mutex_lock(&mutexB);
  printf("Thread A locked mutexB\n");
  pthread_mutex_unlock(&mutexB);
  pthread_mutex_unlock(&mutexA);
  return NULL;
}

void *threadB(void *arg) {
  pthread_mutex_lock(&mutexB);
  printf("Thread B locked mutexB\n");
  sleep(1);
  pthread_mutex_lock(&mutexA);
  printf("Thread B locked mutexA\n");
  pthread_mutex_unlock(&mutexA);
  pthread_mutex_unlock(&mutexB);
  return NULL;
}

int main() {
  pthread_t tidA, tidB;
  pthread_create(&tidA, NULL, threadA, NULL);
  pthread_create(&tidB, NULL, threadB, NULL);
  pthread_join(tidA, NULL);
  pthread_join(tidB, NULL);
  return 0;
}
```
Dans cet exemple, il y a deux threads qui sont exécutés simultanément. Chaque thread essaie de verrouiller deux mutex différents (mutexA et mutexB) dans un ordre différent. Si les deux threads essaient d'obtenir les deux mutex en même temps, cela peut causer un deadlock.

imaginons que le thread A obtienne mutexA et le thread B obtienne mutexB, mais ensuite le thread A essaie d'obtenir mutexB, qui est déjà verrouillé par le thread B, et le thread B essaie d'obtenir mutexA, qui est déjà verrouillé par le thread A. Ainsi, les deux threads restent bloqués indéfiniment et le programme est dans un état de deadlock.

#implementation :

j'ai cree deux structures , une qui represente chaque philosophe et ses donnees perso comme id, et une autre structure generale pour toutes les infos partages par tous les philosophes , tel que les durees , nombre de philos et les mutexes ... bien sur vous pouvez faire autrement mais je suggere de faire en sorte que chaque philosophe pointe sur la structure de data generale.
Apres l'initialisation des donnes , on met une boucle afin de creer n philosophes qui executerons la fonction responsable des 3 actions (thinking , taking forks , eating and sleeping) , faites en sorte de lancer d'abord les threads d'indices paires en premier puis ceux d'indice impaire afin de permettre un petit interval d'execution entre les philosophes pour eviter les interblocages (utlisez ft_usleep aussi). n'oubliez pas de verouiller toute 
ressource partagee (forks, fprintf, des variables partages , ect ect). une fois aue les philosopes sont lances il est necessaire de verifier si l'un d'entre eux est mort ou pas , pour cela on a besoin d'un moniteur qui surveille sur tous les philosophes et verifie leur etat en comparant la duree entre le dernier repas de chaque philosophe avec time_to_die , si cette duree est depassee le programme doit se terminer apres la destruction des mutex et la liberation de memoire allouee. 





