package grpc

import (
	api "swe3/file_storer/api/grpc"
	"swe3/file_storer/internal/telemetry"

	"github.com/leshless/golibrary/graceful"
	"google.golang.org/grpc"
)

const (
	listenPort = 50051
)

func InitPort(
	logger telemetry.Logger,
	submissionsHandler api.SubmissionsServer,
	gracefulRegistrator graceful.Registrator,
) *port {
	grpcServer := grpc.NewServer()
	api.RegisterSubmissionsServer(grpcServer, submissionsHandler)

	gracefulRegistrator.Register(func() error {
		grpcServer.Stop()
		return nil
	})

	return NewPort(grpcServer, logger)
}
