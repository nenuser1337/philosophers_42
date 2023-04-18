# philosophers_42
multithreading project in c to solve the dining philosophers problem.

## description du projet : 
Avant de commencer, je présume que vous êtes déjà familiarisé avec les fonctions de threads et leur fonctionnement en code. Si ce n'est pas le cas, je vous conseille de vous renseigner à ce sujet avant de poursuivre la lecture .

Le diner des philosophes est un exemple courant pour illustrer le concept de **synchronisation** en informatique système. La synchronisation, dans le cadre de notre projet (Mandatory part), on se concentrera sur les threads. Un thread est la plus petite séquence d'instructions programmée par le scheduler (processus responsable d'attribuer les ressources nécessaires pour effectuer une tâche).

La synchronisation entre threads est un mécanisme qui assure que deux threads concurrents ou plus n'exécutent pas un segment particulier du programme en meme temps. Ce segment s'appelle **la section critique** (une partie de code accédée par plusieurs threads en meme temps). En d'autres termes, la synchronisation garantit une exécution concurrente et non simultanée entre les threads. Cette méthode est utile pour éviter les **data races** : l'accès simultané à une ressource partagée par plusieurs acteurs.

La synchronisation est réalise par le biais d'un [algorithme concurrent](https://en.wikipedia.org/wiki/Concurrency_(computer_science)). , où plusieurs tâches peuvent être exécutées dans une période de temps qui se chevauche (sans entrer en conflit). L'intéret de cette méthode est de garantir l'exécution correcte des threads et d'éviter les erreurs de concurrence.      


[Et s'te-plait, parle cash, n*gro, parle-moi concrètement](https://genius.com/Freeze-corleone-fentanyl-lyrics).       
    
Très bien, pour résoudre ce problème, nous avons besoin de mettre en place un mécanisme de synchronisation entre les threads qui représentent les philosophes, et les ressources partagées qui sont les fourchettes. Comme chaque philosophe a besoin de deux fourchettes pour manger, il est essentiel de garantir que deux philosophes adjacents ne peuvent pas accéder a deux fourchettes en même temps. Le but est de trouver une solution pour que tous les philosophes puissent manger, dormir et réfléchir avant que la durée donnée par "time_to_die" ne s'écoule.

La synchronisation nous permettra d'éviter les "data-races" qui surviennent lorsque deux ou plusieurs philosophes/threads essaient de modifier une même ressource partagée en même temps.
Je vais utiliser une analogie simple pour illustrer l'aspect technique de la solution. Imaginons une file d'attente de personnes attendant qu'un cabinet d'essayage se libère pour l'utiliser. À chaque fois qu'une personne entre, elle verrouille la porte avec une clé. La personne suivante vérifie si la porte est verrouillée ou non pour entrer, et ainsi de suite pour le reste de la file. Dans le domaine de l'informatique, on a une abstraction de cette clé de porte, ce sont les mutexes. Ce sont des verrous utilisés pour verrouiller une ressource partagée pour un seul thread et la libérer après.. dans notre projet les ressources partages sont les fourchettes et les printfs (chaque thread utilise la même printf pour afficher un message de son etat actuel)

Dans notre projet, les ressources partagées sont les fourchettes et les printfs (chaque thread utilise la même printf pour afficher un message sur son état actuel).

Pour résumer le projet, chaque philosophe se comportera de cette manière :

-Réfléchir tant que la fourchette à sa droite n'est pas disponible, si c'est le cas, la prendre.
-Si le temps d'attente dépasse la durée demandée dans le sujet, le philosophe meurt de faim et notre expérience s'achève ici.
-Réfléchir tant que la fourchette à sa gauche n'est pas disponible, si c'est le cas, la prendre.
-Si le temps d'attente dépasse la durée demandée dans le sujet, le philosophe meurt de faim et notre expérience s'achève ici.
-Manger pour une durée déterminée (time_to_eat).
-Poser la fourchette à droite.
-Poser la fourchette à gauche.
-Répéter depuis le début.

Attention, une utilisation erronée des mutex peut entrainer un **deadlock**(Un deadlock est une situation dans laquelle aucun membre ne peut procéder, car chacun attend que les autres membres prennent action, y compris lui même). Un exemple pour ce cas de figure :
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
Dans cet exemple, deux threads s'exécutent simultanément. Chaque thread tente de verrouiller deux mutex différents (mutexA et mutexB) dans un ordre différent. Si les deux threads essaient d'obtenir les deux mutex en meme temps, cela peut provoquer une impasse (deadlock)


## implementation :

J'ai créé deux structures : une qui représente chaque philosophe et ses données personnelles comme l'id, et une autre structure générale pour toutes les informations partagées par tous les philosophes, telles que les durées, le nombre de philosophes et les mutexes. Bien sur, vous pouvez faire autrement, mais je suggère de faire en sorte que chaque philosophe pointe vers la structure de données générale.

Après l'initialisation des données, on met une boucle afin de créer n philosophes qui exécuteront la fonction responsable des 3 actions (thinking, taking forks, eating and sleeping). Faites en sorte de lancer d'abord les threads d'indices pairs en premier, puis ceux d'indices impairs afin de permettre un petit intervalle d'exécution entre les philosophes pour éviter les interblocages (utilisez ft_usleep aussi). N'oubliez pas de verrouiller toutes les ressources partagées (forks, fprintf, des variables partagées, etc.). Une fois que les philosophes sont lancés, il est nécessaire de vérifier s'ils sont morts ou pas. Pour cela, on a besoin d'un moniteur qui surveille tous les philosophes et vérifie leur état en comparant la durée entre le dernier repas de chaque philosophe avec time_to_die. Si cette durée est dépassée, le programme doit se terminer après la destruction des mutex et la libération de la mémoire allouée.




