package http

import (
	"errors"
	"net/http"
	"swe3/file_storer/internal/telemetry"
)

//go:generate go run github.com/leshless/golibrary/constructor_generator

type Port interface {
	Run() error
}

// @PublicPointerInstance
type port struct {
	httpServer *http.Server
	logger     telemetry.Logger
}

var _ Port = (*port)(nil)

func (p *port) Run() error {
	p.logger.Info("started http server")

	err := p.httpServer.ListenAndServe()
	if !errors.Is(err, http.ErrServerClosed) {
		return err
	}

	return nil
}
