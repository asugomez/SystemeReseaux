# --------------------------------------------------------------------- #
#                     Makefile du projet STAT                           #
#                                                                       #
#       C. VERCAUTER                                       08/03/2019   #
#                                                                       #
#       Options                                                      	#
#	       DEBUG=on                                                 #
#	       TEST_BASIQUE=on                                          #
#	       NBMAX=<nn>                                               #
#                                                                       #
#       10/03/2020 : ajout de la cible archive                          #
# --------------------------------------------------------------------- #


# --------------------------------------------------------------------- #
# Récupération du nom du répertoire du projet STAT                      #
#   (utilisation pour la création de l'archive du dossier de projet)    #
# --------------------------------------------------------------------- #
CURRENT_DIR = $(shell basename $(shell pwd))


# --------------------------------------------------------------------- #
# Spécification du compilateur utilisé                                  #
# --------------------------------------------------------------------- #
CC = gcc

# --------------------------------------------------------------------- #
# Définition des options du pré-processeur                              #
# --------------------------------------------------------------------- #
CPPFLAGS =
ifeq ($(DEBUG),on)
CPPFLAGS += -D_DEBUG
endif
ifeq ($(TEST_BASIQUE), on)
CPPFLAGS += -D_TEST_BASIQUE
endif
ifneq ($(NBMAX),)
CPPFLAGS += -DNBMAX=$(NBMAX)
endif

# --------------------------------------------------------------------- #
# Définition des options de compilation                                 #
#       -Wall           : affiche tous les messages d'avertissement     #
#       -Werror         : traiter les avertissements comme des erreurs	#
#       -std=c99        : respect  du standard ISO C99                  #
#       -pedantic       : rien que le standard ISO C99                  #
# --------------------------------------------------------------------- #
CFLAGS  = -Wall
CFLAGS += -Werror
CFLAGS += -std=c99
CFLAGS += -pedantic

# --------------------------------------------------------------------- #
# Définition des options de l'éditeur de liens                          #
# --------------------------------------------------------------------- #
LDFLAGS = -lm

# --------------------------------------------------------------------- #
#      Définition des cibles (exécutables/librairies)  à générer        #
# --------------------------------------------------------------------- #
PROGRAM1    = testStat      # génération classique                      #
PROGRAM2    = testStat_ic   # avec liaison statique			#
LIBSTAT     = libStat.so    # librairie dynamique		        #
LIBSTAT_IC  = libStat.a     # librairie statique                        #
# --------------------------------------------------------------------- #
#	versions utilisant des librairies
# --------------------------------------------------------------------- #
PROGRAM3    = test2Stat	    #	génération classique                    #
PROGRAM4    = test2Stat_ic  # avec liaison statique			#
# --------------------------------------------------------------------- #

# --------------------------------------------------------------------- #
#      Définition des listes de fichiers sources                        #
# --------------------------------------------------------------------- #
SRC_LIB   = min.c max.c avg.c std.c
SRC_TEST  = testStat.c
SRC_TEST2 = testBasique.c

# --------------------------------------------------------------------- #
#      Construction des listes de fichiers objet                        #
# --------------------------------------------------------------------- #
OBJ_LIB   =  $(SRC_LIB:.c=.o)
OBJ_TEST  =  $(SRC_TEST:.c=.o)
OBJ_TEST2 =  $(SRC_TEST2:.c=.o)

# --------------------------------------------------------------------- #
#      Toutes les cibles                                                #
# --------------------------------------------------------------------- #
all: $(PROGRAM1) $(PROGRAM2) $(LIBSTAT) $(LIBSTAT_IC) \
$(PROGRAM3) $(PROGRAM4)

# --------------------------------------------------------------------- #
#      Règles de dépendances                                            #
# --------------------------------------------------------------------- #

$(PROGRAM1): $(OBJ_TEST) $(OBJ_LIB) $(OBJ_TEST2)
	$(CC) $^ -o $@ $(LDFLAGS)

$(PROGRAM2): $(OBJ_TEST) $(OBJ_LIB) $(OBJ_TEST2)
	$(CC) $^ -static -o $@ $(LDFLAGS)

$(LIBSTAT) : $(OBJ_LIB)
	$(CC) -fPIC -shared $^ -o $@ $(LDFLAGS)

$(LIBSTAT_IC) : $(OBJ_LIB)
	ar -qvs $@ $^

$(PROGRAM3): $(OBJ_TEST) $(OBJ_TEST2)
	$(CC) -L./  $^ -o $@ $(LDFLAGS) -lStat

$(PROGRAM4): $(OBJ_TEST) $(OBJ_TEST2)
	$(CC) -L./ $^ -static -o $@ $(LDFLAGS) -lStat

# --------------------------------------------------------------------- #
# Dépendances produites par l'exécution de make depend                  #
# --------------------------------------------------------------------- #
avg.o: avg.c
max.o: max.c
min.o: min.c
std.o: std.c avg.h
testBasique.o: testBasique.c stat.h min.h max.h avg.h std.h
testStat.o: testStat.c stat.h min.h max.h avg.h std.h
# --------------------------------------------------------------------- #

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean touchAll depend

# --------------------------------------------------------------------- #
#       Cible secondaire : nettoyage des fichiers objets                #
# --------------------------------------------------------------------- #
clean:
	@rm -f $(OBJ_TEST) $(OBJ_LIB) $(OBJ_TEST2) *~
	@echo "Effacement des fichiers objets ...  effectué"

# --------------------------------------------------------------------- #
#      3 ème cible : nettoyage de tous les fichiers objets, des         #
#               fichiers exécutables et de librairies  générés          #
# --------------------------------------------------------------------- #
realclean: clean
	@rm -f $(PROGRAM1) $(PROGRAM2) $(PROGRAM3) $(PROGRAM4)
	@rm -f $(LIBSTAT) $(LIBSTAT_IC)
	@rm -f "../$(CURRENT_DIR)_$(USER).tar.gz"
	@echo "Effacement(s) effectué(s)"

# --------------------------------------------------------------------- #
#      4 ème cible :                                                    #
# --------------------------------------------------------------------- #
touchAll:
	@touch *.c
# --------------------------------------------------------------------- #
#      5 ème cible :                                                    #
# --------------------------------------------------------------------- #
depend:
	$(CC) $(CPPFLAGS) -MM $(SRC_LIB) $(SRC_TEST) $(SRC_TEST2)

# --------------------------------------------------------------------- #
#      6 ème cible :  création d'une archive du dossier de projet       #
#                                                                       #
#          L'archive ne contient que les fichiers les plus utiles       #
#          du projet : l'effacement des fichiers secondaires est        #
#          préalablement réalisé.                                       #
#                                                                       #
#         Elle porte le nom du dossier de projet suivi d'un souligné    #
#         et du nom de l'utilisateur                                    #
# --------------------------------------------------------------------- #
archive: realclean
	@tar czf "../$(CURRENT_DIR)_$(USER).tar.gz" ../$(CURRENT_DIR)/ 2> /dev/null
	@echo "Création de $(CURRENT_DIR)_$(USER).tar.gz dans .. effectuée."
# --------------------------------------------------------------------- #


