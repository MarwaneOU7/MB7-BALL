# ╔══════════════════════════════════════════════════════════════╗
# ║  Makefile pour la compilation du projet Bouncing Balls       ║
# ║  Projet: Simulation Physique de Balles Rebondissantes        ║
# ║  Auteur: Étudiant Ingénieria - Année 1                        ║
# ╚══════════════════════════════════════════════════════════════╝

# Compilateur et drapeaux
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -fPIC
DEBUGFLAGS = -g -O0 -DDEBUG
LDFLAGS = -lraylib -lm

# Détection du système d'exploitation
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    LDFLAGS += -ldl -lpthread -lX11
    EXECUTABLE = bouncing_balls
endif

ifeq ($(UNAME_S),Darwin)
    # macOS
    LDFLAGS += -framework CoreVideo -framework IOKit -framework Cocoa -framework OpenGL
    EXECUTABLE = bouncing_balls
endif

ifeq ($(OS),Windows_NT)
    LDFLAGS += -lwinmm
    EXECUTABLE = bouncing_balls.exe
endif

# Répertoires
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Fichiers source et objets
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/ball.c $(SRC_DIR)/physics.c $(SRC_DIR)/game.c
OBJECTS = $(OBJ_DIR)/main.o $(OBJ_DIR)/ball.o $(OBJ_DIR)/physics.o $(OBJ_DIR)/game.o
TARGET = $(BIN_DIR)/$(EXECUTABLE)

# Cibles par défaut
.PHONY: all build clean run debug install-raylib help

# Afficher les cibles disponibles
help:
	@echo "═════════════════════════════════════════════════════"
	@echo " Cibles Makefile disponibles:"
	@echo "═════════════════════════════════════════════════════"
	@echo ""
	@echo "  make all            - Compiler le projet (défaut)"
	@echo "  make build          - Alias pour 'all'"
	@echo "  make run            - Compiler et exécuter"
	@echo "  make debug          - Compiler en mode debug"
	@echo "  make clean          - Supprimer les fichiers compilés"
	@echo "  make install-raylib - Installer Raylib (Linux/macOS)"
	@echo "  make help           - Afficher cette aide"
	@echo ""
	@echo "═════════════════════════════════════════════════════"

# Cible par défaut
all: $(TARGET)
	@echo "✓ Compilation réussie!"
	@echo "✓ Exécutable: $(TARGET)"

build: all

# Créer les répertoires s'ils n'existent pas
$(BUILD_DIR) $(OBJ_DIR) $(BIN_DIR):
	@mkdir -p $@

# Compiler les fichiers objets
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/ball.o: $(SRC_DIR)/ball.c $(SRC_DIR)/ball.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/physics.o: $(SRC_DIR)/physics.c $(SRC_DIR)/physics.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/game.o: $(SRC_DIR)/game.c $(SRC_DIR)/game.h $(SRC_DIR)/ball.h $(SRC_DIR)/physics.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Lier les fichiers objets
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

# Exécuter le programme
run: all
	$(TARGET)

# Compiler en mode debug
debug: CFLAGS += $(DEBUGFLAGS)
debug: clean all
	@echo "✓ Compilation en mode debug réussie!"

# Nettoyer les fichiers compilés
clean:
	@rm -rf $(BUILD_DIR)
	@echo "✓ Fichiers compilés supprimés"

# Installer Raylib sur Linux/macOS
install-raylib:
	@echo "Installation de Raylib..."
	@if command -v apt-get > /dev/null; then \
		sudo apt-get install -y libraylib-dev; \
	elif command -v brew > /dev/null; then \
		brew install raylib; \
	else \
		echo "Gestionnaire de paquets non reconnu"; \
		echo "Consultez: https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux"; \
	fi
	@echo "✓ Raylib installé!"

# Cible factice pour éviter les conflits de noms de fichiers
.PHONY: all build clean run debug install-raylib help
