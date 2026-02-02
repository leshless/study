package app

import (
	"fmt"
	"swe3/file_storer/internal/db"
	"swe3/file_storer/internal/grpc"
	"swe3/file_storer/internal/http"
	"swe3/file_storer/internal/logic"
	"swe3/file_storer/internal/storage"
	"swe3/file_storer/internal/telemetry"

	grpcapi "swe3/file_storer/api/grpc"
	httpapi "swe3/file_storer/api/http"

	"github.com/leshless/golibrary/graceful"
	"github.com/leshless/golibrary/interrupter"

	"go.uber.org/dig"
)

func Init() (App, error) {
	container := dig.New()

	provideDependencies(container)
	provideAdapters(container)
	provideUsecases(container)
	providePorts(container)

	app, err := resolveApp(container)
	if err != nil {
		return nil, fmt.Errorf("resolving app from DI container: %w", err)
	}

	go func() {
		<-app.dependencies.interrupter.Ch()

		app.dependencies.logger.Info("app shutdown initiated")

		app.dependencies.gracefulTerminator.Terminate()
	}()

	return app, nil
}

func provideDependencies(container *dig.Container) {
	container.Provide(interrupter.NewInterrupter, dig.As(new(interrupter.Interrupter)))
	container.Provide(graceful.NewManager, dig.As(new(graceful.Registrator)), dig.As(new(graceful.Terminator)))
	container.Provide(telemetry.InitLogger, dig.As(new(telemetry.Logger)))

	container.Provide(newDependencies)
}

func provideAdapters(container *dig.Container) {
	container.Provide(db.InitAdapter, dig.As(new(db.Adapter)))
	container.Provide(storage.InitAdapter, dig.As(new(storage.Adapter)))

	container.Provide(newAdapteres)
}

func provideUsecases(container *dig.Container) {
	container.Provide(logic.NewCreateSubmissionUsecase, dig.As(new(logic.CreateSubmissionUsecase)))
	container.Provide(logic.NewListWorkSubmissionsUsecase, dig.As(new(logic.ListWorkSubmissionsUsecase)))

	container.Provide(newUsecases)
}

func providePorts(container *dig.Container) {
	container.Provide(http.NewHandler, dig.As(new(httpapi.StrictServerInterface)))
	container.Provide(http.InitPort, dig.As(new(http.Port)))

	container.Provide(grpc.NewSubmissionsHandler, dig.As(new(grpcapi.SubmissionsServer)))
	container.Provide(grpc.InitPort, dig.As(new(grpc.Port)))

	container.Provide(newPorts)
}

func resolveApp(container *dig.Container) (*app, error) {
	var app *app
	err := container.Invoke(func(
		dependencies dependencies,
		adapteres adapteres,
		usecases usecases,
		ports ports,
	) {
		app = New(
			dependencies,
			adapteres,
			usecases,
			ports,
		)
	})

	return app, err
}
