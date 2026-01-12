1. pouvoir ouvrir minishell dans minishell.
2. gerer le ctrl+\ : désactivé dans le parent, à réactiver dans les enfants.
3. gerer le ctrl+c : interromp le programme en cours et remet un nouveau prompt.




4. Lexer -> Tokeniser les arguments.
	- Enumerations des arguments.
	- L'execution des commandes.

On regarde si c'est une commande : 
	S_ISREG(st.st_mode)   // fichier normal
	S_ISDIR(st.st_mode)   // dossier
	S_ISLNK(st.st_mode)   // lien symbolique
	S_ISCHR(st.st_mode)   // périphérique caractère
	S_ISBLK(st.st_mode)   // périphérique bloc
	S_ISFIFO(st.st_mode)  // pipe
	S_ISSOCK(st.st_mode)  // socket

	
5. Parsing
6. AST -> Abstract Syntaxic Tree (a = (5 + 3) * 8) gerer l'ordre des executions.

7. Compter le nombre de quotes et doubles : si c'est pair ok, sinon on part direct en quote? avant parsing

8. l'exeprocess recevra direcment arg_cmd[0] et l'arg + option. le split se fera avant.

CHAT:

ARBRE
cmd + option
cmd + option + fichier
cmd + option + vide -> si cmd besoin d'un fichier, ouvre le STDIN.
cmd + option + dossier (built-in)
cmd + (option) + < + fichier + (option) == < + fichier + cmd + option
cmd + (option) + > + fichier + (option)
cmd + ... + pipe

OPERATOR=

redirections:
'<'  + fichier (message d'erreur le cas échéant)
'>'  + fichier (le créer si n'existe pas)
'<<' + mot (peut être collé au << et donc être suivi d'autre chose après)
'>>' + fichier (le créer si n'existe pas)

'$' + mot collé et valide (lettre ou _ au 1er caractère sinon erreur OU '?' seul)