.PHONY: default generate logs clean drop build run

run: logs
	docker compose up

build: 
	docker compose build file_storer
	docker compose build file_analyzer

clean:
	git clean -Xf

drop:
	docker compose down -v

generate: 
	go generate ./...

logs: logs/file_analyzer_postgres.log logs/file_storer_postgres.log

logs/file_analyzer_postgres.log:
	touch logs/file_analyzer_postgres.log
	chmod 0666 logs/file_analyzer_postgres.log

logs/file_storer_postgres.log:
	touch logs/file_storer_postgres.log
	chmod 0666 logs/file_storer_postgres.log
