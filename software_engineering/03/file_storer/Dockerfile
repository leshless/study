FROM golang:1.25.1-alpine AS builder
WORKDIR /build

COPY go.mod go.sum ./
RUN go mod download

COPY ./ ./
RUN go generate ./...
RUN CGO_ENABLED=0 GOOS=linux go build -o /file_storer ./file_storer/cmd/file_storer
RUN chmod +x /file_storer

FROM alpine:3.21
COPY --from=builder /file_storer ./file_storer
ENTRYPOINT ["./file_storer"]