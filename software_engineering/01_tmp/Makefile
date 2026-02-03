.PHONY: run build test generate clean

default: run

run: build
	docker run -it swe_hw_1:latest

build:
	docker build -t swe_hw_1 .

test: generate
	uv run pytest --cov

generate:
	uv run python scripts/generate_exports.py

clean:
	find . -name "__init__.py" -delete
	find . -name ".pytest_cache" -type d -exec rm -rf {} +