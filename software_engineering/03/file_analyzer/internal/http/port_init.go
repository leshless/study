package http

import (
	"context"
	"fmt"
	http "net/http"
	api "swe3/file_analyzer/api/http"
	"swe3/file_analyzer/internal/telemetry"
	"time"

	"github.com/go-chi/chi/v5"
	"github.com/leshless/golibrary/graceful"
)

const (
	listenPort          = 8080
	readTimeoutSeconds  = 15
	writeTimeoutSeconds = 15
	idleTimeoutSeconds  = 60
)

func InitPort(
	logger telemetry.Logger,
	handler api.StrictServerInterface,
	gracefulRegistrator graceful.Registrator,
) *port {
	router := chi.NewRouter()
	api.HandlerFromMux(api.NewStrictHandler(handler, nil), router)

	httpServer := &http.Server{
		Addr:         fmt.Sprintf(":%d", listenPort),
		Handler:      router,
		ReadTimeout:  readTimeoutSeconds * time.Second,
		WriteTimeout: writeTimeoutSeconds * time.Second,
		IdleTimeout:  idleTimeoutSeconds * time.Second,
	}

	gracefulRegistrator.Register(func() error {
		return httpServer.Shutdown(context.Background())
	})

	return NewPort(httpServer, logger)
}
