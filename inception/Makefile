USER_LOGIN  := vsarana
DATA_PATH   := $(HOME)/data
COMPOSE     := docker-compose -f src/docker-compose.yml

GREEN       := \033[0;32m
RED         := \033[0;31m
YELLOW      := \033[1;33m
NC          := \033[0m

all:
	@echo "$(YELLOW)Usage: make [up | build | rebuild | stop | down | logs | status | clean | fclean | re]$(NC)"
	@echo " $(GREEN)up$(NC):       Launch the services"
	@echo " $(GREEN)build$(NC):    Build the services"
	@echo " $(GREEN)rebuild$(NC):  Rebuild the services"
	@echo " $(GREEN)stop$(NC):     Stop the services"
	@echo " $(GREEN)down$(NC):     Stop and remove the services"
	@echo " $(GREEN)logs$(NC):     Show the logs of the services"
	@echo " $(GREEN)status$(NC):   Show the status of the services"
	@echo " $(GREEN)clean$(NC):    Remove the services"
	@echo " $(GREEN)fclean$(NC):   Remove the services and the data"
	@echo " $(GREEN)re$(NC):       Rebuild and launch the services"

up:
	@mkdir -p $(DATA_PATH)/wordpress $(DATA_PATH)/mariadb
	@$(COMPOSE) up -d

build:
	@$(COMPOSE) build

rebuild:
	@$(COMPOSE) build --no-cache
	@$(COMPOSE) up -d

stop:
	@$(COMPOSE) stop

down:
	@$(COMPOSE) down

logs:
	@$(COMPOSE) logs

status:
	@$(COMPOSE) ps

clean:
	@$(COMPOSE) down --rmi all --volumes
	@echo "$(RED)Containers, volumes, and images removed.$(NC)"

fclean: clean
	@rm -rf $(DATA_PATH)
	@echo "$(RED)Data folder $(DATA_PATH) deleted.$(NC)"

re: fclean rebuild up

.PHONY: all up build rebuild stop down logs status clean fclean re