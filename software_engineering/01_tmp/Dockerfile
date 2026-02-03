FROM python:3.11-slim
WORKDIR /swe_hw_1

RUN pip install uv

COPY pyproject.toml uv.lock .python-version README.md ./
RUN uv sync --frozen

COPY . .

RUN uv run python ./scripts/generate_exports.py
RUN uv pip install .

CMD ["uv", "run", "python", "main.py"]