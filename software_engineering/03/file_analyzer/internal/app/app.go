package app

import (
	"errors"
	"fmt"
	"sync/atomic"

	"golang.org/x/sync/errgroup"
)

type App interface {
	Run() error
}

type app struct {
	dependencies dependencies
	adapteres    adapteres
	usecases     usecases
	ports        ports

	isStarted atomic.Bool
}

var _ App = (*app)(nil)

func New(
	dependencies dependencies,
	adapteres adapteres,
	usecases usecases,
	ports ports,
) *app {
	return &app{
		dependencies: dependencies,
		adapteres:    adapteres,
		usecases:     usecases,
		ports:        ports,
	}
}

func (app *app) Run() error {
	if app.isStarted.Load() {
		return errors.New("app is already started")
	}
	app.isStarted.Store(true)

	var eg errgroup.Group
	eg.Go(app.ports.http.Run)

	app.dependencies.logger.Info("app started")

	if err := eg.Wait(); err != nil {
		return fmt.Errorf("finishing app: %w", err)
	}

	return nil
}
