FROM golang:1.25.1-alpine AS builder
WORKDIR /build

COPY go.mod go.sum ./
RUN go mod download

COPY ./ ./
RUN go generate ./...
RUN CGO_ENABLED=0 GOOS=linux go build -o /file_analyzer ./file_analyzer/cmd/file_analyzer
RUN chmod +x /file_analyzer

FROM alpine:3.21
COPY --from=builder /file_analyzer ./file_analyzer
ENTRYPOINT ["./file_analyzer"]