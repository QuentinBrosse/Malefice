# Malefice
> Jetez vous dans l’arène et combattez en équipe afin de marquer le plus de point possible ! Simple à première vue, mais c’est sans compter les maléfices qui s’abattront sur vous et qui modifieront tout au long de la partie votre gameplay, ainsi que le fameux Prédateur qui rôdera dans l’arène !

## Installation de l'environnement de développement

Les dépendances suivantes n'offrent pas de versions précompilées :
* **CEGUI**
* **RakNet**
* **spdlog**
* **TinyXML2**

Ces dépendances sont donc compilées depuis les sources lors de la génération du projet.
Pour les autres dépendances, afin de réduire le temps de compilation, il est préférable d'installer les versions précompilées (C.F. ci-dessous).

### Windows
* [Visual Studio 2015](https://intra-bocal.epitech.eu/index.php?pgid=msdnaa)
* [Git](https://git-scm.com/download/win) -- **Ajouter au PATH Windows !**
* [CMake *version 3.x*](https://cmake.org/download/) -- **Ajouter au PATH Windows !**
* [DirectX SDK](https://www.microsoft.com/en-us/download/details.aspx?id=6812)
* [Boost 1.60](https://sourceforge.net/projects/boost/files/boost-binaries/1.60.0/boost_1_60_0-msvc-14.0-32.exe/download) -- **Laisser le répertoire par défaut !** (C:\local\boost_1_60_0)
* [Irrlicht 1.8.3](http://downloads.sourceforge.net/irrlicht/irrlicht-1.8.3.zip) -- **Décompresser et copier dans C:\local\irrlicht-1.8.3**
* [IrrKlang 1.5.0](http://www.ambiera.at/downloads/irrKlang-32bit-1.5.0.zip) -- **Décompresser et copier dans C:\local\irrKlang-1.5.0**

### Linux
*À faire*


## Configuration de Visual Studio

### Working directory (obligatoire)

Cette procédure est à suivre pour **le client** ***et*** **le serveur**.

* Clic-droit sur le projet
* *Propriétés*
* *Débogage*
* Indiquer le répertoire "Binaries\Debug" (ou "Binaries\Release") dans *Répertoire de travail*

### Projets de démarrage (optionnel)

Si vous souhaitez démarrer à la fois le client et le serveur :
* Clic-droit sur la solution
* *Propriétés*
* Cocher *Plusieurs projets de démarrage*
* Sélectionner *Démarrer* pour *Client.Core* et *Server.Core*



## Cloner et mettre à jour les submodules
Se rendre à la racine du dépôt avec **Git Bash** et lancer la commande :
```
git submodule update --init --recursive
```
Pour éviter de devoir taper cette commande après avoir `git clone`, cloner de cette manière :
```
git clone --recursive git@github.com:QuentinBross/Malefice.git
```

Les projets sont déjà configurés pour compiler avec :
* **Client.Core** : CEGUI, Irrlicht, RakNet et Shared
* **Client.Launcher** : /
* **Server.Core** : Irrlicht, RakNet, TinyXML2 et Shared
* **Shared** : Irrlicht, RakNet, spdlog et TinyXML2

Les projets sont générés dans Binaries/Debug/ et dans Binaries/Release/.

## Résolution des problèmes de génération

***Attention :***
* **Il ne doit pas y avoir d'espace dans les chemins !** Les espaces font échouer la génération de certaines parties du projet (*cegui-dependencies* entre autres).
* **Il faut que `git` et `cmake` soient dans le PATH Windows !** En cas d'erreur de génération, vérifier en ouvrant l'invite de commandes Windows et en tapant `git --version` et `cmake --version`.
* **Les chemins et versions des bibliothèques Boost, Irrlicht et IrrKlang doivent être** ***exactement*** **ceux ci-dessus.**
