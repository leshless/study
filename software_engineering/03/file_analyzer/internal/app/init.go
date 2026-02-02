package app

import (
	"fmt"
	"swe3/file_analyzer/internal/db"
	filestorer "swe3/file_analyzer/internal/file_storer"
	"swe3/file_analyzer/internal/http"
	"swe3/file_analyzer/internal/logic"
	"swe3/file_analyzer/internal/telemetry"

	httpapi "swe3/file_analyzer/api/http"

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
	container.Provide(filestorer.InitAdapter, dig.As(new(filestorer.Adapter)))

	container.Provide(newAdapteres)
}

func provideUsecases(container *dig.Container) {
	container.Provide(logic.NewCreateReportUsecase, dig.As(new(logic.CreateReportUsecase)))
	container.Provide(logic.NewListReportsUsecase, dig.As(new(logic.ListReportsUsecase)))

	container.Provide(newUsecases)
}

func providePorts(container *dig.Container) {
	container.Provide(http.NewHandler, dig.As(new(httpapi.StrictServerInterface)))
	container.Provide(http.InitPort, dig.As(new(http.Port)))

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
