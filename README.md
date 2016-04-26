# Malefice
> Jetez vous dans l’arène et combattez en équipe afin de marquer le plus de point possible ! Simple à première vue, mais c’est sans compter les maléfices qui s’abattront sur vous et qui modifieront tout au long de la partie votre gameplay, ainsi que le fameux Prédateur qui rôdera dans l’arène !

### Installation de l'environnement de développement

Installer :
* [Visual Studio 2015](https://intra-bocal.epitech.eu/index.php?pgid=msdnaa)
* [Git](https://git-scm.com/download/win)
* [CMake](https://cmake.org/download/)
* [DirectX SDK](https://www.microsoft.com/en-us/download/details.aspx?id=6812)

Se rendre à la racine du dépôt avec **Git Bash** et lancer la commande :
```
git submodule update --init --recursive
```

Les projets sont déjà configurés pour compiler avec :
* **Client.Core** : RakNet et Irrlicht
* **Client.Launcher** : /
* **Server.Core** : RakNet

Les projets sont générés dans Debug/ et dans Release/ (à la racine du dépôt).
